//
// Created by Ross Wardrup on 9/10/20.
//

#include "../src/calculate.h"
#include <filesystem>
#include <iostream>
#if __has_include("catch2/catch_test_macros.hpp")
#include <catch2/catch_test_macros.hpp>
#else
#include <catch2/catch.hpp>
#endif

TEST_CASE("Standard Drinks", "[Drink Calculations]") {

    Drink mosaic;
    Drink etrwo;
    Drink old_rasputin;
    Drink asahi;

    mosaic.set_abv(8.6);
    mosaic.set_size(12);
    etrwo.set_abv(6.5);
    etrwo.set_size(12);
    old_rasputin.set_abv(9);
    old_rasputin.set_size(12);
    asahi.set_abv(5.2);
    asahi.set_size(12);

    REQUIRE(Calculate::equal_double(mosaic.get_standard_drinks(), 1.72));
    REQUIRE(Calculate::equal_double(etrwo.get_standard_drinks(), 1.30));
    REQUIRE(Calculate::equal_double(old_rasputin.get_standard_drinks(), 1.80));
    REQUIRE(Calculate::equal_double(asahi.get_standard_drinks(), 1.04));
}

TEST_CASE("Oz Alcohol", "[Drink Calculations]") {

    Drink mosaic;
    Drink etrwo;
    Drink old_rasputin;

    mosaic.set_abv(8.6);
    mosaic.set_size(12);
    etrwo.set_abv(6.5);
    etrwo.set_size(12);
    old_rasputin.set_abv(9);
    old_rasputin.set_size(12);

    REQUIRE(Calculate::equal_double(mosaic.get_alcohol_volume(), 1.032));
    REQUIRE(Calculate::equal_double(etrwo.get_alcohol_volume(), 0.78));
    REQUIRE(Calculate::equal_double(old_rasputin.get_alcohol_volume(), 1.08));
}

TEST_CASE("Std Drinks Remaining - male, NIAAA", "[Drink Calculations]") {
    Options options;
    options.sex = "male";
    options.limit_standard = "NIAAA";
    options.weekly_limit = 0;

    double male_drinks_remaining = Calculate::standard_drinks_remaining(options, 4.6);

    REQUIRE(Calculate::equal_double(male_drinks_remaining, 9.4));
}

TEST_CASE("Std Drinks Remaining - female, Custom", "[Drink Calculations]") {
    Options options;
    options.sex = "female";
    options.limit_standard = "Custom";
    options.weekly_limit = 5;

    double female_drinks_remaining = Calculate::standard_drinks_remaining(options, 8);
    REQUIRE(Calculate::equal_double(female_drinks_remaining, -3.0));
}

TEST_CASE("Std Drinks Remaining - female, NIAAA 1", "[Drink Calculations]") {
    Options options;
    options.sex = "female";
    options.limit_standard = "NIAAA";
    options.weekly_limit = 0;

    double female_drinks_remaining_2 = Calculate::standard_drinks_remaining(options, 4);
    REQUIRE(Calculate::equal_double(female_drinks_remaining_2, 3));
}

