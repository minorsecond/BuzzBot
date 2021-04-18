//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_USERSETTINGS_H
#define BEERTABS_USERSETTINGS_H

#include "ui_user_settings.h"
#include "mainwindow.h"

class UserSettings : public QDialog, public Ui::userSettingsDialog {
    /*
     * User settings dialog
     */

    Q_OBJECT
    Ui::userSettingsDialog ui{};
public:
    explicit UserSettings(QWidget *parent, const Options &options);
    std::string get_sex();
    std::string get_weekday_start();
    std::string get_date_calculation_method();
    int get_drink_limit();
    std::string get_limit_standard();
    std::string get_units();
    double get_std_drink_size();
    std::string get_std_drink_country();

private:
    // Std drink sizes are all stored in Oz. Data are all from Wikipedia:
    // https://en.wikipedia.org/wiki/Standard_drink
    std::map<std::string , double> std_drink_standards = {
            {"Australia", 0.43},
            {"Austria", 0.86},
            {"Canada", 0.57},
            {"Denmark", 0.52},
            {"Finland", 0.52},
            {"France", 0.43},
            {"Germany", 0.47},
            {"Hong Kong", 0.43},
            {"Hungary", 0.73},
            {"Iceland", 0.34},
            {"Ireland", 0.43},
            {"Italy", 0.43},
            {"Japan", 0.85},
            {"Netherlands", 0.43},
            {"New Zealand", 0.43},
            {"Poland", 0.43},
            {"Portugal", 0.47},
            {"Spain", 0.43},
            {"Sweden", 0.51},
            {"Switzerland", 0.52},
            {"United Kingdom", 0.34},
            {"United States", 0.60}
    };


private slots:
    void changed_limit_setting();
    void changed_date_calc();
    void clicked_clear_data();
    void update_std_drink_size_label();
    void std_drink_country_changed();
};

#endif //BEERTABS_USERSETTINGS_H
