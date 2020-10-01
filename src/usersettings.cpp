//
// Created by Ross Wardrup on 9/10/20.
//

#include "usersettings.h"

// LCOV_EXCL_START
UserSettings::UserSettings(QWidget *parent, const Options& options) {
    /*
     * Dialog box for user settings.
     * @param parent: parent widget.
     */

    ui.setupUi(this);
    this->setFixedSize(615, 195);

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

    // Set day of week calc
    if (options.date_calculation_method == "Fixed") {
        ui.weekdayStartInput->setEnabled(true);
        ui.fixedDateRadioButton->setChecked(true);
        ui.rollingDateRadioButton->setChecked(false);
    } else {
        ui.weekdayStartInput->setEnabled(false);
        ui.fixedDateRadioButton->setChecked(false);
        ui.rollingDateRadioButton->setChecked(true);
    }

    // Connections
    connect(ui.rollingDateRadioButton, &QRadioButton::clicked, this, &UserSettings::changed_date_calc);
    connect(ui.fixedDateRadioButton, &QRadioButton::clicked, this, &UserSettings::changed_date_calc);
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

std::string UserSettings::get_date_calculation_method() {
    /*
     * Returns the selected date calculation method.
     * @return: String denoting date calculation method.
     */

    if (ui.rollingDateRadioButton->isChecked()) {
        return "Rolling";
    } else {
        return "Fixed";
    }
}

void UserSettings::changed_date_calc() {
    /*
     * Disable/enable weekday start combobox.
     */

    if (ui.rollingDateRadioButton->isChecked()) {
        ui.weekdayStartInput->setEnabled(false);
    } else {
        ui.weekdayStartInput->setEnabled(true);
    }
}
// LCOV_EXCL_STOP