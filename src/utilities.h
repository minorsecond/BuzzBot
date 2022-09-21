//
// Created by Ross Wardrup on 9/28/21.
//

#ifndef BUZZBOT_UTILITIES_H
#define BUZZBOT_UTILITIES_H

#include <string>
#include "options.h"

class utilities {
public:
    static std::string zero_pad_string(unsigned integer);
    static std::string get_local_date();
    static std::string get_home_path();
    static double round_to_two_decimal_points(const double &val);
    static double get_std_drink_size();
};


#endif //BUZZBOT_UTILITIES_H
