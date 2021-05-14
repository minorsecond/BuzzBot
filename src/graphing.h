//
// Created by Ross Wardrup on 12/7/20.
//

#ifndef BUZZBOT_GRAPHING_H
#define BUZZBOT_GRAPHING_H

#include "include/qcustomplot.h"
#include "database.h"
#include "../ui/ui_graph_window.h"


class Graphing : public QDialog, public Ui::GraphWindow {
    /*
     * About dialog
     */

Q_OBJECT
    Ui::GraphWindow ui{};

public:
    explicit Graphing(const std::vector<Drink>& all_drinks);
    static std::vector<double> get_beer_ibus(const std::vector<Drink>& all_drinks);
    static std::vector<double> get_drink_abvs(const std::vector<Drink>& all_drinks);
    static std::map<double, int> count_values_in_vect(const std::vector<double>& all_values);
    static QCustomPlot * plot_ibus(const std::map<double, int>& ibu_counts, QDialog *parent = nullptr);
    static QVector<QCPGraphData> time_data_aggregator(const std::vector<Drink>& all_drinks);
    static bool compare_by_date(const Drink &a, const Drink &b);
    static int parse_date(std::string &date);
    static QCustomPlot * plot_abvs(const QVector<QCPGraphData>& time_data, QDialog *parent);
    static int week_number(const int date);
};


#endif //BUZZBOT_GRAPHING_H
