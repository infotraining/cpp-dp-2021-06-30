#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#define WINDOWS

enum class IconType
{
    none,
    ok,
    cancel,
    warning,
    error
};

class Widget
{
public:
    virtual void draw() = 0;
    virtual ~Widget() = default;
};

class Button : public Widget
{
    std::string caption_;
    IconType icon_type_;

public:
    Button(const std::string& caption, IconType icon_type)
        : caption_{caption}
        , icon_type_{icon_type}
    {
    }

    std::string caption() const
    {
        return caption_;
    }

    IconType icon() const
    {
        return icon_type_;
    }
};

class Menu : public Widget
{
    std::string text_;

public:
    Menu(const std::string& text)
        : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }
};

class MotifButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "MotifButton [ " << caption() << " ]\n";
    }
};

class MotifMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "MotifMenu { " << text() << " }\n";
    }
};

class WindowsButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "WindowsButton [ " << caption() << " ]\n";
    }
};

class WindowsMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "WindowsMenu { " << text() << " }\n";
    }
};

class Window
{
    std::vector<std::unique_ptr<Widget>> widgets;

public:
    void display() const
    {
        std::cout << "######################\n";
        for (const auto& w : widgets)
            w->draw();
        std::cout << "######################\n\n";
    }

    void add_widget(std::unique_ptr<Widget> widget)
    {
        widgets.push_back(move(widget));
    }
};

class WidgetFactory
{
public:
    virtual ~WidgetFactory() = default;
    virtual std::unique_ptr<Button> gimme_button(const std::string& caption, IconType icon_type) = 0;
    virtual std::unique_ptr<Menu> gimme_menu(const std::string& text) = 0;
};

class MotifWidgetFactory : public WidgetFactory
{
    std::unique_ptr<Button> gimme_button(const std::string& caption, IconType icon_type) override { return std::make_unique<MotifButton>(caption, icon_type); };
    std::unique_ptr<Menu> gimme_menu(const std::string& text) override { return std::make_unique<MotifMenu>(text); };
};

class WindowsWidgetFactory : public WidgetFactory
{
    std::unique_ptr<Button> gimme_button(const std::string& caption, IconType icon_type) override { return std::make_unique<WindowsButton>(caption, icon_type); };
    std::unique_ptr<Menu> gimme_menu(const std::string& text) override { return std::make_unique<WindowsMenu>(text); };
};

class WindowOne : public Window
{

public:
    WindowOne(const std::shared_ptr<WidgetFactory>& widget_factory)
    {
        add_widget(widget_factory->gimme_button("OK", IconType::ok));
        add_widget(widget_factory->gimme_menu("File"));
    }
};

class WindowTwo : public Window
{

public:
    WindowTwo(const std::shared_ptr<WidgetFactory>& widget_factory)
    {
        add_widget(widget_factory->gimme_menu("Edit"));
        add_widget(widget_factory->gimme_button("OK", IconType::ok));
        add_widget(widget_factory->gimme_button("Cancel", IconType::cancel));
    }
};

int main(void)
{
#ifdef MOTIF
    std::shared_ptr<WidgetFactory> widget_factory = std::make_shared<MotifWidgetFactory>();
#else // WINDOWS
    std::shared_ptr<WidgetFactory> widget_factory = std::make_shared<WindowsWidgetFactory>();
#endif

    WindowOne w1(widget_factory);
    w1.display();

    WindowTwo w2(widget_factory);
    w2.display();
}


////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#define MOTIF

enum class IconType
{
    none,
    ok,
    cancel,
    warning,
    error
};

class Widget
{
public:
    virtual void draw() = 0;
    virtual ~Widget() = default;
};

class Button : public Widget
{
    std::string caption_;
    IconType icon_type_;

public:
    Button(const std::string& caption, IconType icon_type)
        : caption_{caption}
        , icon_type_{icon_type}
    {
    }

    std::string caption() const
    {
        return caption_;
    }

    IconType icon() const
    {
        return icon_type_;
    }
};

class Menu : public Widget
{
    std::string text_;

public:
    Menu(const std::string& text)
        : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }
};

class MotifButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "MotifButton [ " << caption() << " ]\n";
    }
};

class MotifMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "MotifMenu { " << text() << " }\n";
    }
};

class WindowsButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "WindowsButton [ " << caption() << " ]\n";
    }
};

class WindowsMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "WindowsMenu { " << text() << " }\n";
    }
};

using WidgetPtr_t = std::unique_ptr<Widget>;

class WidgetFactory
{
public:
    virtual ~WidgetFactory() = default;

    virtual WidgetPtr_t create_button(const std::string& caption, IconType icon_type) = 0;
    virtual WidgetPtr_t create_menu(const std::string& text) = 0;
};

template<typename TButton, typename TMenu>
class WidgetFactoryBase : public WidgetFactory
{
public:
    WidgetPtr_t create_button(const std::string& caption, IconType icon_type) override
    {
        return std::make_unique<TButton>(caption, icon_type);
    }

    WidgetPtr_t create_menu(const std::string& text) override
    {
        return std::make_unique<TMenu>(text);
    }
};

using MotifWidgetFactory = WidgetFactoryBase<MotifButton, MotifMenu>;
using WindowsWidgetFactory = WidgetFactoryBase<WindowsButton, WindowsMenu>;

using WidgetFactoryPtr_t = std::shared_ptr<WidgetFactory>;

class Window
{
    std::vector<WidgetPtr_t> widgets;

public:
    void display() const
    {
        std::cout << "######################\n";
        for (const auto& w : widgets)
            w->draw();
        std::cout << "######################\n\n";
    }

    void add_widget(WidgetPtr_t widget)
    {
        widgets.push_back(move(widget));
    }
};

class WindowOne : public Window
{

public:
    WindowOne(const WidgetFactoryPtr_t& widget_factory)
    {
        add_widget(widget_factory->create_button("OK", IconType::ok));
        add_widget(widget_factory->create_menu("File"));
    }
};

class WindowTwo : public Window
{

public:
    WindowTwo(const WidgetFactoryPtr_t& widget_factory)
    {
        add_widget(widget_factory->create_menu("Edit"));
        add_widget(widget_factory->create_button("OK", IconType::ok));
        add_widget(widget_factory->create_button("Cancel", IconType::cancel));
    }
};

WidgetFactoryPtr_t get_widget_factory()
{
#ifdef MOTIF
    return std::make_shared<MotifWidgetFactory>();
#else // WINDOWS
    return std::make_shared<WindowsWidgetFactory>();
#endif
}

int main(void)
{
    const auto widgetFactory = get_widget_factory();

    WindowOne w1(widgetFactory);
    w1.display();

    WindowTwo w2(widgetFactory);
    w2.display();
}
