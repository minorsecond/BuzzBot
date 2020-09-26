#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ui_mainwindow.h"

struct Options {
    std::string sex = "male";
    std::string date_calculation_method = "Rolling";
    std::string weekday_start = "Sunday";
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    Options options;

private:
    Ui::MainWindow *ui;
    Storage storage = initStorage(Database::path());
    void populate_filter_menus(const std::string& filter_type);
    void update_beer_fields();
    void update_liquor_fields();
    void update_wine_fields();
    static std::string settings_path();
    void program_options(bool write);
    void update_stat_panel();
    void update_drinks_this_week(double standard_drinks, const std::string& weekday_name);
    void update_standard_drinks_left_this_week(double std_drinks_consumed);
    double update_oz_alcohol_consumed_this_week(const std::vector<Drink>& beers_this_week, const std::string& weekday_name);
    void update_oz_alcohol_remaining(double oz_alcohol_consumed);
    void update_favorite_brewery();
    void update_favorite_beer();
    void update_favorite_type();
    void update_mean_abv();
    void update_mean_ibu();
    void update_types_producers_on_name_change();
    std::string get_latest_notes(const std::string& name, const std::string& alcohol_type);
    std::string get_current_tab();
    Drink get_drink_attributes_from_fields();
    void update_selected_row(QItemSelectionModel* select, Drink entered_drink);
    void add_new_row(Drink entered_drink);
    std::vector<std::set<QString>> generate_filter_item_sets();
    static QDate format_date_for_input(const Drink& drink);
    void populate_beer_fields(const Drink& drink_at_row);
    void populate_liquor_fields(const Drink& drink_at_row);
    void populate_wine_fields(const Drink& drink_at_row);
    void update_beer_names_producers();
    void update_liquor_names_producers();
    void update_wine_names_producers();
    void update_beer_names_types();
    void update_liquor_names_types();
    void update_wine_names_types();
    void update_beer_types_producers();
    void update_liquor_types_producers();
    void update_wine_types_producers();
    Drink get_beer_attrs_from_fields(std::string alcohol_type);
    Drink get_liquor_attrs_from_fields(std::string alcohol_type);
    Drink get_wine_attrs_from_fields(std::string alcohol_type);
    void add_menubar_items();
    void configure_calendar();
    void configure_table();
    void add_slot_connections();
    void set_input_states();
    Drink get_drink_at_selected_row();
    void clear_fields(const std::string& alcohol_type);

private slots:
    void submit_button_clicked();
    void reset_fields();
    void update_table();
    void populate_fields(const QItemSelection &, const QItemSelection &);
    void delete_row();
    void enable_filter_text(const QString&);
    void changed_filter_text(const QString&);
    void open_user_settings();
    void open_about_dialog();
    void open_export_dialog();
    void open_std_drink_calculator();
    void reset_table_sort();
    void name_input_changed(const QString&);
    void type_input_changed(const QString&);
    void producer_input_changed(const QString&);
    void tab_changed();
    void clicked_clear_button();
};
#endif // MAINWINDOW_H
