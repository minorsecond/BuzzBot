//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_CALCULATE_H
#define BEERTABS_CALCULATE_H

#include <string>
#include "database.h"

class Calculate {
public:
    static double oz_alcohol(double abv, int amount);
    static double standard_drinks(double abv, int amount);
    static double standard_drinks_remaining(const std::string& sex, double standard_drinks_consumed);
    static double oz_alcohol_remaining(const std::string& sex, double oz_consumed);
    static double round_to_two_decimal_points(double val);
    static std::string favorite_producer(Storage storage);
    static std::string favorite_beer(Storage storage);
    static std::string favorite_type(Storage storage);
    static double mean_abv(Storage storage);
    static double mean_ibu(Storage storage);
    static bool compare_date(const Drink &a, const Drink &b);
};


#endif //BEERTABS_CALCULATE_H
