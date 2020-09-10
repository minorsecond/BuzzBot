//
// Created by Ross Wardrup on 9/10/20.
//

#ifndef BEERTABS_USERSETTINGS_H
#define BEERTABS_USERSETTINGS_H

#include "ui_user_settings.h"

class UserSettings : public QDialog, public Ui::userSettingsDialog {
    /*
     * User settings dialog
     */
    Q_OBJECT
    Ui::userSettingsDialog ui{};
public:
    explicit UserSettings(QWidget *parent = nullptr, const std::string& sex = "male");
    std::string get_sex();
};


#endif //BEERTABS_USERSETTINGS_H
