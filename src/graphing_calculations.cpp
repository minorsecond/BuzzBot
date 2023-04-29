//
// Created by rwardrup on 9/19/22.
//

#include <iomanip>
#include <map>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "graphing_calculations.h"

#ifdef __WIN32
    #include "utilities.h"  // For strptime
#endif

const unsigned tm_year_base {1900};
const unsigned tm_mday_base {1};
const unsigned tm_wday_max {6};

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

    std::map<double, size_t> ibu_counts;

    for (const auto& value : all_values) {
        auto it = ibu_counts.find(value);
        if (it == ibu_counts.end()) {
            ibu_counts.emplace_hint(it, value, 1);
        } else {
            ++it->second;
        }
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
    auto timet = static_cast<int>(std::mktime(&t));

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
#ifdef __WIN32
    utilities::strptime(std::to_string(date).c_str(), "%Y%m%d", &tm);
#else
    strptime(std::to_string(date).c_str(), "%Y%m%d", &tm);
#endif

    const int wday {tm.tm_wday};
    const int delta {wday ? wday - 1 : days_per_week - 1};

    const int week_num {(tm.tm_yday + days_per_week - delta) / days_per_week};

    return std::to_string(date).substr(0, 4) + '-' + std::to_string(week_num);
}

tm GraphingCalculations::update_week_number_and_day(std::string week_num_tmp, unsigned day_num, tm tm) {
    if (day_num > tm_wday_max) {
        day_num = 0;
        const size_t first {week_num_tmp.find('-')};
        const size_t last {week_num_tmp.find_last_of('-')};
        const std::string current_year {week_num_tmp.substr(0, first)};
        const int current_week {std::stoi(week_num_tmp.substr(first, last-first)) + 1};
        week_num_tmp = current_year + "-" + std::to_string(current_week) + "-" + std::to_string(day_num);

#ifdef _WIN32
        utilities::strptime(week_num_tmp.c_str(), "%Y-%W-%w", &tm);
#else
        strptime(week_num_tmp.c_str(), "%Y-%W-%w", &tm);
#endif
    }

    return tm;
}

int GraphingCalculations::date_from_week_num(const std::string& week_num) {
    /*
     * Calculates the date from a week number.
     * @param week_num: theweek number to calculate the date for.
     * @return an integer denoting date, in YYYYMMDD format.
     */

    struct tm tm{};
    int day_num {1};
    std::string week_num_tmp {week_num + "-" + std::to_string(day_num)};

#ifdef __WIN32
    std::function<void()> strptimeFunc = [&]() {
        utilities::strptime(week_num_tmp.c_str(), "%Y-%W-%w", &tm);
    };
#else
    std::function<void()> strptimeFunc = [&]() {
        strptime(week_num_tmp.c_str(), "%Y-%W-%w", &tm);
    };
#endif

    strptimeFunc();

    while (tm.tm_mday < 1) {
        day_num += 1;
        week_num_tmp = week_num + "-" + std::to_string(day_num);
        strptimeFunc();

        tm = update_week_number_and_day(week_num_tmp, day_num, tm);
    }

    std::string year {std::to_string(tm.tm_year + tm_year_base)};
    std::string month {std::to_string(tm.tm_mon + tm_mday_base)};
    std::string day {std::to_string(tm.tm_mday)};

    month = (month.length() == 1) ? '0' + month : month; // Zero pad if single digit month
    day = (day.length() == 1) ? '0' + day : day;  // Zero pad if single digit day

    const std::string date_str = year + month + day;
    int date {std::stoi(date_str)};

    return date;
}