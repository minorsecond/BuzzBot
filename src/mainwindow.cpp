#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "usersettings.h"
#include "about.h"
#include "calculate.h"
#include "../include/date.h"
#include <iomanip>
#include <boost/filesystem.hpp>
#include <iostream>
#include <QMessageBox>
#include <QStandardPaths>
#include <CoreFoundation/CFBundle.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*
     * Set up the main window
     */

    ui->setupUi(this);

    // Read options and create if the file doesn't exist
    // TODO: Create the settings file within program_options()
    program_options(false);
    program_options(true);

    // Upgrade DB version
    Database::increment_version(storage, 2);
    Database::populate_maker_column();  // Copy brewery column to maker if database version is 2

    // Set size hints
    ui->beerDateInput->setProperty("sizeHint", QVariant(QSizeF(241, 22)));

    // Set current tab to Beer tab
    ui->tabWidget->setCurrentIndex(0);

    // Add menubar items
    auto * preferences_action = new QAction("Preferences");
    auto * about_action = new QAction("About");
    QMenu * app_menu = menuBar()->addMenu("App Menu");
    preferences_action->setMenuRole(QAction::PreferencesRole);
    about_action->setMenuRole(QAction::AboutRole);
    app_menu->addAction(preferences_action);
    app_menu->addAction(about_action);

    // Fixed row height in table
    QHeaderView *verticalHeader = ui->drinkLogTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    ui->drinkLogTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Fix up calendar widget
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
                                  "\tqproperty-icon: url(" + previous_month_arrow + ");\n"
                                  "}\n"
                                  "\n"
                                  "QCalendarWidget QToolButton#qt_calendar_nextmonth \n"
                                  "{\n"
                                  "\tqproperty-icon: url(" + next_month_arrow + ");\n"
                                  "}";

    ui->beerDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
    ui->liquorDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
    ui->wineDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));

    Database::write_db_to_disk(storage);

    update_stat_panel();

    // Set up button and input states
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

    // Enable this on release
    ui->drinkLogTable->setRowCount(0);

    // Disable cell editing
    ui->drinkLogTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    update_table();

    // Sort table by date column, by default
    reset_table_sort();

    // Enable table sorting by columns
    ui->drinkLogTable->setSortingEnabled(true);

    // Set table filter options to default values (all)
    ui->filterCategoryInput->addItem("None");
    ui->filterCategoryInput->setCurrentText("None");
    ui->filterCategoryInput->addItem("Name");
    ui->filterCategoryInput->addItem("Type");
    ui->filterCategoryInput->addItem("Subtype");
    ui->filterCategoryInput->addItem("Maker");
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
    QHeaderView* drink_log_header = ui->drinkLogTable->horizontalHeader();
    drink_log_header->setSectionResizeMode(1, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(2, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(3, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(4, QHeaderView::Stretch);

    update_beer_fields();

    // Disconnect corner button so that we can use it for our own method
    auto *corner_button = ui->drinkLogTable->findChild<QAbstractButton*>();
    if (corner_button) {
        corner_button->disconnect();
    }

    // Slot connections
    connect(corner_button, SIGNAL(clicked()), this, SLOT(reset_table_sort()));
    connect(ui->drinkLogTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection&)),
            this, SLOT(populate_fields(const QItemSelection &, const QItemSelection &)));
    connect(ui->filterCategoryInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(enable_filter_text(const QString&)));
    connect(ui->filterTextInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changed_filter_text(const QString&)));
    connect(ui->submitRowButton, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
    connect(ui->clearFieldsButton, SIGNAL(clicked()), this, SLOT(reset_fields()));
    connect(ui->deleteRowButton, SIGNAL(clicked()), this, SLOT(delete_row()));
    connect(preferences_action, SIGNAL(triggered()), this, SLOT(open_user_settings()));
    connect(about_action, SIGNAL(triggered()), this, SLOT(open_about_dialog()));
    connect(ui->beerNameInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(name_input_changed(const QString&)));
    connect(ui->beerTypeInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(type_input_changed(const QString&)));
    connect(ui->beerBreweryInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(brewery_input_changed(const QString&)));

    // Update fields to match beer that comes first alphabetically
    reset_fields();
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

    int drink_year;
    int drink_month;
    int drink_day;
    std::string drink_name;
    std::string beer_type;
    std::string beer_subtype;
    std::string maker;
    double abv;
    double beer_ibu;
    int drink_size;
    int rating;
    std::string notes;

    // Get current tab selected
    std::string alcohol_type;
    int selected_tab_index = ui->tabWidget->currentIndex();
    if (selected_tab_index == 0) {
        alcohol_type = "Drink";
    } else if (selected_tab_index == 1) {
        alcohol_type = "Liquor";
    } else if (selected_tab_index == 2) {
        alcohol_type = "Wine";
    }

    if (alcohol_type == "Drink") {
        drink_year = ui->beerDateInput->date().year();
        drink_month = ui->beerDateInput->date().month();
        drink_day = ui->beerDateInput->date().day();
        drink_name = ui->beerNameInput->currentText().toStdString();
        beer_type = ui->beerTypeInput->currentText().toStdString();
        beer_subtype = ui->beerSubtypeInput->currentText().toStdString();
        maker = ui->beerBreweryInput->currentText().toStdString();
        beer_ibu = ui->beerIbuInput->value();
        abv = ui->beerAbvInput->value();
        drink_size = ui->beerSizeInput->value();
        rating = ui->beerRatingInput->value();
        notes = ui->beerNotesInput->toPlainText().toStdString();
    }

    // Prevent blank submissions
    if (drink_name.empty() || abv == 0.0) {
        QMessageBox::critical(nullptr, "Error", "Please enter beer name and ABV.");
    } else {
        Drink beer{
            -1,
            drink_year,
            drink_month,
            drink_day,
            drink_name,
            beer_type,
            beer_subtype,
            "deprecated",
            maker,
            abv,
            beer_ibu,
            drink_size,
            rating,
            notes,
            alcohol_type
        };

        // Handle updating existing rows
        QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
        if (select->hasSelection()) {
            // Get the selected row
            int selection = select->selectedRows().at(0).row();
            int row_to_update = ui->drinkLogTable->item(selection, 9)->text().toUtf8().toInt();

            // Get the existing timestamp
            std::string timestamp = ui->drinkLogTable->item(selection, 10)->text().toStdString();
            std::cout << "Updating row " << row_to_update << "Timestamp: " << timestamp << std::endl;

            // Update the variables in the beer struct
            beer.id = row_to_update;
            beer.timestamp = timestamp;
            Database::update(storage, beer);
        } else {
            // New row. Get a new timestamp
            std::string timestamp = storage.select(sqlite_orm::datetime("now")).front();
            beer.timestamp = timestamp;
            Database::write(beer, storage);
        }
        update_table();
        if (selected_rows.empty()) {
            reset_fields();  // Reset fields if not updating a row
        }
        update_beer_fields();
        update_stat_panel();
    }
}

