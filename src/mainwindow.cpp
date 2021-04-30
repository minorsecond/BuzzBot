#include "mainwindow.h"
#include "usersettings.h"
#include "about.h"
#include "standard_drink_calculator.h"
#include "confirm_dialog.h"
#include "exporters.h"
#include "calculate.h"
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <QComboBox>
#include <QMessageBox>
#include <QStandardPaths>
#include <CoreFoundation/CFBundle.h>
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*
     * Set up the main window
     */

    ui->setupUi(this);

    // Select entire row vs just a cell
    ui->drinkLogTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Read options and create if the file doesn't exist
    program_options(false);
    program_options(true);

    // Change unit text depending on settings
    if (options.units == "Metric") {
        ui->volAlcoholRemainingLabel->setText("ml. Alcohol Remaining:");
    }

    // Upgrade DB version
    // DB Version 7 removes extra year, month, date columns
    Database::increment_version(storage, 7);

    add_menubar_items();

    if (options.units == "Metric") {
        ui->beerSizeLabel->setText("Size (ml)");
        ui->liquorSizeLabel->setText("Size (ml)");
        ui->wineSizeLabel->setText("Size (ml)");
    } else {
        ui->beerSizeLabel->setText("Size (oz)");
        ui->liquorSizeLabel->setText("Size (oz)");
        ui->wineSizeLabel->setText("Size (oz)");
    }

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

    // Rounded rect frames
    ui->frame->setStyleSheet("QWidget#frame{ border: 1px solid grey; border-radius: 6px; }");
    ui->frame_2->setStyleSheet("QWidget#frame_2{ border: 1px solid grey; border-radius: 6px; }");
    ui->frame_4->setStyleSheet("QWidget#frame_4{ border: 1px solid grey; border-radius: 6px; }");

    // Sort table by date column, by default
    reset_table_sort();
    configure_table();
    add_slot_connections();

    // Update fields to match beer that comes first alphabetically
    reset_fields();

    // Start the stat pane update stat_update_timer
    auto *stats_timer = new QTimer(this);
    connect(stats_timer, &QTimer::timeout, this, &MainWindow::update_stats_if_new_day);
    stats_timer->start(5000);
}

