//
// Created by Ross Wardrup on 9/10/20.
//

#include "usersettings.h"
#include "mainwindow.h"

UserSettings::UserSettings(QWidget *parent, const Options& options) {
    /*
     * Dialog box for user settings.
     * @param parent: parent widget.
     */

    ui.setupUi(this);
    this->setFixedSize(405, 119);

    if (options.sex == "male") {
        ui.maleSelection->setChecked(true);
    } else if (options.sex == "female") {
        ui.femaleSelection->setChecked(true);
    }

    // Set weekday selector
    std::string current_date = options.weekday_start;
    if (!current_date.empty()) {
        ui.weekdayStartInput->setCurrentText(QString::fromStdString(current_date));
    } else {
        ui.weekdayStartInput->setCurrentText(QString::fromStdString("Sunday"));
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

std::string UserSettings::get_weekday_start() {
    /*
     * Return the weekday selected for which day the week begins on.
     * @return: String containing the day of week.
     */
    return ui.weekdayStartInput->currentText().toStdString();
}