TEST_CASE("Std Drinks Remaining - female, NIAAA 2", "[Drink Calculations]") {
    Options options;
    options.sex = "female";
    options.limit_standard = "NIAAA";
    options.weekly_limit = 0;

    double female_drinks_remaining_3 = Calculate::standard_drinks_remaining(options, 12);

    REQUIRE(Calculate::equal_double(female_drinks_remaining_3, -5));
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

    REQUIRE(Calculate::equal_double(male_oz_remaining, 4.1));
    REQUIRE(Calculate::equal_double(female_oz_remaining, 0.5));
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

    Drink etrwo;
    Drink mosaic;
    Drink etrwo2;

    etrwo.set_id(-1); // 1
    etrwo.set_date("2020-09-08");
    etrwo.set_name("Everything Rhymes with Orange");
    etrwo.set_type("IPA");
    etrwo.set_subtype("");
    etrwo.set_producer("Roughtail Brewing");
    etrwo.set_abv(8.0);
    etrwo.set_ibu(60.0);
    etrwo.set_size(12);
    etrwo.set_rating(8);
    etrwo.set_notes("Very good hazy IPA.");
    etrwo.set_vintage(-1);
    etrwo.set_alcohol_type("Beer");
    etrwo.set_timestamp("2020-01-01 00:00:00");
    etrwo.set_sort_order(1);

    mosaic.set_id(-1);
    mosaic.set_date("2020-09-08");
    mosaic.set_name("Mosaic");
    mosaic.set_type("IPA");
    mosaic.set_subtype("");
    mosaic.set_producer("Community Brewing");
    mosaic.set_abv(8.4);
    mosaic.set_ibu(75.0);
    mosaic.set_size(12.0);
    mosaic.set_rating(8);
    mosaic.set_notes("");
    mosaic.set_vintage(-1);
    mosaic.set_alcohol_type("Beer");
    mosaic.set_timestamp("2020-01-01 00:00:00");
    mosaic.set_sort_order(1);

    etrwo2.set_id(-1); // 1
    etrwo2.set_date("2020-09-10");
    etrwo2.set_name("Everything Rhymes with Orange");
    etrwo2.set_type("IPA");
    etrwo2.set_subtype("");
    etrwo2.set_producer("Roughtail Brewing");
    etrwo2.set_abv(8.0);
    etrwo2.set_ibu(60.0);
    etrwo2.set_size(12);
    etrwo2.set_rating(8);
    etrwo2.set_notes("");
    etrwo2.set_vintage(-1);
    etrwo2.set_alcohol_type("Beer");
    etrwo2.set_timestamp("2020-01-01 00:00:00");
    etrwo2.set_sort_order(1);

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    double mean_abv = Calculate::mean_abv(storage_1, "Beer");

    REQUIRE(Calculate::equal_double(mean_abv, 8.13));
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

    Drink etrwo;
    Drink mosaic;
    Drink etrwo2;
    Drink titos;

    etrwo.set_id(-1); // 1
    etrwo.set_date("2020-09-08");
    etrwo.set_name("Everything Rhymes with Orange");
    etrwo.set_type("IPA");
    etrwo.set_subtype("");
    etrwo.set_producer("Roughtail Brewing");
    etrwo.set_abv(8.0);
    etrwo.set_ibu(60.0);
    etrwo.set_size(12);
    etrwo.set_rating(8);
    etrwo.set_notes("Very good hazy IPA.");
    etrwo.set_vintage(-1);
    etrwo.set_alcohol_type("Beer");
    etrwo.set_timestamp("2020-01-01 00:00:00");
    etrwo.set_sort_order(1);

    mosaic.set_id(-1);
    mosaic.set_date("2020-09-08");
    mosaic.set_name("Mosaic");
    mosaic.set_type("IPA");
    mosaic.set_subtype("");
    mosaic.set_producer("Community Brewing");
    mosaic.set_abv(8.4);
    mosaic.set_ibu(75.0);
    mosaic.set_size(12.0);
    mosaic.set_rating(8);
    mosaic.set_notes("");
    mosaic.set_vintage(-1);
    mosaic.set_alcohol_type("Beer");
    mosaic.set_timestamp("2020-01-01 00:00:00");
    mosaic.set_sort_order(1);

    etrwo2.set_id(-1); // 1
    etrwo2.set_date("2020-09-10");
    etrwo2.set_name("Everything Rhymes with Orange");
    etrwo2.set_type("IPA");
    etrwo2.set_subtype("");
    etrwo2.set_producer("Roughtail Brewing");
    etrwo2.set_abv(8.0);
    etrwo2.set_ibu(60.0);
    etrwo2.set_size(12);
    etrwo2.set_rating(8);
    etrwo2.set_notes("");
    etrwo2.set_vintage(-1);
    etrwo2.set_alcohol_type("Beer");
    etrwo2.set_timestamp("2020-01-01 00:00:00");
    etrwo2.set_sort_order(1);

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    double mean_ibu = Calculate::mean_ibu(storage_1, "Beer");

    REQUIRE(Calculate::equal_double(mean_ibu, 65));
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

    Drink etrwo;
    Drink mosaic;
    Drink etrwo2;
    Drink titos;

    etrwo.set_id(-1); // 1
    etrwo.set_date("2020-09-08");
    etrwo.set_name("Everything Rhymes with Orange");
    etrwo.set_type("IPA");
    etrwo.set_subtype("");
    etrwo.set_producer("Roughtail Brewing");
    etrwo.set_abv(8.0);
    etrwo.set_ibu(60.0);
    etrwo.set_size(12);
    etrwo.set_rating(8);
    etrwo.set_notes("Very good hazy IPA.");
    etrwo.set_vintage(-1);
    etrwo.set_alcohol_type("Beer");
    etrwo.set_timestamp("2020-01-01 00:00:00");
    etrwo.set_sort_order(1);

    mosaic.set_id(-1);
    mosaic.set_date("2020-09-08");
    mosaic.set_name("Mosaic");
    mosaic.set_type("IPA");
    mosaic.set_subtype("");
    mosaic.set_producer("Community Brewing");
    mosaic.set_abv(8.4);
    mosaic.set_ibu(75.0);
    mosaic.set_size(12.0);
    mosaic.set_rating(8);
    mosaic.set_notes("");
    mosaic.set_vintage(-1);
    mosaic.set_alcohol_type("Beer");
    mosaic.set_timestamp("2020-01-01 00:00:00");
    mosaic.set_sort_order(1);

    etrwo2.set_id(-1); // 1
    etrwo2.set_date("2020-09-10");
    etrwo2.set_name("Everything Rhymes with Orange");
    etrwo2.set_type("IPA");
    etrwo2.set_subtype("");
    etrwo2.set_producer("Roughtail Brewing");
    etrwo2.set_abv(8.0);
    etrwo2.set_ibu(60.0);
    etrwo2.set_size(12);
    etrwo2.set_rating(8);
    etrwo2.set_notes("");
    etrwo2.set_vintage(-1);
    etrwo2.set_alcohol_type("Beer");
    etrwo2.set_timestamp("2020-01-01 00:00:00");
    etrwo2.set_sort_order(1);

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

    Drink etrwo;
    Drink mosaic;
    Drink etrwo2;
    Drink titos;

    etrwo.set_id(-1); // 1
    etrwo.set_date("2020-09-08");
    etrwo.set_name("Everything Rhymes with Orange");
    etrwo.set_type("IPA");
    etrwo.set_subtype("");
    etrwo.set_producer("Roughtail Brewing");
    etrwo.set_abv(8.0);
    etrwo.set_ibu(60.0);
    etrwo.set_size(12);
    etrwo.set_rating(8);
    etrwo.set_notes("Very good hazy IPA.");
    etrwo.set_vintage(-1);
    etrwo.set_alcohol_type("Beer");
    etrwo.set_timestamp("2020-01-01 00:00:00");
    etrwo.set_sort_order(1);

    mosaic.set_id(-1);
    mosaic.set_date("2020-09-08");
    mosaic.set_name("Mosaic");
    mosaic.set_type("IPA");
    mosaic.set_subtype("");
    mosaic.set_producer("Community Brewing");
    mosaic.set_abv(8.4);
    mosaic.set_ibu(75.0);
    mosaic.set_size(12.0);
    mosaic.set_rating(8);
    mosaic.set_notes("");
    mosaic.set_vintage(-1);
    mosaic.set_alcohol_type("Beer");
    mosaic.set_timestamp("2020-01-01 00:00:00");
    mosaic.set_sort_order(1);

    etrwo2.set_id(-1); // 1
    etrwo2.set_date("2020-09-10");
    etrwo2.set_name("Everything Rhymes with Orange");
    etrwo2.set_type("IPA");
    etrwo2.set_subtype("");
    etrwo2.set_producer("Roughtail Brewing");
    etrwo2.set_abv(8.0);
    etrwo2.set_ibu(60.0);
    etrwo2.set_size(12);
    etrwo2.set_rating(8);
    etrwo2.set_notes("");
    etrwo2.set_vintage(-1);
    etrwo2.set_alcohol_type("Beer");
    etrwo2.set_timestamp("2020-01-01 00:00:00");
    etrwo2.set_sort_order(1);

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

    Drink etrwo;
    Drink mosaic;
    Drink etrwo2;
    Drink titos;

    etrwo.set_id(-1); // 1
    etrwo.set_date("2020-09-08");
    etrwo.set_name("Everything Rhymes with Orange");
    etrwo.set_type("IPA");
    etrwo.set_subtype("");
    etrwo.set_producer("Roughtail Brewing");
    etrwo.set_abv(8.0);
    etrwo.set_ibu(60.0);
    etrwo.set_size(12);
    etrwo.set_rating(8);
    etrwo.set_notes("Very good hazy IPA.");
    etrwo.set_vintage(-1);
    etrwo.set_alcohol_type("Beer");
    etrwo.set_timestamp("2020-01-01 00:00:00");
    etrwo.set_sort_order(1);

    mosaic.set_id(-1);
    mosaic.set_date("2020-09-08");
    mosaic.set_name("Mosaic");
    mosaic.set_type("IPA");
    mosaic.set_subtype("");
    mosaic.set_producer("Community Brewing");
    mosaic.set_abv(8.4);
    mosaic.set_ibu(75.0);
    mosaic.set_size(12.0);
    mosaic.set_rating(8);
    mosaic.set_notes("");
    mosaic.set_vintage(-1);
    mosaic.set_alcohol_type("Beer");
    mosaic.set_timestamp("2020-01-01 00:00:00");
    mosaic.set_sort_order(1);

    etrwo2.set_id(-1); // 1
    etrwo2.set_date("2020-09-10");
    etrwo2.set_name("Everything Rhymes with Orange");
    etrwo2.set_type("IPA");
    etrwo2.set_subtype("");
    etrwo2.set_producer("Roughtail Brewing");
    etrwo2.set_abv(8.0);
    etrwo2.set_ibu(60.0);
    etrwo2.set_size(12);
    etrwo2.set_rating(8);
    etrwo2.set_notes("");
    etrwo2.set_vintage(-1);
    etrwo2.set_alcohol_type("Beer");
    etrwo2.set_timestamp("2020-01-01 00:00:00");
    etrwo2.set_sort_order(1);

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