void MainWindow::add_menubar_items() {
    /*
     * Add items to the system menubar.
     */

    auto * preferences_action = new QAction("Preferences");
    auto * about_action = new QAction("About");
    auto * export_action = new QAction("Export...");
    auto * calc_std_drinks = new QAction("Calculate Std. Drinks...");
    QMenu * app_menu = menuBar()->addMenu("App Menu");
    preferences_action->setMenuRole(QAction::PreferencesRole);
    about_action->setMenuRole(QAction::AboutRole);
    export_action->setMenuRole(QAction::ApplicationSpecificRole);
    calc_std_drinks->setMenuRole(QAction::ApplicationSpecificRole);
    app_menu->addAction(preferences_action);
    app_menu->addAction(about_action);
    app_menu->addAction(export_action);
    app_menu->addAction(calc_std_drinks);

    connect(preferences_action, &QAction::triggered, this, &MainWindow::open_user_settings);
    connect(about_action, &QAction::triggered, this, &MainWindow::open_about_dialog);
    connect(export_action, &QAction::triggered, this, &MainWindow::open_export_dialog);
    connect(calc_std_drinks, &QAction::triggered, this, &MainWindow::open_std_drink_calculator);
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
    ui->drinkLogTable->setColumnWidth(0, 75); // Date
    ui->drinkLogTable->setColumnWidth(1, 428); // Name
    ui->drinkLogTable->setColumnWidth(2, 200); // Type
    ui->drinkLogTable->setColumnWidth(3, 200); // Subtype
    ui->drinkLogTable->setColumnWidth(4, 428); // Producer
    ui->drinkLogTable->setColumnWidth(5, 50); // ABV
    ui->drinkLogTable->setColumnWidth(6, 50); // IBU
    ui->drinkLogTable->setColumnWidth(7, 55); // Size
    ui->drinkLogTable->setColumnWidth(8, 55); // Rating
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
    connect(ui->liquorNameInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::name_input_changed);
    connect(ui->liquorNameInput, &QComboBox::editTextChanged, this, &MainWindow::name_input_changed);
    connect(ui->wineNameInput, QOverload<const QString &>::of(&QComboBox::textActivated), this, &MainWindow::name_input_changed);
    connect(ui->wineNameInput, &QComboBox::editTextChanged, this, &MainWindow::name_input_changed);
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
     * Create a drink from user input and write it to the database.
     */

    QItemSelectionModel *selection_model = ui->drinkLogTable->selectionModel();
    QModelIndexList selected_rows = selection_model->selectedRows();

    // Get current tab selected
    std::string alcohol_type = get_current_tab();
    Drink entered_drink = get_drink_attributes_from_fields();

    // Prevent blank submissions
    if (entered_drink.name.empty() || entered_drink.abv == 0.0 || entered_drink._size == 0.0) {
        QMessageBox::critical(nullptr, "Error", "Please enter drink name, ABV, and size.");
    } else {
        // Handle updating existing rows
        QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
        (select->hasSelection()) ? update_selected_row(select, entered_drink) : add_new_row(entered_drink);

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

void MainWindow::populate_fields(const QItemSelection &, const QItemSelection &) {
    /*
     * Populate user entry fields when user clicks on a row in the table.
     * @param QItemSelection: A QItemSelection.
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
    }
}

void MainWindow::open_about_dialog() {
    /*
     * Open the about dialog which contains author and license information.
     */

    auto *about_dialog = new About();
    about_dialog->setModal(false);
    about_dialog->show();
}

void MainWindow::open_export_dialog() {
    /*
     * Open the export dialog.
     */

    QString desktop_path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0);
    QString preferred_path = desktop_path + "/buzzbot.csv";

    QString filter = "CSV Files (*.csv)";
    QString filepath_qstring = QFileDialog::getSaveFileName(this, "Save File", preferred_path, filter, &filter);

    std::vector<Drink> all_drinks = storage.get_all<Drink>();
    exporters::to_csv(all_drinks, filepath_qstring.toStdString(), options.units);
}

void MainWindow::open_user_settings() {
    /*
     * Open the user settings dialog box, where users can enter their sex and the day which the week should begin on.
     */

    UserSettings user_settings = UserSettings(options, std_drink_standards);
    user_settings.setModal(true);
    std::string std_drink_size = options.std_drink_size;
    if (user_settings.exec() == QDialog::Accepted) {  // Update settings when OK button is clicked
        options.sex = user_settings.get_sex();
        options.date_calculation_method = user_settings.get_date_calculation_method();
        options.weekday_start = user_settings.get_weekday_start();
        options.limit_standard = user_settings.get_limit_standard();
        options.weekly_limit = user_settings.get_drink_limit();
        options.units = user_settings.get_units();
        std_drink_size = Calculate::double_to_string(user_settings.get_std_drink_size());
        options.std_drink_country = user_settings.get_std_drink_country();
        update_stat_panel();
    }

    program_options(true);
    update_table();
    update_stat_panel();
    update_types_and_producers();

    if (options.units == "Metric") {
        ui->beerSizeLabel->setText("Size (ml)");
        ui->liquorSizeLabel->setText("Size (ml)");
        ui->wineSizeLabel->setText("Size (ml)");
        options.std_drink_size = Calculate::double_to_string(Calculate::ml_to_oz(std::stod(std_drink_size)));
    } else {
        ui->beerSizeLabel->setText("Size (oz)");
        ui->liquorSizeLabel->setText("Size (oz)");
        ui->wineSizeLabel->setText("Size (oz)");
        options.std_drink_size = std_drink_size;
    }

    std::cout << std_drink_size << std::endl;
}

std::string MainWindow::settings_path() {
    /*
     * Find database path and create it if it doesn't exist.
     * @return full_path Path where database file should be stored.
     */

    // Find path to application support directory
    std::string directory = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0).toStdString();
    std::string settings_path = directory + "/buzzbot_settings.conf";
    std::filesystem::create_directory(directory);

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
        std::cout << "Writing user settings to " << path << std::endl;
        std::string sex_setting = "sex:" + options.sex;
        std::string start_day = "start_day:" + options.weekday_start;
        std::string date_calculation_method = "date_calculation_method:" + options.date_calculation_method;
        std::string limit_standard = "limit_standard:" + options.limit_standard;
        std::string weekly_limit = "custom_weekly_limit:" + std::to_string(options.weekly_limit);
        std::string units = "units:" + options.units;
        std::string std_drink_size = "std_drink_size:" + options.std_drink_size;
        std::string std_drink_country = "std_drink_country:" + options.std_drink_country;
        std::ofstream out_data;

        if (!out_data) {
            std::cerr << "Error: settings file could not be opened." << std::endl;
            exit(1);
        }

        out_data.open(path);
        out_data << sex_setting + '\n';
        out_data << start_day + '\n';
        out_data << date_calculation_method + '\n';
        out_data << limit_standard + '\n';
        out_data << weekly_limit + '\n';
        out_data << units + '\n';
        out_data << std_drink_size + '\n';
        out_data << std_drink_country + '\n';
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
                } else if (line_counter == 2) { // Third line should be the date calculation method
                    options.date_calculation_method = line.substr(line.find(':') + 1);
                } else if (line_counter == 3) { // Fourth line should be limit standard setting
                    options.limit_standard = line.substr(line.find(':') + 1);
                } else if (line_counter == 4) { // Fifth line should be the weekly limit that is custom set
                    options.weekly_limit = std::stoi(line.substr(line.find(':') + 1));
                } else if (line_counter == 5) { // Sixth line should be the selected units, either Metric or Imperial
                    options.units = line.substr(line.find(':') + 1);
                } else if (line_counter == 6) { // Seventh line should be the std drink size (stored in oz)
                    options.std_drink_size = line.substr(line.find(':') + 1);
                } else if (line_counter == 7) { // Eigth line should be the std drink country
                    options.std_drink_country = line.substr(line.find(':') + 1);
                }
                line_counter += 1;
            }
        }
    }
}

