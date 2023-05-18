#include "mainwindow.h"
#include "usersettings.h"
#include "about.h"
#include "../ui/ui_graph_window.h"
#include "standard_drink_calculator.h"
#include "exporters.h"
#include "calculate.h"
#include "graphing.h"
#include "reports.h"
#include "utilities.h"
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <QComboBox>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <QTimer>
#include <chrono>

#ifdef __APPLE__
    #include <CoreFoundation/CFBundle.h>
#elif _WIN32
    #include <unistd.h>
#endif

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

    // Change unit text depending on settings
    if (options.units == "Metric") {
        ui->volAlcoholRemainingLabel->setText("ml. Alcohol Remaining:");
    }

    // Upgrade DB version
    // DB Version 7 removes extra year, month, date columns
    Database::increment_version(storage, Database::db_version);

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

    ui->frame->setStyleSheet("QWidget#frame{ border: 0; }");
    ui->frame_2->setStyleSheet("QWidget#frame_2{ border: 0; }");
    ui->frame_4->setStyleSheet("QWidget#frame_4{ border: 0; }");

    // Sort table by date column, by default
    reset_table_sort();
    configure_table();
    add_slot_connections();

    // Update fields to match beer that comes first alphabetically
    reset_fields();

    // Set up IBU spinbox No Value item
    ui->beerIbuInput->setRange(-1, 100);
    ui->beerIbuInput->setSingleStep(1);
    ui->beerIbuInput->setSpecialValueText(tr(" "));

    // Start the stat pane update stat_update_timer
    auto *stats_timer = new QTimer(this);
    connect(stats_timer, &QTimer::timeout, this, &MainWindow::update_stats_if_new_day);
    stats_timer->start(1000);
}

void MainWindow::add_menubar_items() {
    /*
     * Add items to the system menubar.
     */

    const QString pref_action_name{"Preferences"};
    const QString about_action_name{"About"};
    const QString export_action_name{"Export"};
    const QString graphs_action_name{"Graphs"};
    const QString table_action_name{"Tables"};
    const QString calc_std_drinks_action_name{"Calculate Std. Drinks"};

    std::array<QString, 5> action_names{
        about_action_name,
        export_action_name,
        graphs_action_name,
        table_action_name,
        calc_std_drinks_action_name
    };

#ifdef __APPLE__
    QMenu *app_menu = menuBar()->addMenu("App Menu");
    const QString ellipses{"..."};

    for (QString &action_name : action_names) {
        action_name += ellipses;
    }

#else
    QMenu *app_menu = menuBar()->addMenu("File");
    QMenu *report_menu = menuBar()->addMenu("Reports");

#endif

    auto *preferences_action = new QAction(pref_action_name, this);
    auto *about_action = new QAction(action_names[0], this);
    auto *export_action = new QAction(action_names[1], this);
    auto *graphs_action = new QAction(action_names[2], this);
    auto *table_action = new QAction(action_names[3], this);
    auto *calc_std_drinks = new QAction(action_names[4], this);

    preferences_action->setMenuRole(QAction::PreferencesRole);
    about_action->setMenuRole(QAction::AboutRole);
    export_action->setMenuRole(QAction::ApplicationSpecificRole);
    graphs_action->setMenuRole(QAction::ApplicationSpecificRole);
    table_action->setMenuRole(QAction::ApplicationSpecificRole);
    calc_std_drinks->setMenuRole(QAction::ApplicationSpecificRole);

    app_menu->addAction(about_action);
    app_menu->addAction(preferences_action);
    app_menu->addAction(export_action);
    app_menu->addAction(calc_std_drinks);

#ifdef __APPLE__
    app_menu->addAction(graphs_action);
    app_menu->addAction(table_action);
#else
    report_menu->addAction(graphs_action);
    report_menu->addAction(table_action);
#endif

    connect(preferences_action, &QAction::triggered, this, &MainWindow::open_user_settings);
    connect(about_action, &QAction::triggered, this, &MainWindow::open_about_dialog);
    connect(export_action, &QAction::triggered, this, &MainWindow::open_export_dialog);
    connect(graphs_action, &QAction::triggered, this, &MainWindow::open_graphs);
    connect(table_action, &QAction::triggered, this, &MainWindow::open_reports);
    connect(calc_std_drinks, &QAction::triggered, this, &MainWindow::open_std_drink_calculator);
}

