//
// Created by Ross Wardrup on 9/10/20.
//

#include "../src/calculate.h"
#include "../src/mainwindow.h"
#include <filesystem>
#include <iostream>
#if __has_include("catch2/catch_test_macros.hpp")
#include <catch2/catch_test_macros.hpp>
#else
#include <catch2/catch.hpp>
#endif

TEST_CASE("Standard Drinks", "[Drink Calculations]") {
    double mosaic_standard_drinks = Calculate::standard_drinks(8.6, 12, 0.6);
    double etrwo_standard_drinks = Calculate::standard_drinks(6.5, 12, 0.6);
    double old_rasputin_standard_drinks = Calculate::standard_drinks(9, 12, 0.6);
    double asahi_super_dry_standard_drinks = Calculate::standard_drinks(5.2, 354.88, 12.7);

    REQUIRE(mosaic_standard_drinks == 1.72);
    REQUIRE(etrwo_standard_drinks == 1.30);
    REQUIRE(old_rasputin_standard_drinks == 1.80);
    REQUIRE(asahi_super_dry_standard_drinks == 1.45);
}

TEST_CASE("Oz Alcohol", "[Drink Calculations]") {
    double mosaic_oz_alcohol = Calculate::alcohol_volume(8.6, 12);
    double etrwo_oz_alcohol = Calculate::alcohol_volume(6.5, 12);
    double old_rasputin_oz_alcohol = Calculate::alcohol_volume(9, 12);

    REQUIRE(mosaic_oz_alcohol == 1.032);
    REQUIRE(etrwo_oz_alcohol == 0.78);
    REQUIRE(old_rasputin_oz_alcohol == 1.08);
}

TEST_CASE("Std Drinks Remaining - male, NIAAA", "[Drink Calculations]") {
    Options options;
    options.sex = "male";
    options.limit_standard = "NIAAA";
    options.weekly_limit = 0;

    double male_drinks_remaining = Calculate::standard_drinks_remaining(options, 4.6);

    REQUIRE(male_drinks_remaining == 9.4);
}

TEST_CASE("Std Drinks Remaining - female, Custom", "[Drink Calculations]") {
    Options options;
    options.sex = "female";
    options.limit_standard = "Custom";
    options.weekly_limit = 5;

    double female_drinks_remaining = Calculate::standard_drinks_remaining(options, 8);
    REQUIRE(female_drinks_remaining == -3.0);
}

TEST_CASE("Std Drinks Remaining - female, NIAAA 1", "[Drink Calculations]") {
    Options options;
    options.sex = "female";
    options.limit_standard = "NIAAA";
    options.weekly_limit = 0;

    double female_drinks_remaining_2 = Calculate::standard_drinks_remaining(options, 4);
    REQUIRE(female_drinks_remaining_2 == 3);
}

TEST_CASE("Std Drinks Remaining - female, NIAAA 2", "[Drink Calculations]") {
    Options options;
    options.sex = "female";
    options.limit_standard = "NIAAA";
    options.weekly_limit = 0;

    double female_drinks_remaining_3 = Calculate::standard_drinks_remaining(options, 12);

    REQUIRE(female_drinks_remaining_3 == -5);
}

TEST_CASE("Oz Alcohol Remaining", "[Drink Calculations]") {
    Options options;
    options.sex = "male";
    options.limit_standard = "NIAA";
    options.weekly_limit = 14;
    double male_oz_remaining = Calculate::volume_alcohol_remaining(options, 4.3);

    options.sex = "female";
    options.limit_standard = "Custom";
    options.weekly_limit = 10;
    double female_oz_remaining = Calculate::volume_alcohol_remaining(options, 5.5);

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

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.",  -1, "Beer", "2020-01-01 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-01-01 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10",
                 "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "",
                 -1, "Beer", "2020-01-01 00:00:00", 1};

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

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08",
                "Everything Rhymes with Orange", "IPA", "","Roughtail Brewing", 8.0,
                60.0, 12.0, 8, "Very good hazy IPA.",  -1, "Beer",
                "2020-01-01 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA",
                 "","Community Brewing", 8.4, 75.0, 12.0, 8,
                 "",  -1, "Beer", "2020-01-01 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10",
                 "Everything Rhymes with Orange", "IPA", "","Roughtail Brewing",
                 8.0, 60.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};

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

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "Very good hazy IPA.",  -1, "Beer",
                "2020-01-01 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10", "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};

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

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "Very good hazy IPA.",  -1, "Beer",
                "2020-01-01 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10", "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};

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

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "Very good hazy IPA.",  -1, "Beer",
                "2020-01-01 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10", "Old Rasputin", "Russian Imperial Stout", "",
                 "North Coast Brewing", 9.0, 75.0, 12.0, 8, "",  -1, "Beer",
                 "2020-01-01 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::string favorite_type = Calculate::favorite_type(storage_1, "Beer");
    REQUIRE(favorite_type == "IPA");
}

TEST_CASE("String Comparison", "[Misc Calculations]") {
    std::string lhs = "WWW";
    std::string rhs = "aaa";
    REQUIRE(Calculate::compare_strings(lhs, rhs) == false);
}