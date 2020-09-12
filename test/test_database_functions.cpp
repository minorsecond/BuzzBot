//
// Created by Ross Wardrup on 9/8/20.
//

#include "../include/Catch2.hpp"
#include "../src/database.h"
#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>

inline bool exists (const std::string& name) {
    struct stat buffer{};
    return (stat (name.c_str(), &buffer) == 0);
}

TEST_CASE("Init DB", "[DB Creation]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage = initStorage(db_path);
    Database::write_db_to_disk(storage);
    REQUIRE( exists(db_path) == true);
    std::remove(file_name);
}

TEST_CASE("DB IO", "[DB IO]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);

    Database::write_db_to_disk(storage_1);

    Storage storage_2 = initStorage(db_path);

    Beer etrwo_read = storage_2.get<Beer>(1);
    Beer mosaic_read = storage_2.get<Beer>(2);

    REQUIRE(etrwo_read.abv == 8.0);
    REQUIRE(etrwo_read.ibu == 60.0);
    REQUIRE(etrwo_read.name == "Everything Rhymes with Orange");
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");
    REQUIRE(mosaic_read.brewery == "Community Brewing");
    REQUIRE(mosaic_read.drink_day == 8);
    REQUIRE(mosaic_read.type == "IPA");
}

TEST_CASE("Truncate DB", "[Truncate DB]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);

    Database::write_db_to_disk(storage_1);

    REQUIRE(storage_1.get_all<Beer>().size() == 2);

    Database::truncate(storage_1);

    REQUIRE(storage_1.get_all<Beer>().empty() == true);
}

TEST_CASE("Delete Row", "[Delete Row]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    int min_id = 3;
    int max_id = -1;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    REQUIRE(storage_1.get_all<Beer>().size() == 2);

    Database::delete_row(storage_1, 1);
    Database::write_db_to_disk(storage_1);
    std::vector<Beer> beers = Database::read(db_path, storage_1);

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

TEST_CASE("Read Row", "[Read Row]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    Beer mosaic_read = Database::read_row(2, storage_1);
    Beer etrwo_read = Database::read_row(1, storage_1);

    REQUIRE(mosaic_read.id == 2);
    REQUIRE(mosaic_read.name == "Mosaic");
    REQUIRE(mosaic.abv == 8.4);
    REQUIRE(etrwo_read.id == 1);
    REQUIRE(etrwo_read.ibu == 60.0);
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");
}

TEST_CASE("Update Row", "[Update Row]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    Beer etrwo_read = Database::read_row(1, storage_1);
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");

    Beer etrwo_update{1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
                      "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA. Will buy again!"};
    Database::update(storage_1, etrwo_update);
    Database::write_db_to_disk(storage_1);
    Beer etrwo_read2 = Database::read_row(1, storage_1);
    REQUIRE(etrwo_read2.notes == "Very good hazy IPA. Will buy again!");
}

TEST_CASE("Filter DB", "[Filter DB]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};
    Beer etrwo2{-1, 2020, 9, 10, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);
    std::vector<Beer> filtered_beers = Database::filter("Date", "08/09/2020", storage_1);

    Beer etrwo_read = filtered_beers.at(0);
    Beer mosaic_read = filtered_beers.at(1);

    REQUIRE(filtered_beers.empty() == false);
    REQUIRE(filtered_beers.size() == 2);
    REQUIRE(etrwo_read.drink_day == 8);
}

TEST_CASE("Get Beer By Name", "[DB Filter]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};
    Beer etrwo2{-1, 2020, 9, 10, "Everything Rhymes with Orange", "IPA",
                "Roughtail Brewing", 8.0, 60.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    Beer selected_beer = Database::get_beer_by_name(storage_1, "Everything Rhymes with Orange");

    REQUIRE(selected_beer.id == 1);
    REQUIRE(selected_beer.name == "Everything Rhymes with Orange");
    REQUIRE(selected_beer.notes == "Very good hazy IPA.");
}

TEST_CASE("Get Beers By Type", "[DB Filter]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage_1 = initStorage(db_path);
    Database::write_db_to_disk(storage_1);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, 12, 8, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, 12, 8, ""};
    Beer etrwo2{-1, 2020, 9, 11, "Old Rasputin", "Russian Imperial Stout",
                "North Coast Brewing Co.", 9.0, 75.0, 12, 8, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    storage_1.insert(etrwo2);
    Database::write_db_to_disk(storage_1);

    std::vector<Beer> selected_beers = Database::get_beers_by_type(storage_1, "IPA");

    REQUIRE(selected_beers.size() == 2);
    REQUIRE(selected_beers.at(0).type == "IPA");
    REQUIRE(selected_beers.at(1).name == "Mosaic");
}