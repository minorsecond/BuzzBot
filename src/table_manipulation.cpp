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
    Database::sort_by_date_id(drinks);

    ui->drinkLogTable->setRowCount(0);
    for (const auto& drink : drinks) {
        // These don't need to be deleted. The table widget takes ownership of these pointers and
        // will delete them as needed.
        const double std_drinks {Calculate::standard_drinks(drink.abv, drink._size, std::stod(options.std_drink_size))};
        std::cout << "Standard drinks: " << std_drinks << std::endl;
        int table_row_num = ui->drinkLogTable->rowCount();
        ui->drinkLogTable->insertRow(table_row_num);
        QDate date = QDate::fromString(QString::fromStdString(drink.date), "yyyy-MM-dd");
        auto *date_qtw = new QTableWidgetItem;
        auto *name = new QTableWidgetItem(drink.name.c_str());
        auto *type = new QTableWidgetItem(drink.type.c_str());
        auto *subtype = new QTableWidgetItem(drink.subtype.c_str());
        auto *producer = new QTableWidgetItem(drink.producer.c_str());
        auto *abv = new QTableWidgetItem(Calculate::double_to_string(drink.abv).c_str());
        auto *standard_drinks = new QTableWidgetItem(Calculate::double_to_string(std_drinks).c_str());
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
        ui->drinkLogTable->setItem(table_row_num, 8, standard_drinks);
        ui->drinkLogTable->setItem(table_row_num, 9, rating);
        ui->drinkLogTable->setItem(table_row_num, 10, id);
        ui->drinkLogTable->setItem(table_row_num, 11, timestamp);
        ui->drinkLogTable->setItem(table_row_num, 12, sort_order);
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
        int row_to_delete = (ui->drinkLogTable->item(select, 10)->text().toUtf8().toInt());
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

Drink MainWindow::get_drink_at_selected_row() {
    /*
     * Get drink at currently-selected row.
     * @return selected_drink: A Drink object.
     */

    Drink selected_drink;
    QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
    int selection = ui->drinkLogTable->selectionModel()->currentIndex().row();

    if (selection >= 0) {
        std::cout << "Getting row " << selection << " from table." << std::endl;
        int row_to_get = ui->drinkLogTable->item(selection, 10)->text().toUtf8().toInt();
        std::cout << "Getting row " << row_to_get << " from database." << std::endl;
        if (select->isRowSelected(selection))
            ui->deleteRowButton->setEnabled(true);
        else
            ui->deleteRowButton->setDisabled(true);

        selected_drink = Database::read_row(row_to_get, storage);

        if (options.units == "Metric") {
            selected_drink._size = Calculate::oz_to_ml(selected_drink._size);
        }
    }
    return selected_drink;
}

std::string MainWindow::get_latest_notes(const std::string& name) {
    /*
     * Get the latest entered notes for a specific drink.
     * @param name: The name to retrieve the notes for.
     * @return notes: String containing drink notes.
     */

    std::string notes;

    // First, try to get notes at the selected row
    Drink drink = get_drink_at_selected_row();
    notes = drink.notes;

    // Only run if notes are empty, or if the selected drink's alcohol type doesn't match that of the current tab
    if (notes.empty() || drink.alcohol_type != get_current_tab()) {
        // Get latest notes entered for the selected drink
        if (ui->tabWidget->currentIndex() == 0) {  // Update beer notes
            notes = Database::get_latest_notes(storage, name, "Beer");
        } else if (ui->tabWidget->currentIndex() == 1) {  // Update liquor notes
            notes = Database::get_latest_notes(storage, name, "Liquor");
        } else if (ui->tabWidget->currentIndex() == 2) {  // Update wine notes
            notes = Database::get_latest_notes(storage, name, "Wine");
        }
    }

    return notes;
}

void MainWindow::reset_table_sort() {
    /*
     * Reset table sort to default, by datetime descending.
     */
    int sort_column = 12;
    std::cout << "Sorting by column: " << ui->drinkLogTable->horizontalHeaderItem(sort_column)->text().toStdString() << std::endl;
    ui->drinkLogTable->sortItems(sort_column, Qt::DescendingOrder);
}
