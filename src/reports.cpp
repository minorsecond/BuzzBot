//
// Created by rossw on 10/12/2022.
//

#include "reports.h"
#include "calculate.h"
#include <string>

void Reports::run_query() {
    const unsigned num_records {static_cast<unsigned>(ui.topNumberSelection->value())};
    const std::string type {ui.alcoholTypeSelection->currentText().toStdString()};
    const std::string start_date {ui.startDateEdit->date().toString("yyyy-MM-dd").toStdString()};
    const std::string end_date {ui.endDateEdit->date().toString("yyyy-MM-dd").toStdString()};
    const unsigned rating {static_cast<unsigned>(ui.ratingSelection->value())};

    std::vector<Drink> results {Database::report_query(this->storage, rating, num_records, type, start_date, end_date)};
    std::sort(results.begin(), results.end(), sort_by_rating_then_name);

    ui.queryResults->setRowCount(0);
    for (const Drink &drink : results) {
        const int table_row_num {ui.queryResults->rowCount()};
        ui.queryResults->insertRow(table_row_num);
        auto *name = new QTableWidgetItem(drink.get_name().c_str());
        auto *table_type = new QTableWidgetItem(drink.get_type().c_str());
        auto *subtype = new QTableWidgetItem(drink.get_subtype().c_str());
        auto *producer = new QTableWidgetItem(drink.get_producer().c_str());
        auto *table_rating = new QTableWidgetItem(std::to_string(drink.get_rating()).c_str());

        ui.queryResults->setItem(table_row_num, 0, name);
        ui.queryResults->setItem(table_row_num, 1, table_type);
        ui.queryResults->setItem(table_row_num, 2, subtype);
        ui.queryResults->setItem(table_row_num, 3, producer);
        ui.queryResults->setItem(table_row_num, 4, table_rating);
    }
}

bool Reports::sort_by_rating_then_name(const Drink &d1, const Drink &d2) {
    /*
     * Sort Drink by rating and then name
     * @param d1: Drink object 1
     * @param d2: Drink object 2
     * @return: Boolean
     */
    if( d1.get_rating() != d2.get_rating())
        return (d1.get_rating() > d2.get_rating());
    return Calculate::compare_strings(d1.get_name(), d2.get_name());
}
