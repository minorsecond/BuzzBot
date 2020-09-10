//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_CALCULATE_H
#define BEERTABS_CALCULATE_H

#include <string>


class Calculate {
public:
    static double oz_alcohol(double abv, int amount);
    static double standard_drinks(double abv, int amount);
    static double standard_drinks_remaining(const std::string& sex, double standard_drinks_consumed);
    static double round_to_one_decimal_point(double val);
};


#endif //BEERTABS_CALCULATE_H
