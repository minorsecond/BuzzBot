//
// Created by Ross Wardrup on 9/19/20.
//

#include <utility>
#include "mainwindow.h"
#include "calculate.h"

void MainWindow::update_liquor_fields() {
    /*
     * Read rows in the DB and populate the distiller, type, subtype, and name dropdowns with unique values.
     */

    std::set<QString> distilleries;
    std::set<QString> types;
    std::set<QString> subtypes;
    std::vector<std::string> names_tmp;
    std::set<std::string> names;

    std::vector<Drink> all_liquor = Database::filter("Alcohol Type", "Liquor", storage);

    // Block signals to avoid crashing
    QSignalBlocker brewery_signal_blocker(ui->liquorDistillerInput);
    QSignalBlocker type_signal_blocker(ui->liquorTypeInput);
    QSignalBlocker subtype_signal_blocker(ui->liquorSubtypeInput);
    QSignalBlocker name_signal_blocker(ui->liquorNameInput);

    ui->liquorDistillerInput->clear();
    ui->liquorDistillerInput->setCurrentText("");
    ui->liquorTypeInput->clear();
    ui->liquorTypeInput->setCurrentText("");
    ui->liquorTypeInput->clear();
    ui->liquorSubtypeInput->setCurrentText("");
    ui->liquorNameInput->clear();
    ui->liquorNameInput->setCurrentText("");

    rename_duplicate_drink_names(all_liquor);

    for (const auto& liquor : all_liquor) {
        QString distiller_name = QString::fromStdString(liquor.producer);
        QString liquor_type = QString::fromStdString(liquor.type);
        QString liquor_subtype = QString::fromStdString(liquor.subtype);
        std::string liquor_name = liquor.name;

        distilleries.insert(distiller_name);
        types.insert(liquor_type);
        subtypes.insert(liquor_subtype);
        names.insert(liquor_name);
    }

    for (const auto& distillery : distilleries) {
        if (!distillery.isEmpty()) {
            ui->liquorDistillerInput->addItem(distillery);
        }
    }

    for (const auto& type : types) {
        if (!type.isEmpty()) {
            ui->liquorTypeInput->addItem(type);
        }
    }

    for (const auto& subtype : subtypes) {
        if (!subtype.isEmpty()) {
            ui->liquorSubtypeInput->addItem(subtype);
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
        ui->liquorNameInput->addItem(name_q);
    }

    // Rest to first name in field
    ui->liquorNameInput->setCurrentIndex(0);
    update_liquor_types_producers();
    std::string liquor_notes_text = get_latest_notes(ui->liquorNameInput->currentText().toStdString());
    ui->liquorNotesInput->setText(QString::fromStdString(liquor_notes_text));
}

void MainWindow::populate_liquor_fields(const Drink& drink_at_row) {
    /*
     * Populate the liquor entry fields if user is on the liquor entry tab.
     */

    QDate date = format_date_for_input(drink_at_row);
    std::string notes = get_latest_notes(drink_at_row.name);
    ui->liquorDateInput->setDate(date);
    ui->liquorNameInput->setCurrentText(drink_at_row.name.c_str());
    ui->liquorTypeInput->setCurrentText(drink_at_row.type.c_str());
    ui->liquorSubtypeInput->setCurrentText(drink_at_row.subtype.c_str());
    ui->liquorDistillerInput->setCurrentText(drink_at_row.producer.c_str());
    ui->liquorAbvInput->setValue(drink_at_row.abv);
    ui->liquorSizeInput->setValue(drink_at_row._size);
    ui->liquorRatingInput->setValue(drink_at_row.rating);
    ui->liquorNotesInput->setText(notes.c_str());

    // Switch to the liquor tab
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::update_liquor_types_producers() {
    /*
     * Update liquor type and distillery when name input changes.
     */

    // This fixes crashes when changing with rows selected.
    QSignalBlocker type_input_signal_blocker(ui->liquorTypeInput);
    QSignalBlocker brewery_input_signal_blocker(ui->liquorDistillerInput);

    std::string input_liquor = ui->liquorNameInput->currentText().toStdString();
    Drink selected_liquor;
    if (input_liquor.find(" -- (") != std::string::npos) {  // This is a drink with a name that matches another beer, and contains the producer name in the dropdown
        std::string producer_name {input_liquor.substr(input_liquor.find(" -- (") + 5)};
        producer_name = producer_name.substr(0, producer_name.size() - 1);
        std::string liquor_name {input_liquor.substr(0, input_liquor.find(" -- ("))};
        selected_liquor = Database::get_drink_by_name(storage, "Liquor", liquor_name, producer_name);
    } else {
        selected_liquor = Database::get_drink_by_name(storage, "Liquor", input_liquor);
    }

    if (!selected_liquor.id || selected_liquor.id == -1) {
        clear_fields("Liquor");
    } else {
        std::string liquor_type = selected_liquor.type;
        std::string liquor_subtype = selected_liquor.subtype;
        std::string producer = selected_liquor.producer;
        double abv = selected_liquor.abv;
        double size = selected_liquor._size;

        if (options.units == "Metric") {
            size = Calculate::oz_to_ml(size);
        }

        int rating = selected_liquor.rating;
        ui->liquorTypeInput->setCurrentText(QString::fromStdString(liquor_type));
        ui->liquorSubtypeInput->setCurrentText(QString::fromStdString(liquor_subtype));
        ui->liquorDistillerInput->setCurrentText(QString::fromStdString(producer));
        ui->liquorAbvInput->setValue(abv);
        ui->liquorSizeInput->setValue(size);
        ui->liquorRatingInput->setValue(rating);

        // Set notes to the notes for liquor in the name input
        std::string notes = get_latest_notes(ui->liquorNameInput->currentText().toStdString());
        ui->liquorNotesInput->setText(QString::fromStdString(notes));
    }
}

Drink MainWindow::get_liquor_attrs_from_fields(std::string alcohol_type) {
    /*
     * Get liquor attributes from user input.
     */

    Drink drink;

    std::string drink_date = ui->liquorDateInput->date().toString("yyyy-MM-dd").toStdString();
    drink.date = drink_date;
    drink.name = ui->liquorNameInput->currentText().toStdString();
    drink.type = ui->liquorTypeInput->currentText().toStdString();
    drink.subtype = ui->liquorSubtypeInput->currentText().toStdString();
    drink.producer = ui->liquorDistillerInput->currentText().toStdString();
    drink.vintage = -999;
    drink.abv = ui->liquorAbvInput->value();
    drink.ibu = -1.0;  // -1 denotes no IBU value
    drink._size = ui->liquorSizeInput->value();
    drink.rating = ui->liquorRatingInput->value();
    drink.notes = ui->liquorNotesInput->toPlainText().toStdString();
    drink.alcohol_type = std::move(alcohol_type);

    return drink;
}
