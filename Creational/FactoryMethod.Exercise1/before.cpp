#include <memory>
#include <vector>

#include "employee.hpp"
#include "hrinfo.hpp"

int main()
{
    using namespace std;

    vector<std::unique_ptr<Employee>> emps;
    emps.push_back(make_unique<Salary>("Jan Kowalski"));
    emps.push_back(make_unique<Hourly>("Adam Nowak"));
    emps.push_back(make_unique<Temp>("Anna Nowakowska"));

    cout << "HR Report:\n---------------\n";

    // creating a HR report - TODO: refactor this code
    for (const auto& emp : emps)
    {
        std::unique_ptr<HRInfo> hri = emp->createHrInfo();
        hri->info();
        cout << endl;
    }
}
