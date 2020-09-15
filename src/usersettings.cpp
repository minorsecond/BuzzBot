//
// Created by Ross Wardrup on 9/10/20.
//

#include "usersettings.h"

UserSettings::UserSettings(QWidget *parent, const std::string& sex) {
    /*
     * Dialog box for user settings.
     * @param parent: parent widget.
     */

    ui.setupUi(this);
    this->setFixedSize(405, 119);

    if (sex == "male") {
        ui.maleSelection->setChecked(true);
    } else if (sex == "female") {
        ui.femaleSelection->setChecked(true);
    }
}

std::string UserSettings::get_sex() {
    /*
     * Return state of radio buttons.
     */

    if (ui.maleSelection->isChecked()) {
        return "male";
    } else {
        return "female";
    }
}

