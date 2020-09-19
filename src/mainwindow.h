#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ui_mainwindow.h"

struct Options {
    std::string sex = "male";
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
    static std::string double_to_string(double input_double);
    void populate_filter_menus(const std::string& filter_type);
    void update_beer_fields();
    void update_liquor_fields();
    static std::string settings_path();
    void program_options(bool write);
    void update_stat_panel();
    void update_drinks_this_week(double standard_drinks);
    void update_standard_drinks_left_this_week(double std_drinks_consumed);
    double update_oz_alcohol_consumed_this_week(const std::vector<Drink>& beers_this_week);
    void update_oz_alcohol_remaining(double oz_alcohol_consumed);
    void update_favorite_brewery();
    void update_favorite_beer();
    void update_favorite_type();
    void update_mean_abv();
    void update_mean_ibu();
    void update_fields_on_drink_name_selected();
    std::string get_latest_notes(const std::string& name, const std::string& alcohol_type);
    std::string get_current_tab();
    Drink get_drink_attributes_from_fields();
    void update_selected_row(QItemSelectionModel* select, Drink entered_drink);
    void add_new_row(Drink entered_drink);

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
    void reset_table_sort();
    void name_input_changed(const QString&);
    void type_input_changed(const QString&);
    void brewery_input_changed(const QString&);
    void tab_changed();
};
#endif // MAINWINDOW_H
