//
// Created by Ross Wardrup on 9/8/20.
//

#include "../src/database.h"
#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#if __has_include("catch2/catch_test_macros.hpp")
#include <catch2/catch_test_macros.hpp>
#else
#include <catch2/catch.hpp>
#endif

inline bool exists (const std::string& name) {
    struct stat buffer{};
    return (stat (name.c_str(), &buffer) == 0);
}

TEST_CASE("Init DB", "[DB Functions]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage);
    REQUIRE( exists(db_path) == true);
    std::remove(file_name);
}

TEST_CASE("DB IO", "[DB Functions]") {
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

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);

    Database::write_db_to_disk(storage_1);

    Storage storage_2 = initStorage(db_path, Database::db_version);

    auto etrwo_read = storage_2.get<Drink>(1);
    auto mosaic_read = storage_2.get<Drink>(2);

    REQUIRE(etrwo_read.get_abv() == 8.0);
    REQUIRE(etrwo_read.get_ibu() == 60.0);
    REQUIRE(etrwo_read.get_name() == "Everything Rhymes with Orange");
    REQUIRE(etrwo_read.get_notes() == "Very good hazy IPA.");
    REQUIRE(mosaic_read.get_producer() == "Community Brewing");
    REQUIRE(mosaic_read.get_date() == "2020-09-08");
    REQUIRE(mosaic_read.get_type() == "IPA");
}

TEST_CASE("Truncate DB", "[DB Functions]") {
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

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);

    Database::write_db_to_disk(storage_1);

    REQUIRE(storage_1.get_all<Drink>().size() == 2);

    Database::truncate(storage_1);

    REQUIRE(storage_1.get_all<Drink>().empty() == true);
}

TEST_CASE("Delete Row", "[DB Functions]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    int min_id = 3;
    int max_id = -1;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo;
    Drink mosaic;

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

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    REQUIRE(storage_1.get_all<Drink>().size() == 2);

    Database::delete_row(storage_1, 1);
    Database::write_db_to_disk(storage_1);
    std::vector<Drink> beers = Database::read(storage_1);

    for(const auto& beer : beers) {
        if (beer.get_id() > max_id)
            max_id = beer.get_id();
        if (beer.get_id() < min_id)
            min_id = beer.get_id();
    }

    REQUIRE(beers.empty() == false);
    REQUIRE(beers.size() == 1);
    REQUIRE(max_id == min_id);
}

TEST_CASE("Read Row", "[DB Functions]") {
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

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    Drink mosaic_read = Database::read_row(2, storage_1);
    Drink etrwo_read = Database::read_row(1, storage_1);

    REQUIRE(mosaic_read.get_id() == 2);
    REQUIRE(mosaic_read.get_name() == "Mosaic");
    REQUIRE(mosaic.get_abv() == 8.4);
    REQUIRE(etrwo_read.get_id() == 1);
    REQUIRE(etrwo_read.get_ibu() == 60.0);
    REQUIRE(etrwo_read.get_notes() == "Very good hazy IPA.");
}

TEST_CASE("Write Row", "[DB Functions]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo;

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

    Database::write(etrwo, storage_1);
    std::vector<Drink> drinks_in_db = storage_1.get_all<Drink>();

    REQUIRE(drinks_in_db.at(0).get_id() == 1);
    REQUIRE(drinks_in_db.size() == 1);
    REQUIRE(drinks_in_db.at(0).get_alcohol_type() == "Beer");
}

TEST_CASE("Update Row", "[DB Functions]") {
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

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    Drink etrwo_read = Database::read_row(1, storage_1);
    REQUIRE(etrwo_read.get_notes() == "Very good hazy IPA.");

    Drink etrwo_update;

    etrwo_update.set_id(1); // 1
    etrwo_update.set_date("2020-09-08");
    etrwo_update.set_name("Everything Rhymes with Orange");
    etrwo_update.set_type("IPA");
    etrwo_update.set_subtype("");
    etrwo_update.set_producer("Roughtail Brewing");
    etrwo_update.set_abv(8.0);
    etrwo_update.set_ibu(60.0);
    etrwo_update.set_size(12);
    etrwo_update.set_rating(8);
    etrwo_update.set_notes("Very good hazy IPA. Will buy again!");
    etrwo_update.set_vintage(-1);
    etrwo_update.set_alcohol_type("Beer");
    etrwo_update.set_timestamp("2020-09-08 00:00:00");
    etrwo_update.set_sort_order(1);

    Database::update(storage_1, etrwo_update);
    Database::write_db_to_disk(storage_1);
    Drink etrwo_read2 = Database::read_row(1, storage_1);
    REQUIRE(etrwo_read2.get_notes() == "Very good hazy IPA. Will buy again!");
}

