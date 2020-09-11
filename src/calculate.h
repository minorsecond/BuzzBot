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
    static double round_to_one_decimal_point(double val);
    static std::string favorite_brewery(Storage storage);
    static std::string favorite_beer(Storage storage);
    static double mean_abv(Storage storage);  // TODO write test
    static double mean_ibu(Storage storage);  // TODO write test
};


#endif //BEERTABS_CALCULATE_H
