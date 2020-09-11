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

double Calculate::oz_alcohol_remaining(const std::string& sex, double oz_consumed) {
    double oz_alcohol_remaining = 0;
    if (sex == "male") {
        oz_alcohol_remaining = (0.6 * 14) - oz_consumed;
    } else {
        oz_alcohol_remaining = (0.6 * 7) - oz_consumed;
    }
    return oz_alcohol_remaining;
}

std::string Calculate::favorite_brewery(Storage storage) {
    /*
     * Get the number of time each brewery appears in the database.
     * @param storage: A Storage instance.
     * @return favorite_brewery: The brewery that appears most often.
     */

    std::map<std::string, unsigned> brewery_counts;
    std::vector<std::string> breweries;
    std::string favorite_brewery;

    std::vector<Beer> all_beers = storage.get_all<Beer>();

    breweries.reserve(all_beers.size());
    for (const auto& beer: all_beers) {
        breweries.push_back(beer.brewery);
    }
    for (const auto& brewery : breweries) {
        int brewery_count = std::count(breweries.begin(), breweries.end(), brewery);
        brewery_counts[brewery] = brewery_count;
    }

    unsigned current_max = 0;

    for (const auto & brewery_count : brewery_counts) {
        if (brewery_count.second > current_max) {
            favorite_brewery = brewery_count.first;
            current_max = brewery_count.second;
        }
    }

    return favorite_brewery;
}

std::string Calculate::favorite_beer(Storage storage) {
    /*
     * Calculates favorite beer based on most common beer in database
     * @param Storage: a Storage instance
     * @return favorite_beer: The most common beer in the database.
     */

    std::map<std::string, unsigned> beer_counts;
    std::vector<std::string> beers;
    std::string favorite_beer;

    std::vector<Beer> all_beers = storage.get_all<Beer>();

    beers.reserve(all_beers.size());
    for (const auto& beer: all_beers) {
        beers.push_back(beer.name);
    }
    for (const auto& brewery : beers) {
        int brewery_count = std::count(beers.begin(), beers.end(), brewery);
        beer_counts[brewery] = brewery_count;
    }

    unsigned current_max = 0;

    for (const auto & beer_count : beer_counts) {
        if (beer_count.second > current_max) {
            favorite_beer = beer_count.first;
            current_max = beer_count.second;
        }
    }

    return favorite_beer;
}