void MainWindow::configure_calendar() {
    /*
     * Set up the calendar widget with nicer settings.
     */

#ifdef __APPLE__
    const CFURLRef app_url_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    const CFStringRef mac_path = CFURLCopyFileSystemPath(app_url_ref, kCFURLPOSIXPathStyle);
    const QString icon_path_qstring = CFStringGetCStringPtr(mac_path, CFStringGetSystemEncoding());
    const std::string previous_month_arrow = icon_path_qstring.toStdString() + "/Contents/Resources/previous.png";
    const std::string next_month_arrow = icon_path_qstring.toStdString() + "/Contents/Resources/next.png";
#elif __linux__
    const std::string home_path = utilities::get_home_path();
    const std::string next_month_arrow = home_path + "/.local/share/icons/com.rwardrup.buzzbot/next.png";
    const std::string previous_month_arrow = home_path + "/.local/share/icons/com.rwardrup.buzzbot/previous.png";
#elif _WIN32
    const std::string current_path {utilities::exe_path()};
    const std::string next_month_arrow {current_path + "/res/next.png"};
    const std::string previous_month_arrow {current_path + "/res/previous.png"};
#endif

    const std::string stylesheet_text = "QCalendarWidget QWidget#qt_calendar_navigationbar\n"
                                  "{\n"
                                  //"\tcolor: rgba(169,204,227,128);\n"
                                  "\tbackground-color: rgba(84, 153, 199 ,128);\n"
                                  "\tborder: 1px solid #4f4f4f;"
                                  "}\n"
                                  "QCalendarWidget QToolButton {\n"
                                  "  \tbackground-color: rgba(128, 128, 128, 0);\n"
                                  "}\n"
                                  " /* header row */\n"
                                  "QCalendarWidget QWidget { alternate-background-color: rgba(128, 128, 128, 0);}\n"
                                  "QCalendarWidget QToolButton#qt_calendar_prevmonth \n"
                                  "{\n"
                                  "\tqproperty-icon: url(" + previous_month_arrow +
                                  ");\n"
                                  "}\n"
                                  "\n"
                                  "QCalendarWidget QToolButton#qt_calendar_nextmonth \n"
                                  "{\n"
                                  "\tqproperty-icon: url(" + next_month_arrow + ");\n""}";
#if __linux__ || __APPLE__
    ui->beerDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
    ui->liquorDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
    ui->wineDateInput->setStyleSheet(QString::fromStdString(stylesheet_text));
#endif
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
    const std::array<std::string, 6> filter_types {
        "None",
        "Name",
        "Type",
        "Subtype",
        "Producer",
        "Rating"
    };

    for (const std::string &filter_name : filter_types) {
        ui->filterCategoryInput->addItem(QString::fromStdString(filter_name));
    }

    ui->filterCategoryInput->setCurrentText("None");
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
    ui->drinkLogTable->setColumnWidth(8, 55); // Standard Drinks
    ui->drinkLogTable->setColumnWidth(9, 55); // Rating
    ui->drinkLogTable->setColumnHidden(10, true);  // Hide ID column
    ui->drinkLogTable->setColumnHidden(11, true);  // Hide Timestamp column
    ui->drinkLogTable->setColumnHidden(12, true);  // Hide Sort column
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
    const QDate todays_date = QDate::currentDate();
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

    const QItemSelectionModel *selection_model = ui->drinkLogTable->selectionModel();
    const QModelIndexList selected_rows = selection_model->selectedRows();

    // Get current tab selected
    const std::string alcohol_type = get_current_tab();
    const Drink entered_drink = get_drink_attributes_from_fields();

    // Prevent blank submissions
    if (entered_drink.get_name().empty() || entered_drink.get_abv() == 0.0 || entered_drink.get_size() == 0.0 || entered_drink.get_producer().empty()) {
        QMessageBox::critical(nullptr, "Error", "Please enter drink name, ABV, producer, and size.");
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

    const Drink drink_at_row = get_drink_at_selected_row();

    if (drink_at_row.get_alcohol_type() == "Beer") {
        populate_beer_fields(drink_at_row);
        ui->tabWidget->setCurrentIndex(0);
    } else if (drink_at_row.get_alcohol_type() == "Liquor") {
        populate_liquor_fields(drink_at_row);
        ui->tabWidget->setCurrentIndex(1);
    } else if (drink_at_row.get_alcohol_type() == "Wine") {
        populate_wine_fields(drink_at_row);
        ui->tabWidget->setCurrentIndex(2);
    }
}

void MainWindow::open_about_dialog() {
    /*
     * Open the about dialog which contains author and license information.
     */

    auto *about_dialog = new About();
    about_dialog->setAttribute(Qt::WA_DeleteOnClose); // Delete pointer on window close
    about_dialog->setModal(false);
    about_dialog->show();
}

void MainWindow::open_export_dialog() {
    /*
     * Open the export dialog.
     */

    const QString desktop_path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0);
    const QString preferred_path = desktop_path + "/buzzbot.csv";

    QString filter = "CSV Files (*.csv)";
    const QString filepath_qstring = QFileDialog::getSaveFileName(this, "Save File", preferred_path, filter, &filter);

    const std::vector<Drink> all_drinks = storage.get_all<Drink>();
    exporters::to_csv(all_drinks, filepath_qstring.toStdString(), options.units);
}

