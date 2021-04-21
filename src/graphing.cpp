//
// Created by Ross Wardrup on 12/7/20.
//

#include "graphing.h"
#include "include/qcustomplot.h"

std::vector<double> Graphing::get_beer_ibus(const std::vector<Drink>& all_drinks) {
    /*
     * Create a vector containing IBU values of all beers.
     * @param all_drinks: A vector of drinks. This will be all drinks in the database.
     * @return: Vector of doubles representing all beer IBUs.
     */

    std::vector<double> ibu_values;

    for (const auto& drink : all_drinks) {
        double ibu = drink.ibu;
        if (ibu > 0)
        ibu_values.push_back(ibu);
    }

    return ibu_values;
}

std::vector<double> Graphing::get_drink_abvs(const std::vector<Drink> &all_drinks) {
    /*
     * Create a vector containing ABV values of all drinks.
     * @param all_drinks: A vector of drinks. This will be all drinks in the database.
     * @return: A vector of doubles denoting all drink IBUs.
     */

    std::vector<double> abv_values;

    abv_values.reserve(all_drinks.size());
    for (const auto& drink : all_drinks) {
        abv_values.push_back(drink.abv);
    }

    return abv_values;
}

std::map<double, int> Graphing::count_values_in_vect(const std::vector<double>& all_values) {
    /*
     * Create QCustomPlot of IBU distribution.
     */

    std::vector<double> ibu_copy = all_values;
    std::map<double, int> ibu_counts;

    // Get count (y value) of each IBU (x value).
    // First, get unique items in vector
    std::sort(ibu_copy.begin(), ibu_copy.end());
    ibu_copy.erase(unique(ibu_copy.begin(), ibu_copy.end()), ibu_copy.end());

    // Create map where key is the IBU value and value is the count of the IBU in all_values.
    for (double & i : ibu_copy) {
        double ibu_value = i;
        int ibu_count = std::count(all_values.begin(), all_values.end(), ibu_value);
        ibu_counts[i] = ibu_count;
    }

    return ibu_counts;
}
