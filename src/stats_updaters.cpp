//
// Created by Ross Wardrup on 4/23/21.
//

#include "mainwindow.h"
#include "calculate.h"
#include <iostream>

void MainWindow::update_stat_panel() {
    /*
     * Calculate number of standard drinks consumed since Sunday.
     */

    date::year_month_day start_date{};
    double standard_drinks = 0;
    std::string weekday_name;
    std::string current_tab = get_current_tab();

    // Get filter day & day of week.
    std::tuple<date::year_month_day, std::string> filter_date_results = get_filter_date();

    start_date = std::get<0>(filter_date_results);
    weekday_name = std::get<1>(filter_date_results);

    std::cout << "Calculating stats since " << start_date << ", which is last " << weekday_name << std::endl;

    std::string query_date = format_date(start_date);

    std::cout << "Querying DB for drinks after " << query_date << std::endl;

    std::vector<Drink> drinks_this_week = Database::filter("After Date", query_date, storage);

    for (const auto& drink : drinks_this_week) {
        if (options.std_drink_country == "Custom") {
            standard_drinks += Calculate::standard_drinks(drink.abv, drink._size, std::stod(options.std_drink_size));
        } else {
            double std_drink_size = std_drink_standards.find(options.std_drink_country)->second;  // This is in oz.

            /*
             * Drink._size will always be in ounces. std_drink_size should also be in ounces. The result will be
             * independent of whichever unit the user has selected, as everything is stored as ounces.
             */
            standard_drinks += Calculate::standard_drinks(drink.abv, drink._size, std_drink_size);
        }
    }

    if (options.units == "Imperial") {
        ui->volAlcoholConsumedLabel->setText("Oz. alcohol consumed:");
        ui->volAlcoholRemainingLabel->setText("Oz. alcohol remaining:");
    } else {
        ui->volAlcoholConsumedLabel->setText("ml alcohol consumed:");
        ui->volAlcoholRemainingLabel->setText("ml alcohol remaining:");
    }

    // Update the individual elements of the stat pane
    update_drinks_this_week(standard_drinks, weekday_name);
    update_standard_drinks_left_this_week(standard_drinks);

    // update_vol_alcohol_consumed_this_week returns either ml or oz, depending on setting
    double vol_alc_consumed = update_vol_alcohol_consumed_this_week(drinks_this_week, weekday_name);
    update_volume_alcohol_remaining(vol_alc_consumed);
    update_favorite_producer(current_tab);
    update_favorite_drink(current_tab);
    update_favorite_type(current_tab);
    update_mean_abv(current_tab);
    update_mean_ibu(current_tab);
    update_std_drinks_today();
}

void MainWindow::update_drinks_this_week(double standard_drinks, const std::string& weekday_name) {
    /*
     * Update the standard drinks this week output label.
     * @param standard_drinks: a double denoting the number of standard drinks consumed.
     * @param weekday_name: The day the calculation began on.
     */

    std::string drinksThisWeekLabelText = "Std. drinks since " + weekday_name + ":";
    ui->drinksThisWeekLabel->setText(QString::fromStdString(drinksThisWeekLabelText));
    if (standard_drinks == 0.0) {
        ui->drinksThisWeekOutput->setText("0.0");
    } else {
        ui->drinksThisWeekOutput->setText(QString::fromStdString(Calculate::double_to_string(standard_drinks)));
    }
}

void MainWindow::update_standard_drinks_left_this_week(double std_drinks_consumed) {
    /*
     * Update the std. drinks left this week to the amount of std. drinks left this week.
     */

    double std_drinks_left = Calculate::standard_drinks_remaining(options.sex, options.limit_standard, options.weekly_limit, std_drinks_consumed);
    ui->drinksLeftOutput->setText(QString::fromStdString(Calculate::double_to_string(std_drinks_left)));

    // Set standard drinks remaining text to red if negative
    if (std_drinks_left < 0) {
        ui->drinksLeftOutput->setStyleSheet("QLabel {color : red;}");
    } else {
        ui->drinksLeftOutput->setStyleSheet("");
    }
}

double MainWindow::update_vol_alcohol_consumed_this_week(const std::vector<Drink>& drinks_this_week, const std::string& weekday_name) {
    /*
     * Update the volume alcohol consumed output label to the total amount alcohol consumed this week.
     * @param drinks_this_week: A vector of Drinks containing the drinks consumed in the past week.
     * @param weekday_name: The day the week began on.
     */

    double volume_consumed = 0;

    std::string units = "Oz.";
    if (options.units == "Metric") {
        units = "ml";
    }
    std::string volumeThisWeekLabelText = units + " alcohol since " + weekday_name + ":";
    ui->volAlcoholConsumedLabel->setText(QString::fromStdString(volumeThisWeekLabelText));

    // Calculate total volume for the week
    for (const auto& drink : drinks_this_week) {
        double drinks_vol_alcohol;
        if (options.units == "Imperial") {
            drinks_vol_alcohol = (drink.abv / 100) * drink._size;
        } else {
            // Everything is stored in DB as oz. Convert back to ml for display.
            double drink_size = Calculate::oz_to_ml(drink._size);
            drinks_vol_alcohol = (drink.abv / 100) * drink_size;
        }
        volume_consumed += drinks_vol_alcohol;
    }

    if (volume_consumed == 0.0) {
        ui->volAlcoholConsumedOutput->setText("0.0");
    } else {
        // Round to tenth place
        volume_consumed = floor(volume_consumed * 10 + 0.5) / 10;
        ui->volAlcoholConsumedOutput->setText(QString::fromStdString(Calculate::double_to_string(volume_consumed)));
    }

    return volume_consumed;
}

