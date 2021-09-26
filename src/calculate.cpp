//
// Created by Ross Wardrup on 9/10/20.
//

#include "calculate.h"
#include <cmath>
#include <iostream>
#include <algorithm>

double Calculate::standard_drinks(const double &abv, const double &amount, const double &std_drink_size) {
    /*
     * Calculate the number of standard drinks in a drink.
     * 1 Std. drink in the US is .6 oz pure alcohol. In Europe,
     * it's 17.5 ml pure alcohol. These two measurements are
     * roughly the same.
     * @param abv: the alcohol by volume of the drink.
     * @param amount: the amount of drink in the container.
     * @param std_drink_size: the size of the standard drink, in the same unit as amount.
     */

    double alcohol_amt = alcohol_volume(abv, amount);
    return round_to_two_decimal_points(alcohol_amt / std_drink_size);
}

double Calculate::alcohol_volume(const double &abv, const double &amount) {
    /*
     * Calculate the volume of alcohol in a drink.
     * @param abv: The alcohol by volume of the drink.
     * @param amount: The amount of drink in the container.
     */

    return (abv/100)*amount;
}

double Calculate::standard_drinks_remaining(const Options& options, const double &standard_drinks_consumed) {
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

    int drink_limit = Calculate::weekly_limit(options);

    weekly_drinks_remaining = drink_limit - standard_drinks_consumed;

    return weekly_drinks_remaining;
}

double Calculate::round_to_two_decimal_points(const double &val) {
    /*
     * Round a double to two decimal points.
     * @param val: The value that should be rounded.
     */

    return floor((val * 100) + .5)/100;
}

double Calculate::volume_alcohol_remaining(const Options& options, const double &volume_consumed) {
    /*
     * Calculate the amount of alcohol the user has remaining based on their sex.
     * @return: The amount of volume remaining for user.
     */

    double vol_alcohol_remaining {0};

    if (options.limit_standard == "Custom") {
        vol_alcohol_remaining = (std::stod(options.std_drink_size) * options.weekly_limit) - volume_consumed;
    } else {
        if (options.sex == "male") {
            vol_alcohol_remaining = (std::stod(options.std_drink_size) * 14) - volume_consumed;
        } else if (options.sex == "female") {
            vol_alcohol_remaining = (std::stod(options.std_drink_size) * 7) - volume_consumed;
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
        if (const unsigned second_count {brewery_count.second}; second_count > current_max) {
            favorite_producer = brewery_count.first;
            current_max = second_count;
        }
    }

    return favorite_producer;
}

std::string Calculate::favorite_drink(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculates favorite drink based on most common drink in database
     * @param Storage: a Storage instance
     * @return favorite_drink: The most common drink in the database.
     */

    std::map<std::string, unsigned> drink_counts;
    std::vector<std::string> drinks;
    std::string favorite_drink;

    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    drinks.reserve(all_drinks.size());
    for (const auto& drink: all_drinks) {
        drinks.push_back(drink.name);
    }
    for (const auto& producer : drinks) {
        int producer_count = std::count(drinks.begin(), drinks.end(), producer);
        drink_counts[producer] = producer_count;
    }

    unsigned current_max = 0;

    for (const auto & producer_count : drink_counts) {
        if (const unsigned second_count {producer_count.second}; second_count > current_max) {
            favorite_drink = producer_count.first;
            current_max = second_count;
        }
    }

    return favorite_drink;
}

double Calculate::mean_abv(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculate the mean ABV for all drinks.
     * @param storage: A storage instance.
     * @return: The average ABV at two decimal points.
     */

    double abv_sum = 0.0;
    unsigned drink_count = 0;
    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    for (const auto& drink : all_drinks) {
        drink_count += 1;
        abv_sum += drink.abv;
    }

    return round_to_two_decimal_points(abv_sum / drink_count);
}

double Calculate::mean_ibu(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculate the mean IBU of all drinks in the database.
     * @param storage: A storage instance.
     * @return: The average IBU per drink.
     */

    double ibu_sum = 0.0;
    unsigned drink_count = 0;
    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    for (const auto& drink : all_drinks) {
        // Ignore empty IBU values
        if (drink.ibu > 0) {
            drink_count += 1;
        }
        ibu_sum += drink.ibu;
    }

    return ibu_sum / drink_count;
}

std::string Calculate::favorite_type(const Storage& storage, const std::string& drink_type) {
    /*
     * Calculates favorite drink type based on most common type in database
     * @param Storage: a Storage instance
     * @return favorite_type: The most common type in the database.
     */

    std::map<std::string, unsigned> type_counts;
    std::vector<std::string> types;
    std::string favorite_type;

    std::vector<Drink> all_drinks = Database::filter("Alcohol Type", drink_type, storage);

    types.reserve(all_drinks.size());
    for (const auto& drink: all_drinks) {
        types.push_back(drink.type);
    }
    for (const auto& type : types) {
        int producer_count = std::count(types.begin(), types.end(), type);
        type_counts[type] = producer_count;
    }

    unsigned current_max = 0;

    for (const auto & type_count : type_counts) {
        if (const unsigned second_count {type_count.second}; second_count > current_max) {
            favorite_type = type_count.first;
            current_max = second_count;
        }
    }

    return favorite_type;
}

std::string Calculate::double_to_string(const double &input_double) {
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

double Calculate::oz_to_ml(const double &input_oz) {
    /*
     * Convert oz to ml for metric support. 1 oz = 29.5735 ml.
     * @param input_oz: A double denoting drink volume in ounces.
     * @return: A double denoting drink volume in milliliters.
     */

    double ml = input_oz * 29.5735;
    return ml;
}

double Calculate::ml_to_oz(const double &input_ml) {
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

    // Convert strings to uppercase
    for (char& c : lhs) {
        c = std::toupper(c, std::locale());
    }

    for (char& c : rhs) {
        c = std::toupper(c, std::locale());
    }

    return lhs < rhs;
}

int Calculate::weekly_limit(const Options& options) {
    /*
     * Get the weekly limit.
     * @param options: an options struct.
     * @return: the weekly standard drink limit.
     */

    std::string standard = options.limit_standard;
    std::string sex = options.sex;
    int drink_limit = options.weekly_limit;

    if (standard == "NIAAA") {
        if (sex == "male") {
            drink_limit = 14;
        } else if (sex == "female") {
            drink_limit = 7;
        } else {
            std::cout << "Sex is incorrectly set: " << sex << std::endl;
        }
    }

    return drink_limit;
}