void MainWindow::open_user_settings() {
    /*
     * Open the user settings dialog box, where users can enter their sex and the day which the week should begin on.
     */

    UserSettings user_settings = UserSettings(options, std_drink_standards);
    user_settings.setModal(true);
    double std_drink_size = options.std_drink_size;

    const std::string current_db_path_setting{options.database_path};
    bool custom_db {options.custom_database};

    if (user_settings.exec() == QDialog::Accepted) {  // Update settings when OK button is clicked
        custom_db = user_settings.get_custom_database_status();
        options.sex = user_settings.get_sex();
        options.date_calculation_method = user_settings.get_date_calculation_method();
        options.weekday_start = user_settings.get_weekday_start();
        options.limit_standard = user_settings.get_limit_standard();
        options.weekly_limit = user_settings.get_drink_limit();
        options.units = user_settings.get_units();
        std_drink_size = user_settings.get_std_drink_size();
        options.std_drink_country = user_settings.get_std_drink_country();
        options.custom_database = custom_db;
        options.database_path = user_settings.get_database_path(custom_db);
        update_stat_panel();
    }

    if (options.units == "Metric") {
        ui->beerSizeLabel->setText("Size (ml)");
        ui->liquorSizeLabel->setText("Size (ml)");
        ui->wineSizeLabel->setText("Size (ml)");
        options.std_drink_size = Calculate::ml_to_oz(std_drink_size);
    } else {
        ui->beerSizeLabel->setText("Size (oz)");
        ui->liquorSizeLabel->setText("Size (oz)");
        ui->wineSizeLabel->setText("Size (oz)");
        options.std_drink_size = std_drink_size;
    }

    if (options.database_path == utilities::get_application_data_path() + "/buzzbot.db" && options.custom_database) {
        // User didn't change the path from the default path but select custom DB. set option back to default
        options.custom_database = false;

        QMessageBox::StandardButton reply{};
        reply = QMessageBox::warning(this, QString::fromStdString("Path Unchanged"),
                              QString::fromStdString("Database path unchanged. It is not being moved."),
                              QMessageBox::Ok);
    }

    this->options.write_options();
    update_table();
    update_stat_panel();
    update_types_and_producers();
    if (current_db_path_setting != options.database_path) {
        // User changed DB get_db_path settings
        const DbMoveStatus result{Database::move_db(current_db_path_setting, options.database_path)};
        if (result == DbMoveStatus::ErrorCopyingDb) {
            std::cout << "Error copying database from " << current_db_path_setting << " to " << options.database_path
                      << std::endl;

            QMessageBox::StandardButton reply{};
            reply = QMessageBox::critical(this, QString::fromStdString("DB Operation Error"),
                                          QString::fromStdString("Error copying file. Restore from backup? Cancelling will exit the app."),
                                          QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::Yes) {
                const std::string backup_loc {current_db_path_setting + ".bak"};
                Database::move_db(backup_loc, current_db_path_setting);
            } else {
                exit(1);
            }
        } else if (result == DbMoveStatus::Success) { // Prompt user to reopen app and close automatically (else it will crash)
            QMessageBox::StandardButton reply{};
            reply = QMessageBox::information(this, QString::fromStdString("Move Database"),
                                          QString::fromStdString("Closing app. Restart to load data from new location."),
                                          QMessageBox::Ok);
            if (reply == QMessageBox::Ok) {
                exit(1);
            }
        } else if (result == DbMoveStatus::DestFileExists) {
            // Move didn't happen because destination file already exists
            QMessageBox::StandardButton reply{};
            reply = QMessageBox::information(this, QString::fromStdString("Move Database"),
                                             QString::fromStdString("Destination file already exists.\n"
                                                                    "BuzzBot will load it upon next launch. \n"
                                                                    "Do you want to delete the current file, keeping the destination file?\n"
                                                                    "BuzzBot will close after your response."),
                                             QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // User wants to delete current file and keep destination file
                std::filesystem::remove(current_db_path_setting);
            }
            exit(1);
        }
    }
    std::cout << "Custom standard drink size: " << std_drink_size << std::endl;
}