void MainWindow::reset_fields() {
    /*
     * Clear user entry fields and table selection for entering a new beer.
     */

    std::string beer_notes;
    std::string liquor_notes;
    std::string wine_notes;

    std::cout << "clearing fields" << std::endl;
    ui->drinkLogTable->clearSelection();
    update_beer_fields();
    update_fields_on_beer_name();

    // Set notes to the notes for beer in the name input
    beer_notes = get_latest_notes(ui->beerNameInput->currentText().toStdString());
    ui->beerNotesInput->setText(QString::fromStdString(beer_notes));

    // Set datepicker to today's date
    QDate todays_date = QDate::currentDate();
    ui->beerDateInput->setDate(todays_date);
}

void MainWindow::update_table() {
    /*
     * Populate the table with data from the database.
     */

    // Temporarily sort by database ID to fix issues with blank rows
    ui->drinkLogTable->sortItems(9, Qt::AscendingOrder);

    std::string filter_category = ui->filterCategoryInput->currentText().toStdString();
    std::string filter_text = ui->filterTextInput->currentText().toStdString();

    std::vector<Drink> beers = Database::filter(filter_category, filter_text, storage);

    ui->drinkLogTable->setRowCount(0);
    for (const auto& beer : beers) {
        int table_row_num = ui->drinkLogTable->rowCount();
        ui->drinkLogTable->insertRow(table_row_num);
        QDate date = QDate(beer.drink_year, beer.drink_month, beer.drink_day);
        auto *date_qtw = new QTableWidgetItem;
        auto *name = new QTableWidgetItem(beer.name.c_str());
        auto *type = new QTableWidgetItem(beer.type.c_str());
        auto *subtype = new QTableWidgetItem(beer.subtype.c_str());
        auto *brewery = new QTableWidgetItem(beer.producer.c_str());
        auto *abv = new QTableWidgetItem(double_to_string(beer.abv).c_str());
        auto *ibu = new QTableWidgetItem(double_to_string(beer.ibu).c_str());
        auto *size = new QTableWidgetItem(double_to_string(beer.size).c_str());
        auto *rating = new QTableWidgetItem(std::to_string(beer.rating).c_str());
        auto *id = new QTableWidgetItem;
        auto *timestamp = new QTableWidgetItem(beer.timestamp.c_str());

        // Sort ID numerically
        id->setData(Qt::DisplayRole, beer.id);
        date_qtw->setData(Qt::DisplayRole, date);

        std::string notes = beer.notes;

        ui->drinkLogTable->setItem(table_row_num, 0, date_qtw);
        ui->drinkLogTable->setItem(table_row_num, 1, name);
        ui->drinkLogTable->setItem(table_row_num, 2, type);
        ui->drinkLogTable->setItem(table_row_num, 3, subtype);
        ui->drinkLogTable->setItem(table_row_num, 4, brewery);
        ui->drinkLogTable->setItem(table_row_num, 5, abv);
        ui->drinkLogTable->setItem(table_row_num, 6, ibu);
        ui->drinkLogTable->setItem(table_row_num, 7, size);
        ui->drinkLogTable->setItem(table_row_num, 8, rating);
        ui->drinkLogTable->setItem(table_row_num, 9, id);
        ui->drinkLogTable->setItem(table_row_num, 10, timestamp);
    }
    reset_table_sort();
}

