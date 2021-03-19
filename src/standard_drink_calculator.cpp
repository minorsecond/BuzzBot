//
// Created by Ross Wardrup on 9/25/20.
//

#include "standard_drink_calculator.h"
#include "calculate.h"

StandardDrinkCalc::StandardDrinkCalc(QWidget *parent) {
    /*
     * UI for calculating standard drinks based on ABV & drink volume.
     */

    ui.setupUi(this);
    this->setFixedSize(237, 142);
    ui.standardDrinksOutput->setText("0");

    connect(ui.abvInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::abv_changed);
    connect(ui.volumeInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::volume_changed);
    connect(ui.stdDrinkCalcOkButton, &QPushButton::clicked, this, &StandardDrinkCalc::close);
}

void StandardDrinkCalc::volume_changed() {
    /*
     * Calculate standard drinks when volume number changes.
     */

    double volume = ui.volumeInput->value();
    double abv = ui.abvInput->value();

    std::string standard_drinks = Calculate::double_to_string(Calculate::standard_drinks(abv, volume));
    ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
}

void StandardDrinkCalc::abv_changed() {
    /*
     * Calculate standard drinks when ABV value changes.
     */

    double abv = ui.abvInput->value();
    double volume = ui.volumeInput->value();

    std::string standard_drinks = Calculate::double_to_string(Calculate::standard_drinks(abv, volume));
    ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
}


