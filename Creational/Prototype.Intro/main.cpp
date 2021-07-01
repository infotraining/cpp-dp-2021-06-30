#include <cassert>
#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;

class Engine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::unique_ptr<Engine> clone() const = 0;
    virtual ~Engine() = default;
};

class Diesel : public Engine
{
public:
    virtual void start() override
    {
        cout << "Diesel starts\n";
    }

    virtual void stop() override
    {
        cout << "Diesel stops\n";
    }

    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<Diesel>(*this); // call of copy constructor
    }
};

class TDI : public Diesel
{
public:
    virtual void start() override
    {
        cout << "TDI starts\n";
    }

    virtual void stop() override
    {
        cout << "TDI stops\n";
    }
        
    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<TDI>(*this); // call of copy constructor
    }
};

class Hybrid : public Engine
{
public:
    virtual void start() override
    {
        cout << "Hybrid starts\n";
    }

    virtual void stop() override
    {
        cout << "Hybrid stops\n";
    }

    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<Hybrid>(*this); // call of copy constructor
    }
};

class Car
{
    unique_ptr<Engine> engine_;

public:
    Car(unique_ptr<Engine> engine)
        : engine_{move(engine)}
    {
    }

    Car(const Car& source) : engine_{source.engine_->clone()}
    {}

    Car& operator=(const Car& source)
    {
        if (this != &source)
        {
            engine_ = source.engine_->clone();
        }

        return *this;
    }

    Car(Car&&) = default;
    Car& operator=(Car&&) = default;

    void drive(int km)
    {
        engine_->start();
        cout << "Driving " << km << " kms\n";
        engine_->stop();
    }
};

int main()
{
    Car c1{make_unique<Hybrid>()};
    c1.drive(100);

    cout << "\n";

    Car c2 = c1;
    c2.drive(200);
}
