//
// Created by Ross Wardrup on 4/23/21.
//

#include "mainwindow.h"
#include "confirm_dialog.h"
#include "calculate.h"
#include <iostream>

void MainWindow::update_selected_row(QItemSelectionModel* select, Drink entered_drink) {
    /*
     * Update a row that already exists in the database.
     * @param select: A selection model.
     * @param entered_drink: A Drink containing data from the database.
     */

    ConfirmDialog confirmation_dialog = ConfirmDialog("Update");
    if (confirmation_dialog.exec() == QDialog::Accepted) {
        // Get the selected row
        int selection = select->selectedRows().at(0).row();
        int row_to_update = ui->drinkLogTable->item(selection, 9)->text().toUtf8().toInt();

        // Get the existing timestamp
        std::string timestamp = ui->drinkLogTable->item(selection, 10)->text().toStdString();
        std::cout << "Updating row " << row_to_update << " Timestamp: " << timestamp << std::endl;

        // Update the variables in the drink struct
        entered_drink.id = row_to_update;
        entered_drink.timestamp = timestamp;

        if (options.units == "Metric") {
            entered_drink._size = Calculate::ml_to_oz(entered_drink._size);
        }

        Database::update(storage, entered_drink);
    }
}

void MainWindow::add_new_row(Drink entered_drink) {
    /*
     * Add a new drink to the database.
     * @param entered_drink: A Drink containing data entered by the user.
     */

    // New row. Get a new timestamp
    std::string timestamp = storage.select(sqlite_orm::datetime("now")).front();
    entered_drink.timestamp = timestamp;

    // Convert ml to oz
    if (options.units == "Metric") {
        entered_drink._size = Calculate::ml_to_oz(entered_drink._size);
    }
    Database::write(entered_drink, storage);
}

void MainWindow::reset_fields() {
    /*
     * Clear user entry fields and table selection for entering a new drink.
     */

    std::string beer_notes;
    std::string liquor_notes;
    std::string wine_notes;

    std::string alcohol_type = get_current_tab();

    if (alcohol_type == "Beer") {
        update_beer_fields();
        update_types_and_producers();

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->beerDateInput->setDate(todays_date);
    } else if (alcohol_type == "Liquor") {
        update_liquor_fields();
        update_types_and_producers();

        // Set datepicker to today's date
        QDate todays_date = QDate::currentDate();
        ui->liquorDateInput->setDate(todays_date);
    } else if (alcohol_type == "Wine") {
        update_wine_fields();
        update_types_and_producers();

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
    //ui->drinkLogTable->sortItems(9, Qt::AscendingOrder);

    std::string filter_category = ui->filterCategoryInput->currentText().toStdString();
    std::string filter_text = ui->filterTextInput->currentText().toStdString();

    std::vector<Drink> drinks = Database::filter(filter_category, filter_text, storage);
    drinks = Database::sort_by_date_id(drinks);

    ui->drinkLogTable->setRowCount(0);
    for (const auto& drink : drinks) {
        int table_row_num = ui->drinkLogTable->rowCount();
        ui->drinkLogTable->insertRow(table_row_num);
        QDate date = QDate::fromString(QString::fromStdString(drink.date), "yyyy-MM-dd");
        auto *date_qtw = new QTableWidgetItem;
        auto *name = new QTableWidgetItem(drink.name.c_str());
        auto *type = new QTableWidgetItem(drink.type.c_str());
        auto *subtype = new QTableWidgetItem(drink.subtype.c_str());
        auto *producer = new QTableWidgetItem(drink.producer.c_str());
        auto *abv = new QTableWidgetItem(Calculate::double_to_string(drink.abv).c_str());
        auto *rating = new QTableWidgetItem(std::to_string(drink.rating).c_str());
        auto *id = new QTableWidgetItem;
        auto *timestamp = new QTableWidgetItem(drink.timestamp.c_str());
        auto *sort_order =  new QTableWidgetItem(drink.sort_order);

        // Calculate & Display size
        double drink_size = drink._size;
        if (options.units == "Metric") {
            drink_size = Calculate::oz_to_ml(drink_size);

            // Round to tenth place
            drink_size = floor(drink_size * 10 + 0.5) / 10;
        }
        auto *size = new QTableWidgetItem(Calculate::double_to_string(drink_size).c_str());

        // Sort ID numerically
        id->setData(Qt::DisplayRole, drink.id);
        sort_order->setData(Qt::DisplayRole, drink.sort_order);
        date_qtw->setData(Qt::DisplayRole, date);

        std::string notes = drink.notes;

        // Handle blank IBU
        auto *ibu = (drink.ibu == -1.0) ? new QTableWidgetItem("") : new QTableWidgetItem(Calculate::double_to_string(drink.ibu).c_str());

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
        ui->drinkLogTable->setItem(table_row_num, 11, sort_order);
    }
    reset_table_sort();
}

void MainWindow::delete_row() {
    /*
     * Delete the row in the database that corresponds to the row selected in the table.
     */

    ConfirmDialog confirmation_dialog = ConfirmDialog("Delete");
    if (confirmation_dialog.exec() == QDialog::Accepted) {
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
        update_wine_fields();
    }
}
