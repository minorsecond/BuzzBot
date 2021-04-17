//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_CALCULATE_H
#define BEERTABS_CALCULATE_H

#include <string>
#include "database.h"

class Calculate {
public:
    static double alcohol_volume(double abv, double amount);
    static double standard_drinks(double abv, double amount, double std_drink_size);
    static double standard_drinks_remaining(const std::string& sex, const std::string& standard, int drink_limit, double standard_drinks_consumed);
    static double volume_alcohol_remaining(const std::string& sex, const std::string& standard, int drink_limit, double oz_consumed, double std_drink_size);
    static double round_to_two_decimal_points(double val);
    static std::string favorite_producer(const Storage& storage, const std::string& drink_type);
    static std::string favorite_drink(const Storage& storage, const std::string& drink_type);
    static std::string favorite_type(const Storage& storage, const std::string& drink_type);
    static double mean_abv(const Storage& storage, const std::string& drink_type);
    static double mean_ibu(Storage storage, const std::string& drink_type);
    static bool compare_date(const Drink &a, const Drink &b);
    static std::string double_to_string(double input_double);
    static double oz_to_ml(double input_oz);
    static double ml_to_oz(double input_ml);
    static bool compare_strings(std::string lhs, std::string rhs);
};


#endif //BEERTABS_CALCULATE_H
