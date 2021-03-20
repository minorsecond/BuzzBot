//
// Created by Ross Wardrup on 9/10/20.
//

#include "../include/Catch2.hpp"
#include "../src/calculate.h"
#include <filesystem>
#include <iostream>

TEST_CASE("Standard Drinks", "[Drink Calculations]") {
    double mosaic_standard_drinks = Calculate::standard_drinks(8.6, 12);
    double etrwo_standard_drinks = Calculate::standard_drinks(6.5, 12);
    double old_rasputin_standard_drinks = Calculate::standard_drinks(9, 12);

    REQUIRE(mosaic_standard_drinks == 1.72);
    REQUIRE(etrwo_standard_drinks == 1.30);
    REQUIRE(old_rasputin_standard_drinks == 1.80);
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
    double male_drinks_remaining = Calculate::standard_drinks_remaining("male", "NIAAA", 0, 4.6);
    double female_drinks_remaining = Calculate::standard_drinks_remaining("female", "Custom", 5, 8);

    REQUIRE(male_drinks_remaining == 9.4);
    REQUIRE(female_drinks_remaining == -3.0);
}

TEST_CASE("Oz Alcohol Remaining", "[Drink Calculations]") {
    double male_oz_remaining = Calculate::oz_alcohol_remaining("male", "NIAAA", 0, 4.3);
    double female_oz_remaining = Calculate::oz_alcohol_remaining("female", "Custom", 10, 5.5);

    REQUIRE(male_oz_remaining == 4.1);
    REQUIRE(female_oz_remaining == 0.5);
}

TEST_CASE("Mean ABV", "[Drink Calculations]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", 2020, 9, 8, "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, "Very good hazy IPA."};
    Drink mosaic{-1, "2020-09-08", 2020, 9, 8, "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12, 12.0, 8, ""};
    Drink etrwo2{-1, "2020-09-10", 2020, 9, 10, "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    double mean_abv = Calculate::mean_abv(storage_1, "Beer");

    REQUIRE(mean_abv == 8.13);
}

TEST_CASE("Mean IBU", "[Drink Calculations]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", 2020, 9, 8, "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, "Very good hazy IPA."};
    Drink mosaic{-1, "2020-09-08", 2020, 9, 8, "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12, 12.0, 8, ""};
    Drink etrwo2{-1, "2020-09-10", 2020, 9, 10, "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    double mean_ibu = Calculate::mean_ibu(storage_1, "Beer");

    REQUIRE(mean_ibu == 65);
}

TEST_CASE("Favorite Brewery", "[Favorite Calculations]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", 2020, 9, 8, "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, "Very good hazy IPA."};
    Drink mosaic{-1, "2020-09-08", 2020, 9, 8, "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12, 12.0, 8, ""};
    Drink etrwo2{-1, "2020-09-10", 2020, 9, 10, "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::string favorite_brewery = Calculate::favorite_producer(storage_1, "Beer");
    REQUIRE(favorite_brewery == "Roughtail Brewing");
}

TEST_CASE("Favorite Drink", "[Favorite Calculations]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", 2020, 9, 8, "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, "Very good hazy IPA."};
    Drink mosaic{-1, "2020-09-08", 2020, 9, 8, "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12, 12.0, 8, ""};
    Drink etrwo2{-1, "2020-09-10", 2020, 9, 10, "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::string favorite_beer = Calculate::favorite_drink(storage_1, "Beer");
    REQUIRE(favorite_beer == "Everything Rhymes with Orange");
}

TEST_CASE("Favorite Type", "[Favorite Calculations]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", 2020, 9, 8, "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12, 12.0, 8, "Very good hazy IPA."};
    Drink mosaic{-1, "2020-09-08", 2020, 9, 8, "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12, 12.0, 8, ""};
    Drink etrwo2{-1, "2020-09-10", 2020, 9, 10, "Old Rasputin", "Russian Imperial Stout", "",
                 "North Coast Brewing", 9.0, 75.0, 12, 12.0, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::string favorite_type = Calculate::favorite_type(storage_1, "Beer");
    REQUIRE(favorite_type == "IPA");
}