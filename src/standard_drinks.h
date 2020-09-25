//
// Created by Ross Wardrup on 9/25/20.
//

#ifndef BUZZBOT_STANDARD_DRINKS_H
#define BUZZBOT_STANDARD_DRINKS_H

#include <QDialog>
#include "ui_standard_drink_calc.h"

class StandardDrinkCalc : public QDialog, public Ui::stdDrinkDialog {
    /*
     * Standard drink calculation dialog.
     */

    Q_OBJECT
    Ui::stdDrinkDialog ui{};

public:
    explicit StandardDrinkCalc(QWidget *parent = nullptr);

private slots:
    void volume_changed();
    void abv_changed();

};

#endif //BUZZBOT_STANDARD_DRINKS_H
