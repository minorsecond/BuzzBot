//
// Created by Ross Wardrup on 9/28/21.
//

#include "utilities.h"
#include <sstream>
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
    int str_length = ret.length();
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

    auto todays_date = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(todays_date);
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