std::string MainWindow::double_to_string(double input_double) {
    /*
     * Convert a double to a string with 1 decimal value.
     * @param input_double: Double value that should be converted.
     */

    double purchase_price = std::ceil(input_double * 100.0) / 100.0;
    std::ostringstream price_stream;
    price_stream << purchase_price;

    return price_stream.str();
}

void MainWindow::populate_fields(const QItemSelection &, const QItemSelection &) {
    /*
     * Populate user entry fields when user clicks on a row in the table.
     */

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

        Drink beer = Database::read_row(row_to_get, storage);

        std::string notes = get_latest_notes(beer.name);

        std::ostringstream month_padded;
        std::ostringstream day_padded;

        month_padded << std::setw(2) << std::setfill('0') << beer.drink_month;
        day_padded << std::setw(2) << std::setfill('0') << beer.drink_day;
        std::string date_from_db = day_padded.str() + "/" + month_padded.str() + "/" + std::to_string(beer.drink_year);
        QDate date = QDate::fromString(QString::fromUtf8(date_from_db.c_str()), "dd/MM/yyyy");

        ui->beerDateInput->setDate(date);
        ui->beerNameInput->setCurrentText(beer.name.c_str());
        ui->beerTypeInput->setCurrentText(beer.type.c_str());
        ui->beerSubtypeInput->setCurrentText(beer.subtype.c_str());
        ui->beerBreweryInput->setCurrentText(beer.producer.c_str());
        ui->beerAbvInput->setValue(beer.abv);
        ui->beerIbuInput->setValue(beer.ibu);
        ui->beerSizeInput->setValue(beer.size);
        ui->beerRatingInput->setValue(beer.rating);
        ui->beerNotesInput->setText(notes.c_str());
    } else {
        std::cout << "Empty table." << std::endl;
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
}