TEST_CASE("Increment Version", "[DB Functions]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path, Database::db_version - 1);
    Database::write_db_to_disk(storage_1);

    int base_version = Database::increment_version(storage_1, 8);
    REQUIRE(base_version == 8);
}

TEST_CASE("Filter DB", "[DB Functions]") {
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
    etrwo.set_subtype("Hazy IPA");
    etrwo.set_producer("Roughtail Brewing");
    etrwo.set_abv(8.0);
    etrwo.set_ibu(60.0);
    etrwo.set_size(12);
    etrwo.set_rating(7);
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
    etrwo2.set_subtype("Hazy IPA");
    etrwo2.set_producer("Roughtail Brewing");
    etrwo2.set_abv(8.0);
    etrwo2.set_ibu(60.0);
    etrwo2.set_size(12);
    etrwo2.set_rating(7);
    etrwo2.set_notes("");
    etrwo2.set_vintage(-1);
    etrwo2.set_alcohol_type("Beer");
    etrwo2.set_timestamp("2020-01-01 00:00:00");
    etrwo2.set_sort_order(1);

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    std::vector<Drink> filtered_beers = Database::filter("After Date", "2020-09-08", storage_1);

    Drink etrwo_read = filtered_beers.at(0);

    REQUIRE(filtered_beers.empty() == false);
    REQUIRE(filtered_beers.size() == 3);
    REQUIRE(etrwo_read.get_date() == "2020-09-08");

    std::vector<Drink> filter_by_subtype = Database::filter("Subtype", "Hazy IPA", storage_1);

    REQUIRE(filter_by_subtype.at(0).get_name() == "Everything Rhymes with Orange");
    REQUIRE(filter_by_subtype.size() == 2);

    std::vector<Drink> filter_by_rating = Database::filter("Rating", "8", storage_1);
    REQUIRE(filter_by_rating.size() == 1);
    REQUIRE(filter_by_rating.at(0).get_name() == "Mosaic");

    std::vector<Drink> filter_by_producer = Database::filter("Producer", "Community Brewing", storage_1);
    REQUIRE(filter_by_rating.size() == 1);
    REQUIRE(filter_by_rating.at(0).get_name() == "Mosaic");
}

TEST_CASE("Get Drink By Name", "[DB Functions]") {
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

    // Get last entered beer
    Drink selected_beer = Database::get_drink_by_name(storage_1,"Beer", "Everything Rhymes with Orange");

    REQUIRE(selected_beer.get_id() == 3);
    REQUIRE(selected_beer.get_name() == "Everything Rhymes with Orange");
    REQUIRE(selected_beer.get_notes().empty() == true);
}

TEST_CASE("Get Beers By Type", "[DB Functions]") {
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
    Drink old_rasputin;

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

    old_rasputin.set_id(-1); // 1
    old_rasputin.set_date("2020-09-11");
    old_rasputin.set_name("Old Rasputin");
    old_rasputin.set_type("Russian Imperial Stout");
    old_rasputin.set_subtype("");
    old_rasputin.set_producer("North Coast Brewing Co.");
    old_rasputin.set_abv(9.0);
    old_rasputin.set_ibu(75.0);
    old_rasputin.set_size(12);
    old_rasputin.set_rating(8);
    old_rasputin.set_notes("");
    old_rasputin.set_vintage(-1);
    old_rasputin.set_alcohol_type("Beer");
    old_rasputin.set_timestamp("2020-09-08 00:00:00");
    old_rasputin.set_sort_order(1);

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(old_rasputin);
    Database::write_db_to_disk(storage_1);

    std::vector<Drink> selected_beers = Database::get_drinks_by_type(storage_1, "IPA");

    REQUIRE(selected_beers.size() == 2);
    REQUIRE(selected_beers.at(0).get_type() == "IPA");
    REQUIRE(selected_beers.at(1).get_name() == "Mosaic");

    std::vector<Drink> blank_selection = Database::get_drinks_by_type(storage_1, "Porter");
    REQUIRE(blank_selection.empty());
}