void MainWindow::update_types_and_producers() {
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

void MainWindow::name_input_changed(const QString&) {
    /*
     * Update fields when a drink name is chosen.
     */

    update_types_and_producers();
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
    update_stat_panel();

    reset_fields();
    if (new_tab == "Beer") {
        ui->averageIbuDrinkLabel->setText("Average IBU per beer:");
        if (!name.empty()) {  // If a current row is selected, update the beer name to that row and get notes
            ui->beerNameInput->setCurrentText(QString::fromStdString(name));
            // When user clicks on beer tab with a liquor or wine selected in the table, clear the selection
            // and go to the beer tab.
            if (new_tab != selected_drink_alc_type) {  // If new tab is different type than selected drink
                ui->drinkLogTable->clearSelection();  // Clear the selection
                ui->tabWidget->setCurrentIndex(0);  // Go to the beer tab
                reset_fields();  // Reset fields to the first beer name, alphabetically
            } else {  // If new tab is the same as the selected drink (E.G. If browsing among beers in table).
                std::string beer_notes_text = get_latest_notes(name);
                ui->beerNotesInput->setText(QString::fromStdString(beer_notes_text));
            }
        }
    } else if (new_tab == "Liquor") {
        ui->averageIbuDrinkLabel->setText("");
        ui->avgIbuDrinkOutput->setText("");
        if (!name.empty()) {
            ui->liquorNameInput->setCurrentText(QString::fromStdString(name));
            if (new_tab != selected_drink_alc_type) {
                ui->drinkLogTable->clearSelection();
                ui->tabWidget->setCurrentIndex(1);
                reset_fields();
            } else {
                std::string liquor_notes_text = get_latest_notes(name);
                ui->liquorNotesInput->setText(QString::fromStdString(liquor_notes_text));
            }
        }
    } else if(new_tab == "Wine") {
        ui->averageIbuDrinkLabel->setText("");
        ui->avgIbuDrinkOutput->setText("");
        if (!name.empty()) {
            ui->wineNameInput->setCurrentText(QString::fromStdString(name));
            if (new_tab != selected_drink_alc_type) {
                ui->drinkLogTable->clearSelection();
                ui->tabWidget->setCurrentIndex(2);
                reset_fields();
            } else {
                std::string wine_notes_text = get_latest_notes(name);
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

    // Size values are converted to/from ml and oz in add_new_row()
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

void MainWindow::clear_fields(const std::string& alcohol_type) {
    /*
     * Blank the fields for selected alcohol type.
     */

    // Do not clear names!

    QItemSelectionModel *selection_model = ui->drinkLogTable->selectionModel();
    QModelIndexList selected_rows = selection_model->selectedRows();

    if (selected_rows.empty()) {
        if (alcohol_type == "Beer") {
            ui->beerAbvInput->clear();
            ui->beerIbuInput->clear();
            ui->beerSizeInput->clear();
            ui->beerRatingInput->clear();
            ui->beerNotesInput->clear();
        } else if (alcohol_type == "Liquor") {
            ui->liquorAbvInput->clear();
            ui->liquorSizeInput->clear();
            ui->liquorRatingInput->clear();
            ui->liquorNotesInput->clear();
        } else if (alcohol_type == "Wine") {
            ui->wineVintage->clear();
            ui->wineAbvInput->clear();
            ui->wineRatingInput->clear();
            ui->wineSizeInput->clear();
            ui->wineNotesInput->clear();
        }
    }
}

void MainWindow::open_std_drink_calculator() const {
    /*
     * Open the standard drink calculator dialog box.
     */

    auto * std_drink_calculator = new StandardDrinkCalc(std::stod(options.std_drink_size), options.units);
    std_drink_calculator->show();
}

date::weekday MainWindow::get_filter_weekday_start() const {
    /*
     * Get filter day from options.
     * @return filter_day: a date object for the filter day.
     */

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

    return filter_day;
}

std::tuple<date::year_month_day, std::string> MainWindow::get_filter_date() {
    /*
     * Get the date and day of week for the filter date specified in the options.
     * @return: Tuple containing the start date (a date::year_month_day object) and weekday name (string).
     */

    date::year_month_day start_date{};
    std::string weekday_name;

    date::weekday filter_day = get_filter_weekday_start();

    // get_local_date returns a string in the form of YYYY-MM-DD
    std::string query_date = get_local_date();

    // Back to date object
    std::tm tm = {};
    std::stringstream ss(query_date);
    ss >> std::get_time(&tm,"%Y-%m-%d");
    auto tp = date::floor<date::days>(std::chrono::system_clock::from_time_t(std::mktime(&tm)));

    std::cout << "The system time is: " << date::format("%Y-%m-%d", tp) << std::endl;

    // Get date of last filter_day
    if (options.date_calculation_method == "Fixed") {
        std::cout << "Using fixed date method" << std::endl;
        start_date = tp - (date::weekday{tp} - filter_day);
        weekday_name = options.weekday_start;
    } else {  // Don't include day 7 days ago.
        std::cout << "Using rolling date method" << std::endl;
        start_date = tp - date::days{6};
        // Get weekday name
        weekday_name = date::format("%A", date::weekday(tp - date::days{7}));
    }

    return std::make_tuple(start_date, weekday_name);
}

void MainWindow::update_stats_if_new_day() {
    /*
     * Update the stats panel if day of the week isn't the same as the date in stats panel.
     */

    std::time_t t = std::time(nullptr);
    std::stringstream ssTp;
    ssTp << std::put_time(std::localtime(&t), "%A");
    std::string weekday_name = ssTp.str();

    if (ui->drinksThisWeekLabel->text().toStdString().find(weekday_name) == std::string::npos) {
        update_stat_panel();
    }
}

std::string MainWindow::format_date(date::year_month_day date) {
    /*
     * Format date for use in DB filter.
     * @return: formated date string.
     */

    std::string year = date::format("%Y", date.year());
    std::string month = date::format("%m", date.month());
    std::string day = date::format("%d", date.day());
    std::string query_date = year + "-" + month + "-" + day;

    return query_date;
}

std::string MainWindow::get_local_date() {
    /*
     * Get date in localtime
     * @return: A string denoting the date in localtime, with the format YYYY-MM-DD
     */

    // Get today's date in local time.
    char query_date[10];
    std::string output;

    auto todays_date = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(todays_date);
    std::tm now_tm = *std::localtime(&now_c);
    std::strftime(query_date, sizeof query_date, "%Y-%m-%d", &now_tm);

    for (char i : query_date) {
        output += std::string(1, i);
    }

    std::cout << "The time is " << output << std::endl;

    return output;
}
