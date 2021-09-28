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