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
     * Create a map of values and their counts.
     * @param all_values: a vector of doubles.
     * @return: a map<double, int> of values (keys) and their counts (values).
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

void Graphing::plot_ibus(const std::map<double, int>& ibu_counts) {
    /*
     * Plot IBU values in QCustomPlot
     * @param ibu_counts: a map<double, int> of ibu values (keys) and their counts (values).
     */

    QCustomPlot ibu_plot;
    QVector<double> ibus(ibu_counts.size());
    QVector<double> counts(ibu_counts.size());

    // Build vectors
    int i = 0;
    for (auto const& [key, val] : ibu_counts) {
        ibus[i] = key;
        counts[i] = val;
        i++;
    }

    // Get min/max values for axes
    double ibu_min = *std::min_element(ibus.begin(), ibus.end());
    double ibu_max = *std::max_element(ibus.begin(), ibus.end());
    double count_min = *std::min_element(counts.begin(), counts.end());
    double count_max = *std::max_element(counts.begin(), counts.end());

    ibu_plot.addGraph();
    ibu_plot.graph(0)->setData(ibus, counts);
    ibu_plot.xAxis->setLabel("IBU");
    ibu_plot.yAxis->setLabel("Count");
    ibu_plot.xAxis->setRange(ibu_min, ibu_max);
    ibu_plot.yAxis->setRange(count_min, count_max);
    ibu_plot.replot();
}
