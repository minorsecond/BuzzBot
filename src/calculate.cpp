//
// Created by Ross Wardrup on 9/10/20.
//

#include "calculate.h"
#include <math.h>

double Calculate::standard_drinks(double abv, int amount) {
    /*
     * Calculate the number of standard drinks in a beer.
     * @param abv: the alcohol by volume of the beer.
     * @param amount: the amount of beer in the container.
     */

    double alcohol_amt = oz_alcohol(abv, amount);
    return round_to_one_decimal_point(alcohol_amt/.6);
}

double Calculate::oz_alcohol(double abv, int amount) {
    /*
     * Calculate the ounces of alcohol in a beer.
     * @param abv: The alcohol by volume of the beer.
     * @param amount: The amount of beer in the container.
     */

    return (abv/100)*amount;
}

double Calculate::standard_drinks_remaining(const std::string& sex, double standard_drinks_consumed) {
    /*
     * Calculate the number of standard drinks remaining for the user this week.
     * @param sex: The sex of the user.
     * @param standard_drinks_consumed: The number of standard drinks consumed so far this week.
     */

    double weekly_drinks_remaining;

    if (sex == "male") {
        // Low risk: 4 drinks daily, 14 per week
        // Binge drinking: over 5 drinks within 2 hours
        weekly_drinks_remaining = 14-standard_drinks_consumed;
    } else {
        // Low risk: 3 drinks daily, 7 per week
        // Binge drinking: over 4 drinks within 2 hours
        weekly_drinks_remaining = 7-standard_drinks_consumed;
    }

    if (weekly_drinks_remaining < 0) {
        weekly_drinks_remaining = 0;
    }

    return weekly_drinks_remaining;
}

double Calculate::round_to_one_decimal_point(double val) {
    /*
     * Round a double to one decimal point.
     * @param val: The value that should be rounded.
     */

    double value = floor((val * 10) + .5);
    return value / 10;
}