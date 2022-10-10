//
// Created by Ross Wardrup on 9/10/20.
//

#include "usersettings.h"
#include "database.h"
#include <iostream>
#include <regex>
#include <filesystem>

// LCOV_EXCL_START
UserSettings::UserSettings(const Options& options, const std::map<std::string, double>& country_info) {
    /*
     * Dialog box for user settings.
     * @param parent: parent widget.
     * @param options: Options struct containing settings from user file.
     * @country_info: map of countries and their standard drink sizes, in ounces.
     */

    ui.setupUi(this);

    const int std_drink_cbox_index = populate_country_cbox(country_info);
    ui.stdDrinkDefComboBox->insertItem(std_drink_cbox_index, QString::fromStdString("Custom"));

    set_std_drink_input_states(options);

    if (options.sex == "male") {
        ui.maleSelection->setChecked(true);
    } else if (options.sex == "female") {
        ui.femaleSelection->setChecked(true);
    }

    if (options.weekly_limit != -1) {
        ui.customLimitSpinBox->setValue(options.weekly_limit);
    } else {
        ui.customLimitSpinBox->setValue(0);
    }

    set_limit_standard_states(options);

    ui.stdDrinkDefInput->setValue(options.std_drink_size);

    if (options.units == "Metric") {
        ui.metricRadioButton->setChecked(true);
    } else {
        ui.imperialRadioButton->setChecked(true);
    }

    // Set weekday selector
    const std::string current_date = options.weekday_start;
    if (!current_date.empty()) {
        ui.weekdayStartInput->setCurrentText(QString::fromStdString(current_date));
    } else {
        ui.weekdayStartInput->setCurrentText(QString::fromStdString("Sunday"));
    }

    // Set day of week calc
    set_day_of_week_setting_state(options);

    // Set delete data button text color to red
    QPalette pal = ui.clearDataButton->palette();
    pal.setColor(QPalette::ButtonText, QColor(Qt::red));
    ui.clearDataButton->setPalette(pal);
    ui.clearDataButton->update();

    ui.dbLocationTextInput->setText(QString::fromStdString(options.database_path));
    if (options.custom_database) {
        ui.customLocationRadioBtn->setChecked(true);
        ui.defaultLocationRadioBtn->setChecked(false);
        ui.dbLocationTextInput->setEnabled(true);
        ui.dbLocationBrowseButton->setEnabled(true);
    } else {
        ui.defaultLocationRadioBtn->setChecked(true);
        ui.customLocationRadioBtn->setChecked(false);
        ui.dbLocationTextInput->setEnabled(false);
        ui.dbLocationBrowseButton->setEnabled(false);
    }


    update_std_drink_size_label();

    // Connections
    connect(ui.rollingDateRadioButton, &QRadioButton::clicked, this, &UserSettings::changed_date_calc);
    connect(ui.fixedDateRadioButton, &QRadioButton::clicked, this, &UserSettings::changed_date_calc);
    connect(ui.niaaaStandardsRadioButton, &QRadioButton::clicked, this, &UserSettings::changed_limit_setting);
    connect(ui.customLimitRadioButton, &QRadioButton::clicked, this, &UserSettings::changed_limit_setting);
    connect(ui.defaultLocationRadioBtn, &QRadioButton::clicked, this, &UserSettings::set_custom_database_status);
    connect(ui.customLocationRadioBtn, &QRadioButton::clicked, this, &UserSettings::set_custom_database_status);
    connect(ui.clearDataButton, &QPushButton::clicked, this, &UserSettings::clicked_clear_data);
    connect(ui.dbLocationBrowseButton, &QPushButton::clicked, this, &UserSettings::clicked_browse_db_path);
    connect(ui.imperialRadioButton, &QRadioButton::clicked, this, &UserSettings::update_std_drink_size_label);
    connect(ui.metricRadioButton, &QRadioButton::clicked, this, &UserSettings::update_std_drink_size_label);
    connect(ui.stdDrinkDefComboBox, QOverload<int>::of(&QComboBox::activated), this, &UserSettings::std_drink_country_changed);
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

int UserSettings::get_drink_limit() {
    /*
     * Get the drink limit that user has specified.
     */

    return ui.customLimitSpinBox->value();
}

void UserSettings::changed_limit_setting() {
    /*
     * Disable/enable the custom limit spinbox.
     */

    if (ui.customLimitRadioButton->isChecked()) {
        ui.customLimitSpinBox->setEnabled(true);
    } else {
        ui.customLimitSpinBox->setEnabled(false);
    }
}

std::string UserSettings::get_limit_standard() {
    /*
     * Get the user-selected drink standard.
     */

    std::string selected_standard {"NIAAA"};

    if (ui.niaaaStandardsRadioButton->isChecked()) {
        selected_standard = "NIAAA";
    } else if (ui.customLimitRadioButton->isChecked()) {
        selected_standard = "Custom";
    }

    return selected_standard;
}

void UserSettings::clicked_clear_data() {
    /*
     * Clear the data if user so desires.
     */

    QMessageBox::StandardButton reply{};
    reply = QMessageBox::warning(nullptr, QString::fromStdString("Delete All Data"),
                                  QString::fromStdString("You are attempting to clear the database. Click Yes to confirm."),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Storage storage = initStorage(utilities::get_db_path());
        Database::truncate(storage);
        std::cout << "*** Truncated the database ***" << std::endl;
    }
}

std::string UserSettings::get_units() {
    /*
     * Get nuits
     * @return: String of either Imperial or Metric
     */

    std::string selected_units {"Imperial"}; // Default to imperial as most users will be from the US

    if (ui.metricRadioButton->isChecked()) {
        selected_units = "Metric";
    } else {
        selected_units = "Imperial";
    }

    return selected_units;
}

double UserSettings::get_std_drink_size() {
    /*
     * Get the volume of alcohol that denotes a standard drink.
     * @return: Value set in stdDrinkDefComboBox that denotes how big a standard drink is.
     */

    double std_drink_size {ui.stdDrinkDefInput->value()};

    return std_drink_size;
}

void UserSettings::update_std_drink_size_label() {
    /*
     * Update the standard drink size label when unit is changed.
     */

    if (ui.imperialRadioButton->isChecked()) {
        ui.stdDrinkDefLabel->setText("Oz. Alcohol");

    } else {
        ui.stdDrinkDefLabel->setText("ml Alcohol");
    }
}

std::string UserSettings::get_std_drink_country() {
    /*
     * Get the selected standard drink country.
     */

    std::string country_data = ui.stdDrinkDefComboBox->currentText().toStdString();
    country_data = std::regex_replace(country_data, std::regex(R"(\([^()]*\))"), "");
    country_data = std::regex_replace(country_data, std::regex(R"(/^\s+|\s+$|\s+(?=\s)/g)"), "");

    return country_data;
}

void UserSettings::std_drink_country_changed() {
    /*
     * Check the value of std drink country when changed, and toggle country entry box when necessary.
     */

    if (ui.stdDrinkDefComboBox->currentText().toStdString() == "Custom") {
        ui.stdDrinkDefInput->setEnabled(true);
    } else {
        ui.stdDrinkDefInput->setEnabled(false);
    }
}

int UserSettings::populate_country_cbox(const std::map<std::string, double> &country_info) {
    /*
     * Populate the country std drink sizes combo box with country_info data
     * @param country_info: A map containing CountryName: StdDrinkSize
     * @param options: The options struct.
     * @return: Int denoting next index of combobox
     */

    // Add country names to std drink size combobox
    auto country_name_iterator = country_info.begin();
    int std_drink_cbox_index {0};
    while (country_name_iterator != country_info.end()) {
        std::string country_name_drinks = country_name_iterator->first;
        ui.stdDrinkDefComboBox->insertItem(std_drink_cbox_index, QString::fromStdString(country_name_drinks));
        country_name_iterator++;
        std_drink_cbox_index += 1;
    }

    return std_drink_cbox_index;
}

void UserSettings::set_std_drink_input_states(const Options& options) {
    /*
     * Set the standard drinks size input field states.
     * @param options: An options struct
     */

    if (options.std_drink_country == "Custom") {
        ui.stdDrinkDefComboBox->setCurrentIndex(ui.stdDrinkDefComboBox->count() - 1);
        ui.stdDrinkDefInput->setEnabled(true);
    } else {
        std::string search_string = options.std_drink_country;
        int index = ui.stdDrinkDefComboBox->findText(QString::fromStdString(search_string));
        ui.stdDrinkDefComboBox->setCurrentIndex(index);
        ui.stdDrinkDefInput->setEnabled(false);
    }
    ui.stdDrinkDefInput->setSingleStep(0.1);
}

void UserSettings::set_limit_standard_states(const Options& options) {
    /*
     * Set the limit standard states.
     * @param options: An options struct.
     */

    if (options.limit_standard == "NIAAA") {
        ui.niaaaStandardsRadioButton->setChecked(true);
        ui.customLimitRadioButton->setChecked(false);
        ui.customLimitSpinBox->setEnabled(false);
    } else if (options.limit_standard == "Custom") {
        ui.niaaaStandardsRadioButton->setChecked(false);
        ui.customLimitRadioButton->setChecked(true);
        ui.customLimitSpinBox->setEnabled(true);
    }
}

void UserSettings::set_day_of_week_setting_state(const Options& options) {
    /*
     * Set the states for day of week setting.
     * @param options: An options struct.
     */

    if (options.date_calculation_method == "Fixed") {
        ui.weekdayStartInput->setEnabled(true);
        ui.fixedDateRadioButton->setChecked(true);
        ui.rollingDateRadioButton->setChecked(false);
    } else {
        ui.weekdayStartInput->setEnabled(false);
        ui.fixedDateRadioButton->setChecked(false);
        ui.rollingDateRadioButton->setChecked(true);
    }
}

void UserSettings::set_custom_database_status() {
    /*
     * Sets the DB customize status
     * @param db_status: Bool - true if using custom DB, else false
     * @return: None
     */

    if (ui.defaultLocationRadioBtn->isChecked()) {
        ui.dbLocationBrowseButton->setEnabled(false);
        ui.dbLocationTextInput->setEnabled(false);
    } else if (ui.customLocationRadioBtn->isChecked()){
        ui.dbLocationBrowseButton->setEnabled(true);
        ui.dbLocationTextInput->setEnabled(true);
    }
}

void UserSettings::set_database_path(const std::string &db_path) {
    /*
     * Sets the DB path input box according to the DB path
     * @param db_path: string denoting DB get_db_path
     */

    ui.dbLocationTextInput->setText(QString::fromStdString(db_path));
}

bool UserSettings::get_custom_database_status() {
    /*
     * Get database status from pref pane
     * @param: None
     * @return: Bool - true if custom DB get_db_path, else false
     */

    if (ui.customLocationRadioBtn->isChecked()) {
        return true;
    }

    return false;
}

std::string UserSettings::get_database_path(bool custom_db) {
    /*
     * Get DB path from pref pane
     * @param: None
     * @return: String denoting DB get_db_path
     */

    std::string full_path{};
    if (!custom_db) {
        // Find get_db_path to application support directory
        const std::string directory{utilities::get_application_data_path()};
        full_path = directory + "/buzzbot.db";
        std::filesystem::create_directory(directory);
    } else {  // Custom DB get_db_path
        full_path = ui.dbLocationTextInput->text().toStdString();
    }

    return full_path;
}

void UserSettings::clicked_browse_db_path() {
    /*
     * Action for when user clicks the DB browse button.
     * @param: None
     * @return: None
     */

    QMessageBox::StandardButton reply{};
    reply = QMessageBox::information(this, QString::fromStdString("DB Notification"),
                                  QString::fromStdString("After moving the DB, the app will close. \n"
                                                         "You will have to reopoen it after saving preferences."),
                                  QMessageBox::Ok);

    if (reply == QMessageBox::Ok) {
        const QString desktop_path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0);
        const QString preferred_path = desktop_path + "/buzzbot.db";

        QString filepath {QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                  desktop_path, QFileDialog::ShowDirsOnly |
                                                                  QFileDialog::DontResolveSymlinks)};
        filepath += QString::fromStdString("/buzzbot.db");
        ui.dbLocationTextInput->setText(filepath);
    }
}

// LCOV_EXCL_STOP