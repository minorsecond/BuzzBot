//
// Created by Ross Wardrup on 9/19/20.
//

#include "mainwindow.h"
#include <iostream>

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

    std::string beer_notes_text = get_latest_notes(ui->beerNameInput->currentText().toStdString(), "Beer");
    ui->beerNotesInput->setText(QString::fromStdString(beer_notes_text));
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

void MainWindow::update_beer_names_producers() {
    /*
     * Update the names and breweries fields of the beer tab.
     */

    std::set<QString> drink_names;
    std::set<QString> producer_names;
    std::string input_type = ui->beerTypeInput->currentText().toStdString();
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
}

void MainWindow::update_beer_names_types() {
    /*
     * Update the name and type on the beer tab.
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
}

void MainWindow::update_beer_types_producers() {
    /*
     * Update beer type and brewery when name input changes.
     */

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
    std::string notes = get_latest_notes(ui->beerNameInput->currentText().toStdString(), get_current_tab());
    ui->beerNotesInput->setText(QString::fromStdString(notes));
}

Drink MainWindow::get_beer_attrs_from_fields(std::string alcohol_type) {
    /*
     * Populate drink attributes with user input.
     */

    Drink drink;

    drink.drink_year = ui->beerDateInput->date().year();
    drink.drink_month = ui->beerDateInput->date().month();
    drink.drink_day = ui->beerDateInput->date().day();
    drink.name = ui->beerNameInput->currentText().toStdString();
    drink.type = ui->beerTypeInput->currentText().toStdString();
    drink.subtype = ui->beerSubtypeInput->currentText().toStdString();
    drink.producer = ui->beerBreweryInput->currentText().toStdString();
    drink.vintage = -999;
    drink.ibu = ui->beerIbuInput->value();
    drink.abv = ui->beerAbvInput->value();
    drink.size = ui->beerSizeInput->value();
    drink.rating = ui->beerRatingInput->value();
    drink.notes = ui->beerNotesInput->toPlainText().toStdString();
    drink.alcohol_type = std::move(alcohol_type);

    return drink;
}