void MainWindow::populate_filter_menus(const std::string& filter_type) {
    /*
     * Populate the filter menus depending on user selection.
     * @param filter type: Type of filter to use. Options in beer name (name), beer type (type) and brewery.
     */

    std::set<QString> beer_names;
    std::set<QString> beer_types;
    std::set<QString> beer_subtypes;
    std::set<QString> breweries;
    std::set<QString> ratings;

    // This fixes crashes when changing filters with rows selected.
    QSignalBlocker filterTextInputSignalBlocker(ui->filterTextInput);

    std::vector<Drink> all_beers = Database::read(Database::path(), storage);

    ui->filterTextInput->clear();

    // Add items to the sets
    for (const auto& beer : all_beers) {
        QString beer_name = QString::fromStdString(beer.name);
        QString beer_type = QString::fromStdString(beer.type);
        QString beer_subtype = QString::fromStdString(beer.subtype);
        QString brewery = QString::fromStdString(beer.producer);
        QString rating = QString::fromStdString(std::to_string(beer.rating));

        beer_names.insert(beer_name);
        beer_types.insert(beer_type);
        beer_subtypes.insert(beer_subtype);
        breweries.insert(brewery);
        ratings.insert(rating);
    }

    if (filter_type == "Name") {
        for (const auto& name : beer_names) {
            ui->filterTextInput->addItem(name);
        }
    } else if (filter_type == "Type") {
        for (const auto& type : beer_types) {
            ui->filterTextInput->addItem(type);
        }
    } else if (filter_type == "Subtype") {
        for (const auto& subtype : beer_subtypes) {
            if (!subtype.isEmpty()) {
                ui->filterTextInput->addItem(subtype);
            }
        }
    } else if (filter_type == "Brewery") {
        for (const auto& brewery : breweries) {
            ui->filterTextInput->addItem(brewery);
        }
    } else if (filter_type == "Rating") {
        for (const auto& rating : ratings) {
            ui->filterTextInput->addItem(rating);
        }
    }
}

void MainWindow::enable_filter_text(const QString&) {
    /*
     * Enable the filter text combobox when user selects anything other than None in the filter category box.
     */

    if (ui->filterCategoryInput->currentText().toStdString() == "None")
        ui->filterTextInput->setDisabled(true);
    else
        ui->filterTextInput->setEnabled(true);

    std::string filter_type = ui->filterCategoryInput->currentText().toStdString();
    populate_filter_menus(filter_type);
    update_table();
}

void MainWindow::changed_filter_text(const QString &) {
    /*
     * Update the table when user selects a value from the filterText combobox.
     */

    update_table();
}

