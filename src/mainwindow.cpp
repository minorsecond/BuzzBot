#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*
     * Set up the main window
     */

    ui->setupUi(this);
    this->setFixedSize(1397, 699);

    //std::string database_path = Database::path();
    Database::write_db_to_disk(storage);

    // Set up button and input states

    ui->deleteRowButton->setDisabled(true);
    ui->nameInput->setDuplicatesEnabled(false);
    ui->typeInput->setDuplicatesEnabled(false);
    ui->breweryInput->setDuplicatesEnabled(false);

    // Set datepicker to today's date
    QDate todays_date = QDate::currentDate();
    ui->drinkDateInput->setDate(todays_date);

    // Enable this on release
    ui->drinkLogTable->setRowCount(0);

    update_table();

    // Set table filter options to default values (all)
    ui->filterCategoryInput->addItem("None");
    ui->filterCategoryInput->setCurrentText("None");
    ui->filterCategoryInput->addItem("Name");
    ui->filterCategoryInput->addItem("Type");
    ui->filterCategoryInput->addItem("Brewery");
    ui->filterCategoryInput->addItem("Rating");

    ui->filterTextInput->setDisabled(true);

    // Set column widths
    ui->drinkLogTable->setColumnWidth(0, 100);
    ui->drinkLogTable->setColumnWidth(1, 428);
    ui->drinkLogTable->setColumnWidth(2, 200);
    ui->drinkLogTable->setColumnWidth(3, 428);
    ui->drinkLogTable->setColumnWidth(4, 50);
    ui->drinkLogTable->setColumnWidth(5, 50);
    ui->drinkLogTable->setColumnWidth(6, 50);
    ui->drinkLogTable->setColumnHidden(8, true);  // Hide ID column
    QHeaderView* drink_log_header = ui->drinkLogTable->horizontalHeader();
    drink_log_header->setSectionResizeMode(7, QHeaderView::Stretch);

    // Slot connections
    connect(ui->drinkLogTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection&)),
            this, SLOT(populate_fields(const QItemSelection &, const QItemSelection &)));
    connect(ui->filterCategoryInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(enable_filter_text(const QString&)));
    connect(ui->filterTextInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(changed_filter_text(const QString&)));
    connect(ui->submitRowButton, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
    connect(ui->clearFieldsButton, SIGNAL(clicked()), this, SLOT(clear_fields()));
    connect(ui->deleteRowButton, SIGNAL(clicked()), this, SLOT(delete_row()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submit_button_clicked() {
    /*
     * Create a beer from user input and write it to the database.
     */

    int drink_year = ui->drinkDateInput->date().year();
    int drink_month = ui->drinkDateInput->date().month();
    int drink_day = ui->drinkDateInput->date().day();
    std::string beer_name = ui->nameInput->currentText().toStdString();
    std::string beer_type = ui->typeInput->currentText().toStdString();
    std::string brewery_name = ui->breweryInput->currentText().toStdString();
    double beer_ibu = ui->ibuInput->value();
    double beer_abv = ui->abvInput->value();
    double beer_size = ui->sizeInput->value();
    int rating = ui->ratingInput->value();
    std::string notes = ui->notesInput->toPlainText().toStdString();

    Beer beer{
        -1,
        drink_year,
        drink_month,
        drink_day,
        beer_name,
        beer_type,
        brewery_name,
        beer_abv,
        beer_ibu,
        beer_size,
        rating,
        notes
    };
    Database::write(beer, storage);
    update_table();
}

void MainWindow::clear_fields() {
    /*
     * Clear user entry fields for entering a new beer.
     */

    std::cout << "clearing fields" << std::endl;

    QDate todays_date = QDate::currentDate();
    ui->drinkDateInput->setDate(todays_date);
    ui->breweryInput->setCurrentIndex(0);
    ui->typeInput->setCurrentIndex(0);
    ui->nameInput->setCurrentIndex(0);
    ui->notesInput->clear();
    ui->abvInput->setValue(0.0);
    ui->ibuInput->setValue(0.0);
    ui->sizeInput->setValue(0.0);
    ui->ratingInput->setValue(0);
}

void MainWindow::update_table() {
    /*
     * Populate the table with data from the database.
     */

    std::string filter_category = ui->filterCategoryInput->currentText().toStdString();
    std::string filter_text = ui->filterTextInput->currentText().toStdString();

    std::vector<Beer> beers = Database::filter(filter_category, filter_text, storage);

    std::cout << beers.size() << " rows in the database." << std::endl;

    ui->drinkLogTable->setRowCount(beers.size());

    int table_row_num = 0;
    for (const auto& beer : beers) {
        auto *date = new QTableWidgetItem((std::to_string(beer.drink_year) + "/" +
                std::to_string(beer.drink_month) + "/" + std::to_string(beer.drink_day)).c_str());
        auto *name = new QTableWidgetItem(beer.name.c_str());
        auto *type = new QTableWidgetItem(beer.type.c_str());
        auto *brewery = new QTableWidgetItem(beer.brewery.c_str());
        auto *abv = new QTableWidgetItem(double_to_string(beer.abv).c_str());
        auto *ibu = new QTableWidgetItem(double_to_string(beer.ibu).c_str());
        auto *size = new QTableWidgetItem(double_to_string(beer.size).c_str());
        auto *rating = new QTableWidgetItem(std::to_string(beer.rating).c_str());
        auto *id = new QTableWidgetItem(std::to_string(beer.id).c_str());

        std::string notes = beer.notes;

        ui->drinkLogTable->setItem(table_row_num, 0, date);
        ui->drinkLogTable->setItem(table_row_num, 1, name);
        ui->drinkLogTable->setItem(table_row_num, 2, type);
        ui->drinkLogTable->setItem(table_row_num, 3, brewery);
        ui->drinkLogTable->setItem(table_row_num, 4, abv);
        ui->drinkLogTable->setItem(table_row_num, 5, ibu);
        ui->drinkLogTable->setItem(table_row_num, 6, size);
        ui->drinkLogTable->setItem(table_row_num, 7, rating);
        ui->drinkLogTable->setItem(table_row_num, 8, id);

        table_row_num += 1;
    }
    std::cout << table_row_num << " rows in the table." << std::endl;
}

std::string MainWindow::double_to_string(double input_double) {
    /*
     * Convert a double to a string with 1 decimal value.
     * @param input_double: Double value that should be converted.
     */

    double purchase_price = std::ceil(input_double * 10.0) / 10.0;
    std::ostringstream price_stream;
    price_stream << purchase_price;

    return price_stream.str();
}

void MainWindow::populate_fields(const QItemSelection &, const QItemSelection &) {
    /*
     * Populate user entry fields when user clicks on a row in the table.
     */

    QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
    int selection = ui->drinkLogTable->selectionModel()->currentIndex().row();
    std::cout << "Getting row " << selection << " from table." << std::endl;
    int row_to_get = ui->drinkLogTable->item(selection, 8)->text().toUtf8().toInt();
    std::cout << "Getting row " << row_to_get << " from database." << std::endl;
    if (select->isRowSelected(selection))
        ui->deleteRowButton->setEnabled(true);
    else
        ui->deleteRowButton->setDisabled(true);
    Beer beer = Database::read_row(row_to_get, storage);

    std::ostringstream month_padded;
    std::ostringstream day_padded;

    month_padded << std::setw(2) << std::setfill('0') << beer.drink_month;
    day_padded << std::setw(2) << std::setfill('0') << beer.drink_day;
    std::string date_from_db = day_padded.str() + "/" + month_padded.str() + "/" + std::to_string(beer.drink_year);
    QDate date = QDate::fromString(QString::fromUtf8(date_from_db.c_str()), "dd/MM/yyyy");

    ui->drinkDateInput->setDate(date);
    ui->nameInput->setCurrentText(beer.name.c_str());
    ui->typeInput->setCurrentText(beer.type.c_str());
    ui->breweryInput->setCurrentText(beer.type.c_str());
    ui->abvInput->setValue(beer.abv);
    ui->ibuInput->setValue(beer.ibu);
    ui->sizeInput->setValue(beer.size);
    ui->sizeInput->setValue(beer.rating);
}

void MainWindow::delete_row() {
    /*
     * Delete the row in the database that corresponds to the row selected in the table.
     */

    int select = ui->drinkLogTable->selectionModel()->currentIndex().row();
    int row_to_delete = (ui->drinkLogTable->item(select, 8)->text().toUtf8().toInt());
    Database::delete_row(storage, row_to_delete);
    update_table();
}

void MainWindow::populate_filter_menus(const std::string& filter_type) {
    /*
     * Populate the filter menus depending on user selection.
     * @param filter type: Type of filter to use. Options in beer name (name), beer type (type) and brewery.
     */

    std::set<QString> beer_names;
    std::set<QString> beer_types;
    std::set<QString> breweries;
    std::set<QString> ratings;

    // This fixes crashes when changing filters with rows selected.
    QSignalBlocker filterTextInputSignalBlocker(ui->filterTextInput);

    std::vector<Beer> all_beers = Database::read(Database::path(), storage);

    ui->filterTextInput->clear();

    // Add items to the sets
    for (const auto& beer : all_beers) {
        QString beer_name = QString::fromStdString(beer.name);
        QString beer_type = QString::fromStdString(beer.type);
        QString brewery = QString::fromStdString(beer.brewery);
        QString rating = QString::fromStdString(std::to_string(beer.rating));

        beer_names.insert(beer_name);
        beer_types.insert(beer_type);
        breweries.insert(brewery);
        ratings.insert(rating);
    }

    if (filter_type == "Name") {
        for (const auto& name : beer_names) {
            ui->filterTextInput->addItem(name);
        }
    } else if (filter_type == "Type") {
        for (const auto& type : beer_types) {
            ui->filterTextInput->addItem(type);
        }
    } else if (filter_type == "Brewery") {
        for (const auto& brewery : breweries) {
            ui->filterTextInput->addItem(brewery);
        }
    } else if (filter_type == "Rating") {
        for (auto rating : ratings) {
            ui->filterTextInput->addItem(rating);
        }
    }
}

void MainWindow::enable_filter_text(const QString&) {
    /*
     * Enable the filter text combobox when user selects anything other than None in the filter category box.
     */

    if (ui->filterCategoryInput->currentText().toStdString() == "None")
        ui->filterTextInput->setDisabled(true);
    else
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
