//
// Created by Ross Wardrup on 12/7/20.
//

#ifndef BUZZBOT_GRAPHING_H
#define BUZZBOT_GRAPHING_H

#include "include/qcustomplot.h"
#include "database.h"


class Graphing {

public:
    static std::vector<double> get_beer_ibus(const std::vector<Drink>& all_drinks);
    static std::vector<double> get_drink_abvs(const std::vector<Drink>& all_drinks);
    static std::map<double, int> count_values_in_vect(const std::vector<double>& all_values);
    static QCustomPlot * plot_ibus(const std::map<double, int>& ibu_counts, QMainWindow *parent = nullptr);
};


#endif //BUZZBOT_GRAPHING_H
