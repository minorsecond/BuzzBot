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
               "Roughtail Brewing", 8.0, 60.0, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, ""};

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
               "Roughtail Brewing", 8.0, 60.0, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, ""};

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
               "Roughtail Brewing", 8.0, 60.0, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, ""};

    storage_1.insert(etrwo);
    storage_1.insert(mosaic);
    Database::write_db_to_disk(storage_1);

    REQUIRE(storage_1.get_all<Beer>().size() == 2);

    Database::delete_row(storage_1, 1);
    Database::write_db_to_disk(storage_1);
    std::vector<Beer> beers = Database::read(db_path);

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