void MainWindow::update_volume_alcohol_remaining(double volume_alcohol_consumed) {
    /*
     * Update the volume alcohol remaining label text to the amount of alcohol remaining.
     * @param: volume_alcohol_consumed: A double denoting the volume of alcohol consumed in the past week. This will
     * either be in ounces or milliliters, depending on the option setting. The value is set in
     * update_vol_alcohol_consumed_this_week().
     */

    double volume_alcohol_remaining;
    double std_drink_size;

    if (options.std_drink_country == "Custom") {
        std_drink_size = std::stod(options.std_drink_size);
    } else {
        std_drink_size = std_drink_standards.find(options.std_drink_country)->second;
    }

    if (options.units == "Imperial") {
        volume_alcohol_remaining = Calculate::volume_alcohol_remaining(options.sex, options.limit_standard, options.weekly_limit, volume_alcohol_consumed, std_drink_size);
    } else {
        volume_alcohol_consumed = Calculate::ml_to_oz(volume_alcohol_consumed);
        volume_alcohol_remaining = Calculate::volume_alcohol_remaining(options.sex, options.limit_standard, options.weekly_limit, volume_alcohol_consumed, std_drink_size);
        volume_alcohol_remaining = Calculate::oz_to_ml(volume_alcohol_remaining);

        // Round to tenth place
        volume_alcohol_remaining = floor(volume_alcohol_remaining * 10 + 0.5) / 10;
    }
    ui->volAlcoholRemainingOutput->setText(QString::fromStdString(Calculate::double_to_string(volume_alcohol_remaining)));

    // Set volume alcohol remaining text to red if negative
    if (volume_alcohol_remaining < 0) {
        ui->volAlcoholRemainingOutput->setStyleSheet("QLabel {color : red;}");
    } else {
        ui->volAlcoholRemainingOutput->setStyleSheet("");
    }
}

void MainWindow::update_favorite_producer(const std::string& drink_type) {
    /*
     * Update the favorite brewery text label to the most common drink in the database.
     */

    std::string favorite_producer = Calculate::favorite_producer(storage, drink_type);
    if (favorite_producer.empty()) {
        favorite_producer = "No " + drink_type + " entered";
    }
    ui->favoriteProducerOutput->setText(QString::fromStdString(favorite_producer));
}

void MainWindow::update_favorite_drink(const std::string& drink_type) {
    /*
     * Update the favorite beer text label to the most common beer in the database.
     */

    std::string favorite_drink = Calculate::favorite_drink(storage, drink_type);
    if (favorite_drink.empty()) {
        favorite_drink = "No " + drink_type + " entered";
    }
    ui->favoriteDrinkOutput->setText(QString::fromStdString(favorite_drink));
}

void MainWindow::update_mean_abv(const std::string& drink_type) {
    /*
     * Update the mean ABV text label to the mean ABV of all drinks in the database.
     */

    std::string mean_abv = Calculate::double_to_string(Calculate::mean_abv(storage, drink_type));
    if (mean_abv == "nan" || mean_abv.empty()) {
        mean_abv = "No " + drink_type + " entered";
    }
    ui->avgAbvDrinkOutput->setText(QString::fromStdString(mean_abv));
}

void MainWindow::update_mean_ibu(const std::string& drink_type) {
    /*
     * Set the mean IBU text label to the mean IBU of all beers in the database.
     */

    if (drink_type == "Beer") {
        std::string mean_ibu = Calculate::double_to_string(Calculate::mean_ibu(storage, drink_type));
        if (mean_ibu == "nan" || mean_ibu.empty()) {
            mean_ibu = "No " + drink_type + " entered";
        }
        ui->avgIbuDrinkOutput->setText(QString::fromStdString(mean_ibu));
    }
}

void MainWindow::update_std_drinks_today() {
    /*
     * Calculate standard drinks consumed today & update the line in the stats panel.
     */

    double std_drinks_today {0.0};

    auto now_time = std::chrono::system_clock::now();

    // Delete the following
    auto now_c = std::chrono::system_clock::to_time_t(now_time);
    std::tm now_tm = *std::localtime(&now_c);
    char query_date[70];
    std::strftime(query_date, sizeof query_date, "%Y-%m-%d", &now_tm);

    std::vector<Drink> drinks_today = Database::filter("After Date", query_date, storage);

    for (auto& drink : drinks_today) {
        double std_drinks;
        if (options.std_drink_country == "Custom") {
            std_drinks= Calculate::standard_drinks(drink.abv, drink._size, std::stod(options.std_drink_size));
        } else {
            double std_drink_size = std_drink_standards.find(options.std_drink_country)->second;
            std_drinks = Calculate::standard_drinks(drink.abv, drink._size, std_drink_size);
        }
        std_drinks_today += std_drinks;
    }

    ui->stdDrinksTodayOutput->setText(QString::fromStdString(Calculate::double_to_string(std_drinks_today)));
}

void MainWindow::update_favorite_type(const std::string& drink_type) {
    /*
     * Set the favoriteTypeOutput to the most common drink found in the database.
     */

    std::string fave_type = Calculate::favorite_type(storage, drink_type);
    if (fave_type.empty()) {
        fave_type = "No " + drink_type + " entered";
    }
    ui->favoriteTypeOutput->setText(QString::fromStdString(fave_type));
}