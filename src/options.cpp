//
// Created by rwardrup on 9/24/22.
//

#include "options.h"
#include "utilities.h"
#include "include/json.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

using json = nlohmann::json;

int Options::write_options() const {
    /*
     * Read or write to/from the settings file.
     * @param sex: Sex of user.
     * @param write: Boolean denoting whether function should write to the file or not.
     * If false, assume should read.
     */

    json output_data{};
    std::string read_sex;
    const std::string custom_db_setting{custom_database ? "true" : "false"};
    const std::string path = utilities::settings_path();

    std::cout << "Writing user settings to " << path << std::endl;

    output_data["sex"] = sex;
    output_data["start_day"] = weekday_start;
    output_data["date_calculation_method"] = date_calculation_method;
    output_data["limit_standard"] = limit_standard;
    output_data["custom_weekly_limit"] = std::to_string(weekly_limit);
    output_data["units"] = units;
    output_data["std_drink_size"] = std::to_string(std_drink_size);
    output_data["std_drink_country"] = std_drink_country;
    output_data["custom_db"] = custom_db_setting;
    output_data["database_path"] = database_path;

    std::ofstream out_data;
    if (!out_data) {  // File doesn't exist on FS yet
        std::cerr << "Error: settings file could not be opened." << std::endl;  // TODO: Raise error window
    } else {
        out_data.open(path);
        out_data << std::setw(4) << output_data << std::endl;
        out_data.close();
    }

    return 0;
}

Options::Options() {
    // Read settings file on instantiation

    const std::string path {utilities::settings_path()};
    if (std::filesystem::exists(path)) {
        std::ifstream f(path);
        json config_data = json::parse(f);
        const bool custom_db_setting{ config_data["custom_db"] == "true" };

        sex = config_data["sex"];
        weekday_start = config_data["start_day"];
        date_calculation_method = config_data["date_calculation_method"];
        limit_standard = config_data["limit_standard"];
        weekly_limit =  std::stoi(config_data["custom_weekly_limit"].get_ref<std::string&>());
        units = config_data["units"];
        std_drink_size = std::stod(config_data["std_drink_size"].get_ref<std::string&>());
        std_drink_country = config_data["std_drink_country"];
        custom_database = custom_db_setting;
        database_path = config_data["database_path"];
    } else {
        std::cout << "Settings path doesn't exist. Writing defaults" << std::endl;
        write_options();
    }
}
