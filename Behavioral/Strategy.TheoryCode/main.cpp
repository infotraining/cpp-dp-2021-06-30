#include "strategy.hpp"
#include <set>

int main()
{
    DataContext data{std::make_shared<UpperCaseFormatter>()};
    data.pretty_print();

    auto lcf = std::make_shared<LowerCaseFormatter>();
    data.reset_formatter(lcf);
    data.pretty_print();

    data.reset_formatter(std::make_shared<CapitalizeFormatter>());
    data.pretty_print();

    std::set<int, std::greater<>> my_set = {5, 6, 2, 8, 1};
    for(const auto& item : my_set)
        std::cout << item << " ";
    std::cout << "\n";

    FormattedContext<CapitalizeFormatter> data2;
    data2.pretty_print();
}
