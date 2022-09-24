//
// Created by rwardrup on 9/24/22.
//

#include "options.h"
#include "utilities.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

int Options::write_options() {
    /*
     * Read or write to/from the settings file.
     * @param sex: Sex of user.
     * @param write: Boolean denoting whether function should write to the file or not.
     * If false, assume should read.
     */

    std::string read_sex;
    const std::string custom_db_setting{custom_database ? "true" : "false"};
    const std::string path = utilities::settings_path();

    std::cout << "Writing user settings to " << path << std::endl;

    std::ofstream out_data;
    if (!out_data) {  // File doesn't exist on FS yet
        std::cerr << "Error: settings file could not be opened." << std::endl;  // TODO: Raise error window
    } else {
        out_data.open(path);
        out_data << "sex:" + sex + '\n';
        out_data << "start_day:" + weekday_start + '\n';
        out_data << "date_calculation_method:" + date_calculation_method + '\n';
        out_data << "limit_standard:" + limit_standard + '\n';
        out_data << "custom_weekly_limit:" + std::to_string(weekly_limit) + '\n';
        out_data << "units:" + units + '\n';
        out_data << "std_drink_size:" + std_drink_size + '\n';
        out_data << "std_drink_country:" + std_drink_country + '\n';
        out_data << "custom_db:" + custom_db_setting + '\n';
        out_data << "database_path:" + database_path + '\n';
        out_data.close();
    }

    return 0;
}

Options::Options() {
    // Read settings file on instantiation
    int line_counter{0};
    const std::string path = utilities::settings_path();
    std::string line;

    if (std::filesystem::exists(path)) {
        std::ifstream options_file(path);
        if (options_file.is_open()) {
            while (std::getline(options_file, line)) {
                if (line_counter == 0) {  // First line should be sex
                    sex = line.substr(line.find(':') + 1);
                } else if (line_counter == 1) { // Second line should be week start day
                    weekday_start = line.substr(line.find(':') + 1);
                } else if (line_counter == 2) { // Third line should be the date calculation method
                    date_calculation_method = line.substr(line.find(':') + 1);
                } else if (line_counter == 3) { // Fourth line should be limit standard setting
                    limit_standard = line.substr(line.find(':') + 1);
                } else if (line_counter == 4) { // Fifth line should be the weekly limit that is custom set
                    weekly_limit = std::stoi(line.substr(line.find(':') + 1));
                } else if (line_counter == 5) { // Sixth line should be the selected units, either Metric or Imperial
                    units = line.substr(line.find(':') + 1);
                } else if (line_counter == 6) { // Seventh line should be the std drink size (stored in oz)
                    std_drink_size = line.substr(line.find(':') + 1);
                } else if (line_counter == 7) { // Eigth line should be the std drink country
                    std_drink_country = line.substr(line.find(':') + 1);
                } else if (line_counter == 8) { // Ninth line should be custom db status
                    const bool custom_db{line.substr(line.find(':') + 1) == "true"};
                    custom_database = custom_db;
                } else if (line_counter == 9) { // tenth line should be the db get_db_path
                    database_path = line.substr(line.find(':') + 1);
                }
                line_counter += 1;
            }
        }
    } else {
        std::cout << "Settings path doesn't exist. Writing defaults" << std::endl;
        write_options();
    }
}
