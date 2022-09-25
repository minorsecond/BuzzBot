//
// Created by Ross Wardrup on 4/21/21.
//

#include "src/graphing_calculations.h"
#include <map>
#if __has_include("catch2/catch_test_macros.hpp")
#include <catch2/catch_test_macros.hpp>
#else
#include <catch2/catch.hpp>
#endif

TEST_CASE("IBU Vector Creation", "[Graph Data Compilation]") {
    std::vector<Drink> all_drinks;
    std::vector<double> expected_values{60.0, 75.0, 60.0};

    Drink etrwo;
    Drink mosaic;
    Drink etrwo2;
    Drink titos;

    etrwo.set_id(-1);
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

    titos.set_id(-1);
    titos.set_date("2021-04-21");
    titos.set_name("Tito's Vodka");
    titos.set_type("Vodka");
    titos.set_subtype("");
    titos.set_producer("Tito's");
    titos.set_abv(40.0);
    titos.set_ibu(-1);
    titos.set_size(2);
    titos.set_rating(9);
    titos.set_notes("");
    titos.set_vintage(-1);
    titos.set_alcohol_type("Liquor");
    titos.set_timestamp("2021-04-21 04:38:00");
    titos.set_sort_order(1);

    all_drinks.push_back(etrwo);
    all_drinks.push_back(mosaic);
    all_drinks.push_back(etrwo2);
    all_drinks.push_back(titos);

    std::vector<double> beer_ibus = GraphingCalculations::get_beer_ibus(all_drinks);

    REQUIRE(beer_ibus == expected_values);
}

TEST_CASE("ABV Vector Creation", "[Graph Data Compilation]") {
    std::vector<Drink> all_drinks;
    std::vector<double> expected_values{8.0, 8.4, 8.0, 40.0};

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

    titos.set_id(-1);
    titos.set_date("2021-04-21");
    titos.set_name("Tito's Vodka");
    titos.set_type("Vodka");
    titos.set_subtype("");
    titos.set_producer("Tito's");
    titos.set_abv(40.0);
    titos.set_ibu(-1);
    titos.set_size(2);
    titos.set_rating(9);
    titos.set_notes("");
    titos.set_vintage(-1);
    titos.set_alcohol_type("Liquor");
    titos.set_timestamp("2021-04-21 04:38:00");
    titos.set_sort_order(1);

    all_drinks.push_back(etrwo);
    all_drinks.push_back(mosaic);
    all_drinks.push_back(etrwo2);
    all_drinks.push_back(titos);

    std::vector<double> drink_abvs = GraphingCalculations::get_drink_abvs(all_drinks);

    REQUIRE(drink_abvs == expected_values);
}

TEST_CASE("Count Values in Vector", "[Graph Data Compilation]") {
    std::vector<double> input_values{5.5, 5.5, 6.0, 10.0, 5.5, 4.8, 4.8, 10.0, 10.0, 10.0};
    std::map<double, size_t> expected_values = {{4.8, 2},
                                             {5.5, 3},
                                             {6.0, 1},
                                             {10.0, 4}};

    std::map<double, size_t> output_values = GraphingCalculations::count_values_in_vect(input_values);

    REQUIRE(output_values == expected_values);
}