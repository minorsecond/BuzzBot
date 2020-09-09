#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

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
    //ui->drinkLogTable->setRowCount(0);

    // Set column widths
    ui->drinkLogTable->setColumnWidth(0, 100);
    ui->drinkLogTable->setColumnWidth(1, 453);
    ui->drinkLogTable->setColumnWidth(2, 200);
    ui->drinkLogTable->setColumnWidth(3, 453);
    ui->drinkLogTable->setColumnWidth(4, 50);
    ui->drinkLogTable->setColumnWidth(5, 50);
    ui->drinkLogTable->setColumnWidth(6, 50);
    //QHeaderView* drink_log_header = ui->drinkLogTable->horizontalHeader();
    //drink_log_header->setSectionResizeMode(7, QHeaderView::Stretch);

    // Slot connections
    connect(ui->submitRowButton, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
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
        notes
    };
    Database::write(beer);
}

void MainWindow::update_table() {

}
