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

    ui.stdDrinkInput->setValue(std_drink_size);

    if (units == "Metric") {
        ui.stdDrinkLabel->setText("1 Std. Drink (ml alcohol)");
    } else {
        ui.stdDrinkLabel->setText("1 std. Drink (oz alcohol)");
    }

    connect(ui.abvInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::abv_changed);
    connect(ui.volumeInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::volume_changed);
    connect(ui.stdDrinkInput, &QDoubleSpinBox::textChanged, this, &StandardDrinkCalc::std_drinks_changed);
    connect(ui.stdDrinkCalcOkButton, &QPushButton::clicked, this, &StandardDrinkCalc::close);
}

void StandardDrinkCalc::volume_changed() {
    /*
     * Calculate standard drinks when volume number changes.
     */

    double volume = ui.volumeInput->value();
    double abv = ui.abvInput->value();
    double std_drink = ui.stdDrinkInput->value();

    if (std_drink > 0) {
        std::string standard_drinks = Calculate::double_to_string(Calculate::standard_drinks(abv, volume, std_drink));
        ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
    } else {
        ui.standardDrinksOutput->setText(QString::fromStdString("Std. Drinks = 0"));
    }
}

void StandardDrinkCalc::abv_changed() {
    /*
     * Calculate standard drinks when ABV value changes.
     */

    double abv = ui.abvInput->value();
    double volume = ui.volumeInput->value();
    double std_drink = ui.stdDrinkInput->value();

    if (std_drink > 0) {
        std::string standard_drinks = Calculate::double_to_string(Calculate::standard_drinks(abv, volume, std_drink));
        ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
    } else {
        ui.standardDrinksOutput->setText(QString::fromStdString("Std. Drinks = 0"));
    }
}

void StandardDrinkCalc::std_drinks_changed() {
    /*
     * Calculate standard drinks when std drink value changes.
     */

    double abv = ui.abvInput->value();
    double volume = ui.volumeInput->value();
    double std_drink = ui.stdDrinkInput->value();

    if (std_drink > 0) {
        std::string standard_drinks = Calculate::double_to_string(Calculate::standard_drinks(abv, volume, std_drink));
        ui.standardDrinksOutput->setText(QString::fromStdString(standard_drinks));
    } else {
        ui.standardDrinksOutput->setText(QString::fromStdString("Std. Drinks = 0"));
    }
}

StandardDrinkCalc::~StandardDrinkCalc() {
    std::cout << "Deleted StandardDrinkCalc" << std::endl;
}


