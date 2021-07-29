//
// Created by Ross Wardrup on 9/8/20.
//

#include "../src/database.h"
#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#include <catch2/catch.hpp>

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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1,  "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);

    Database::write_db_to_disk(storage_1);

    Storage storage_2 = initStorage(db_path, Database::db_version);

    auto etrwo_read = storage_2.get<Drink>(1);
    auto mosaic_read = storage_2.get<Drink>(2);

    REQUIRE(etrwo_read.abv == 8.0);
    REQUIRE(etrwo_read.ibu == 60.0);
    REQUIRE(etrwo_read.name == "Everything Rhymes with Orange");
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");
    REQUIRE(mosaic_read.producer == "Community Brewing");
    REQUIRE(mosaic_read.date == "2020-09-08");
    REQUIRE(mosaic_read.type == "IPA");
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};

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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    REQUIRE(storage_1.get_all<Drink>().size() == 2);

    Database::delete_row(storage_1, 1);
    Database::write_db_to_disk(storage_1);
    std::vector<Drink> beers = Database::read(storage_1);

    for(const auto& beer : beers) {
        if (beer.id > max_id)
            max_id = beer.id;
        if (beer.id < min_id)
            min_id = beer.id;
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1,"2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    Drink mosaic_read = Database::read_row(2, storage_1);
    Drink etrwo_read = Database::read_row(1, storage_1);

    REQUIRE(mosaic_read.id == 2);
    REQUIRE(mosaic_read.name == "Mosaic");
    REQUIRE(mosaic.abv == 8.4);
    REQUIRE(etrwo_read.id == 1);
    REQUIRE(etrwo_read.ibu == 60.0);
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};

    Database::write(etrwo, storage_1);
    std::vector<Drink> drinks_in_db = storage_1.get_all<Drink>();

    REQUIRE(drinks_in_db.at(0).id == 1);
    REQUIRE(drinks_in_db.size() == 1);
    REQUIRE(drinks_in_db.at(0).alcohol_type == "Beer");
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    Drink etrwo_read = Database::read_row(1, storage_1);
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");

    Drink etrwo_update{1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                       "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                       "Very good hazy IPA. Will buy again!", -1, "Beer", "2020-09-08 00:00:00", 1};
    Database::update(storage_1, etrwo_update);
    Database::write_db_to_disk(storage_1);
    Drink etrwo_read2 = Database::read_row(1, storage_1);
    REQUIRE(etrwo_read2.notes == "Very good hazy IPA. Will buy again!");
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "Hazy IPA",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 7,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1,"2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10", "Everything Rhymes with Orange", "IPA", "Hazy IPA",
                 "Roughtail Brewing", 8.0, 60.0, 12.0, 7, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    std::vector<Drink> filtered_beers = Database::filter("After Date", "2020-09-08", storage_1);

    Drink etrwo_read = filtered_beers.at(0);

    REQUIRE(filtered_beers.empty() == false);
    REQUIRE(filtered_beers.size() == 3);
    REQUIRE(etrwo_read.date == "2020-09-08");

    std::vector<Drink> filter_by_subtype = Database::filter("Subtype", "Hazy IPA", storage_1);

    REQUIRE(filter_by_subtype.at(0).name == "Everything Rhymes with Orange");
    REQUIRE(filter_by_subtype.size() == 2);

    std::vector<Drink> filter_by_rating = Database::filter("Rating", "8", storage_1);
    REQUIRE(filter_by_rating.size() == 1);
    REQUIRE(filter_by_rating.at(0).name == "Mosaic");

    std::vector<Drink> filter_by_producer = Database::filter("Producer", "Community Brewing", storage_1);
    REQUIRE(filter_by_rating.size() == 1);
    REQUIRE(filter_by_rating.at(0).name == "Mosaic");
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-10", "Everything Rhymes with Orange", "IPA", "",
                 "Roughtail Brewing", 8.0, 60.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    // Get last entered beer
    Drink selected_beer = Database::get_drink_by_name(storage_1,"Beer", "Everything Rhymes with Orange");

    REQUIRE(selected_beer.id == 3);
    REQUIRE(selected_beer.name == "Everything Rhymes with Orange");
    REQUIRE(selected_beer.notes.empty() == true);
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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-11", "Old Rasputin", "Russian Imperial Stout", "",
                 "North Coast Brewing Co.", 9.0, 75.0, 12.0, 8,
                 "", -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::vector<Drink> selected_beers = Database::get_drinks_by_type(storage_1, "IPA");

    REQUIRE(selected_beers.size() == 2);
    REQUIRE(selected_beers.at(0).type == "IPA");
    REQUIRE(selected_beers.at(1).name == "Mosaic");

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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic{-1, "2020-09-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink etrwo2{-1, "2020-09-08", "Old Rasputin", "Russian Imperial Stout", "",
                 "North Coast Brewing Co.", 9.0, 75.0, 12.0, 8,
                 "", -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::vector<Drink> selected_beers = Database::get_drinks_by_producer(storage_1, "North Coast Brewing Co.");

    REQUIRE(selected_beers.size() == 1);
    REQUIRE(selected_beers.at(0).type == "Russian Imperial Stout");
    REQUIRE(selected_beers.at(0).name == "Old Rasputin");

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

    Drink etrwo{-1, "2020-09-08", "Everything Rhymes with Orange", "IPA", "",
                "Roughtail Brewing", 8.0, 60.0, 12.0, 8,
                "Very good hazy IPA.", -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic1{-1, "2020-08-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink mosaic2{-1, "2020-08-08", "Mosaic", "IPA", "",
                 "Community Brewing", 8.4, 75.0, 12.0, 8, "",
                 -1, "Beer", "2020-09-08 00:00:00", 1};
    Drink old_rasputin{-1, "2020-07-11", "Old Rasputin", "Russian Imperial Stout", "",
                       "North Coast Brewing Co.", 9.0, 75.0, 12.0, 8,
                       "", -1, "Beer", "2020-09-08 00:00:00", 1};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic1);
    storage_1.insert(mosaic2);
    storage_1.insert(old_rasputin);
    Database::write_db_to_disk(storage_1);
    std::vector<Drink> drinks = storage_1.get_all<Drink>();
    Database::sort_by_date_id(drinks);

    for (const auto& drink : drinks)
        std::cout << drink.name << std::endl;

    REQUIRE(drinks.at(0).name == "Old Rasputin");
    REQUIRE(drinks.at(1).name == "Mosaic");
    REQUIRE(drinks.at(2).name == "Mosaic");
    REQUIRE(drinks.at(3).name == "Everything Rhymes with Orange");
}