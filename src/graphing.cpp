//
// Created by Ross Wardrup on 12/7/20.
//

#include "graphing.h"
#include "include/qcustomplot.h"
#include <iostream>

Graphing::Graphing(const std::vector<Drink>& all_drinks) {
    /*
     * Main graphing window.
     */

    ui.setupUi(this);
    this->setWindowTitle("Alcohol Habits");

    //Plot the IBU plot
    std::vector ibus = Graphing::get_beer_ibus(all_drinks);
    std::map<double, int> ibu_counts = Graphing::count_values_in_vect(ibus);
    auto ibu_plot = Graphing::plot_ibus(ibu_counts, this);
    ibu_plot->show();

    // Plot the ABV plot
    QVector<QCPGraphData> time_data = time_data_aggregator(all_drinks);
    auto abv_plot = Graphing::plot_abvs(time_data, this);
    abv_plot->show();
}

std::vector<double> Graphing::get_beer_ibus(const std::vector<Drink>& all_drinks) {
    /*
     * Create a vector containing IBU values of all beers.
     * @param all_drinks: A vector of drinks. This will be all drinks in the database.
     * @return: Vector of doubles representing all beer IBUs.
     */

    std::vector<double> ibu_values;

    for (const auto& drink : all_drinks) {
        double ibu = drink.ibu;
        if (ibu > 0)  // Exclude non-beer drinks
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

QCustomPlot * Graphing::plot_ibus(const std::map<double, int>& ibu_counts, QDialog *parent) {
    /*
     * Plot IBU values in QCustomPlot
     * @param parent: The window that the graph should appear in.
     * @param ibu_counts: a map<double, int> of ibu values (keys) and their counts (values).
     */

    auto *ibu_plot = new QCustomPlot(parent);
    ibu_plot->resize(parent->width(), parent->height() / 4);

    // Add title
    // add title layout element:
    ibu_plot->plotLayout()->insertRow(0);
    ibu_plot->plotLayout()->addElement(0, 0,
                                       new QCPTextElement(ibu_plot, "Beer IBU Distribution",
                                                          QFont(".AppleSystemUIFont", 12,
                                                                QFont::Bold)));

    QVector<double> ibus(ibu_counts.size());
    //QVector<double> counts(ibu_counts.size());
    QVector<double> percentages(ibu_counts.size());
    double total_drinks {0};

    // Build vectors

    // Get total count of drinks
    for (auto const& [key, val] : ibu_counts) {
        total_drinks += val;
    }

    int i = 0;
    for (auto const& [key, val] : ibu_counts) {
        ibus[i] = key;
        //counts[i] = val;
        percentages[i] = ((double)val / total_drinks) * 100;
        i++;
    }

    // Get min/max values for axes
    double ibu_min = *std::min_element(ibus.begin(), ibus.end());
    double ibu_max = *std::max_element(ibus.begin(), ibus.end());
    //double count_min = *std::min_element(counts.begin(), counts.end());
    //double count_max = *std::max_element(counts.begin(), counts.end());
    double perc_min = *std::min_element(percentages.begin(), percentages.end());
    double perc_max = *std::max_element(percentages.begin(), percentages.end());

    // Graph style
    QPen drawPen;
    drawPen.setColor(Qt::black);
    drawPen.setStyle(Qt::PenStyle::SolidLine);
    drawPen.setWidth(2);

    // Create the IBU graph
    ibu_plot->addGraph();
    ibu_plot->graph(0)->setData(ibus, percentages);
    ibu_plot->graph()->setPen(drawPen);
    ibu_plot->xAxis->setLabel("IBU");
    ibu_plot->yAxis->setLabel("%");
    ibu_plot->xAxis->setRange(ibu_min, ibu_max);
    ibu_plot->yAxis->setRange(perc_min, perc_max);
    ibu_plot->replot();

    return ibu_plot;
}

QVector<QCPGraphData> Graphing::time_data_aggregator(const std::vector<Drink> &all_drinks) {
    /*
     * Creates a QVector of QCPGraphData from a vector of Drinks.
     * @param all_drinks: a vector of Drinks.
     */

    std::map<int, double> date_std_drinks;
    int date_tmp {0};
    double std_drinks {0.0};

    // Sort by date
    //std::sort(all_drinks.begin(), all_drinks.end(), compare_by_date);

    for (auto & all_drink : all_drinks) {
        date_tmp = parse_date(all_drink.date);
        std_drinks = (all_drink._size*all_drink.abv) / 0.6;  // TODO Change this to use user setting
        if (date_std_drinks.find(date_tmp) != date_std_drinks.end()) {
            // Date not in date_std_drinks
            date_std_drinks[date_tmp] = std_drinks;
        } else {
            // Date already processed
            auto it = date_std_drinks.find(date_tmp);
            it->second += std_drinks;
        }
    }

    // Create the QVectof of QCPGraphData objects
    QVector<QCPGraphData> time_data(date_std_drinks.size());
    auto it = date_std_drinks.begin();
    int it_value {0};
    for (it = date_std_drinks.begin(); it != date_std_drinks.end(); it++) {
        time_data[it_value].key = it->first;
        time_data[it_value].value = it->second;
        it_value += 1;
    }

    return time_data;
}

bool Graphing::compare_by_date(const Drink &a, const Drink &b) {
    /*
     * Compares dates between two drinks.
     * @return: True if drink a is earlier than drink b. Else, false.
     */

    int date_a = parse_date(a.date);
    int date_b = parse_date(b.date);

    return date_a < date_b;
}

int Graphing::parse_date(const std::string &date) {
    /*
     * Convert date string to integer date.
     * @param date: A date in the format YYYY-MM-DD
     * @return: an integer in the format YYYYMMDD
     */

    int month {0};
    int day {0};
    int year {0};
    struct tm tm{};

    char date_array[11];
    strcpy(date_array, date.c_str());

    strptime(date_array, "%Y-%m-%d", &tm);
    year = tm.tm_year + 1900;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;

    std::string const date_string = std::to_string(year) + std::to_string(month) + std::to_string(day);
    int const date_int = std::stoi(date_string);

    return date_int;
}

QCustomPlot *Graphing::plot_abvs(const Storage storage, QDialog *parent) {
    /*
     * Plot the ABV over time graph.
     * @param time_data: A QVector of QCPGraphData objects.
     */

    auto *abv_plot = new QCustomPlot(parent);
    auto aggregated_data = storage.group

    // Get min and max values
    int min_year = std::numeric_limits<int>::max(); // Everything is <= this
    int max_year = std::numeric_limits<int>::min(); // Everything is >= this
    double min_drinks = std::numeric_limits<int>::max();
    double max_drinks = std::numeric_limits<int>::min();
    for (auto data : time_data) {
        int year = data.key;
        double std_drinks = data.value;
        if (year < min_year) {
            min_year = year;
        }

        if (year > max_year) {
            max_year = year;
        }

        if (std_drinks < min_drinks) {
            min_drinks = std_drinks;
        }

        if (std_drinks > max_drinks) {
            max_drinks = std_drinks;
        }
    }

    // Create the ABV graph
    abv_plot->addGraph();
    abv_plot->graph(0)->data()->set(time_data);
    abv_plot->xAxis->setLabel("Date");
    abv_plot->yAxis->setLabel("ABV Value");
    abv_plot->xAxis->setRange(min_year, max_year);
    abv_plot->yAxis->setRange(min_drinks, max_drinks);
    abv_plot->resize(parent->width(), parent->height() / 4);
    abv_plot->replot();

    return abv_plot;
}
