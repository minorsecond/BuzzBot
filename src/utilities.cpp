//
// Created by Ross Wardrup on 9/28/21.
//

#include "utilities.h"

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
    char query_date[10];
    std::string output;

    auto todays_date = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(todays_date);
    std::tm now_tm = *std::localtime(&now_c);
    std::strftime(query_date, sizeof query_date, "%Y-%m-%d", &now_tm);

    for (char i : query_date) {
        output += std::string(1, i);
    }

    return output;
}