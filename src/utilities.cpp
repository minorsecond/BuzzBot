//
// Created by Ross Wardrup on 9/28/21.
//

#include "utilities.h"
#include "drink_standards.h"
#include <sstream>
#include <cmath>
#ifdef __linux
    #include <chrono>
    #include <boost/format.hpp>
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#endif

std::string utilities::zero_pad_string(unsigned integer) {
    /*
     * Add a leading zero to a string.
     * @param integer: The input integer which should be padded.
     * @return: A 0-padded string.
     */

    std::stringstream ss;

    // the number is converted to string with the help of stringstream
    ss << integer;
    std::string ret;
    ss >> ret;

    // Append zero chars
    const int str_length = ret.length();
    for (int i = 0; i < 2 - str_length; i++)
        ret = "0" + ret;
    return ret;
}

std::string utilities::get_local_date() {
    /*
     * Get date in localtime
     * @return: A string denoting the date in localtime, with the format YYYY-MM-DD
     */

    // Get today's date in local time.
    std::string output;

    const auto todays_date = std::chrono::system_clock::now();
    const auto now_c = std::chrono::system_clock::to_time_t(todays_date);
    std::tm now_tm = *std::localtime(&now_c);
#ifdef __APPLE__
    char query_date[10];
    std::strftime(query_date, sizeof query_date, "%Y-%m-%d", &now_tm);

    for (char i : query_date) {
        output += std::string(1, i);
    }
#elif __linux
    const int year {1900+now_tm.tm_year};
    const int month {1+now_tm.tm_mon};
    output = boost::str(boost::format("%1%-%2%-%3%") % year % month % now_tm.tm_mday);
#endif

    return output;
}

std::string utilities::get_home_path() {
    return std::getenv("HOME");
}

double utilities::round_to_two_decimal_points(const double &val) {
    /*
     * Round a double to two decimal points.
     * @param val: The value that should be rounded.
     */

    return floor((val * 100) + .5)/100;
}

double utilities::get_std_drink_size_from_options() {
    /*
     * Get the std drink size for the selected country.
     * @param country: The country for which to retrieve the size.
     * @return: a double denoting the size of a standard drink.
     */

    Options options;

    double std_drink_size {0.6}; // Default to US
    if (options.std_drink_country == "Custom") {
        std_drink_size = std::stod(options.std_drink_size);
    } else {
        std_drink_size = std_drink_standards.find(options.std_drink_country)->second;
    }

    return std_drink_size;
}

double utilities::get_std_drink_size() {
    /*
     * Get standard drink size from either options or map.
     * @return: Standard drink size
     */

    Options options;
    double standard_drink_size {0.0};

    if (options.std_drink_country == "Custom") {
        standard_drink_size = std::stod(options.std_drink_size);
    } else {
        standard_drink_size = get_std_drink_size_from_options();  // Try to grab std. drink size for country
    }

    return standard_drink_size;
}