void MainWindow::update_beer_fields() {
    /*
     * Read rows in the DB and populate the brewery, type, and name dropdowns with unique values.
     */

    std::set<QString> breweries;
    std::set<QString> types;
    std::set<QString> names;
    std::vector<Drink> all_beers = Database::read(Database::path(), storage);

    // Block signals to avoid crashing
    QSignalBlocker brewery_signal_blocker(ui->beerBreweryInput);
    QSignalBlocker type_signal_blocker(ui->beerTypeInput);
    QSignalBlocker name_signal_blocker(ui->beerNameInput);

    ui->beerBreweryInput->clear();
    ui->beerTypeInput->clear();
    ui->beerNameInput->clear();

    for (const auto& beer : all_beers) {
        QString brewery_name = QString::fromStdString(beer.producer);
        QString beer_type = QString::fromStdString(beer.type);
        QString beer_name = QString::fromStdString(beer.name);

        breweries.insert(brewery_name);
        types.insert(beer_type);
        names.insert(beer_name);
    }

    for (const auto& brewery : breweries) {
        ui->beerBreweryInput->addItem(brewery);
    }

    for (const auto& type : types) {
        ui->beerTypeInput->addItem(type);
    }

    for (const auto& name : names) {
        ui->beerNameInput->addItem(name);
    }
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

    std::cout << "Opening user settings." << std::endl;
    UserSettings user_settings = UserSettings(nullptr, options);
    user_settings.setModal(true);
    if (user_settings.exec() == QDialog::Accepted) {
        options.sex = user_settings.get_sex();
        options.weekday_start = user_settings.get_weekday_start();
        update_stat_panel();
        std::cout << "Sex: " << options.sex << ", Weekday starts on " << options.weekday_start << std::endl;
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

    std::string settings_path = directory + "/beertabs_settings.conf";

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

    std::cout << "Stats filter day: " << options.weekday_start << std::endl;

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
    std::cout << "Last filter day: " << start_date << std::endl;

    // Create the date for the SQL query
    std::string year = date::format("%Y", start_date.year());
    std::string month = date::format("%m", start_date.month());
    std::string day = date::format("%d", start_date.day());
    std::string query_date = day + "/" + month + "/" + year;

    std::vector<Drink> beers_this_week = Database::filter("After Date", query_date, storage);

    for (const auto& beer : beers_this_week) {
        standard_drinks += Calculate::standard_drinks(beer.abv, beer.size);
    }

    // TODO: refactor this
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

    ui->drinkLogTable->sortItems(0, Qt::DescendingOrder);
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

    std::string fave_brewery = Calculate::favorite_brewery(storage);
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

void MainWindow::name_input_changed(const QString&) {
    /*
     * Change the beer attributes based on the beer selected in the nameInput field.
     */
    update_fields_on_beer_name();
}

void MainWindow::type_input_changed(const QString &) {
    /*
     * Change the beer attributes based on the type of beer selected in the typeInput field.
     */

    std::string input_type = ui->beerTypeInput->currentText().toStdString();
    std::cout << input_type << std::endl;
    std::vector<Drink> selected_beers = Database::get_beers_by_type(storage, input_type);
    std::set<QString> beer_names;
    std::set<QString> brewery_names;

    // This fixes crashes when changing with rows selected.
    QSignalBlocker name_input_signal_blocker(ui->beerNameInput);
    QSignalBlocker brewery_input_signal_blocker(ui->beerBreweryInput);

    ui->beerAbvInput->setValue(0.0);
    ui->beerIbuInput->setValue(0.0);
    ui->beerSizeInput->setValue(0);
    ui->beerRatingInput->setValue(0);
    ui->beerNameInput->clear();
    ui->beerBreweryInput->clear();

    for (const auto& selected_beer : selected_beers) {
        beer_names.insert(QString::fromStdString(selected_beer.name));
        brewery_names.insert(QString::fromStdString(selected_beer.producer));
    }

    for (const auto& brewery : brewery_names) {
        ui->beerBreweryInput->addItem(brewery);
    }

    for (const auto& beer : beer_names) {
        ui->beerNameInput->addItem(beer);
    }

    // Update fields based on newly selected beer
    update_fields_on_beer_name();
}

void MainWindow::brewery_input_changed(const QString&) {
    /*
     *  Change the beer attributes based on the brewery selected in the breweryInput field.
     */

    std::string input_brewery = ui->beerBreweryInput->currentText().toStdString();
    std::vector<Drink> selected_beers = Database::get_beers_by_brewery(storage, input_brewery);
    std::set<QString> beer_names;
    std::set<QString> types;

    // This fixes crashes when changing with rows selected.
    QSignalBlocker name_input_signal_blocker(ui->beerNameInput);
    QSignalBlocker type_input_signal_blocker(ui->beerTypeInput);

    ui->beerAbvInput->setValue(0.0);
    ui->beerIbuInput->setValue(0.0);
    ui->beerSizeInput->setValue(0);
    ui->beerRatingInput->setValue(0);
    ui->beerNameInput->clear();
    ui->beerTypeInput->clear();

    for (const auto& selected_beer : selected_beers) {
        beer_names.insert(QString::fromStdString(selected_beer.name));
        types.insert(QString::fromStdString(selected_beer.type));
    }

    for (const auto& name : beer_names) {
        ui->beerNameInput->addItem(name);
    }

    for (const auto& beer_type : types) {
        ui->beerTypeInput->addItem(beer_type);
    }

    // Update fields based on newly selected beer
    update_fields_on_beer_name();
}

void MainWindow::update_fields_on_beer_name() {
    /*
     * Update fields when a beer name is chosen.
     */

    std::string beer_name = ui->beerNameInput->currentText().toStdString();

    if (!beer_name.empty()) {
        // This fixes crashes when changing with rows selected.
        QSignalBlocker type_input_signal_blocker(ui->beerTypeInput);
        QSignalBlocker brewery_input_signal_blocker(ui->beerBreweryInput);

        std::string input_beer = ui->beerNameInput->currentText().toStdString();
        Drink selected_beer = Database::get_beer_by_name(storage, input_beer);
        std::string beer_type = selected_beer.type;
        std::string brewery = selected_beer.producer;
        double abv = selected_beer.abv;
        double ibu = selected_beer.ibu;
        int size = selected_beer.size;
        int rating = selected_beer.rating;

        ui->beerTypeInput->setCurrentText(QString::fromStdString(beer_type));
        ui->beerBreweryInput->setCurrentText(QString::fromStdString(brewery));
        ui->beerAbvInput->setValue(abv);
        ui->beerIbuInput->setValue(ibu);
        ui->beerSizeInput->setValue(size);
        ui->beerRatingInput->setValue(rating);
    }

    // Set notes to the notes for beer in the name input
    std::string notes;
    notes = get_latest_notes(ui->beerNameInput->currentText().toStdString());
    ui->beerNotesInput->setText(QString::fromStdString(notes));
}

void MainWindow::update_favorite_type() {
    /*
     * Set the favoriteTypeOutput to the most common beer found in the database.
     */

    std::string fave_type = Calculate::favorite_type(storage);
    ui->favoriteTypeOutput->setText(QString::fromStdString(fave_type));
}

std::string MainWindow::get_latest_notes(const std::string& name) {
    /*
     * Get the latest entered notes for a specific beer.
     * @param name: The name to retrieve the notes for.
     * @return notes: String containing beer notes.
     */

    std::string notes;

    // Get latest notes entered for the selected drink
    // TODO: Refactor the filter code. This whole function could be reduced by allowing filtering on name and alc type.
    std::vector<Drink> drinks_by_name = Database::filter("Name", name, storage);
    unsigned temp_id = 0;
    if (ui->tabWidget->currentIndex() == 0) {  // Update beer notes
        for (const auto& beer_for_notes : drinks_by_name) {
            if (beer_for_notes.id > temp_id) {
                temp_id = beer_for_notes.id;
                if (!beer_for_notes.notes.empty()) {
                    notes = beer_for_notes.notes;
                }
            }
        }
    } else if (ui->tabWidget->currentIndex() == 1) {  // Update liquor notes
        for (const auto& liquor_for_notes : drinks_by_name) {
            if (liquor_for_notes.id > temp_id) {
                temp_id = liquor_for_notes.id;
                if (!liquor_for_notes.notes.empty()) {
                    notes = liquor_for_notes.notes;
                }
            }
        }
    } else if (ui->tabWidget->currentIndex() == 2) {  // Update wine notes
        for (const auto& wine_for_notes : drinks_by_name) {
            if (wine_for_notes.id > temp_id) {
                temp_id = wine_for_notes.id;
                if (!wine_for_notes.notes.empty()) {
                    notes = wine_for_notes.notes;
                }
            }
        }
    }

    return notes;
}
