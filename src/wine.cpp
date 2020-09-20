//
// Created by Ross Wardrup on 9/19/20.
//

#include <utility>

#include "mainwindow.h"

void MainWindow::update_wine_fields() {
    /*
     * Read rows in the DB and populate the winery, type, and name dropdowns with unique values.
     */

    std::set<QString> wineries;
    std::set<QString> types;
    std::set<QString> names;

    std::vector<Drink> all_wine = Database::filter("Alcohol Type", "Wine", storage);

    // Block signals to avoid crashing
    QSignalBlocker winery_signal_blocker(ui->wineryInput);
    QSignalBlocker type_signal_blocker(ui->wineTypeInput);
    QSignalBlocker name_signal_blocker(ui->wineNameInput);

    ui->wineryInput->clear();
    ui->wineryInput->setCurrentText("");
    ui->wineTypeInput->clear();
    ui->wineTypeInput->setCurrentText("");
    ui->wineNameInput->clear();
    ui->wineNameInput->setCurrentText("");

    for (const auto& wine : all_wine) {
        QString winery_name = QString::fromStdString(wine.producer);
        QString wine_type = QString::fromStdString(wine.type);
        QString wine_name = QString::fromStdString(wine.name);

        wineries.insert(winery_name);
        types.insert(wine_type);
        names.insert(wine_name);
    }

    for (const auto& winery : wineries) {
        ui->wineryInput->addItem(winery);
    }

    for (const auto& type : types) {
        ui->wineTypeInput->addItem(type);
    }

    for (const auto& name : names) {
        ui->wineNameInput->addItem(name);
    }

    std::string wine_notes_text = get_latest_notes(ui->wineNameInput->currentText().toStdString(), "Wine");
    ui->wineNotesInput->setText(QString::fromStdString(wine_notes_text));
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
    ui->wineVintage->setValue(drink_at_row.vintage);
    ui->wineAbvInput->setValue(drink_at_row.abv);
    ui->wineSizeInput->setValue(drink_at_row.size);
    ui->wineRatingInput->setValue(drink_at_row.rating);
    ui->wineNotesInput->setText(notes.c_str());

    // Switch to the liquor tab
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::update_wine_names_producers() {
    /*
     * Update the names and winery fields of the wine tab.
     */

    std::set<QString> drink_names;
    std::set<QString> producer_names;

    std::string input_type = ui->wineTypeInput->currentText().toStdString();
    std::vector<Drink> selected_drinks = Database::get_beers_by_type(storage, input_type);

    // This fixes crashes when changing with rows selected.
    QSignalBlocker name_input_signal_blocker(ui->wineNameInput);
    QSignalBlocker winery_input_signal_blocker(ui->wineryInput);

    ui->wineAbvInput->setValue(0.0);
    ui->wineSizeInput->setValue(0);
    ui->wineRatingInput->setValue(0);
    ui->wineNameInput->clear();
    ui->wineryInput->clear();

    for (const auto& selected_drink : selected_drinks) {
        drink_names.insert(QString::fromStdString(selected_drink.name));
        producer_names.insert(QString::fromStdString(selected_drink.producer));
    }

    for (const auto& winery : producer_names) {
        ui->wineryInput->addItem(winery);
    }

    for (const auto& drink_name : drink_names) {
        ui->wineNameInput->addItem(drink_name);
    }
}

void MainWindow::update_wine_names_types() {
    /*
     * Update the name and type on the liquor tab.
     */

    std::string input_winery = ui->wineryInput->currentText().toStdString();
    std::vector<Drink> selected_drinks = Database::get_beers_by_brewery(storage, input_winery);
    std::set<QString> wine_names;
    std::set<QString> types;

    // This fixes crashes when changing with rows selected.
    QSignalBlocker name_input_signal_blocker(ui->wineNameInput);
    QSignalBlocker type_input_signal_blocker(ui->wineTypeInput);

    ui->wineAbvInput->setValue(0.0);
    ui->wineSizeInput->setValue(0);
    ui->wineRatingInput->setValue(0);
    ui->wineNameInput->clear();
    ui->wineTypeInput->clear();

    for (const auto& selected_drink : selected_drinks) {
        wine_names.insert(QString::fromStdString(selected_drink.name));
        types.insert(QString::fromStdString(selected_drink.type));
    }

    for (const auto& name : wine_names) {
        ui->wineNameInput->addItem(name);
    }

    for (const auto& wine_type : types) {
        ui->wineTypeInput->addItem(wine_type);
    }
}

void MainWindow::update_wine_types_producers() {
    /*
     * Update wine type and winery when name input changes.
     */

    // This fixes crashes when changing with rows selected.
    QSignalBlocker type_input_signal_blocker(ui->wineTypeInput);
    QSignalBlocker brewery_input_signal_blocker(ui->wineryInput);

    std::string input_wine = ui->wineNameInput->currentText().toStdString();
    Drink selected_wine = Database::get_drink_by_name(storage, input_wine);
    std::string wine_type = selected_wine.type;
    std::string wine_subtype = selected_wine.subtype;
    std::string producer = selected_wine.producer;
    double abv = selected_wine.abv;
    int size = selected_wine.size;
    int rating = selected_wine.rating;

    ui->wineTypeInput->setCurrentText(QString::fromStdString(wine_type));
    ui->wineSubtypeInput->setCurrentText(QString::fromStdString(wine_subtype));
    ui->wineryInput->setCurrentText(QString::fromStdString(producer));
    ui->wineAbvInput->setValue(abv);
    ui->wineSizeInput->setValue(size);
    ui->wineRatingInput->setValue(rating);

    // Set notes to the notes for liquor in the name input
    std::string notes = get_latest_notes(ui->wineNameInput->currentText().toStdString(), get_current_tab());
    ui->wineNotesInput->setText(QString::fromStdString(notes));
}

Drink MainWindow::get_wine_attrs_from_fields(std::string alcohol_type) {
    /*
     * Get wine attributes from user input
     */

    Drink drink;

    drink.drink_year = ui->wineDateInput->date().year();
    drink.drink_month = ui->wineDateInput->date().month();
    drink.drink_day = ui->wineDateInput->date().day();
    drink.name = ui->wineNameInput->currentText().toStdString();
    drink.type = ui->wineTypeInput->currentText().toStdString();
    drink.subtype = ui->wineSubtypeInput->currentText().toStdString();
    drink.producer = ui->wineryInput->currentText().toStdString();
    drink.vintage = ui->wineVintage->value();
    drink.abv = ui->wineAbvInput->value();
    drink.ibu = -1.0;  // -1 denotes no IBU value
    drink.size = ui->wineSizeInput->value();
    drink.rating = ui->wineRatingInput->value();
    drink.notes = ui->wineNotesInput->toPlainText().toStdString();
    drink.alcohol_type = std::move(alcohol_type);

    return drink;
}