#include "employee.hpp"
#include "hrinfo.hpp"

Employee::Employee(const std::string& name)
    : name_{name}
{
}

Salary::Salary(const std::string& name)
    : Employee{name}
{
}

void Salary::description() const
{
    std::cout << "Salaried Employee: " << name() << std::endl;
}

HRInfoPtr_t Salary::createHrInfo() const
{
    return std::make_unique<StdInfo>(this);
}

Hourly::Hourly(const std::string& name)
    : Employee{name}
{
}

void Hourly::description() const
{
    std::cout << "Hourly Employee: " << name() << std::endl;
}

HRInfoPtr_t Hourly::createHrInfo() const
{
    return std::make_unique<StdInfo>(this);
}

Temp::Temp(const std::string& name)
    : Employee(name)
{
}

void Temp::description() const
{
    std::cout << "Temporary Employee: " << name() << std::endl;
}

HRInfoPtr_t Temp::createHrInfo() const
{
    return std::make_unique<TempInfo>(this);
}