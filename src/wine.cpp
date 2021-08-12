//
// Created by Ross Wardrup on 9/19/20.
//

#include <utility>
#include "mainwindow.h"
#include "calculate.h"

void MainWindow::update_wine_fields() {
    /*
     * Read rows in the DB and populate the winery, type, and name dropdowns with unique values.
     */

    std::set<QString> wineries;
    std::set<QString> types;
    std::set<QString> subtypes;
    std::vector<std::string> names_tmp;
    std::set<std::string> names;

    std::vector<Drink> all_wine = Database::filter("Alcohol Type", "Wine", storage);

    // Block signals to avoid crashing
    QSignalBlocker winery_signal_blocker(ui->wineryInput);
    QSignalBlocker type_signal_blocker(ui->wineTypeInput);
    QSignalBlocker subtype_signal_blocker(ui->wineSubtypeInput);
    QSignalBlocker name_signal_blocker(ui->wineNameInput);

    ui->wineryInput->clear();
    ui->wineryInput->setCurrentText("");
    ui->wineTypeInput->clear();
    ui->wineTypeInput->setCurrentText("");
    ui->wineSubtypeInput->clear();
    ui->wineSubtypeInput->setCurrentText("");
    ui->wineNameInput->clear();
    ui->wineNameInput->setCurrentText("");

    std::map<std::string, int> count_map {};
    std::set<std::string> names_producers {};

    for (const Drink &wine : all_wine) {
        names_producers.insert(wine.name + "-" + wine.producer);
    }

    for (const auto &name_prod_pair : names_producers) {
        const std::string wine_name {name_prod_pair.substr(0, name_prod_pair.find("-"))};
        auto result {count_map.insert(std::pair<std::string, int>(wine_name, 1))};
        if (result.second == false) {
            result.first->second++;
        }
    }

    for (const auto &elem : count_map) {
        if (elem.second > 1) {
            //count_map.erase(count_map.find(elem.first));  // Erase drinks with only one name entry
            for (Drink &wine : all_wine) {
                if (wine.name == elem.first) {
                    wine.name += " -- (" + wine.producer + ")";
                }
            }
        }
    }

    for (const auto& wine : all_wine) {
        QString winery_name = QString::fromStdString(wine.producer);
        QString wine_type = QString::fromStdString(wine.type);
        QString wine_subtype = QString::fromStdString(wine.subtype);
        std::string wine_name = wine.name;

        wineries.insert(winery_name);
        types.insert(wine_type);
        subtypes.insert(wine_subtype);
        names.insert(wine_name);
    }

    for (const auto& winery : wineries) {
        if (!winery.isEmpty()) {
            ui->wineryInput->addItem(winery);
        }
    }

    for (const auto& type : types) {
        if (!type.isEmpty()) {
            ui->wineTypeInput->addItem(type);
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
        QString name_q = QString::fromStdString(name);
        ui->wineNameInput->addItem(name_q);
    }

    for (const auto& subtype : subtypes) {
        if (!subtype.isEmpty()) {
            ui->wineSubtypeInput->addItem(subtype);
        }
    }

    // Rest to first name in field
    ui->wineNameInput->setCurrentIndex(0);
    update_wine_types_producers();
    std::string wine_notes_text = get_latest_notes(ui->wineNameInput->currentText().toStdString());
    ui->wineNotesInput->setText(QString::fromStdString(wine_notes_text));
}

void MainWindow::populate_wine_fields(const Drink& drink_at_row) {
    /*
     * Populate the wine entry fields if user is on the wine entry tab.
     */

    QDate date = format_date_for_input(drink_at_row);
    std::string notes = get_latest_notes(drink_at_row.name);
    ui->wineDateInput->setDate(date);
    ui->wineNameInput->setCurrentText(drink_at_row.name.c_str());
    ui->wineTypeInput->setCurrentText(drink_at_row.type.c_str());
    ui->wineSubtypeInput->setCurrentText(drink_at_row.subtype.c_str());
    ui->wineryInput->setCurrentText(drink_at_row.producer.c_str());
    ui->wineVintage->setValue(drink_at_row.vintage);
    ui->wineAbvInput->setValue(drink_at_row.abv);
    ui->wineSizeInput->setValue(drink_at_row._size);
    ui->wineRatingInput->setValue(drink_at_row.rating);
    ui->wineNotesInput->setText(notes.c_str());

    // Switch to the liquor tab
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::update_wine_types_producers() {
    /*
     * Update wine type and winery when name input changes.
     */

    // This fixes crashes when changing with rows selected.
    QSignalBlocker type_input_signal_blocker(ui->wineTypeInput);
    QSignalBlocker subtype_input_signal_blocker(ui->wineSubtypeInput);
    QSignalBlocker brewery_input_signal_blocker(ui->wineryInput);

    std::string input_wine = ui->wineNameInput->currentText().toStdString();
    Drink selected_wine = Database::get_drink_by_name(storage, "Wine",input_wine);

    if (!selected_wine.id || selected_wine.id == -1) {
        clear_fields("Wine");
    } else {
        std::string wine_type = selected_wine.type;
        std::string wine_subtype = selected_wine.subtype;
        std::string producer = selected_wine.producer;
        double abv = selected_wine.abv;
        double size = selected_wine._size;

        if (options.units == "Metric") {
            size = Calculate::oz_to_ml(size);
        }

        int rating = selected_wine.rating;
        ui->wineTypeInput->setCurrentText(QString::fromStdString(wine_type));
        ui->wineSubtypeInput->setCurrentText(QString::fromStdString(wine_subtype));
        ui->wineryInput->setCurrentText(QString::fromStdString(producer));
        ui->wineAbvInput->setValue(abv);
        ui->wineSizeInput->setValue(size);
        ui->wineRatingInput->setValue(rating);

        // Set notes to the notes for liquor in the name input
        std::string notes = get_latest_notes(ui->wineNameInput->currentText().toStdString());
        ui->wineNotesInput->setText(QString::fromStdString(notes));
    }
}

Drink MainWindow::get_wine_attrs_from_fields(std::string alcohol_type) {
    /*
     * Get wine attributes from user input
     */

    Drink drink;

    std::string drink_date = ui->wineDateInput->date().toString("yyyy-MM-dd").toStdString();
    drink.date = drink_date;
    drink.name = ui->wineNameInput->currentText().toStdString();
    drink.type = ui->wineTypeInput->currentText().toStdString();
    drink.subtype = ui->wineSubtypeInput->currentText().toStdString();
    drink.producer = ui->wineryInput->currentText().toStdString();
    drink.vintage = ui->wineVintage->value();
    drink.abv = ui->wineAbvInput->value();
    drink.ibu = -1.0;  // -1 denotes no IBU value
    drink._size = ui->wineSizeInput->value();
    drink.rating = ui->wineRatingInput->value();
    drink.notes = ui->wineNotesInput->toPlainText().toStdString();
    drink.alcohol_type = std::move(alcohol_type);

    return drink;
}
