//
// Created by rossw on 10/12/2022.
//

#ifndef BUZZBOT_REPORTS_H
#define BUZZBOT_REPORTS_H

#include "database.h"
#include "../ui/ui_drink_report.h"

class Reports : public QDialog, public Ui::TopDrinkReportGui {
    Q_OBJECT
    Ui::TopDrinkReportGui ui{};
    Storage storage;

public:
    Reports(const Storage &in_storage) : storage(in_storage) {
        ui.setupUi(this);

        Drink first_drink {Database::get_drink_at_place(storage, Database::RecordPlace::First)};
        Drink last_drink {Database::get_drink_at_place(storage, Database::RecordPlace::Last)};

        QDate start_date_qdate {QDate::fromString(QString::fromStdString(first_drink.get_date()), "yyyy-MM-dd")};
        QDate end_date_qdate {QDate::fromString(QString::fromStdString(last_drink.get_date()), "yyyy-MM-dd")};

        ui.startDateEdit->setMinimumDate(start_date_qdate);
        ui.startDateEdit->setMaximumDate(end_date_qdate);
        ui.startDateEdit->setDate(start_date_qdate);
        ui.endDateEdit->setMinimumDate(start_date_qdate);
        ui.endDateEdit->setMaximumDate(end_date_qdate);
        ui.endDateEdit->setDate(end_date_qdate);

        run_query();

        connect(ui.topNumberSelection, &QSpinBox::valueChanged, this, &Reports::run_query);
        connect(ui.alcoholTypeSelection, &QComboBox::currentTextChanged, this, &Reports::run_query);
        connect(ui.startDateEdit, &QDateEdit::dateChanged, this, &Reports::run_query);
        connect(ui.endDateEdit, &QDateEdit::dateChanged, this, &Reports::run_query);
        connect(ui.ratingSelection, &QSpinBox::valueChanged, this, &Reports::run_query);
    };

private:
    void run_query();
    static bool sort_by_rating_then_name(const Drink & d1, const Drink & d2);
};


#endif //BUZZBOT_REPORTS_H
