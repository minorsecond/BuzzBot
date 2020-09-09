#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    static std::string double_to_string(double input_double);

private slots:
    void submit_button_clicked();
    void clear_fields();
    void update_table();
    void populate_fields(const QItemSelection &, const QItemSelection &);
    void delete_row();
};
#endif // MAINWINDOW_H
