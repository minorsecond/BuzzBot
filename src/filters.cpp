//
// Created by Ross Wardrup on 9/19/20.
//

#include "mainwindow.h"

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

    (ui->filterCategoryInput->currentText().toStdString() == "None") ? ui->filterTextInput->setDisabled(true) : \
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