//
// Created by Ross Wardrup on 9/10/20.
//

#include "../include/Catch2.hpp"
#include "../src/calculate.h"

TEST_CASE("Standard Drinks", "[Drink Calculations]") {

    double mosaic_standard_drinks = Calculate::standard_drinks(8.6, 12);
    double etrwo_standard_drinks = Calculate::standard_drinks(6.5, 12);
    double old_rasputin_standard_drinks = Calculate::standard_drinks(9, 12);

    REQUIRE(mosaic_standard_drinks == 1.7);
    REQUIRE(etrwo_standard_drinks == 1.3);
    REQUIRE(old_rasputin_standard_drinks == 1.8);
}

TEST_CASE("Oz Alcohol", "[Drink Calculations]") {
    double mosaic_oz_alcohol = Calculate::oz_alcohol(8.6, 12);
    double etrwo_oz_alcohol = Calculate::oz_alcohol(6.5, 12);
    double old_rasputin_oz_alcohol = Calculate::oz_alcohol(9, 12);

    REQUIRE(mosaic_oz_alcohol == 1.032);
    REQUIRE(etrwo_oz_alcohol == 0.78);
    REQUIRE(old_rasputin_oz_alcohol == 1.08);
}

TEST_CASE("Std Drinks Remaining", "[Drink Calculations]") {
    double male_drinks_remaining = Calculate::standard_drinks_remaining("male", 4.6);
    double female_drinks_remaining = Calculate::standard_drinks_remaining("female", 8);

    REQUIRE(male_drinks_remaining == 9.4);
    REQUIRE(female_drinks_remaining == 0);
}