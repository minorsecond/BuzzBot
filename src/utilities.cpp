//
// Created by Ross Wardrup on 9/28/21.
//

//#include "mainwindow.h"
#include "options.h"
#include "utilities.h"
#include "drink_standards.h"
#include "usersettings.h"
#include <QStandardPaths>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>

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

double utilities::get_std_drink_size() {
    /*
     * Get standard drink size from either options or map.
     * @return: Standard drink size
     */

    Options options;  // Reads options from FS
    double standard_drink_size{0.0};

    if (options.std_drink_country == "Custom") {
        standard_drink_size = std::stod(options.std_drink_size);
    } else {
        standard_drink_size = std_drink_standards.find(options.std_drink_country)->second;
    }

    return standard_drink_size;
}

std::string utilities::get_application_data_path() {
    /*
     * Get data storage path for OS
     * @param: None
     * @return: an std::string denoting app data get_db_path
     */

    return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0).toStdString();
}

bool utilities::file_exists(const std::string &path) {
    /*
     * Check if file exists.
     * @param path: a string to file get_db_path
     * @return: bool - true if file exists, else false
     */

    std::ifstream f(path.c_str());
    return f.good();
}

std::string utilities::get_db_path() {
    /*
     * Find database get_db_path and create it if it doesn't exist.
     * @return full_path Path where database file should be stored.
     */

    Options options;  // Reads options from FS
    std::string full_path{};
    if (!options.custom_database) {
        // Find get_db_path to application support directory
        const std::string directory{utilities::get_application_data_path()};
        full_path = directory + "/buzzbot.db";
        std::filesystem::create_directory(directory);
    } else {  // Custom DB get_db_path
        full_path = options.database_path;
    }

    std::cout << "Using DB located at " << full_path << std::endl;

    return full_path;
}

std::string utilities::settings_path() {
    /*
     * Find database get_db_path and create it if it doesn't exist.
     * @return full_path Path where database file should be stored.
     */

    // Find get_db_path to application support directory
    const std::string directory = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(
            0).toStdString();
    const std::string settings_path = directory + "/buzzbot_settings.conf";
    std::filesystem::create_directory(directory);

    return settings_path;
}