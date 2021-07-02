#include <iostream>
#include <tuple>
#include <vector>
#include <boost/flyweight.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

struct first_name_pool {};

class Taxpayer
{
    int id_;
    boost::flyweight<std::string, boost::flyweights::tag<first_name_pool>> first_name_;
    boost::flyweight<std::string> last_name_;

public:
    Taxpayer(int id, const string& first_name, const string& last_name)
        : id_(id)
        , first_name_(first_name)
        , last_name_(last_name)
    {
    }

    int id() const
    {
        return id_;
    }

    string first_name() const
    {
        return first_name_;
    }

    void set_first_name(const string& first_name)
    {
        first_name_ = first_name;
    }

    void to_upper()
    {
        first_name_ = boost::to_upper_copy(first_name_.get());
        last_name_ = boost::to_upper_copy(last_name_.get());
    }

    string last_name() const
    {
        return last_name_;
    }

    void set_last_name(const string& last_name)
    {
        last_name_ = last_name;
    }

    bool operator==(const Taxpayer& p)
    {
        return std::tie(id_, first_name_, last_name_) == std::tie(p.id_, p.first_name_, p.last_name_);
    }
};

int main()
{
    vector<Taxpayer> payers{Taxpayer{1, "Jan", "Kowalski"}, Taxpayer{2, "Jan", "Nowak"}};

    payers.emplace_back(3, "Anna", "Kowalska");
    payers.emplace_back(1, "Anna", "Nowakowska");
    payers.insert(payers.end(), {Taxpayer{6, "Jan", "Nijaki"}, Taxpayer{10, "Anna", "Anonim"}});

    payers[0].to_upper();
    payers[1].to_upper();

    for (const auto& p : payers)
    {
        cout << p.first_name() << " " << p.last_name() << endl;
    }
}
