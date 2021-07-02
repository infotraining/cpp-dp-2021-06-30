#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <functional>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

enum StatisticsType
{
    avg,
    min_max,
    sum
};

class Calculator
{
    public:
        virtual ~Calculator() = default;
        virtual void calculate(const Data& data_, Results& results_) = 0;
};

class AvgCalculator : public Calculator
{
    public:
        void calculate(const Data& data_, Results& results_) override
        {
            double sum = std::accumulate(data_.begin(), data_.end(), 0.0);
            double avg = data_.size() ? sum / data_.size() : 0;

            StatResult result("Avg", avg);
            results_.push_back(result);
        }
};

class MinMaxCalculator : public Calculator
{
    public:
        void calculate(const Data& data_, Results& results_) override
        {
            double min = *(std::min_element(data_.begin(), data_.end()));
            double max = *(std::max_element(data_.begin(), data_.end()));

            results_.push_back(StatResult("Min", min));
            results_.push_back(StatResult("Max", max));
        }
};

class SumCalculator : public Calculator
{
    public:
        void calculate(const Data& data_, Results& results_) override
        {
            double sum = std::accumulate(data_.begin(), data_.end(), 0.0);

            results_.push_back(StatResult("Sum", sum));
        }
};

// Composite

class AgregateCalculator : public Calculator
{
    std::vector<std::shared_ptr<Calculator>> calculators_;

public:
    void calculate(const Data& data_, Results& results_) override
    {
        for (auto const& calc : calculators_)
        {
            calc->calculate(data_, results_);
        }
    }
    void add_calculator(std::shared_ptr<Calculator> calc)
    {
        calculators_.push_back(calc);
    }
};

class DataAnalyzer
{
    //StatisticsType stat_type_;
    std::shared_ptr<Calculator> calculator_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(std::shared_ptr<Calculator> calculator)
        : calculator_{calculator}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(std::shared_ptr<Calculator> calculator)
    {
        calculator_ = calculator;
    }

    void calculate()
    {
        calculator_->calculate(data_, results_);
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

namespace ModernCpp
{
    using Statistics = std::function<Results (const Data& data)>;

    class Avg
    {
    public:
        Results operator()(const Data &data)
        {
            double sum = std::accumulate(data.begin(), data.end(), 0.0);
            double avg = data.size() ? sum / data.size() : 0;

            return { {"AVG", avg} };
        }
    };

    class DataAnalyzer
    {
        Statistics statistics_;
        Data data_;
    public:

        void set_statistics(Statistics new_stat)
        {
            statistics_ = new_stat;
        }

        void calculate()
        {
            auto results = statistics_(data_); // delegation to strategy
        }
    };
}

int main()
{
    auto std_stats = std::make_shared<AgregateCalculator>();
    std_stats->add_calculator(std::make_shared<AvgCalculator>());
    std_stats->add_calculator(std::make_shared<MinMaxCalculator>());
    std_stats->add_calculator(std::make_shared<SumCalculator>());

    DataAnalyzer da{std_stats};
    da.load_data("data.dat");
    da.calculate();
    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_data.dat");
    da.calculate();
    show_results(da.results());
}
