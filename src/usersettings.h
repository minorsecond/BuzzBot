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
};

#endif //BEERTABS_USERSETTINGS_H
