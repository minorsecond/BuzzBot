#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Storage storage = initStorage(Database::path());
    std::string sex = program_options("", false);
    static std::string double_to_string(double input_double);
    void populate_filter_menus(const std::string& filter_type);
    void update_beer_fields();
    static std::string settings_path();
    static std::string program_options(const std::string& sex, bool write);
    void update_stat_panel();
    void update_standard_drinks_left_this_week(double std_drinks_consumed);
    double update_oz_alcohol_consumed_this_week(const std::vector<Beer>& beers_this_week);
    void update_oz_alcohol_remaining(double oz_alcohol_consumed);
    void update_favorite_brewery();
    void update_favorite_beer();
    void update_mean_abv();
    void update_mean_ibu();

private slots:
    void submit_button_clicked();
    void clear_fields();
    void update_table();
    void populate_fields(const QItemSelection &, const QItemSelection &);
    void delete_row();
    void enable_filter_text(const QString&);
    void changed_filter_text(const QString&);
    void open_user_settings();
    void reset_table_sort();
    void name_input_changed(const QString&);
    void type_input_changed(const QString&);
    //void brewery_input_changed();
};
#endif // MAINWINDOW_H
