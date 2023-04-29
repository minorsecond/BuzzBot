//
// Created by rwardrup on 9/19/22.
//

#ifndef BUZZBOT_GRAPHING_CALCULATIONS_H
#define BUZZBOT_GRAPHING_CALCULATIONS_H

#include <vector>
#include <string>
#include <map>
#include "drink.h"

class GraphingCalculations {
public:
    static std::vector<double> get_beer_ibus(const std::vector<Drink>& all_drinks);
    static std::vector<double> get_drink_abvs(const std::vector<Drink>& all_drinks);
    static std::map<double, size_t> count_values_in_vect(const std::vector<double>& all_values);
    static bool compare_by_date(const Drink &a, const Drink &b);
    static int parse_date(const std::string &date);
    static std::string week_number(int date);
    static int date_from_week_num(const std::string& week_num);

private:
    static tm update_week_number_and_day(std::string week_num_tmp, unsigned day_num, tm tm);
};


#endif //BUZZBOT_GRAPHING_CALCULATIONS_H
