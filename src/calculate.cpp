//
// Created by Ross Wardrup on 9/10/20.
//

#include "calculate.h"
#include <cmath>
#include <iostream>
#include <algorithm>

double Calculate::standard_drinks(double abv, double amount, double std_drink_size) {
    /*
     * Calculate the number of standard drinks in a beer.
     * 1 Std. drink in the US is .6 oz pure alcohol. In Europe,
     * it's 17.5 ml pure alcohol. These two measurements are
     * roughly the same.
     * @param abv: the alcohol by volume of the beer.
     * @param amount: the amount of beer in the container.
     */

    double alcohol_amt = alcohol_volume(abv, amount);
    return round_to_two_decimal_points(alcohol_amt / std_drink_size);
}

double Calculate::alcohol_volume(double abv, double amount) {
    /*
     * Calculate the volume of alcohol in a beer.
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

    weekly_drinks_remaining = drink_limit - standard_drinks_consumed;

    return weekly_drinks_remaining;
}

double Calculate::round_to_two_decimal_points(double val) {
    /*
     * Round a double to two decimal points.
     * @param val: The value that should be rounded.
     */

    return floor((val * 100) + .5)/100;
}

double Calculate::volume_alcohol_remaining(const std::string& sex, const std::string& standard, int drink_limit, double volume_consumed, double std_drink_size) {
    /*
     * Calculate the amount of alcohol the user has remaining based on their sex.
     * @return: The amount of volume remaining for user.
     */

    // TODO: Allow using different standards and custom amounts

    double vol_alcohol_remaining {0};

    if (standard == "Custom") {
        vol_alcohol_remaining = (std_drink_size * drink_limit) - volume_consumed;
    } else {
        if (sex == "male") {
            vol_alcohol_remaining = (std_drink_size * 14) - volume_consumed;
        } else if (sex == "female") {
            vol_alcohol_remaining = (std_drink_size * 7) - volume_consumed;
        }
    }

    return round_to_two_decimal_points(vol_alcohol_remaining);
}

std::string Calculate::favorite_producer(const Storage& storage, const std::string& drink_type) {
    /*
     * Get the number of time each brewery appears in the database.
     * @param storage: A Storage instance.
     * @return favorite_producer: The brewery that appears most often.
     */

    std::map<std::string, unsigned> producer_counts;
    std::vector<std::string> producers;
    std::string favorite_producer;

    //std::vector<Drink> all_drinks = storage.get_all<Drink>();
    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

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

std::string Calculate::favorite_drink(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculates favorite beer based on most common beer in database
     * @param Storage: a Storage instance
     * @return favorite_drink: The most common beer in the database.
     */

    std::map<std::string, unsigned> beer_counts;
    std::vector<std::string> beers;
    std::string favorite_beer;

    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    beers.reserve(all_drinks.size());
    for (const auto& beer: all_drinks) {
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

double Calculate::mean_abv(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculate the mean ABV for all drinks.
     * @param storage: A storage instance.
     * @return: The average ABV at two decimal points.
     */

    double abv_sum = 0.0;
    unsigned beer_count = 0;
    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    for (const auto& beer : all_drinks) {
        beer_count += 1;
        abv_sum += beer.abv;
    }

    return round_to_two_decimal_points(abv_sum / beer_count);
}

double Calculate::mean_ibu(Storage storage, const std::string& drink_type) {
    /*
     * Calculate the mean IBU of all beers in the database.
     * @param storage: A storage instance.
     * @return: The average IBU per beer.
     */

    double ibu_sum = 0.0;
    unsigned beer_count = 0;
    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    for (const auto& beer : all_drinks) {
        // Ignore empty IBU values
        if (beer.ibu > 0) {
            beer_count += 1;
        }
        ibu_sum += beer.ibu;
    }

    return ibu_sum / beer_count;
}

std::string Calculate::favorite_type(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculates favorite beer type based on most common type in database
     * @param Storage: a Storage instance
     * @return favorite_type: The most common type in the database.
     */

    std::map<std::string, unsigned> type_counts;
    std::vector<std::string> types;
    std::string favorite_type;

    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    types.reserve(all_drinks.size());
    for (const auto& beer: all_drinks) {
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

double Calculate::oz_to_ml(double input_oz) {
    /*
     * Convert oz to ml for metric support. 1 oz = 29.5735 ml.
     * @param input_oz: A double denoting drink volume in ounces.
     * @return: A double denoting drink volume in milliliters.
     */

    double ml = input_oz * 29.5735;
    return ml;
}

double Calculate::ml_to_oz(double input_ml) {
    /*
     * Convert ml to oz for metric support. 29.5735 ml = 1 lz.
     * @param input_ml: A double denoting drink volume in milliliters.
     * @return: A double denoting drink volume in ounces.
     */

    double oz = input_ml / 29.5735;
    return oz;
}

bool Calculate::compare_strings(std::string lhs, std::string rhs) {
    /*
     * Compare two strings alphabetically. Used to compare strings, ignoring case.
     */

    std::string lhs_tmp;
    std::string rhs_tmp;

    // Convert strings to uppercase
    for (char& c : lhs) {
        c = std::toupper(c, std::locale());
        lhs_tmp += c;
    }

    for (char& c : rhs) {
        c = std::toupper(c, std::locale());
        rhs_tmp += c;
    }

    return lhs < rhs;
}
