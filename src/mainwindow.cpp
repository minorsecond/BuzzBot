#include "mainwindow.h"
#include "usersettings.h"
#include "about.h"
#include "calculate.h"
#include "../include/date.h"
#include <iomanip>
#include <boost/filesystem.hpp>
#include <iostream>
#include <QComboBox>
#include <QMessageBox>
#include <QStandardPaths>
#include <CoreFoundation/CFBundle.h>

// LCOV_EXCL_START
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*
     * Set up the main window
     *
     */

    ui->setupUi(this);

    // Read options and create if the file doesn't exist
    // TODO: Create the settings file within program_options()
    program_options(false);
    program_options(true);

    // Upgrade DB version
    // TODO: Remove the brewery column from database at DB version 3
    Database::increment_version(storage, 3);

    add_menubar_items();

    // Set size hints
    ui->beerDateInput->setProperty("sizeHint", QVariant(QSizeF(241, 22)));

    // Set current tab to Beer tab
    ui->tabWidget->setCurrentIndex(0);

    configure_calendar();
    Database::write_db_to_disk(storage);
    update_stat_panel();

    // Set up button and input states
    set_input_states();

    // Enable this on release
    ui->drinkLogTable->setRowCount(0);

    // Disable cell editing
    ui->drinkLogTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    update_table();

    ui->wineVintage->setMaximum(QDate::currentDate().year());
    ui->wineVintage->setMinimum(0);

    // Sort table by date column, by default
    reset_table_sort();
    configure_table();
    add_slot_connections();

    // Update fields to match beer that comes first alphabetically
    reset_fields();
}

void MainWindow::add_menubar_items() {
    /*
     * Add items to the system menubar.
     */


    auto * preferences_action = new QAction("Preferences");
    auto * about_action = new QAction("About");
    QMenu * app_menu = menuBar()->addMenu("App Menu");
    preferences_action->setMenuRole(QAction::PreferencesRole);
    about_action->setMenuRole(QAction::AboutRole);
    app_menu->addAction(preferences_action);
    app_menu->addAction(about_action);

    connect(preferences_action, SIGNAL(triggered()), this, SLOT(open_user_settings()));
    connect(about_action, SIGNAL(triggered()), this, SLOT(open_about_dialog()));
}

void MainWindow::configure_calendar() {
    /*
     * Set up the calendar widget with nicer settings.
     */

    // First, get path of .app file
    CFURLRef app_url_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef mac_path = CFURLCopyFileSystemPath(app_url_ref, kCFURLPOSIXPathStyle);
    QString icon_path_qstring = CFStringGetCStringPtr(mac_path, CFStringGetSystemEncoding());

    // Set path to icons
    std::string previous_month_arrow = icon_path_qstring.toStdString() + "/Contents/Resources/previous.png";
    std::string next_month_arrow = icon_path_qstring.toStdString() + "/Contents/Resources/next.png";
    std::string stylesheet_text = "QCalendarWidget QWidget#qt_calendar_navigationbar\n"
                                  "{\n"
                                  "\tcolor: transparent;\n"
                                  "\tbackground-color: transparent;\n"
                                  "}\n"
                                  "QCalendarWidget QToolButton {\n"
                                  "  \tbackground-color: rgba(128, 128, 128, 0);\n"
                                  "}\n"
                                  " /* header row */\n"
                                  "QCalendarWidget QWidget { alternate-background-color: rgba(128, 128, 128, 0); }\n"
                                  "QCalendarWidget QToolButton#qt_calendar_prevmonth \n"
                                  "{\n"
                                  "\tqproperty-icon: url(" + previous_month_arrow +
                                  ");\n"
                                  "}\n"
                                  "\n"
                                  "QCalendarWidget QToolButton#qt_calendar_nextmonth \n"
                                  "{\n"
                                  "\tqproperty-icon: url(" + next_month_arrow + ");\n""}";
    ui->beerDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
    ui->liquorDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
    ui->wineDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
}