TEST_CASE("Get Beers By Brewery", "[DB Functions]") {
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
    Drink old_rasputin;

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

    old_rasputin.set_id(-1); // 1
    old_rasputin.set_date("2020-09-08");
    old_rasputin.set_name("Old Rasputin");
    old_rasputin.set_type("Russian Imperial Stout");
    old_rasputin.set_subtype("");
    old_rasputin.set_producer("North Coast Brewing Co.");
    old_rasputin.set_abv(890);
    old_rasputin.set_ibu(75.0);
    old_rasputin.set_size(12);
    old_rasputin.set_rating(8);
    old_rasputin.set_notes("");
    old_rasputin.set_vintage(-1);
    old_rasputin.set_alcohol_type("Beer");
    old_rasputin.set_timestamp("2020-01-08 00:00:00");
    old_rasputin.set_sort_order(1);

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(old_rasputin);
    Database::write_db_to_disk(storage_1);

    std::vector<Drink> selected_beers = Database::get_drinks_by_producer(storage_1, "North Coast Brewing Co.");

    REQUIRE(selected_beers.size() == 1);
    REQUIRE(selected_beers.at(0).get_type() == "Russian Imperial Stout");
    REQUIRE(selected_beers.at(0).get_name() == "Old Rasputin");

    std::vector<Drink> blank_selection = Database::get_drinks_by_producer(storage_1, "Coors");
    REQUIRE(blank_selection.empty());
}

TEST_CASE("DB Sort", "[DB Functions]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path, Database::db_version);
    Database::write_db_to_disk(storage_1);

    Drink etrwo;
    Drink mosaic1;
    Drink mosaic2;
    Drink old_rasputin;

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

    mosaic1.set_id(-1);
    mosaic1.set_date("2020-08-08");
    mosaic1.set_name("Mosaic");
    mosaic1.set_type("IPA");
    mosaic1.set_subtype("");
    mosaic1.set_producer("Community Brewing");
    mosaic1.set_abv(8.4);
    mosaic1.set_ibu(75.0);
    mosaic1.set_size(12.0);
    mosaic1.set_rating(8);
    mosaic1.set_notes("");
    mosaic1.set_vintage(-1);
    mosaic1.set_alcohol_type("Beer");
    mosaic1.set_timestamp("2020-01-01 00:00:00");
    mosaic1.set_sort_order(1);

    mosaic2.set_id(-1);
    mosaic2.set_date("2020-08-08");
    mosaic2.set_name("Mosaic");
    mosaic2.set_type("IPA");
    mosaic2.set_subtype("");
    mosaic2.set_producer("Community Brewing");
    mosaic2.set_abv(8.4);
    mosaic2.set_ibu(75.0);
    mosaic2.set_size(12.0);
    mosaic2.set_rating(8);
    mosaic2.set_notes("");
    mosaic2.set_vintage(-1);
    mosaic2.set_alcohol_type("Beer");
    mosaic2.set_timestamp("2020-01-01 00:00:00");
    mosaic2.set_sort_order(1);

    old_rasputin.set_id(-1); // 1
    old_rasputin.set_date("2020-07-11");
    old_rasputin.set_name("Old Rasputin");
    old_rasputin.set_type("Russian Imperial Stout");
    old_rasputin.set_subtype("");
    old_rasputin.set_producer("North Coast Brewing Co.");
    old_rasputin.set_abv(9.0);
    old_rasputin.set_ibu(75.0);
    old_rasputin.set_size(12);
    old_rasputin.set_rating(8);
    old_rasputin.set_notes("");
    old_rasputin.set_vintage(-1);
    old_rasputin.set_alcohol_type("Beer");
    old_rasputin.set_timestamp("2020-09-08 00:00:00");
    old_rasputin.set_sort_order(1);

    storage_1.insert(etrwo);
    storage_1.insert(mosaic1);
    storage_1.insert(mosaic2);
    storage_1.insert(old_rasputin);
    Database::write_db_to_disk(storage_1);
    std::vector<Drink> drinks = storage_1.get_all<Drink>();
    Database::sort_by_date_id(drinks);

    for (const auto& drink : drinks)
        std::cout << drink.get_name() << std::endl;

    REQUIRE(drinks.at(0).get_name() == "Old Rasputin");
    REQUIRE(drinks.at(1).get_name() == "Mosaic");
    REQUIRE(drinks.at(2).get_name() == "Mosaic");
    REQUIRE(drinks.at(3).get_name() == "Everything Rhymes with Orange");
}