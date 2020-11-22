//
// Created by Ross Wardrup on 9/10/20.
//

#include "calculate.h"
#include <cmath>
#include <iostream>

double Calculate::standard_drinks(double abv, double amount) {
    /*
     * Calculate the number of standard drinks in a beer.
     * @param abv: the alcohol by volume of the beer.
     * @param amount: the amount of beer in the container.
     */

    double alcohol_amt = oz_alcohol(abv, amount);
    return round_to_two_decimal_points(alcohol_amt / .6);
}

double Calculate::oz_alcohol(double abv, double amount) {
    /*
     * Calculate the ounces of alcohol in a beer.
     * @param abv: The alcohol by volume of the beer.
     * @param amount: The amount of beer in the container.
     */

    return (abv/100)*amount;
}

double Calculate::standard_drinks_remaining(const std::string& sex, const std::string& standard, int drink_limit, double standard_drinks_consumed) {
    /*
     * Calculate the number of standard drinks remaining for the user this week.
     *
     * Male low risk: 4 drinks daily, 14 per week.
     * Male high risk: Over 5 drinks within 2 hours or over 14 drinks per week.
     *
     * Female low risk: 3 drinks daily, 7 per week.
     * Female high risk: over 4 drinks within 2 hours or over 7 drinks per week.
     *
     * @param sex: The sex of the user.
     * @param standard_drinks_consumed: The number of standard drinks consumed so far this week.
     */

    double weekly_drinks_remaining;

    if (standard == "NIAAA") {
        if (sex == "male") {
            drink_limit = 14;
        } else if (sex == "female") {
            drink_limit = 7;
        } else {
            std::cout << "Sex is incorrectly set: " << sex << std::endl;
        }
    }

    (sex == "male") ? weekly_drinks_remaining = drink_limit - standard_drinks_consumed : weekly_drinks_remaining = drink_limit - standard_drinks_consumed;

    return weekly_drinks_remaining;
}

double Calculate::round_to_two_decimal_points(double val) {
    /*
     * Round a double to two decimal points.
     * @param val: The value that should be rounded.
     */

    return floor((val * 100) + .5)/100;
}

double Calculate::oz_alcohol_remaining(const std::string& sex, const std::string& standard, int drink_limit, double oz_consumed) {
    /*
     * Calculate the amount of alcohol the user has remaining based on their sex.
     * @return: The amount of oz remaining for user.
     */

    // TODO: Allow using different standards and custom amounts

    double oz_alcohol_remaining {0};

    if (standard == "Custom") {
        oz_alcohol_remaining = (0.6 * drink_limit) - oz_consumed;
    } else {
        if (sex == "male") {
            oz_alcohol_remaining = (0.6 * 14) - oz_consumed;
        } else if (sex == "female") {
            oz_alcohol_remaining = (0.6 * 7) - oz_consumed;
        }
    }

    return round_to_two_decimal_points(oz_alcohol_remaining);
}

std::string Calculate::favorite_producer(Storage storage) {
    /*
     * Get the number of time each brewery appears in the database.
     * @param storage: A Storage instance.
     * @return favorite_producer: The brewery that appears most often.
     */

    std::map<std::string, unsigned> producer_counts;
    std::vector<std::string> producers;
    std::string favorite_producer;

    std::vector<Drink> all_drinks = storage.get_all<Drink>();

    producers.reserve(all_drinks.size());
    for (const auto& drink: all_drinks) {
        producers.push_back(drink.producer);
    }
    for (const auto& producer : producers) {
        int producer_count = std::count(producers.begin(), producers.end(), producer);
        producer_counts[producer] = producer_count;
    }

    unsigned current_max = 0;
    for (const auto & brewery_count : producer_counts) {
        if (brewery_count.second > current_max) {
            favorite_producer = brewery_count.first;
            current_max = brewery_count.second;
        }
    }

    return favorite_producer;
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

    std::vector<Drink> all_beers = storage.get_all<Drink>();

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

double Calculate::mean_abv(Storage storage) {
    /*
     * Calculate the mean ABV for all drinks.
     * @param storage: A storage instance.
     * @return: The average ABV at two decimal points.
     */

    double abv_sum = 0.0;
    unsigned beer_count = 0;
    std::vector<Drink> all_beers = storage.get_all<Drink>();

    for (const auto& beer : all_beers) {
        beer_count += 1;
        abv_sum += beer.abv;
    }

    return round_to_two_decimal_points(abv_sum / beer_count);
}

double Calculate::mean_ibu(Storage storage) {
    /*
     * Calculate the mean IBU of all beers in the database.
     * @param storage: A storage instance.
     * @return: The average IBU per beer.
     */

    double ibu_sum = 0.0;
    unsigned beer_count = 0;
    std::vector<Drink> all_beers = storage.get_all<Drink>();

    for (const auto& beer : all_beers) {
        // Ignore empty IBU values
        if (beer.ibu > 0) {
            beer_count += 1;
        }
        ibu_sum += beer.ibu;
    }

    return ibu_sum / beer_count;
}

std::string Calculate::favorite_type(Storage storage) {
    /*
     * Calculates favorite beer type based on most common type in database
     * @param Storage: a Storage instance
     * @return favorite_type: The most common type in the database.
     */

    std::map<std::string, unsigned> type_counts;
    std::vector<std::string> types;
    std::string favorite_type;

    std::vector<Drink> all_beers = storage.get_all<Drink>();

    types.reserve(all_beers.size());
    for (const auto& beer: all_beers) {
        types.push_back(beer.type);
    }
    for (const auto& type : types) {
        int brewery_count = std::count(types.begin(), types.end(), type);
        type_counts[type] = brewery_count;
    }

    unsigned current_max = 0;

    for (const auto & type_count : type_counts) {
        if (type_count.second > current_max) {
            favorite_type = type_count.first;
            current_max = type_count.second;
        }
    }

    return favorite_type;
}

bool Calculate::compare_date(const Drink &a, const Drink &b) {
    /*
     * Determine if second date is greater than the first date.
     * @return: True if second date is more recent than the first date. Else, false.
     */

    if (a.drink_year < b.drink_year) {
        return true;
    } else if (a.drink_year == b.drink_year && a.drink_month < b.drink_month) {
        return true;
    } else if (a.drink_year == b.drink_year && a.drink_month == b.drink_month && a.drink_day < b.drink_day) {
        return true;
    } else {
        return false;
    }
}

std::string Calculate::double_to_string(double input_double) {
    /*
     * Convert a double to a string with two decimal points.
     * @param input_double: Input double to be converted
     * @return output_string: string-formatted double with two decimal points.
     */

    double converted_double;
    converted_double = std::floor((input_double * 100.0) + .5) / 100.0;

    std::ostringstream output_string;
    output_string << converted_double;

    return output_string.str();
}