void MainWindow::configure_table() {
    /*
     * Set table settings
     */

    // Fixed row height in table
    QHeaderView *verticalHeader = ui->drinkLogTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    ui->drinkLogTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Enable table sorting by columns
    ui->drinkLogTable->setSortingEnabled(true);

    // Set table filter options to default values (all)
    ui->filterCategoryInput->addItem("None");
    ui->filterCategoryInput->setCurrentText("None");
    ui->filterCategoryInput->addItem("Name");
    ui->filterCategoryInput->addItem("Type");
    ui->filterCategoryInput->addItem("Subtype");
    ui->filterCategoryInput->addItem("Producer");
    ui->filterCategoryInput->addItem("Rating");
    ui->filterTextInput->setDisabled(true);

    // Set column widths
    ui->drinkLogTable->setColumnWidth(0, 75);
    ui->drinkLogTable->setColumnWidth(1, 428);
    ui->drinkLogTable->setColumnWidth(2, 200);
    ui->drinkLogTable->setColumnWidth(3, 200);
    ui->drinkLogTable->setColumnWidth(4, 428);
    ui->drinkLogTable->setColumnWidth(5, 50);
    ui->drinkLogTable->setColumnWidth(6, 50);
    ui->drinkLogTable->setColumnWidth(7, 50);
    ui->drinkLogTable->setColumnWidth(8, 55);
    ui->drinkLogTable->setColumnHidden(9, true);  // Hide ID column
    ui->drinkLogTable->setColumnHidden(10, true);  // Hide Timestamp column
    ui->drinkLogTable->setColumnHidden(11, true);  // Hide Sort column
    QHeaderView* drink_log_header = ui->drinkLogTable->horizontalHeader();
    drink_log_header->setSectionResizeMode(1, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(2, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(3, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(4, QHeaderView::Stretch);
}

void MainWindow::add_slot_connections() {
    /*
     * Connect buttons to slots
     */

    // Disconnect corner button so that we can use it for our own method
    auto *corner_button = ui->drinkLogTable->findChild<QAbstractButton*>();
    if (corner_button) {
        corner_button->disconnect();
    }

    // Slot connections
    connect(corner_button, &QAbstractButton::clicked, this, &MainWindow::reset_table_sort);
    connect(ui->drinkLogTable->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::populate_fields);
    connect(ui->filterCategoryInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::enable_filter_text);
    connect(ui->filterTextInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::changed_filter_text);
    connect(ui->submitRowButton, &QPushButton::clicked, this, &MainWindow::submit_button_clicked);
    connect(ui->clearFieldsButton, &QPushButton::clicked, this, &MainWindow::clicked_clear_button);
    connect(ui->deleteRowButton, &QPushButton::clicked, this, &MainWindow::delete_row);
    connect(ui->beerNameInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::name_input_changed);
    connect(ui->beerNameInput, &QComboBox::editTextChanged, this, &MainWindow::name_input_changed);
    connect(ui->beerTypeInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::type_input_changed);
    connect(ui->beerBreweryInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::producer_input_changed);
    connect(ui->liquorNameInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::name_input_changed);
    connect(ui->liquorNameInput, &QComboBox::editTextChanged, this, &MainWindow::name_input_changed);
    connect(ui->liquorTypeInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::type_input_changed);
    connect(ui->liquorDistillerInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::producer_input_changed);
    connect(ui->wineNameInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::name_input_changed);
    connect(ui->wineNameInput, &QComboBox::editTextChanged, this, &MainWindow::name_input_changed);
    connect(ui->wineTypeInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::type_input_changed);
    connect(ui->wineryInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::producer_input_changed);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tab_changed);
}

void MainWindow::set_input_states() {
    /*
     * Set up the default input states.
     */

    ui->deleteRowButton->setDisabled(true);
    ui->beerNameInput->setDuplicatesEnabled(false);
    ui->liquorNameInput->setDuplicatesEnabled(false);
    ui->wineNameInput->setDuplicatesEnabled(false);
    ui->beerTypeInput->setDuplicatesEnabled(false);
    ui->liquorTypeInput->setDuplicatesEnabled(false);
    ui->wineTypeInput->setDuplicatesEnabled(false);
    ui->beerBreweryInput->setDuplicatesEnabled(false);
    ui->liquorDistillerInput->setDuplicatesEnabled(false);
    ui->wineryInput->setDuplicatesEnabled(false);

    // Set datepicker to today's date
    QDate todays_date = QDate::currentDate();
    ui->beerDateInput->setDate(todays_date);
    ui->liquorDateInput->setDate(todays_date);
    ui->wineDateInput->setDate(todays_date);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submit_button_clicked() {
    /*
     * Create a beer from user input and write it to the database.
     */

    QItemSelectionModel *selection_model = ui->drinkLogTable->selectionModel();
    QModelIndexList selected_rows = selection_model->selectedRows();

    // Get current tab selected
    std::string alcohol_type = get_current_tab();
    Drink entered_drink = get_drink_attributes_from_fields();

    // Prevent blank submissions
    if (entered_drink.name.empty() || entered_drink.abv == 0.0) {
        QMessageBox::critical(nullptr, "Error", "Please enter drink name and ABV.");
    } else {
        // Handle updating existing rows
        QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
        if (select->hasSelection()) {
            update_selected_row(select, entered_drink);
        } else {
            add_new_row(entered_drink);
        }
        update_table();
        if (selected_rows.empty()) {
            reset_fields();  // Reset fields if not updating a row
        }
        update_beer_fields();
        update_liquor_fields();
        update_wine_fields();
        update_stat_panel();
    }
}

void MainWindow::update_selected_row(QItemSelectionModel* select, Drink entered_drink) {
    /*
     * Update a row that already exists in the database.
     * @param select: A selection model.
     * @param entered_drink: A Drink containing data from the database.
     */
    // Get the selected row
    int selection = select->selectedRows().at(0).row();
    int row_to_update = ui->drinkLogTable->item(selection, 9)->text().toUtf8().toInt();

    // Get the existing timestamp
    std::string timestamp = ui->drinkLogTable->item(selection, 10)->text().toStdString();
    std::cout << "Updating row " << row_to_update << " Timestamp: " << timestamp << std::endl;

    // Update the variables in the beer struct
    entered_drink.id = row_to_update;
    entered_drink.timestamp = timestamp;
    Database::update(storage, entered_drink);
}

void MainWindow::add_new_row(Drink entered_drink) {
    /*
     * Add a new drink to the database.
     * @param entered_drink: A Drink containing data entered by the user.
     */

    // New row. Get a new timestamp
    std::string timestamp = storage.select(sqlite_orm::datetime("now")).front();
    entered_drink.timestamp = timestamp;
    Database::write(entered_drink, storage);
}

void MainWindow::reset_fields() {
    /*
     * Clear user entry fields and table selection for entering a new drink.
     */

    std::string beer_notes;
    std::string liquor_notes;
    std::string wine_notes;

    std::string alcohol_type = get_current_tab();

    if (alcohol_type == "Beer") {
        std::cout << "Updating beer fields on name change" << std::endl;
        update_beer_fields();
        update_types_producers_on_name_change();

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->beerDateInput->setDate(todays_date);
    } else if (alcohol_type == "Liquor") {
        update_liquor_fields();
        update_types_producers_on_name_change();

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->liquorDateInput->setDate(todays_date);
    } else if (alcohol_type == "Wine") {
        update_wine_fields();
        update_types_producers_on_name_change();

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->wineDateInput->setDate(todays_date);
    }
}

void MainWindow::update_table() {
    /*
     * Populate the table with data from the database.
     */

    // Temporarily sort by database ID to fix issues with blank rows
    //ui->drinkLogTable->sortItems(9, Qt::AscendingOrder);

    std::string filter_category = ui->filterCategoryInput->currentText().toStdString();
    std::string filter_text = ui->filterTextInput->currentText().toStdString();

    std::vector<Drink> drinks = Database::filter(filter_category, filter_text, storage);
    drinks = Database::sort_by_date_id(drinks);

    ui->drinkLogTable->setRowCount(0);
    for (const auto& drink : drinks) {
        int table_row_num = ui->drinkLogTable->rowCount();
        ui->drinkLogTable->insertRow(table_row_num);
        QDate date = QDate::fromString(QString::fromStdString(drink.date), "yyyy-MM-dd");
        auto *date_qtw = new QTableWidgetItem;
        auto *name = new QTableWidgetItem(drink.name.c_str());
        auto *type = new QTableWidgetItem(drink.type.c_str());
        auto *subtype = new QTableWidgetItem(drink.subtype.c_str());
        auto *producer = new QTableWidgetItem(drink.producer.c_str());
        auto *abv = new QTableWidgetItem(double_to_string(drink.abv).c_str());
        auto *size = new QTableWidgetItem(double_to_string(drink.size).c_str());
        auto *rating = new QTableWidgetItem(std::to_string(drink.rating).c_str());
        auto *id = new QTableWidgetItem;
        auto *timestamp = new QTableWidgetItem(drink.timestamp.c_str());
        auto *sort_order =  new QTableWidgetItem(drink.sort_order);

        // Sort ID numerically
        id->setData(Qt::DisplayRole, drink.id);
        sort_order->setData(Qt::DisplayRole, drink.sort_order);
        date_qtw->setData(Qt::DisplayRole, date);

        std::string notes = drink.notes;

        // Handle blank IBU
        auto *ibu = new QTableWidgetItem;
        if (drink.ibu == -1.0) {  // -1 denotes no IBU value
            *ibu = QTableWidgetItem("");
        } else {
            *ibu = QTableWidgetItem(double_to_string(drink.ibu).c_str());
        }

        ui->drinkLogTable->setItem(table_row_num, 0, date_qtw);
        ui->drinkLogTable->setItem(table_row_num, 1, name);
        ui->drinkLogTable->setItem(table_row_num, 2, type);
        ui->drinkLogTable->setItem(table_row_num, 3, subtype);
        ui->drinkLogTable->setItem(table_row_num, 4, producer);
        ui->drinkLogTable->setItem(table_row_num, 5, abv);
        ui->drinkLogTable->setItem(table_row_num, 6, ibu);
        ui->drinkLogTable->setItem(table_row_num, 7, size);
        ui->drinkLogTable->setItem(table_row_num, 8, rating);
        ui->drinkLogTable->setItem(table_row_num, 9, id);
        ui->drinkLogTable->setItem(table_row_num, 10, timestamp);
        ui->drinkLogTable->setItem(table_row_num, 11, sort_order);
    }
    reset_table_sort();
}

std::string MainWindow::double_to_string(double input_double) {
    /*
     * Convert a double to a string with 1 decimal value.
     * @param input_double: Double value that should be converted.
     */

    double converted_double;
    converted_double = std::floor((input_double * 100.0) + .5) / 100.0;

    std::ostringstream price_stream;
    price_stream << converted_double;

    return price_stream.str();
}

void MainWindow::populate_fields(const QItemSelection &, const QItemSelection &) {
    /*
     * Populate user entry fields when user clicks on a row in the table.
     */

    Drink drink_at_row = get_drink_at_selected_row();

    if (drink_at_row.alcohol_type == "Beer") {
        populate_beer_fields(drink_at_row);
        ui->tabWidget->setCurrentIndex(0);
    } else if (drink_at_row.alcohol_type == "Liquor") {
        populate_liquor_fields(drink_at_row);
        ui->tabWidget->setCurrentIndex(1);
    } else if (drink_at_row.alcohol_type == "Wine") {
        populate_wine_fields(drink_at_row);
        ui->tabWidget->setCurrentIndex(2);
    } else {
        std::cout << "Not updating fields because not in correct tab." << std::endl;
    }
}

void MainWindow::delete_row() {
    /*
     * Delete the row in the database that corresponds to the row selected in the table.
     */

    int select = ui->drinkLogTable->selectionModel()->currentIndex().row();
    int row_to_delete = (ui->drinkLogTable->item(select, 9)->text().toUtf8().toInt());
    std::cout << "Deleting row " << row_to_delete << std::endl;
    Database::delete_row(storage, row_to_delete);
    update_table();
    update_stat_panel();
    ui->deleteRowButton->setDisabled(true);

    // Update the fields to reflect deleted row
    update_beer_fields();
    update_liquor_fields();
    update_wine_fields();
}

void MainWindow::open_about_dialog() {
    /*
     * Open the about dialog which contains author and license information.
     */

    auto *about_dialog = new About(this);
    about_dialog->setModal(false);
    about_dialog->show();
}

void MainWindow::open_user_settings() {
    /*
     * Open the user settings dialog box, where users can enter their sex and the day which the week should begin on.
     */

    UserSettings user_settings = UserSettings(nullptr, options);
    user_settings.setModal(true);
    if (user_settings.exec() == QDialog::Accepted) {
        options.sex = user_settings.get_sex();
        options.weekday_start = user_settings.get_weekday_start();
        update_stat_panel();
    }
    program_options(true);
}

std::string MainWindow::settings_path() {
    /*
     * Find database path and create it if it doesn't exist.
     * @return full_path Path where database file should be stored.
     */
    // Find path to application support directory

    std::string directory = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0).toStdString();

    std::string settings_path = directory + "/buzzbot_settings.conf";

    boost::filesystem::create_directory(directory);

    return settings_path;
}

void MainWindow::program_options(bool write) {
    /*
     * Read or write to/from the settings file.
     * @param sex: Sex of user.
     * @param write: Boolean denoting whether function should write to the file or not.
     * If false, assume should read.
     */

    std::string path = settings_path();
    std::string read_sex;

    if (write) {
        std::string sex_setting = "sex:" + options.sex;
        std::string start_day = "start_day:" + options.weekday_start;
        std::ofstream out_data;

        if (!out_data) {
            std::cerr << "Error: settings file could not be opened." << std::endl;
            exit(1);
        }

        out_data.open(path);
        out_data << sex_setting + '\n';
        out_data << start_day + '\n';
        out_data.close();
    } else {
        std::cout << "Reading user settings from " << path << std::endl;
        int line_counter = 0;
        // Read from the file
        std::string line;
        std::ifstream options_file(path);
        if (options_file.is_open()) {
            while (std::getline(options_file, line)) {
                if (line_counter == 0) {  // First line should be sex
                    options.sex = line.substr(line.find(':') + 1);
                } else if (line_counter == 1) { // Second line should be week start day
                    options.weekday_start = line.substr(line.find(':') + 1);
                }
                line_counter += 1;
            }
        }
    }
}

void MainWindow::update_stat_panel() {
    /*
     * Calculate number of standard drinks consumed since Sunday.
     */

    double standard_drinks = 0;
    date::weekday filter_day{};

    // Get date to filter on
    if (options.weekday_start == "Monday") {
        filter_day = date::Monday;
    } else if (options.weekday_start == "Tuesday") {
        filter_day = date::Tuesday;
    } else if (options.weekday_start == "Wednesday") {
        filter_day = date::Wednesday;
    } else if (options.weekday_start == "Thursday") {
        filter_day = date::Thursday;
    } else if (options.weekday_start == "Friday") {
        filter_day = date::Friday;
    } else {
        filter_day = date::Sunday;
    }
    // This returns yyyy-mm-dd
    auto todays_date = date::floor<date::days>(std::chrono::system_clock::now());

    // Get date of last filter_day
    date::year_month_day start_date = todays_date - (date::weekday{todays_date} - filter_day);

    // Create the date for the SQL query
    std::string year = date::format("%Y", start_date.year());
    std::string month = date::format("%m", start_date.month());
    std::string day = date::format("%d", start_date.day());
    //std::string query_date = day + "-" + month + "-" + year;
    std::string query_date = year + "-" + month + "-" + day;

    std::vector<Drink> beers_this_week = Database::filter("After Date", query_date, storage);

    for (const auto& beer : beers_this_week) {
        standard_drinks += Calculate::standard_drinks(beer.abv, beer.size);
    }

    update_drinks_this_week(standard_drinks);
    update_standard_drinks_left_this_week(standard_drinks);
    double oz_alc_consumed = update_oz_alcohol_consumed_this_week(beers_this_week);
    update_oz_alcohol_remaining(oz_alc_consumed);
    update_favorite_brewery();
    update_favorite_beer();
    update_favorite_type();
    update_mean_abv();
    update_mean_ibu();
}

void MainWindow::update_drinks_this_week(double standard_drinks) {
    /*
     * Update the standard drinks this week output label.
     */

    std::string drinksThisWeekLabelText = "Std. drinks since " + options.weekday_start + ":";
    ui->drinksThisWeekLabel->setText(QString::fromStdString(drinksThisWeekLabelText));
    if (standard_drinks == 0.0) {
        ui->drinksThisWeekOutput->setText("0.0");
    } else {
        ui->drinksThisWeekOutput->setText(QString::fromStdString(double_to_string(standard_drinks)));
    }
}

void MainWindow::update_standard_drinks_left_this_week(double std_drinks_consumed) {
    /*
     * Update the std. drinks left this week to the amount of std. drinks left this week.
     */

    double std_drinks_left = Calculate::standard_drinks_remaining(options.sex, std_drinks_consumed);
    ui->drinksLeftOutput->setText(QString::fromStdString(double_to_string(std_drinks_left)));

    // Set standard drinks remaining text to red if negative
    if (std_drinks_left < 0) {
        ui->drinksLeftOutput->setStyleSheet("QLabel {color : red;}");
    } else {
        ui->drinksLeftOutput->setStyleSheet("");
    }
}

void MainWindow::reset_table_sort() {
    /*
     * Reset table sort to default, by datetime descending.
     */
    int sort_column = 11;
    std::cout << "Sorting by column: " << ui->drinkLogTable->horizontalHeaderItem(sort_column)->text().toStdString() << std::endl;
    ui->drinkLogTable->sortItems(sort_column, Qt::DescendingOrder);
}

double MainWindow::update_oz_alcohol_consumed_this_week(const std::vector<Drink>& beers_this_week) {
    /*
     * Update the Oz. alcohol consumed output label to the total amount alcohol consumed this week.
     */

    double oz_consumed = 0;

    std::string ozThisWeekLabelText = "Oz. alcohol since " + options.weekday_start + ":";
    ui->ozAlcoholConsumedLabel->setText(QString::fromStdString(ozThisWeekLabelText));

    for (const auto& beer : beers_this_week) {
        double beer_oz_alcohol = (beer.abv/100) * beer.size;
        oz_consumed += beer_oz_alcohol;
    }

    if (oz_consumed == 0.0) {
        ui->ozAlcoholConsumedOutput->setText("0.0");
    } else {
        ui->ozAlcoholConsumedOutput->setText(QString::fromStdString(double_to_string(oz_consumed)));
    }

    return oz_consumed;
}

void MainWindow::update_oz_alcohol_remaining(double oz_alcohol_consumed) {
    /*
     * Update the OZ. alcohol remaining label text to the amount of alcohol remaining.
     */

    double oz_alcohol_remaining = Calculate::oz_alcohol_remaining(options.sex, oz_alcohol_consumed);
    ui->ozAlcoholRemainingOutput->setText(QString::fromStdString(double_to_string(oz_alcohol_remaining)));

    // Set oz alcohol remaining text to red if negative
    if (oz_alcohol_remaining < 0) {
        ui->ozAlcoholRemainingOutput->setStyleSheet("QLabel {color : red;}");
    } else {
        ui->ozAlcoholRemainingOutput->setStyleSheet("");
    }
}

void MainWindow::update_favorite_brewery() {
    /*
     * Update the favorite brewery text label to the most common beer in the database.
     */

    std::string fave_brewery = Calculate::favorite_producer(storage);
    ui->favoriteBreweryOutput->setText(QString::fromStdString(fave_brewery));
}

void MainWindow::update_favorite_beer() {
    /*
     * Update the favorite beer text label to the most common beer in the database.
     */

    std::string fave_beer = Calculate::favorite_beer(storage);
    ui->favoriteBeerOutput->setText(QString::fromStdString(fave_beer));
}

void MainWindow::update_mean_abv() {
    /*
     * Update the mean ABV text label to the mean ABV of all beers in the database.
     */

    std::string mean_abv = double_to_string(Calculate::mean_abv(storage));
    if (mean_abv == "nan") {
        mean_abv = " ";
    }
    ui->avgAbvDrinkOutput->setText(QString::fromStdString(mean_abv));
}

void MainWindow::update_mean_ibu() {
    /*
     * Set the mean IBU text label to the mean IBU of all beers in the database.
     */

    std::string mean_ibu = double_to_string(Calculate::mean_ibu(storage));
    if (mean_ibu == "nan") {
        mean_ibu = " ";
    }
    ui->avgIbuDrinkOutput->setText(QString::fromStdString(mean_ibu));
}

void MainWindow::update_types_producers_on_name_change() {
    /*
     * Change the drink attributes based on the drink selected in the nameInput field.
     */

    std::string alcohol_type = get_current_tab();
    if (alcohol_type == "Beer") {
        if (!ui->beerNameInput->currentText().toStdString().empty()) {
            update_beer_types_producers();
        }
    } else if(alcohol_type == "Liquor") {
        if (!ui->liquorNameInput->currentText().toStdString().empty()) {
            update_liquor_types_producers();
        }
    } else if (alcohol_type == "Wine") {
        if (!ui->wineNameInput->currentText().toStdString().empty()) {
            update_wine_types_producers();
        }
    }
}

void MainWindow::type_input_changed(const QString &) {
    /*
     * Change the beer attributes based on the type of beer selected in the typeInput field.
     */

    std::string alcohol_type = get_current_tab();

    if (alcohol_type == "Beer") {
        update_beer_names_producers();
    } else if (alcohol_type == "Liquor") {
        update_liquor_names_producers();
    } else if (alcohol_type == "Wine") {
        update_wine_names_producers();
    }

    // Update fields based on newly selected drink
    update_types_producers_on_name_change();
}

void MainWindow::producer_input_changed(const QString&) {
    /*
     *  Change the beer attributes based on the brewery selected in the breweryInput field.
     */

    std::string alcohol_type = get_current_tab();

    if (alcohol_type == "Beer") {
        update_beer_names_types();
    } else if (alcohol_type == "Liquor") {
        update_liquor_names_types();
    } else if (alcohol_type == "Wine") {
        update_wine_names_types();
    }

    // Update fields based on newly selected beer
    update_types_producers_on_name_change();
}

void MainWindow::name_input_changed(const QString&) {
    /*
     * Update fields when a beer name is chosen.
     */

    std::cout << "Name input changed" << std::endl;
    update_types_producers_on_name_change();
}

void MainWindow::update_favorite_type() {
    /*
     * Set the favoriteTypeOutput to the most common beer found in the database.
     */

    std::string fave_type = Calculate::favorite_type(storage);
    ui->favoriteTypeOutput->setText(QString::fromStdString(fave_type));
}

std::string MainWindow::get_latest_notes(const std::string& name, const std::string& alcohol_type) {
    /*
     * Get the latest entered notes for a specific beer.
     * @param name: The name to retrieve the notes for.
     * @return notes: String containing beer notes.
     */

    std::string notes;

    // First, try to get notes at the selected row
    Drink drink = get_drink_at_selected_row();
    notes = drink.notes;

    if (notes.empty() || drink.alcohol_type != get_current_tab()) {
        // Get latest notes entered for the selected drink
        if (ui->tabWidget->currentIndex() == 0) {  // Update beer notes
            notes = Database::get_latest_notes(storage, name, "Beer");
        } else if (ui->tabWidget->currentIndex() == 1) {  // Update liquor notes
            notes = Database::get_latest_notes(storage, name, "Liquor");
        } else if (ui->tabWidget->currentIndex() == 2) {  // Update wine notes
            notes = Database::get_latest_notes(storage, name, "Wine");
        }
    }

    return notes;
}

std::string MainWindow::get_current_tab() {
    /*
     * Convert tabwidgets index to alcohol type.
     * @return alcohol_type: String of Beer, Liquor, or Wine
     */

    std::string alcohol_type;
    if (ui->tabWidget->currentIndex() == 0) {
        alcohol_type = "Beer";
    } else if (ui->tabWidget->currentIndex() == 1) {
        alcohol_type = "Liquor";
    } else if (ui->tabWidget->currentIndex() == 2) {
        alcohol_type = "Wine";
    }

    return alcohol_type;
}

void MainWindow::tab_changed() {
    /*
     * Update notes when tab is changed.
     */

    Drink selected_drink = get_drink_at_selected_row();
    std::string name = selected_drink.name;
    std::string selected_drink_alc_type = selected_drink.alcohol_type;
    std::string new_tab = get_current_tab();

    reset_fields();
    if (new_tab == "Beer") {
        if (!name.empty()) {  // If a current row is selected, update the beer name to that row and get notes
            ui->beerNameInput->setCurrentText(QString::fromStdString(name));
            // When user clicks on beer tab with a liquor or wine selected in the table, clear the selection
            // and go to the beer tab.
            if (new_tab != selected_drink_alc_type) {  // If new tab is different type than selected drink
                ui->drinkLogTable->clearSelection();  // Clear the selection
                ui->tabWidget->setCurrentIndex(0);  // Go to the beer tab
                reset_fields();  // Reset fields to the first beer name, alphabetically
            } else {  // If new tab is the same as the selected drink (E.G. If browsing among beers in table).
                std::string beer_notes_text = get_latest_notes(name, new_tab);
                ui->beerNotesInput->setText(QString::fromStdString(beer_notes_text));
            }
        }
    } else if (new_tab == "Liquor") {
        if (!name.empty()) {
            ui->liquorNameInput->setCurrentText(QString::fromStdString(name));
            if (new_tab != selected_drink_alc_type) {
                ui->drinkLogTable->clearSelection();
                ui->tabWidget->setCurrentIndex(1);
                reset_fields();
            } else {
                std::string liquor_notes_text = get_latest_notes(name, new_tab);
                ui->liquorNotesInput->setText(QString::fromStdString(liquor_notes_text));
            }
        }
    } else if(new_tab == "Wine") {
        if (!name.empty()) {
            ui->wineNameInput->setCurrentText(QString::fromStdString(name));
            if (new_tab != selected_drink_alc_type) {
                ui->drinkLogTable->clearSelection();
                ui->tabWidget->setCurrentIndex(2);
                reset_fields();
            } else {
                std::string wine_notes_text = get_latest_notes(name, new_tab);
                ui->wineNotesInput->setText(QString::fromStdString(wine_notes_text));
            }
        }
    }
}

Drink MainWindow::get_drink_attributes_from_fields() {
    /*
     * Get user inputs and put them into the Drink struct
     * @return drink: A Drink instance containing user-input data.
     */

    std::string alcohol_type = get_current_tab();

    Drink drink;

    if (alcohol_type == "Beer") {
        drink = get_beer_attrs_from_fields(alcohol_type);
    } else if (alcohol_type == "Liquor") {
        drink = get_liquor_attrs_from_fields(alcohol_type);
    } else if (alcohol_type == "Wine") {
        drink = get_wine_attrs_from_fields(alcohol_type);
    } else {
        std::cout << "Somehow got illegal alcohol type." << std::endl;
    }

    return drink;
}

QDate MainWindow::format_date_for_input(const Drink& drink) {
    /*
     * Format date to correct format for use in QDateEdit widget
     * @return date: A formatted QDate.
     */

    return QDate::fromString(QString::fromUtf8(drink.date.c_str()), "yyyy-MM-dd");
}

void MainWindow::clicked_clear_button() {
    /*
     * When user clicks clear button, reset fields and clear table selection.
     */

    ui->drinkLogTable->clearSelection();
    reset_fields();
}

Drink MainWindow::get_drink_at_selected_row() {
    /*
     * Get drink at currently-selected row.
     * @return selected_drink: A Drink object.
     */

    Drink selected_drink;
    QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
    int selection = ui->drinkLogTable->selectionModel()->currentIndex().row();

    if (selection >= 0) {
        std::cout << "Getting row " << selection << " from table." << std::endl;
        int row_to_get = ui->drinkLogTable->item(selection, 9)->text().toUtf8().toInt();
        std::cout << "Getting row " << row_to_get << " from database." << std::endl;
        if (select->isRowSelected(selection))
            ui->deleteRowButton->setEnabled(true);
        else
            ui->deleteRowButton->setDisabled(true);

        selected_drink = Database::read_row(row_to_get, storage);
    }
    return selected_drink;
}

void MainWindow::clear_fields(const std::string& alcohol_type) {
    /*
     * Blank the fields for selected alcohol type.
     */

    // Do not clear names!

    if (alcohol_type == "Beer") {
        //ui->beerBreweryInput->clear();
        ui->beerBreweryInput->setCurrentText("");
        //ui->beerTypeInput->clear();
        ui->beerTypeInput->setCurrentText("");
        //ui->beerSubtypeInput->clear();
        ui->beerSubtypeInput->setCurrentText("");
        ui->beerAbvInput->clear();
        ui->beerIbuInput->clear();
        ui->beerSizeInput->clear();
        ui->beerRatingInput->clear();
        ui->beerNotesInput->clear();
    } else if (alcohol_type == "Liquor") {
        //ui->liquorDistillerInput->clear();
        ui->liquorDistillerInput->setCurrentText("");
        //ui->liquorTypeInput->clear();
        ui->liquorTypeInput->setCurrentText("");
        //ui->liquorSubtypeInput->clear();
        ui->liquorSubtypeInput->setCurrentText("");
        ui->liquorAbvInput->clear();
        ui->liquorSizeInput->clear();
        ui->liquorRatingInput->clear();
        ui->liquorNotesInput->clear();
    } else if (alcohol_type == "Wine") {
        //ui->wineryInput->clear();
        ui->wineryInput->setCurrentText("");
        //ui->wineTypeInput->clear();
        ui->wineTypeInput->setCurrentText("");
        //ui->wineSubtypeInput->clear();
        ui->wineSubtypeInput->setCurrentText("");
        ui->wineVintage->clear();
        ui->wineAbvInput->clear();
        ui->wineRatingInput->clear();
        ui->wineSizeInput->clear();
        ui->wineNotesInput->clear();
    }
}

// LCOV_EXCL_STOP