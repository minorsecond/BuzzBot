//
// Created by Ross Wardrup on 9/10/20.
//

#include "usersettings.h"

UserSettings::UserSettings(QWidget *parent) {
    /*
     * Dialog box for user settings.
     * @param parent: parent widget.
     */

    ui.setupUi(this);
    this->setFixedSize(242, 117);
    ui.maleSelection->setChecked(true);
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

