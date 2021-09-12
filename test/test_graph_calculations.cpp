//
// Created by Ross Wardrup on 4/21/21.
//

#include "src/graphing.h"
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("IBU Vector Creation", "[Graph Data Compilation]") {
    std::vector<Drink> all_drinks;
    std::vector<double> expected_values{60.0, 75.0, 60.0};

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
    Drink titos{-1, "2021-04-21", "Tito's Vodka", "Vodka", "", "Tito's",
                40.0, -1, 2, 9, "", -1, "Liquor",
                "2021-04-21 04:38:00", 1};

    all_drinks.push_back(etrwo2);
    all_drinks.push_back(mosaic);
    all_drinks.push_back(etrwo2);
    all_drinks.push_back(titos);

    std::vector<double> beer_ibus = Graphing::get_beer_ibus(all_drinks);

    REQUIRE(beer_ibus == expected_values);
}

TEST_CASE("ABV Vector Creation", "[Graph Data Compilation]") {
    std::vector<Drink> all_drinks;
    std::vector<double> expected_values{8.0, 8.4, 8.0, 40.0};

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
    Drink titos{-1, "2021-04-21", "Tito's Vodka", "Vodka", "", "Tito's",
                40.0, -1, 2, 9, "", -1, "Liquor",
                "2021-04-21 04:38:00", 1};

    all_drinks.push_back(etrwo2);
    all_drinks.push_back(mosaic);
    all_drinks.push_back(etrwo2);
    all_drinks.push_back(titos);

    std::vector<double> drink_abvs = Graphing::get_drink_abvs(all_drinks);

    REQUIRE(drink_abvs == expected_values);
}

TEST_CASE("Count Values in Vector", "[Graph Data Compilation]") {
    std::vector<double> input_values{5.5, 5.5, 6.0, 10.0, 5.5, 4.8, 4.8, 10.0, 10.0, 10.0};
    std::map<double, size_t> expected_values = {{4.8, 2},
                                             {5.5, 3},
                                             {6.0, 1},
                                             {10.0, 4}};

    std::map<double, size_t> output_values = Graphing::count_values_in_vect(input_values);

    REQUIRE(output_values == expected_values);
}