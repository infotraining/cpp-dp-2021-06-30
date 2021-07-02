#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <iostream>
#include <string>
#include "observer.hpp"

// Subject
class Stock
{
private:
    std::string symbol_;
    double price_;
public:
    Stock(const std::string& symbol, double price) : symbol_(symbol), price_(price)
    {
    }

    std::string get_symbol() const
    {
        return symbol_;
    }

    double get_price() const
    {
        return price_;
    }

    void set_price(double price)
    {
        price_ = price;

        // TODO: sending notification to all observers
    }
};

#endif /*STOCK_HPP_*/
