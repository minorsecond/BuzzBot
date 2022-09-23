//
// Created by rwardrup on 9/19/22.
//

#include <iomanip>
#include <map>
#include <cstring>
#include <sstream>
#include "graphing_calculations.h"

std::vector<double> GraphingCalculations::get_beer_ibus(const std::vector<Drink>& all_drinks) {
    /*
     * Create a vector containing IBU values of all beers.
     * @param all_drinks: A vector of drinks. This will be all drinks in the database.
     * @return: Vector of doubles representing all beer IBUs.
     */

    std::vector<double> ibu_values {};

    for (const auto& drink : all_drinks) {
        double ibu = drink.get_ibu();
        if (ibu > 0)  // Exclude non-beer drinks
            ibu_values.push_back(ibu);
    }

    return ibu_values;
}

std::vector<double> GraphingCalculations::get_drink_abvs(const std::vector<Drink> &all_drinks) {
    /*
     * Create a vector containing ABV values of all drinks.
     * @param all_drinks: A vector of drinks. This will be all drinks in the database.
     * @return: A vector of doubles denoting all drink IBUs.
     */

    std::vector<double> abv_values {};

    abv_values.reserve(all_drinks.size());
    for (const auto& drink : all_drinks) {
        abv_values.push_back(drink.get_abv());
    }

    return abv_values;
}

std::map<double, size_t> GraphingCalculations::count_values_in_vect(const std::vector<double>& all_values) {
    /*
     * Create a map of values and their counts.
     * @param all_values: a vector of doubles.
     * @return: a map<double, int> of values (keys) and their counts (values).
     */

    std::vector<double> ibu_copy {all_values};
    std::map<double, size_t> ibu_counts {};

    // Get count (y value) of each IBU (x value).
    // First, get unique items in vector
    std::sort(ibu_copy.begin(), ibu_copy.end());
    ibu_copy.erase(unique(ibu_copy.begin(), ibu_copy.end()), ibu_copy.end());

    // Create map where key is the IBU value and value is the count of the IBU in all_values.
    for (const double &i : ibu_copy) {
        const double ibu_value = i;
        size_t ibu_count = std::count(all_values.begin(), all_values.end(), ibu_value);
        ibu_counts[i] = ibu_count;
    }

    return ibu_counts;
}

bool GraphingCalculations::compare_by_date(const Drink &a, const Drink &b) {
    /*
     * Compare dates between two drinks.
     * @return: True if drink a is earlier than drink b. Else, false.
     */

    const std::string date_a_cpy {a.get_date()};
    const std::string date_b_cpy {b.get_date()};

    int date_a {parse_date(date_a_cpy)};
    int date_b {parse_date(date_b_cpy)};

    return date_a < date_b;
}

int GraphingCalculations::parse_date(const std::string &date) {
    /*
     * Convert date string to integer date.
     * @param date: A date in the format YYYYMMDD
     * @return: an integer in UNIX epoch time
     */

    std::tm t {};
    std::stringstream date_str;
    date_str.str(date);
    std::stringstream new_date;

    date_str >> std::get_time(&t, "%Y%m%d");
    std::put_time(&t, "%c");
    auto timet = (int)std::mktime(&t);

    return timet;
}

std::string GraphingCalculations::week_number(const int date) {
    /*
     * Get the week number for a date
     * @param date: An integer of date, e.g. 20210405
     * @return: year and week number, e.g. 2021-05
     */

    constexpr int days_per_week {7};
    struct tm tm{};
    strptime(std::to_string(date).c_str(), "%Y%m%d", &tm);

    const int wday {tm.tm_wday};
    const int delta {wday ? wday - 1 : days_per_week - 1};

    const int week_num {(tm.tm_yday + days_per_week - delta) / days_per_week};

    return std::to_string(date).substr(0, 4) + '-' + std::to_string(week_num);
}

int GraphingCalculations::date_from_week_num(const std::string& week_num) {
    /*
     * Calculates the date from a week number.
     * @param week_num: theweek number to calculate the date for.
     * @return an integer denoting date, in YYYYMMDD format.
     */

    struct tm tm{};
    const std::string week_num_tmp {week_num + "-1"};
    strptime(week_num_tmp.c_str(), "%Y-%W-%w", &tm);

    std::string year {std::to_string(tm.tm_year +1900)};
    std::string month {std::to_string(tm.tm_mon + 1)};
    std::string day {std::to_string(tm.tm_mday)};

    month = (month.length() == 1) ? '0' + month : month; // Zero pad if single digit month
    day = (day.length() == 1) ? '0' + day : day;  // Zero pad if single digit day

    const std::string date_str = year + month + day;
    int date {std::stoi(date_str)};

    return date;
}