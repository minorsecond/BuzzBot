//
// Created by Ross Wardrup on 12/7/20.
//

#include "graphing.h"
#include "include/qcustomplot.h"
#include "calculate.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>

Graphing::Graphing(const std::vector<Drink>& all_drinks, double std_drink_size, const Options& options) {
    /*
     * Main graphing window.
     */

    ui.setupUi(this);
    this->setWindowTitle("Alcohol Habits");

    int window_width {512};
    int window_height {512};

    bool no_beers {true};

    this->setFixedWidth(window_width);
    this->setFixedHeight(window_height);

    //Plot the IBU plot
    std::vector ibus {Graphing::get_beer_ibus(all_drinks)};

    if (!ibus.empty()) {
        no_beers = false;
        std::map<double, size_t> ibu_counts = Graphing::count_values_in_vect(ibus);
        auto ibu_plot = Graphing::plot_ibus(ibu_counts, this);
        ibu_plot->setAttribute(Qt::WA_DeleteOnClose);  // Delete pointer on window close
        ibu_plot->setGeometry(0, 0, window_width, window_height/2);
        ibu_plot->show();
    }

    // Plot the ABV plot
    QVector<QCPGraphData> time_data;
    if (!all_drinks.empty()) {
        time_data = time_data_aggregator(all_drinks, std_drink_size);
    }

    auto abv_plot = Graphing::plot_abvs(time_data, options, this);

    if (no_beers) {  // Full size plot if beer data is empty
        abv_plot->setGeometry(0, 0, window_width, window_height);
    } else {
        abv_plot->setGeometry(0, (window_height/2+2), window_width, window_height/2);
    }
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

std::map<double, size_t> Graphing::count_values_in_vect(const std::vector<double>& all_values) {
    /*
     * Create a map of values and their counts.
     * @param all_values: a vector of doubles.
     * @return: a map<double, int> of values (keys) and their counts (values).
     */

    std::vector<double> ibu_copy {all_values};
    std::map<double, size_t> ibu_counts;

    // Get count (y value) of each IBU (x value).
    // First, get unique items in vector
    std::sort(ibu_copy.begin(), ibu_copy.end());
    ibu_copy.erase(unique(ibu_copy.begin(), ibu_copy.end()), ibu_copy.end());

    // Create map where key is the IBU value and value is the count of the IBU in all_values.
    for (const double &i : ibu_copy) {
        double ibu_value = i;
        size_t ibu_count = std::count(all_values.begin(), all_values.end(), ibu_value);
        ibu_counts[i] = ibu_count;
    }

    return ibu_counts;
}

QCustomPlot * Graphing::plot_ibus(const std::map<double, size_t>& ibu_counts, QDialog *parent) {
    /*
     * Plot IBU values in QCustomPlot
     * @param parent: The window that the graph should appear in.
     * @param ibu_counts: a map<double, int> of ibu values (keys) and their counts (values).
     */

    auto *ibu_plot {new QCustomPlot(parent)};
    ibu_plot->setAttribute(Qt::WA_DeleteOnClose);

    // Add title
    // add title layout element:
    ibu_plot->plotLayout()->insertRow(0);
    ibu_plot->plotLayout()->addElement(0, 0,
                                       new QCPTextElement(ibu_plot, "Beer IBU Distribution",
                                                          QFont(".AppleSystemUIFont", 12,
                                                                QFont::Bold)));

    QVector<double> ibus(static_cast<qsizetype>(ibu_counts.size()));
    //QVector<double> counts(ibu_counts.size());
    QVector<double> percentages(static_cast<qsizetype>(ibu_counts.size()));
    size_t total_drinks {0};

    // Build vectors

    // Get total count of drinks
    for (auto const& [key, val] : ibu_counts) {
        total_drinks += val;
    }

    int i = 0;
    for (auto const& [key, val] : ibu_counts) {
        ibus[i] = key;
        //counts[i] = val;
        percentages[i] = (static_cast<double>(val) / static_cast<double>(total_drinks)) * 100;
        i++;
    }

    // Get min/max values for axes
    double ibu_min {*std::min_element(ibus.begin(), ibus.end())};
    double ibu_max {*std::max_element(ibus.begin(), ibus.end())};
    //double count_min = *std::min_element(counts.begin(), counts.end());
    //double count_max = *std::max_element(counts.begin(), counts.end());
    double perc_min {*std::min_element(percentages.begin(), percentages.end())};
    double perc_max {*std::max_element(percentages.begin(), percentages.end())};

    // Graph style
    QPen drawPen;
    drawPen.setColor(Qt::black);
    drawPen.setStyle(Qt::PenStyle::SolidLine);
    drawPen.setWidth(2);

    QColor color(120,77, 150, 150);

    // Create the IBU graph
    ibu_plot->addGraph();
    ibu_plot->graph(0)->setData(ibus, percentages);
    ibu_plot->graph()->setPen(drawPen);
    ibu_plot->xAxis->setLabel("IBU");
    ibu_plot->yAxis->setLabel("% of All Drinks");
    ibu_plot->xAxis->setRange(ibu_min, ibu_max);
    ibu_plot->yAxis->setRange(perc_min, perc_max);
    ibu_plot->graph()->setLineStyle(QCPGraph::lsLine);
    ibu_plot->graph()->setPen(QPen(color.darker(200)));
    ibu_plot->graph()->setBrush(QBrush(color));
    ibu_plot->replot();

    return ibu_plot;
}

QVector<QCPGraphData> Graphing::time_data_aggregator(std::vector<Drink> all_drinks, double std_drink_size) {
    /*
     * Creates a QVector of QCPGraphData from a vector of Drinks.
     * @param all_drinks: a vector of Drinks.
     */

    // TODO: Refactor this method
    std::map<int, double> date_std_drinks;
    const std::string first_week_string {week_number(std::stoi(all_drinks.at(0).date))};
    const std::string last_week_string {week_number(std::stoi(all_drinks[all_drinks.size()-1].date))};
    int min_date {std::numeric_limits<int>::max()}; // Everything is <= this
    int max_date {std::numeric_limits<int>::min()}; // Everything is >= this
    const int first_year {std::stoi(first_week_string.substr(0, first_week_string.find('-')))};
    const int last_year {std::stoi(last_week_string.substr(0, last_week_string.find('-')))};
    double std_drinks {0.0};

    // Sort by date
    std::sort(all_drinks.begin(), all_drinks.end(), compare_by_date);

    for (auto & all_drink : all_drinks) {
        //date_tmp = parse_date(all_drink.date);
        std::string date_tmp = all_drink.date;

        // Get week number & integer date value from DB date
        date_tmp.erase(std::remove(date_tmp.begin(), date_tmp.end(), '-'), date_tmp.end());
        std::string week_num = week_number(std::stoi(date_tmp));
        std::string date_str = std::to_string(date_from_week_num(week_num));
        int date = parse_date(date_str);

        // Get min & max dates for graph
        if (date > max_date) {
            max_date = date;
        }

        if (date < min_date) {
            min_date = date;
        }

        // Add to the map of dates & std drinks
        std_drinks = Calculate::standard_drinks(all_drink.abv, all_drink._size, std_drink_size);
        if (date_std_drinks.find(date) == date_std_drinks.end()) {
            // Date not in date_std_drinks
            date_std_drinks[date] = std_drinks;
        } else {
            // Date already processed
            auto it = date_std_drinks.find(date);
            it->second += std_drinks;
        }
    }

    // Add empty drinks to fix graph where no drinks were entered
    for (int year = first_year; year <= last_year; year++) {
        for (int week_num = 0; week_num <= 51; week_num++) {
            std::string year_week_num = std::to_string(year) + '-' + std::to_string(week_num);
            std::string date_str = std::to_string(date_from_week_num(year_week_num));
            int date = parse_date(date_str);

            // Add to vector
            if (date_std_drinks.find(date) == date_std_drinks.end() && date <= max_date && date >= min_date) {
                // Date not in date_std_drinks
                date_std_drinks[date] = 0;
            }
        }
    }

    // Create the QVectof of QCPGraphData objects
    QVector<QCPGraphData> time_data(static_cast<qsizetype>(date_std_drinks.size()));
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

    std::string date_a_cpy = a.date;
    std::string date_b_cpy = b.date;

    int date_a {parse_date(date_a_cpy)};
    int date_b {parse_date(date_b_cpy)};

    return date_a < date_b;
}

int Graphing::parse_date(std::string &date) {
    /*
     * Convert date string to integer date.
     * @param date: A date in the format YYYYMMDD
     * @return: an integer in UNIX epoch time
     */

    std::tm t = {};
    std::stringstream date_str;
    date_str.str(date);
    std::stringstream new_date;

    date_str >> std::get_time(&t, "%Y%m%d");
    std::put_time(&t, "%c");
    auto timet = (int)std::mktime(&t);

    return timet;
}

QCustomPlot *Graphing::plot_abvs(const QVector<QCPGraphData>& time_data, const Options& options, QDialog *parent) {
    /*
     * Plot the ABV over time graph.
     * @param time_data: A QVector of QCPGraphData objects.
     */

    auto *abv_plot = new QCustomPlot(parent);
    abv_plot->setAttribute(Qt::WA_DeleteOnClose);
    int limit = Calculate::weekly_limit(options);

    abv_plot->plotLayout()->insertRow(0);
    abv_plot->plotLayout()->addElement(0, 0,
                                       new QCPTextElement(abv_plot, "Alcohol Consumption Over Time",
                                                          QFont("sans", 12, QFont::Bold)));

    // Create the ABV graph

    // Graph style
    QPen drawPen;
    drawPen.setColor(Qt::black);
    drawPen.setStyle(Qt::PenStyle::SolidLine);
    drawPen.setWidth(2);

    if (time_data.size() > 1) {
        // Get min and max values
        int min_year = std::numeric_limits<int>::max(); // Everything is <= this
        int max_year = std::numeric_limits<int>::min(); // Everything is >= this
        double min_drinks = std::numeric_limits<int>::max();
        double max_drinks = std::numeric_limits<int>::min();
        for (auto data : time_data) {
            int year = static_cast<int>(data.key);
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

        // Set min drinks to just below limit line if limit is below min drinks
        if (limit <= min_drinks) {
            min_drinks = limit - 3;
            std::cout << "Limit below minimum drinks consumed. "\
                     "Resetting graph Y-axis to a min of " << min_drinks << std::endl;
        }

        QColor color(70,95, 150, 150);
        // Set up limit line
        auto* limit_line = new QCPItemStraightLine(abv_plot);
        limit_line->point1->setCoords(min_year, limit);
        limit_line->point2->setCoords(max_year, limit);
        limit_line->setPen(QPen(QColor(255, 0, 0)));

        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);

        // Show dates if fewer than 15 weeks of data
        if (time_data.size() < 15) {
            dateTicker->setDateTimeFormat("d. MMM\nyyyy");
        } else {
            dateTicker->setDateTimeFormat("MMM\nyyyy");
        }

        if (min_drinks > 0) {
            min_drinks -= 0.5;
        }

        dateTicker->setTickOrigin(min_year);
        abv_plot->xAxis->setTicker(dateTicker);
        abv_plot->addGraph();
        abv_plot->graph()->setPen(drawPen);
        abv_plot->graph(0)->data()->set(time_data);
        abv_plot->xAxis->setLabel("Date");
        abv_plot->yAxis->setLabel("Std. Drinks");
        abv_plot->xAxis->setRange(min_year, max_year);
        abv_plot->yAxis->setRange(min_drinks, max_drinks);
        //abv_plot->graph(0)->rescaleAxes();
        abv_plot->graph()->setLineStyle(QCPGraph::lsLine);
        abv_plot->graph()->setPen(QPen(color.darker(200)));
        abv_plot->graph()->setBrush(QBrush(color));
    } else {
        auto *no_data_label = new QCPItemText(abv_plot);
        no_data_label->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
        no_data_label->position->setType(QCPItemPosition::ptAxisRectRatio);
        no_data_label->position->setCoords(0.5, .5);
        no_data_label->setText("Not enough data to plot");
        no_data_label->setPen(QPen(Qt::black));
        no_data_label->setPadding(QMargins(2, 2, 2, 2));
        abv_plot->xAxis->setVisible(false);
        abv_plot->yAxis->setVisible(false);
    }

    abv_plot->replot();

    return abv_plot;
}

std::string Graphing::week_number(const int date) {
    /*
     * Get the week number for a date
     * @param date: An integer of date, e.g. 20210405
     * @return: year and week number, e.g. 2021-05
     */

    constexpr int days_per_week {7};
    struct tm tm{};
    strptime(std::to_string(date).c_str(), "%Y%m%d", &tm);

    const int wday = tm.tm_wday;
    const int delta = wday ? wday - 1 : days_per_week - 1;

    int week_num = (tm.tm_yday + days_per_week - delta) / days_per_week;

    return std::to_string(date).substr(0, 4) + '-' + std::to_string(week_num);
}

int Graphing::date_from_week_num(const std::string& week_num) {
    /*
     * Calculates the date from a week number.
     * @param week_num: theweek number to calculate the date for.
     * @return an integer denoting date, in YYYYMMDD format.
     */

    struct tm tm{};
    std::string week_num_tmp = week_num + "-1";
    auto week_char = std::make_unique<char>(week_num_tmp.length() + 1);
    strcpy(week_char.get(), week_num_tmp.c_str());
    strptime(week_char.get(), "%Y-%W-%w", &tm);

    std::string year = std::to_string(tm.tm_year +1900);
    std::string month = std::to_string(tm.tm_mon + 1);
    std::string day = std::to_string(tm.tm_mday);

    month = (month.length() == 1) ? '0' + month : month; // Zero pad if single digit month
    day = (day.length() == 1) ? '0' + day : day;  // Zero pad if single digit day

    std::string date_str = year + month + day;
    int date = std::stoi(date_str);

    return date;
}
