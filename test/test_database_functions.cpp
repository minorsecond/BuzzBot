//
// Created by Ross Wardrup on 9/8/20.
//

#include "../include/Catch2.hpp"
#include "../src/database.h"
#include <stdio.h>
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

TEST_CASE("Read DB", "[DB Read]") {
    std::string current_path = std::filesystem::current_path();
    const char *file_name = "testdb.db";
    std::string db_path = current_path + "/" + file_name;

    if (remove(db_path.c_str())) {
        std::cout << "Removed existing testdb.sqlite file" << std::endl;
    }

    Storage storage = initStorage(db_path);
    Database::write_db_to_disk(storage);

    Beer etrwo{-1, 2020, 9, 8, "Everything Rhymes with Orange", "IPA",
               "Roughtail Brewing", 8.0, 60.0, "Very good hazy IPA."};
    Beer mosaic{-1, 2020, 9, 8, "Mosaic", "IPA",
                "Community Brewing", 8.4, 75.0, ""};

    storage.insert(etrwo);
    storage.insert(mosaic);

    Database::write_db_to_disk(storage);

    Beer etrwo_read = storage.get<Beer>(1);
    Beer mosaic_read = storage.get<Beer>(2);

    REQUIRE(etrwo_read.abv == 8.0);
    REQUIRE(etrwo_read.ibu == 60.0);
    REQUIRE(etrwo_read.name == "Everything Rhymes with Orange");
    REQUIRE(etrwo_read.notes == "Very good hazy IPA.");
    REQUIRE(mosaic_read.brewery == "Community Brewing");
    REQUIRE(mosaic_read.drink_day == 8);
    REQUIRE(mosaic_read.type == "IPA");
}