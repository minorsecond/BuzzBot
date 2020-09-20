//
// Created by Ross Wardrup on 9/19/20.
//

#include <utility>
#include "mainwindow.h"

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

    std::string liquor_notes_text = get_latest_notes(ui->liquorNameInput->currentText().toStdString(), "Wine");
    ui->liquorNotesInput->setText(QString::fromStdString(liquor_notes_text));
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

void MainWindow::update_liquor_names_producers() {
    /*
     * Update the names and distillery fields of the liquor tab.
     */

    std::string alcohol_type = get_current_tab();
    std::set<QString> drink_names;
    std::set<QString> producer_names;

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

void MainWindow::update_liquor_names_types() {
    /*
     * Update the name and type on the liquor tab.
     */

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

void MainWindow::update_liquor_types_producers() {
    /*
     * Update liquor type and distillery when name input changes.
     */

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
    std::string notes = get_latest_notes(ui->liquorNameInput->currentText().toStdString(), get_current_tab());
    ui->liquorNotesInput->setText(QString::fromStdString(notes));
}

Drink MainWindow::get_liquor_attrs_from_fields(std::string alcohol_type) {
    /*
     * Get liquor attributes from user input.
     */

    Drink drink;

    drink.drink_year = ui->liquorDateInput->date().year();
    drink.drink_month = ui->liquorDateInput->date().month();
    drink.drink_day = ui->liquorDateInput->date().day();
    drink.name = ui->liquorNameInput->currentText().toStdString();
    drink.type = ui->liquorTypeInput->currentText().toStdString();
    drink.subtype = ui->liquorSubtypeInput->currentText().toStdString();
    drink.producer = ui->liquorDistillerInput->currentText().toStdString();
    drink.vintage = -999;
    drink.abv = ui->liquorAbvInput->value();
    drink.ibu = -1.0;  // -1 denotes no IBU value
    drink.size = ui->liquorSizeInput->value();
    drink.rating = ui->liquorRatingInput->value();
    drink.notes = ui->liquorNotesInput->toPlainText().toStdString();
    drink.alcohol_type = std::move(alcohol_type);

    return drink;
}