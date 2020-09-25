//
// Created by Ross Wardrup on 9/25/20.
//

#include "standard_drinks.h"
#include "calculate.h"

StandardDrinkCalc::StandardDrinkCalc(QWidget *parent) {
    /*
     * UI for calculating standard drinks based on ABV & drink volume.
     */

    ui.setupUi(this);
    ui.standardDrinksOutput->setText(" ");

    connect(ui.abvInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::abv_changed);
    connect(ui.volumeInput, &QSpinBox::textChanged, this, &StandardDrinkCalc::volume_changed);

}

void StandardDrinkCalc::volume_changed() {
    /*
     * Calculate standard drinks when volume number changes.
     */

    int volume = ui.volumeInput->value();
    double abv = ui.abvInput->value();

    double standard_drinks = Calculate::round_to_two_decimal_points(Calculate::standard_drinks(abv, volume));
    ui.standardDrinksOutput->setText(QString::fromStdString(std::to_string(standard_drinks)));
}

void StandardDrinkCalc::abv_changed() {
    /*
     * Calculate standard drinks when ABV value changes.
     */

    double abv = ui.abvInput->value();
    int volume = ui.volumeInput->value();

    double standard_drinks = Calculate::round_to_two_decimal_points(Calculate::standard_drinks(abv, volume));
    ui.standardDrinksOutput->setText(QString::fromStdString(std::to_string(standard_drinks)));
}


