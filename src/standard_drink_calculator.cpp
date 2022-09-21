//
// Created by Ross Wardrup on 9/25/20.
//

#include "standard_drink_calculator.h"
#include "calculate.h"
#include <iostream>

StandardDrinkCalc::StandardDrinkCalc(const double std_drink_size, const std::string& units) {
    /*
     * UI for calculating standard drinks based on ABV & drink volume.
     */

    ui.setupUi(this);
    this->setFixedSize(275, 175);
    ui.standardDrinksOutput->setText("0");

    connect(ui.abvInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::abv_changed);
    connect(ui.volumeInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::volume_changed);
    connect(ui.stdDrinkCalcOkButton, &QPushButton::clicked, this, &StandardDrinkCalc::close);
}

void StandardDrinkCalc::volume_changed() {
    /*
     * Calculate standard drinks when volume number changes.
     */

    Drink drink;
    drink.set_size(ui.volumeInput->value());
    drink.set_abv(ui.abvInput->value());

    const double std_drink {drink.standard_drinks()};
    if (std_drink > 0) {
        std::string standard_drinks = Calculate::double_to_string(std_drink);
        ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
    } else {
        ui.standardDrinksOutput->setText(QString::fromStdString("Std. Drinks = 0"));
    }
}

void StandardDrinkCalc::abv_changed() {
    /*
     * Calculate standard drinks when ABV value changes.
     */

    Drink drink;
    drink.set_size(ui.volumeInput->value());
    drink.set_abv(ui.abvInput->value());

    const double std_drink {drink.standard_drinks()};
    if (std_drink > 0) {
        std::string standard_drinks = Calculate::double_to_string(std_drink);
        ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
    } else {
        ui.standardDrinksOutput->setText(QString::fromStdString("Std. Drinks = 0"));
    }
}

StandardDrinkCalc::~StandardDrinkCalc() {
    std::cout << "Deleted StandardDrinkCalc" << std::endl;
}


