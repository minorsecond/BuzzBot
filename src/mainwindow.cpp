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
    // TODO: Remove the brewery column from database at DB version 3
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
    QHeaderView* drink_log_header = ui->drinkLogTable->horizontalHeader();
    drink_log_header->setSectionResizeMode(1, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(2, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(3, QHeaderView::Stretch);
    drink_log_header->setSectionResizeMode(4, QHeaderView::Stretch);

    update_beer_fields();
    update_liquor_fields();

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
    connect(ui->liquorNameInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(name_input_changed(const QString&)));
    connect(ui->liquorTypeInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(type_input_changed(const QString&)));
    connect(ui->liquorDistillerInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(brewery_input_changed(const QString&)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tab_changed()));

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
     * Clear user entry fields and table selection for entering a new beer.
     */

    std::string beer_notes;
    std::string liquor_notes;
    std::string wine_notes;

    std::string alcohol_type = get_current_tab();

    std::cout << "clearing fields" << std::endl;
    ui->drinkLogTable->clearSelection();

    if (alcohol_type == "Beer") {
        update_beer_fields();
        update_fields_on_drink_name_selected();

        // Set notes to the notes for beer in the name input
        beer_notes = get_latest_notes(ui->beerNameInput->currentText().toStdString(), alcohol_type);
        ui->beerNotesInput->setText(QString::fromStdString(beer_notes));

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->beerDateInput->setDate(todays_date);
    } else if (alcohol_type == "Liquor") {
        update_liquor_fields();
        update_fields_on_drink_name_selected();

        // Set notes to the notes for beer in the name input
        liquor_notes = get_latest_notes(ui->liquorNameInput->currentText().toStdString(), alcohol_type);
        ui->liquorNotesInput->setText(QString::fromStdString(liquor_notes));

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->liquorDateInput->setDate(todays_date);
    } else if (alcohol_type == "Wine") {
        update_beer_fields();  // TODO: Change this to wine update_wine_fields
        update_fields_on_drink_name_selected();

        // Set notes to the notes for beer in the name input
        wine_notes = get_latest_notes(ui->wineNameInput->currentText().toStdString(), alcohol_type);
        ui->wineNotesInput->setText(QString::fromStdString(wine_notes));

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
        auto *producer = new QTableWidgetItem(beer.producer.c_str());
        auto *abv = new QTableWidgetItem(double_to_string(beer.abv).c_str());
        auto *size = new QTableWidgetItem(double_to_string(beer.size).c_str());
        auto *rating = new QTableWidgetItem(std::to_string(beer.rating).c_str());
        auto *id = new QTableWidgetItem;
        auto *timestamp = new QTableWidgetItem(beer.timestamp.c_str());

        // Sort ID numerically
        id->setData(Qt::DisplayRole, beer.id);
        date_qtw->setData(Qt::DisplayRole, date);

        std::string notes = beer.notes;

        // Handle blank IBU
        auto *ibu = new QTableWidgetItem;
        if (beer.ibu == -1.0) {  // -1 denotes no IBU value
            *ibu = QTableWidgetItem("");
        } else {
            *ibu = QTableWidgetItem(double_to_string(beer.ibu).c_str());
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

void MainWindow::populate_beer_fields(const Drink& drink_at_row) {
    /*
     * Populate the beer entry fields if user is on the beer entry tab.
     */

    QDate date = format_date_for_input(drink_at_row);
    // Only update the beer fields if the user is currently on the beer tab
    std::string notes = get_latest_notes(drink_at_row.name, drink_at_row.alcohol_type);
    ui->beerDateInput->setDate(date);
    ui->beerNameInput->setCurrentText(drink_at_row.name.c_str());
    ui->beerTypeInput->setCurrentText(drink_at_row.type.c_str());
    ui->beerSubtypeInput->setCurrentText(drink_at_row.subtype.c_str());
    ui->beerBreweryInput->setCurrentText(drink_at_row.producer.c_str());
    ui->beerAbvInput->setValue(drink_at_row.abv);
    ui->beerIbuInput->setValue(drink_at_row.ibu);
    ui->beerSizeInput->setValue(drink_at_row.size);
    ui->beerRatingInput->setValue(drink_at_row.rating);
    ui->beerNotesInput->setText(notes.c_str());

    // Switch to the beer tab
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::populate_liquor_fields(const Drink& drink_at_row) {
    /*
     * Populate the liquor entry fields if user is on the liquor entry tab.
     */
    QDate date = format_date_for_input(drink_at_row);
    std::string notes = get_latest_notes(drink_at_row.name, drink_at_row.alcohol_type);
    ui->liquorDateInput->setDate(date);
    ui->liquorNameInput->setCurrentText(drink_at_row.name.c_str());
    ui->liquorTypeInput->setCurrentText(drink_at_row.type.c_str());
    ui->liquorSubtypeInput->setCurrentText(drink_at_row.subtype.c_str());
    ui->liquorDistillerInput->setCurrentText(drink_at_row.producer.c_str());
    ui->liquorAbvInput->setValue(drink_at_row.abv);
    ui->liquorSizeInput->setValue(drink_at_row.size);
    ui->liquorRatingInput->setValue(drink_at_row.rating);
    ui->liquorNotesInput->setText(notes.c_str());

    // Switch to the liquor tab
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::populate_wine_fields(const Drink& drink_at_row) {
    /*
     * Populate the wine entry fields if user is on the wine entry tab.
     */

    QDate date = format_date_for_input(drink_at_row);
    std::string notes = get_latest_notes(drink_at_row.name, drink_at_row.alcohol_type);
    ui->wineDateInput->setDate(date);
    ui->wineNameInput->setCurrentText(drink_at_row.name.c_str());
    ui->wineTypeInput->setCurrentText(drink_at_row.type.c_str());
    ui->wineSubtypeInput->setCurrentText(drink_at_row.subtype.c_str());
    ui->wineryInput->setCurrentText(drink_at_row.producer.c_str());
    ui->wineAbvInput->setValue(drink_at_row.abv);
    ui->wineSizeInput->setValue(drink_at_row.size);
    ui->wineRatingInput->setValue(drink_at_row.rating);
    ui->wineNotesInput->setText(notes.c_str());

    // Switch to the liquor tab
    ui->tabWidget->setCurrentIndex(2);
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

        std::string notes;

        Drink drink_at_row = Database::read_row(row_to_get, storage);

        // Set up the date string
        QDate date = format_date_for_input(drink_at_row);

        if (drink_at_row.alcohol_type == "Beer") {
            populate_beer_fields(drink_at_row);
        } else if (drink_at_row.alcohol_type == "Liquor") {  // TODO: Refactor this
            populate_liquor_fields(drink_at_row);
        } else {
            std::cout << "Not updating fields because not in correct tab." << std::endl;
            std::cout << "On tab " << get_current_tab() << std::endl;
            std::cout << "Alcohol type: " << drink_at_row.alcohol_type << std::endl;
        }
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

    // Update the fields to reflect deleted row
    update_beer_fields();
    update_liquor_fields();
}

std::vector<std::set<QString>> MainWindow::generate_filter_item_sets() {
    /*
     * Generate sets containing unique filter values.
     * @return filter_values: A vector of sets containing unique values to pass to the filter dropdown.
     */

    std::vector<std::set<QString>> filter_values;

    std::set<QString> drink_names;
    std::set<QString> drink_types;
    std::set<QString> drink_subtypes;
    std::set<QString> producers;
    std::set<QString> ratings;

    ui->filterTextInput->clear();

    // This fixes crashes when changing filters with rows selected.
    QSignalBlocker filterTextInputSignalBlocker(ui->filterTextInput);

    // Add items to the sets
    std::vector<Drink> all_beers = Database::read(Database::path(), storage);
    for (const auto& beer : all_beers) {
        QString drink_name = QString::fromStdString(beer.name);
        QString drink_type = QString::fromStdString(beer.type);
        QString drink_subtype = QString::fromStdString(beer.subtype);
        QString producer = QString::fromStdString(beer.producer);
        QString rating = QString::fromStdString(std::to_string(beer.rating));

        drink_names.insert(drink_name);
        drink_types.insert(drink_type);
        drink_subtypes.insert(drink_subtype);
        producers.insert(producer);
        ratings.insert(rating);
    }
    filter_values.push_back(drink_names);
    filter_values.push_back(drink_types);
    filter_values.push_back(drink_subtypes);
    filter_values.push_back(producers);
    filter_values.push_back(ratings);

    return filter_values;
}

void MainWindow::populate_filter_menus(const std::string& filter_type) {
    /*
     * Populate the filter menus depending on user selection.
     * @param filter type: Type of filter to use. Options in beer name (name), beer type (type) and brewery.
     */

    std::vector<std::set<QString>> filter_values = generate_filter_item_sets();

    if (filter_type == "Name") {
        for (const auto& name : filter_values.at(0)) {
            ui->filterTextInput->addItem(name);
        }
    } else if (filter_type == "Type") {
        for (const auto& type : filter_values.at(1)) {
            ui->filterTextInput->addItem(type);
        }
    } else if (filter_type == "Subtype") {
        for (const auto& subtype : filter_values.at(2)) {
            if (!subtype.isEmpty()) {
                ui->filterTextInput->addItem(subtype);
            }
        }
    } else if (filter_type == "Producer") {
        for (const auto& brewery : filter_values.at(3)) {
            ui->filterTextInput->addItem(brewery);
        }
    } else if (filter_type == "Rating") {
        for (const auto& rating : filter_values.at(4)) {
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
    std::vector<Drink> all_beers = Database::filter("Alcohol Type", "Beer", storage);

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

void MainWindow::name_input_changed(const QString&) {
    /*
     * Change the drink attributes based on the drink selected in the nameInput field.
     */

    //TODO: directly connect the button to the update_fields method.
    update_fields_on_drink_name_selected();
}

void MainWindow::type_input_changed(const QString &) {
    /*
     * Change the beer attributes based on the type of beer selected in the typeInput field.
     */

    std::string alcohol_type = get_current_tab();
    std::set<QString> drink_names;
    std::set<QString> producer_names;

    if (alcohol_type == "Beer") {
        std::string input_type = ui->beerTypeInput->currentText().toStdString();
        std::cout << input_type << std::endl;
        std::vector<Drink> selected_beers = Database::get_beers_by_type(storage, input_type);

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
            drink_names.insert(QString::fromStdString(selected_beer.name));
            producer_names.insert(QString::fromStdString(selected_beer.producer));
        }

        for (const auto& brewery : producer_names) {
            ui->beerBreweryInput->addItem(brewery);
        }

        for (const auto& beer : drink_names) {
            ui->beerNameInput->addItem(beer);
        }
    } else if (alcohol_type == "Liquor") {
        std::string input_type = ui->liquorTypeInput->currentText().toStdString();
        std::vector<Drink> selected_drinks = Database::get_beers_by_type(storage, input_type);

        // This fixes crashes when changing with rows selected.
        QSignalBlocker name_input_signal_blocker(ui->liquorNameInput);
        QSignalBlocker brewery_input_signal_blocker(ui->liquorDistillerInput);

        ui->liquorAbvInput->setValue(0.0);
        ui->liquorSizeInput->setValue(0);
        ui->liquorRatingInput->setValue(0);
        ui->liquorNameInput->clear();
        ui->liquorDistillerInput->clear();

        for (const auto& selected_drink : selected_drinks) {
            drink_names.insert(QString::fromStdString(selected_drink.name));
            producer_names.insert(QString::fromStdString(selected_drink.producer));
        }

        for (const auto& distillery : producer_names) {
            ui->liquorDistillerInput->addItem(distillery);
        }

        for (const auto& drink_name : drink_names) {
            ui->liquorNameInput->addItem(drink_name);
        }
    }

    // Update fields based on newly selected beer
    update_fields_on_drink_name_selected();
}

void MainWindow::brewery_input_changed(const QString&) {
    /*
     *  Change the beer attributes based on the brewery selected in the breweryInput field.
     */

    std::string alcohol_type = get_current_tab();

    if (alcohol_type == "Beer") {
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
    } else if (alcohol_type == "Liquor") {
        std::string input_distillery = ui->liquorDistillerInput->currentText().toStdString();
        std::vector<Drink> selected_drinks = Database::get_beers_by_brewery(storage, input_distillery);
        std::set<QString> liquor_names;
        std::set<QString> types;

        // This fixes crashes when changing with rows selected.
        QSignalBlocker name_input_signal_blocker(ui->liquorNameInput);
        QSignalBlocker type_input_signal_blocker(ui->liquorTypeInput);

        ui->liquorAbvInput->setValue(0.0);
        ui->liquorSizeInput->setValue(0);
        ui->liquorRatingInput->setValue(0);
        ui->liquorNameInput->clear();
        ui->liquorTypeInput->clear();

        for (const auto& selected_drink : selected_drinks) {
            liquor_names.insert(QString::fromStdString(selected_drink.name));
            types.insert(QString::fromStdString(selected_drink.type));
        }

        for (const auto& name : liquor_names) {
            ui->liquorNameInput->addItem(name);
        }

        for (const auto& liquor_type : types) {
            ui->liquorTypeInput->addItem(liquor_type);
        }
    }

    // Update fields based on newly selected beer
    update_fields_on_drink_name_selected();
}

void MainWindow::update_fields_on_drink_name_selected() {
    /*
     * Update fields when a beer name is chosen.
     */

    std::string notes;
    std::string drink_name = ui->beerNameInput->currentText().toStdString();
    std::string alcohol_type = get_current_tab();

    if (!drink_name.empty()) {
        if (alcohol_type == "Beer") {
            // This fixes crashes when changing with rows selected.
            QSignalBlocker type_input_signal_blocker(ui->beerTypeInput);
            QSignalBlocker brewery_input_signal_blocker(ui->beerBreweryInput);

            std::string input_beer = ui->beerNameInput->currentText().toStdString();
            Drink selected_beer = Database::get_drink_by_name(storage, input_beer);
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

            // Set notes to the notes for beer in the name input
            notes = get_latest_notes(ui->beerNameInput->currentText().toStdString(), get_current_tab());
            ui->beerNotesInput->setText(QString::fromStdString(notes));
        } else if(alcohol_type == "Liquor") {
            // This fixes crashes when changing with rows selected.
            QSignalBlocker type_input_signal_blocker(ui->liquorTypeInput);
            QSignalBlocker brewery_input_signal_blocker(ui->liquorDistillerInput);

            std::string input_liquor = ui->liquorNameInput->currentText().toStdString();
            Drink selected_liquor = Database::get_drink_by_name(storage, input_liquor);
            std::string liquor_type = selected_liquor.type;
            std::string liquor_subtype = selected_liquor.subtype;
            std::string producer = selected_liquor.producer;
            double abv = selected_liquor.abv;
            int size = selected_liquor.size;
            int rating = selected_liquor.rating;

            ui->liquorTypeInput->setCurrentText(QString::fromStdString(liquor_type));
            ui->liquorSubtypeInput->setCurrentText(QString::fromStdString(liquor_subtype));
            ui->liquorDistillerInput->setCurrentText(QString::fromStdString(producer));
            ui->liquorAbvInput->setValue(abv);
            ui->liquorSizeInput->setValue(size);
            ui->liquorRatingInput->setValue(rating);

            // Set notes to the notes for liquor in the name input
            notes = get_latest_notes(ui->liquorNameInput->currentText().toStdString(), get_current_tab());
            ui->liquorNotesInput->setText(QString::fromStdString(notes));
        }
    }
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

    // Get latest notes entered for the selected drink
    // TODO: Refactor the filter code. This whole function could be reduced by allowing filtering on name and alc type.
    std::vector<Drink> drinks_by_name = Database::filter("Name", name, storage);
    unsigned temp_id = 0;
    if (ui->tabWidget->currentIndex() == 0) {  // Update beer notes
        for (const auto& drink_for_notes : drinks_by_name) {
            if (drink_for_notes.id > temp_id && drink_for_notes.alcohol_type == alcohol_type) {
                temp_id = drink_for_notes.id;
                if (!drink_for_notes.notes.empty()) {
                    notes = drink_for_notes.notes;
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

void MainWindow::update_liquor_fields() {
    /*
     * Read rows in the DB and populate the distiller, type, and name dropdowns with unique values.
     */

    std::set<QString> distilleries;
    std::set<QString> types;
    std::set<QString> names;

    std::vector<Drink> all_liquor = Database::filter("Alcohol Type", "Liquor", storage);

    // Block signals to avoid crashing
    QSignalBlocker brewery_signal_blocker(ui->liquorDistillerInput);
    QSignalBlocker type_signal_blocker(ui->liquorTypeInput);
    QSignalBlocker name_signal_blocker(ui->liquorNameInput);

    ui->liquorDistillerInput->clear();
    ui->liquorDistillerInput->setCurrentText("");
    ui->liquorTypeInput->clear();
    ui->liquorTypeInput->setCurrentText("");
    ui->liquorNameInput->clear();
    ui->liquorNameInput->setCurrentText("");

    for (const auto& liquor : all_liquor) {
        QString distiller_name = QString::fromStdString(liquor.producer);
        QString liquor_type = QString::fromStdString(liquor.type);
        QString liquor_name = QString::fromStdString(liquor.name);

        distilleries.insert(distiller_name);
        types.insert(liquor_type);
        names.insert(liquor_name);
    }

    for (const auto& distillery : distilleries) {
        ui->liquorDistillerInput->addItem(distillery);
    }

    for (const auto& type : types) {
        ui->liquorTypeInput->addItem(type);
    }

    for (const auto& name : names) {
        ui->liquorNameInput->addItem(name);
    }
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

    std::string alcohol_type = get_current_tab();
    if (alcohol_type == "Beer") {
        std::string beer_notes_text = get_latest_notes(ui->beerNameInput->currentText().toStdString(), alcohol_type);
        ui->beerNotesInput->setText(QString::fromStdString(beer_notes_text));
    } else if (alcohol_type == "Liquor") {
        std::string liquor_notes_text = get_latest_notes(ui->liquorNameInput->currentText().toStdString(), alcohol_type);
        ui->liquorNotesInput->setText(QString::fromStdString(liquor_notes_text));
    } else if(alcohol_type == "Wine") {
        std::string wine_notes_text = get_latest_notes(ui->wineNameInput->currentText().toStdString(), alcohol_type);
        ui->wineNotesInput->setText(QString::fromStdString(wine_notes_text));
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
        drink.drink_year = ui->beerDateInput->date().year();
        drink.drink_month = ui->beerDateInput->date().month();
        drink.drink_day = ui->beerDateInput->date().day();
        drink.name = ui->beerNameInput->currentText().toStdString();
        drink.type = ui->beerTypeInput->currentText().toStdString();
        drink.subtype = ui->beerSubtypeInput->currentText().toStdString();
        drink.producer = ui->beerBreweryInput->currentText().toStdString();
        drink.ibu = ui->beerIbuInput->value();
        drink.abv = ui->beerAbvInput->value();
        drink.size = ui->beerSizeInput->value();
        drink.rating = ui->beerRatingInput->value();
        drink.notes = ui->beerNotesInput->toPlainText().toStdString();
        drink.alcohol_type = alcohol_type;
    } else if (alcohol_type == "Liquor") {
        drink.drink_year = ui->liquorDateInput->date().year();
        drink.drink_month = ui->liquorDateInput->date().month();
        drink.drink_day = ui->liquorDateInput->date().day();
        drink.name = ui->liquorNameInput->currentText().toStdString();
        drink.type = ui->liquorTypeInput->currentText().toStdString();
        drink.subtype = ui->liquorSubtypeInput->currentText().toStdString();
        drink.producer = ui->liquorDistillerInput->currentText().toStdString();
        drink.abv = ui->liquorAbvInput->value();
        drink.ibu = -1.0;  // -1 denotes no IBU value
        drink.size = ui->liquorSizeInput->value();
        drink.rating = ui->liquorRatingInput->value();
        drink.notes = ui->liquorNotesInput->toPlainText().toStdString();
        drink.alcohol_type = alcohol_type;
    } else if (alcohol_type == "Wine") {
        //TODO: Finish this
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

    std::ostringstream month_padded;
    std::ostringstream day_padded;
    month_padded << std::setw(2) << std::setfill('0') << drink.drink_month;
    day_padded << std::setw(2) << std::setfill('0') << drink.drink_day;
    std::string date_from_db = day_padded.str() + "/" + month_padded.str() + "/" + std::to_string(drink.drink_year);

    return QDate::fromString(QString::fromUtf8(date_from_db.c_str()), "dd/MM/yyyy");
}