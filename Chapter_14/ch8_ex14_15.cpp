//
// Created by Dmytrenko Kyrylo on 31.03.2026.
//
#include "drill_ex.h"

namespace ch8::ex14_15 {
    std::ifstream open_input_stream(const std::string& file_name){
        std::ifstream ifs {file_name};
        if (!ifs)
            error("can't open file");

        return ifs;
    }

    long int round(double d) {
        auto round_d =d*10000;
        if (std::abs(fmod(round_d,10000)) >= 4999) {
            return static_cast<long int>(d+1);
        }

        return static_cast<long int>(d);
    }

    Converter::Converter(const string &file_name) {
        auto file = open_input_stream(file_name);
        double factor;

        for (string currency; file >> currency >> factor;)
            this->conversion_factors.emplace_back(currency,factor);

    }

    void Converter::set_amount(double amount, const string &currency) {
        this->temp_money.amount  = amount;
        temp_money.currency = currency;
    }

    void Converter::set_currency(const string &currency) {
        this->temp_money.currency = currency;
    }

    void Converter::convert_to(const string &currency) {
        if (this->temp_money.currency == currency)
            return;

        double old_factor = find_currency_and_get_factor_conversion(temp_money.currency);
        double new_factor = find_currency_and_get_factor_conversion(currency);

        temp_money.amount = (temp_money.amount/old_factor)*new_factor;
        temp_money.currency = currency;
    }

    double Converter::get_current_amount() const {
        return temp_money.amount;
    }

    const string& Converter::get_currency() const {
        return temp_money.currency;
    }

    const std::vector<pair<string, double>> & Converter::get_conversion_factors() const {
        return this->conversion_factors;
    }

    double Converter::find_currency_and_get_factor_conversion(const string & currency_name) const {
        double result = 0;
        for (const auto& el : this->conversion_factors)
                if (el.first == currency_name) {
                    result = el.second;
                    break;
                }

        return result;
    }

    std::ostream& operator<<(std::ostream& os, const Converter& converter) {
        return os << converter.get_current_amount() << converter.get_current_amount();

    }





    /*int find_iterator_currency_prompt_by_str(std::string& str) {
             for (size_t i = 0; i < _currency_prompt.size(); ++i) {
                 if (_currency_prompt[i] == str)
                     return static_cast<int>(i);
             }

             error("Bad currency");
             return -1;
    }*/
}

