//
// Created by Ross Wardrup on 9/25/20.
//

#ifndef BUZZBOT_STANDARD_DRINK_CALCULATOR_H
#define BUZZBOT_STANDARD_DRINK_CALCULATOR_H

#include <QDialog>
#include "ui_standard_drink_calc.h"

class StandardDrinkCalc : public QDialog, public Ui::stdDrinkDialog {
    /*
     * Standard drink calculation dialog.
     */

    Q_OBJECT
    Ui::stdDrinkDialog ui{};

public:
    explicit StandardDrinkCalc(QWidget *parent = nullptr, const double std_drink_size = 0.6, const std::string& units = "Imperial");

private slots:
    void volume_changed();
    void abv_changed();
    void std_drinks_changed();
};

#endif //BUZZBOT_STANDARD_DRINK_CALCULATOR_H
