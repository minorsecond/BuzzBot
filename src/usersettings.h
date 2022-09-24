//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_USERSETTINGS_H
#define BEERTABS_USERSETTINGS_H

#include "../ui/ui_user_settings.h"
#include "mainwindow.h"

class UserSettings : public QDialog, public Ui::userSettingsDialog {
    /*
     * User settings dialog
     */

Q_OBJECT
    Ui::userSettingsDialog ui{};

public:
    explicit UserSettings(const Options &options, const std::map<std::string, double> &country_info);

    std::string get_sex();

    std::string get_weekday_start();

    std::string get_date_calculation_method();

    int get_drink_limit();

    std::string get_limit_standard();

    std::string get_units();

    double get_std_drink_size();

    std::string get_std_drink_country();

    bool get_custom_database_status();

    std::string get_database_path();

    int populate_country_cbox(const std::map<std::string, double> &country_info);

    void set_std_drink_input_states(const Options &options);

    void set_limit_standard_states(const Options &options);

    void set_day_of_week_setting_state(const Options &options);

    void set_frame_style();

    void set_custom_database_status(const bool db_status);

    void set_database_path(const std::string &db_path);

private slots:

    void changed_limit_setting();

    void changed_date_calc();

    static void clicked_clear_data();

    static std::string clicked_browse_db_path();

    void update_std_drink_size_label();

    void std_drink_country_changed();
};

#endif //BEERTABS_USERSETTINGS_H
