#include "stock.hpp"

using namespace std;

// Observer
class Investor 
{
    std::string name_;

public:
    Investor(const std::string& name) : name_(name)
    {
    }

    void update(/*...*/)
    {
        // TODO
    }
};

int main()
{
    Stock misys("Misys", 340.0);
    Stock ibm("IBM", 245.0);
    Stock tpsa("TPSA", 95.0);

    // Create some investors and register them as observers to stock price changes
    // TODO:

    misys.set_price(360.0);
    ibm.set_price(210.0);
    tpsa.set_price(45.0);

    misys.set_price(380.0);
    ibm.set_price(230.0);
    tpsa.set_price(15.0);
}
