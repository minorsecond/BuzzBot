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
    double update_standard_drinks_this_week();
    void update_standard_drinks_left_this_week(double std_drinks_consumed);

private slots:
    void submit_button_clicked();
    void clear_fields();
    void update_table();
    void populate_fields(const QItemSelection &, const QItemSelection &);
    void delete_row();
    void enable_filter_text(const QString&);
    void changed_filter_text(const QString&);
    void open_user_settings();
};
#endif // MAINWINDOW_H
