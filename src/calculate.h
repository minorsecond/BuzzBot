//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_CALCULATE_H
#define BEERTABS_CALCULATE_H

#include <string>
#include "database.h"
#include "options.h"

class Calculate {
public:
    static double alcohol_volume(const double &abv, const double &amount);
    static double standard_drinks(const double &abv, const double &amount, const double &std_drink_size);
    static double standard_drinks_remaining(const Options& options, const double &standard_drinks_consumed);
    static double volume_alcohol_remaining(const Options& options, const double &volume_consumed);
    static std::string favorite_producer(const Storage& storage, const std::string& drink_type);
    static std::string favorite_drink(const Storage& storage, const std::string& drink_type);
    static std::string favorite_type(const Storage& storage, const std::string& drink_type);
    static double mean_abv(const Storage& storage, const std::string& drink_type);
    static double mean_ibu(const Storage& storage, const std::string& drink_type);
    static std::string double_to_string(const double &input_double);
    static double oz_to_ml(const double &input_oz);
    static double ml_to_oz(const double &input_ml);
    static bool compare_strings(std::string lhs, std::string rhs);
    static int weekly_limit(const Options& options);
    static unsigned days_in_row(Storage &storage);
    static bool equal_double(const double a, const double b);
    static double round_to_decimal_place(double input_val, unsigned places);
    static double get_volume_alcohol(const double abv, const double drink_size);

private:
    static constexpr unsigned us_male_limit {14};
    static constexpr unsigned us_female_limit {7};
    static void decrement_day(std::tm &date);
};


#endif //BEERTABS_CALCULATE_H
