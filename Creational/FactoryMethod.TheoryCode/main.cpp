#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "factory.hpp"

using namespace std;

class Service
{
    LoggerCreator logger_creator_;
    bool is_started_ = false;

public:
    Service(const LoggerCreator& creator)
        : logger_creator_(creator)
    {
    }

    Service(const Service&) = delete;
    Service& operator=(const Service&) = delete;

    void run()
    {
        unique_ptr<Logger> logger = logger_creator_();
        if (!is_started_)
            start();
            logger->log("Service has been started...");
        process_requests();
        logger->log("Service has processed all requests...");
    }

protected:
    virtual void start() {}
    virtual void process_requests() {}
};

using LoggerFactory = std::unordered_map<std::string, LoggerCreator>;

void foo()
{
    std::cout << "foo()\n";
}

class Foo
{
public:
    void operator()()
    {
        std::cout << "Foo::operator()\n";
    }

    void bar()
    {
        std::cout << "Foo::bar()\n";
    }
};

int main()
{
    LoggerFactory logger_factory;  
    logger_factory.insert(make_pair("ConsoleLogger", std::make_unique<ConsoleLogger>));
    logger_factory.insert(make_pair("FileLogger", [] { return std::make_unique<FileLogger>("data.log"); }));
    logger_factory.insert(make_pair("DbLogger", [] { return std::make_unique<DbLogger>("DbWithLogs"); }));

    Service srv(logger_factory.at("DbLogger"));
    srv.run();

    ////////////////////////////////////////////
    void (*fun_ptr)() = &foo;
    void (Foo::*method_ptr)() = &Foo::bar;
    Foo foo_obj{};
    (foo_obj.*method_ptr)(); // foo.obj.bar();
    
    std::function<void()> f;
    f = foo; // stores function
    f();
    f = fun_ptr; // stores pointer to function
    f();
    f = Foo{}; // stores functor
    //fun_ptr = Foo{};
    f();
    int x = 42;
    f = [x]() { std::cout << "Lambda with captured " << x << "\n"; }; // stores closure
    f();

    std::function<void (Foo&)> fm = &Foo::bar; // stores pointer to member function
    fm(foo_obj);

    f = [&foo_obj]{ foo_obj.bar(); };
    f();
}


