//
// Created by Ross Wardrup on 9/19/20.
//

#include "mainwindow.h"
#include "calculate.h"
#include <iostream>

void MainWindow::update_beer_fields() {
    /*
     * Read rows in the DB and populate the brewery, type, and name dropdowns with unique values.
     */

    std::set<QString> breweries;
    std::set<QString> types;
    std::set<QString> subtypes;
    std::set<std::string> names;
    std::vector<std::string> names_tmp;
    std::vector<Drink> all_beers = Database::filter("Alcohol Type", "Beer", storage);

    // Block signals to avoid crashing
    QSignalBlocker brewery_signal_blocker(ui->beerBreweryInput);
    QSignalBlocker type_signal_blocker(ui->beerTypeInput);
    QSignalBlocker subtype_signal_blocker(ui->beerSubtypeInput);
    QSignalBlocker name_signal_blocker(ui->beerNameInput);

    ui->beerBreweryInput->clear();
    ui->beerTypeInput->clear();
    ui->beerSubtypeInput->clear();
    ui->beerNameInput->clear();

    rename_duplicate_drink_names(all_beers);

    for (const auto& beer : all_beers) {
        const QString brewery_name = QString::fromStdString(beer.get_producer());
        const QString beer_type = QString::fromStdString(beer.get_type());
        const QString beer_subtype = QString::fromStdString(beer.get_subtype());
        const std::string name = beer.get_name();

        breweries.insert(brewery_name);
        types.insert(beer_type);
        subtypes.insert(beer_subtype);
        names.insert(name);
    }

    for (const auto& brewery : breweries) {
        if (!brewery.isEmpty()) {
            ui->beerBreweryInput->addItem(brewery);
        }
    }

    for (const auto& type : types) {
        if (!type.isEmpty()) {
            ui->beerTypeInput->addItem(type);
        }
    }

    for (const auto& subtype : subtypes) {
        if (!subtype.isEmpty()) {
            ui->beerSubtypeInput->addItem(subtype);
        }
    }

    for (const auto& name : names) {
        if (!name.empty()) {
            if (std::find(names_tmp.begin(), names_tmp.end(), name) == names_tmp.end())
                names_tmp.push_back(name);
        }
    }

    std::sort(names_tmp.begin(), names_tmp.end(), Calculate::compare_strings);

    for (const auto& name : names_tmp) {
        const QString name_q = QString::fromStdString(name);
        ui->beerNameInput->addItem(name_q);
    }

    // Reset to first name in field
    ui->beerNameInput->setCurrentIndex(0);
    update_beer_types_producers();
    const std::string beer_notes_text = get_latest_notes(ui->beerNameInput->currentText().toStdString());
    ui->beerNotesInput->setText(QString::fromStdString(beer_notes_text));
}

void MainWindow::populate_beer_fields(const Drink& drink_at_row) {
    /*
     * Populate the beer entry fields if user is on the beer entry tab.
     */

    const QDate date = format_date_for_input(drink_at_row);
    // Only update the beer fields if the user is currently on the beer tab
    const std::string notes = get_latest_notes(drink_at_row.get_name());
    ui->beerDateInput->setDate(date);
    ui->beerNameInput->setCurrentText(drink_at_row.get_name().c_str());
    ui->beerTypeInput->setCurrentText(drink_at_row.get_type().c_str());
    ui->beerSubtypeInput->setCurrentText(drink_at_row.get_subtype().c_str());
    ui->beerBreweryInput->setCurrentText(drink_at_row.get_producer().c_str());
    ui->beerAbvInput->setValue(drink_at_row.get_abv());
    ui->beerIbuInput->setValue(drink_at_row.get_ibu());
    ui->beerRatingInput->setValue(drink_at_row.get_rating());
    ui->beerNotesInput->setText(notes.c_str());
    ui->beerSizeInput->setValue(drink_at_row.get_size());

    // Switch to the beer tab
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::update_beer_types_producers() {
    /*
     * Update beer type and brewery when name input changes.
     */

    // This fixes crashes when changing with rows selected.
    QSignalBlocker type_input_signal_blocker(ui->beerTypeInput);
    QSignalBlocker brewery_input_signal_blocker(ui->beerBreweryInput);

    Drink selected_beer;
    const std::string input_beer = ui->beerNameInput->currentText().toStdString();
    if (input_beer.find(" -- (") != std::string::npos) {  // This is a beer with a name that matches another beer, and contains the producer name in the dropdown
        std::string producer_name {input_beer.substr(input_beer.find(" -- (") + 5)};
        producer_name = producer_name.substr(0, producer_name.size() - 1);
        const std::string beer_name {input_beer.substr(0, input_beer.find(" -- ("))};
        selected_beer = Database::get_drink_by_name(storage, "Beer", beer_name, producer_name);
        std::cout << selected_beer.get_id() << std::endl;
    } else {
        selected_beer = Database::get_drink_by_name(storage, "Beer", input_beer);
    }

    if (!selected_beer.get_id() || selected_beer.get_id() == -1) {  // Clear fields if new name
        clear_fields("Beer");
        ui->beerIbuInput->setValue(-1);
    } else {
        const std::string beer_type = selected_beer.get_type();
        const std::string beer_subtype = selected_beer.get_subtype();
        const std::string brewery = selected_beer.get_producer();
        const double abv = selected_beer.get_abv();
        const double ibu = selected_beer.get_ibu();
        double size = selected_beer.get_size();

        if (options.units == "Metric") {
            size = Calculate::oz_to_ml(size);
        }

        const int rating = selected_beer.get_rating();
        ui->beerTypeInput->setCurrentText(QString::fromStdString(beer_type));
        ui->beerSubtypeInput->setCurrentText(QString::fromStdString(beer_subtype));
        ui->beerBreweryInput->setCurrentText(QString::fromStdString(brewery));
        ui->beerAbvInput->setValue(abv);
        ui->beerIbuInput->setValue(ibu);
        ui->beerSizeInput->setValue(size);
        ui->beerRatingInput->setValue(rating);

        // Set notes to the notes for beer in the name input
        const std::string notes = get_latest_notes(ui->beerNameInput->currentText().toStdString());
        ui->beerNotesInput->setText(QString::fromStdString(notes));
    }
}

Drink MainWindow::get_beer_attrs_from_fields(std::string alcohol_type) {
    /*
     * Populate drink attributes with user input.
     */

    Drink drink;
    std::string drink_name {ui->beerNameInput->currentText().toStdString()};

    if (drink_name.find(" -- (") != std::string::npos) {  // This is a beer with a name that matches another beer, and contains the producer name in the dropdown
        const std::string producer_name {drink_name.substr(drink_name.find(" -- (") + 5)};
        drink_name = drink_name.substr(0, drink_name.find(" -- ("));
    }

    const std::string drink_date = ui->beerDateInput->date().toString("yyyy-MM-dd").toStdString();
    drink.set_date(drink_date);
    drink.set_name(drink_name);;
    drink.set_type(ui->beerTypeInput->currentText().toStdString());
    drink.set_subtype(ui->beerSubtypeInput->currentText().toStdString());
    drink.set_producer(ui->beerBreweryInput->currentText().toStdString());
    drink.set_vintage(-999);
    drink.set_ibu(ui->beerIbuInput->value());
    std::cout << "IBU: " << drink.get_ibu() << std::endl;
    drink.set_abv(ui->beerAbvInput->value());
    drink.set_size(ui->beerSizeInput->value());
    drink.set_rating(ui->beerRatingInput->value());
    drink.set_notes(ui->beerNotesInput->toPlainText().toStdString());
    drink.set_alcohol_type(alcohol_type);

    return drink;
}