void MainWindow::update_types_and_producers() {
    /*
     * Change the drink attributes based on the drink selected in the nameInput field.
     */

    if (get_current_tab() == "Beer") {
        if (!ui->beerNameInput->currentText().toStdString().empty()) {
            update_beer_types_producers();
        }
    } else if(get_current_tab() == "Liquor") {
        if (!ui->liquorNameInput->currentText().toStdString().empty()) {
            update_liquor_types_producers();
        }
    } else if (get_current_tab() == "Wine") {
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

    const Drink selected_drink = get_drink_at_selected_row();
    const std::string name = selected_drink.get_name();
    const std::string selected_drink_alc_type = selected_drink.get_alcohol_type();
    const std::string new_tab = get_current_tab();
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

    Drink drink;

    // Size values are converted to/from ml and oz in add_new_row()
    if (const std::string alcohol_type {get_current_tab()}; alcohol_type == "Beer") {
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

    return QDate::fromString(QString::fromUtf8(drink.get_date().c_str()), "yyyy-MM-dd");
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
    const QItemSelectionModel *selection_model = ui->drinkLogTable->selectionModel();
    const QModelIndexList selected_rows = selection_model->selectedRows();

    if (selected_rows.empty()) {
        if (alcohol_type == "Beer") {
            ui->beerAbvInput->setValue(0.0);
            ui->beerAbvInput->clear();
            ui->beerIbuInput->setValue(0);
            ui->beerIbuInput->clear();
            ui->beerSizeInput->setValue(0.0);
            ui->beerSizeInput->clear();
            ui->beerRatingInput->setValue(5);
            ui->beerNotesInput->clear();
        } else if (alcohol_type == "Liquor") {
            ui->liquorAbvInput->setValue(0.0);
            ui->liquorAbvInput->clear();
            ui->liquorSizeInput->setValue(0.0);
            ui->liquorSizeInput->clear();
            ui->liquorRatingInput->setValue(5);
            ui->liquorNotesInput->clear();
        } else if (alcohol_type == "Wine") {
            ui->wineVintage->setValue(0);
            ui->wineVintage->clear();
            ui->wineAbvInput->setValue(0.0);
            ui->wineAbvInput->clear();
            ui->wineRatingInput->setValue(5);
            ui->wineSizeInput->setValue(0.0);
            ui->wineSizeInput->clear();
            ui->wineNotesInput->clear();
        }
    }
}

void MainWindow::open_std_drink_calculator() const {
    /*
     * Open the standard drink calculator dialog box.
     */

    auto * std_drink_calculator = new StandardDrinkCalc(options.std_drink_size, options.units);
    std_drink_calculator->setAttribute(Qt::WA_DeleteOnClose);  // Delete pointer on window close
    std_drink_calculator->show();
}

std::chrono::weekday MainWindow::get_filter_weekday_start() const {
    /*
     * Get filter day from options.
     * @return filter_day: a date object for the filter day.
     */

    std::chrono::weekday filter_day{};

    // Get date to filter on
    if (options.weekday_start == "Monday") {
        filter_day = std::chrono::Monday;
    } else if (options.weekday_start == "Tuesday") {
        filter_day = std::chrono::Tuesday;
    } else if (options.weekday_start == "Wednesday") {
        filter_day = std::chrono::Wednesday;
    } else if (options.weekday_start == "Thursday") {
        filter_day = std::chrono::Thursday;
    } else if (options.weekday_start == "Friday") {
        filter_day = std::chrono::Friday;
    } else {
        filter_day = std::chrono::Sunday;
    }

    return filter_day;
}

std::tuple<std::chrono::year_month_day, std::string> MainWindow::get_filter_date() {
    /*
     * Get the date and day of week for the filter date specified in the options.
     * @return: Tuple containing the start date (a date::year_month_day object) and weekday name (string).
     */

    std::chrono::year_month_day start_date{};
    std::string weekday_name;

    const std::chrono::weekday filter_day = get_filter_weekday_start();

    // get_local_date returns a string in the form of YYYY-MM-DD
    const std::string query_date = utilities::get_local_date();

    // Back to date object
    std::tm tm = {};
    std::stringstream ss(query_date);
    ss >> std::get_time(&tm,"%Y-%m-%d");
    const auto tp = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::from_time_t(std::mktime(&tm)));

    // Get date of last filter_day
    if (options.date_calculation_method == "Fixed") {
        std::cout << "Using fixed date method" << std::endl;
        start_date = tp - (std::chrono::weekday{tp} - filter_day);
        weekday_name = options.weekday_start;
    } else {  // Don't include day 7 days ago.
        std::cout << "Using rolling date method" << std::endl;
        start_date = tp - std::chrono::days{6};

        // Get weekday name
        const std::chrono::weekday one_week = std::chrono::weekday(tp - std::chrono::days{7});
        const unsigned weekday = one_week.iso_encoding();
        weekday_name = get_weekday_name(weekday);
    }

    return std::make_tuple(start_date, weekday_name);
}

void MainWindow::update_stats_if_new_day() {
    /*
     * Update the stats panel if day of the week isn't the same as the date in stats panel.
     */

    const std::time_t t = std::time(nullptr);
    std::stringstream ssTp;
    ssTp << std::put_time(std::localtime(&t), "%A");
    std::string weekday_name = ssTp.str();

    if (ui->drinksThisWeekLabel->text().toStdString().find(weekday_name) == std::string::npos) {
        update_stat_panel();
    }
}

std::string MainWindow::format_date(std::chrono::year_month_day date) {
    /*
     * Format date for use in DB filter.
     * @return: formatted date string.
     */

    const std::string year = std::to_string((int)date.year());

    const std::string month = utilities::zero_pad_string(static_cast<unsigned>(date.month()));
    const std::string day = utilities::zero_pad_string(static_cast<unsigned>(date.day()));

    return year + "-" + month + "-" + day;
}

void MainWindow::open_graphs() {
    /*
     * Create graphs of drink data.
     */

    const std::string db_path = utilities::get_db_path();
    const std::vector<Drink> all_drinks = Database::read(storage);
    const double std_drink_size = get_std_drink_size_from_options();
    auto *graphing_window = new Graphing(all_drinks, std_drink_size, options);
    graphing_window->setAttribute(Qt::WA_DeleteOnClose); // Delete pointer on window close
    graphing_window->setModal(false);
    graphing_window->show();
}

void MainWindow::open_reports() {
    /*
     * Open the reports dialog
     */

    auto *reports_window = new Reports(storage);
    reports_window->setAttribute(Qt::WA_DeleteOnClose);
    reports_window->setModal(false);
    reports_window->show();
}

void MainWindow::rename_duplicate_drink_names(std::vector<Drink> &drinks) {
    /*
     * Rename drink name to DRINK NAME -- (Producer name) if there
     * are multiple drinks with the same name.
     * @param drinks: A reference to a vector of Drinks.
     */

    std::map<std::string, int> count_map {};
    std::set<std::string> names_producers {};

    for (const Drink &drink : drinks) {
        names_producers.insert(drink.get_name() + "-" + drink.get_producer());
    }

    for (const auto &name_prod_pair : names_producers) {
        const std::string drink_name {name_prod_pair.substr(0, name_prod_pair.find("-"))};
        auto result {count_map.insert(std::pair<std::string, int>(drink_name, 1))};
        if (result.second == false) {
            result.first->second++;
        }
    }

    for (const auto &elem : count_map) {
        if (elem.second > 1) {
            for (Drink &drink : drinks) {
                if (drink.get_name() == elem.first) {
                    if (!drink.get_producer().empty()) {
                        drink.set_name(drink.get_name() += " -- (" + drink.get_producer() + ")");
                    }
                }
            }
        }
    }
}
// LCOV_EXCL_STOP