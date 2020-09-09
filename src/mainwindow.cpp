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

    Database db;
    std::string database_path = db.path();
    Storage storage = initStorage(database_path);
    db.write_db_to_disk(storage);

    // Set datepicker to today's date
    QDate todays_date = QDate::currentDate();
    ui->drinkDateInput->setDate(todays_date);

    // Enable this on release
    ui->drinkLogTable->setRowCount(0);

    update_table();

    // Set table filter options to default values (all)
    ui->filterCategoryInput->addItem("None");
    ui->filterTextInput->addItem("All");

    // Set column widths
    ui->drinkLogTable->setColumnWidth(0, 100);
    ui->drinkLogTable->setColumnWidth(1, 453);
    ui->drinkLogTable->setColumnWidth(2, 200);
    ui->drinkLogTable->setColumnWidth(3, 453);
    ui->drinkLogTable->setColumnWidth(4, 50);
    ui->drinkLogTable->setColumnWidth(5, 50);
    ui->drinkLogTable->setColumnWidth(6, 50);
    ui->drinkLogTable->horizontalHeader()->setStretchLastSection(true);
    //QHeaderView* drink_log_header = ui->drinkLogTable->horizontalHeader();
    //drink_log_header->setSectionResizeMode(7, QHeaderView::Stretch);

    // Slot connections
    connect(ui->drinkLogTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection&)),
            this, SLOT(populate_fields(const QItemSelection &, const QItemSelection &)));
    connect(ui->submitRowButton, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
    connect(ui->clearFieldsButton, SIGNAL(clicked()), this, SLOT(clear_fields()));
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
        notes
    };
    Database::write(beer);
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
}

void MainWindow::update_table() {
    /*
     * Populate the table with data from the database.
     */

    std::string filter_category = ui->filterCategoryInput->currentText().toStdString();
    std::string filter_text = ui->filterTextInput->currentText().toStdString();

    std::vector<Beer> beers = Database::filter(filter_category, filter_text);

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
        auto *id = new QTableWidgetItem(std::to_string(beer.id).c_str());

        std::string notes = beer.notes;

        ui->drinkLogTable->setItem(table_row_num, 0, date);
        ui->drinkLogTable->setItem(table_row_num, 1, name);
        ui->drinkLogTable->setItem(table_row_num, 2, type);
        ui->drinkLogTable->setItem(table_row_num, 3, brewery);
        ui->drinkLogTable->setItem(table_row_num, 4, abv);
        ui->drinkLogTable->setItem(table_row_num, 5, ibu);
        ui->drinkLogTable->setItem(table_row_num, 6, size);
        ui->drinkLogTable->setItem(table_row_num, 7, id);

        table_row_num += 1;
    }

}

std::string MainWindow::double_to_string(double input_double) {
    double purchase_price = std::ceil(input_double * 10.0) / 10.0;
    std::ostringstream price_stream;
    price_stream << purchase_price;

    return price_stream.str();
}

void MainWindow::populate_fields(const QItemSelection &, const QItemSelection &) {

    QItemSelectionModel *select = ui->drinkLogTable->selectionModel();
    int selection = ui->drinkLogTable->selectionModel()->currentIndex().row();
    int column_count = ui->drinkLogTable->columnCount();
    int row_to_get = ui->drinkLogTable->item(selection, 7)->text().toUtf8().toInt();
    if (select->isRowSelected(selection))
        ui->deleteRowButton->setEnabled(true);
    else
        ui->deleteRowButton->setDisabled(true);
    Beer beer = Database::read_row(row_to_get);

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
}
