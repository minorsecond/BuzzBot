//
// Created by Ross Wardrup on 12/7/20.
//

#ifndef BUZZBOT_GRAPHING_H
#define BUZZBOT_GRAPHING_H

#include "include/qcustomplot.h"
#include "database.h"
#include "mainwindow.h"
#include "../ui/ui_graph_window.h"
#include "graphing_calculations.h"

class Graphing : public QDialog, public Ui::GraphWindow {
    /*
     * About dialog
     */

Q_OBJECT
    Ui::GraphWindow ui{};

public:
    explicit Graphing(const std::vector<Drink>& all_drinks, double std_drink_size, const Options& options);
    static QCustomPlot * plot_ibus(const std::map<double, size_t>& ibu_counts, QDialog *parent = nullptr);
    static QCustomPlot * plot_abvs(const QVector<QCPGraphData>& time_data, const Options& options, QDialog *parent);
private:
    static void add_empty_drinks(const int first_year, const int last_year, const int max_date, const int min_date,
    std::map<int, double> &date_std_drinks);
    static QVector<QCPGraphData> create_qvect(const std::map<int, double> &date_std_drinks);
    static QVector<QCPGraphData> time_data_aggregator(std::vector<Drink> all_drinks, double std_drink_size);
};


#endif //BUZZBOT_GRAPHING_H
