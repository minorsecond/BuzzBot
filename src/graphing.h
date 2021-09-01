//
// Created by Ross Wardrup on 12/7/20.
//

#ifndef BUZZBOT_GRAPHING_H
#define BUZZBOT_GRAPHING_H

#include "include/qcustomplot.h"
#include "database.h"
#include "mainwindow.h"
#include "../ui/ui_graph_window.h"


class Graphing : public QDialog, public Ui::GraphWindow {
    /*
     * About dialog
     */

Q_OBJECT
    Ui::GraphWindow ui{};

public:
    explicit Graphing(const std::vector<Drink>& all_drinks, double std_drink_size, const Options& options);
    static std::vector<double> get_beer_ibus(const std::vector<Drink>& all_drinks);
    static std::vector<double> get_drink_abvs(const std::vector<Drink>& all_drinks);
    static std::map<double, size_t> count_values_in_vect(const std::vector<double>& all_values);
    static QCustomPlot * plot_ibus(const std::map<double, size_t>& ibu_counts, QDialog *parent = nullptr);
    static QVector<QCPGraphData> time_data_aggregator(std::vector<Drink> all_drinks, double std_drink_size);
    static bool compare_by_date(const Drink &a, const Drink &b);
    static int parse_date(std::string &date);
    static QCustomPlot * plot_abvs(const QVector<QCPGraphData>& time_data, const Options& options, QDialog *parent);
    static std::string week_number(int date);
    static int date_from_week_num(const std::string& week_num);
private:
    static void add_empty_drinks(const int first_year, const int last_year, const int max_date, const int min_date,
    std::map<int, double> &date_std_drinks);
    static QVector<QCPGraphData> create_qvect(const std::map<int, double> &date_std_drinks);
};


#endif //BUZZBOT_GRAPHING_H
