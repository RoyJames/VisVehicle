#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <QStackedWidget>
#include <QWidget>
#include <QTableView>
#include <QButtonGroup>
#include <QListWidget>

#include "buttons.h"
#include "loaderbuttons.h"
#include "engine.h"
#include "testcategory.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);
    void addLoadButtons();
    void addTestButtons();
    void linkEngine();
    void setDisplayTable(int button_id);
    void createVehicleDatabase(QString vehicle_name);
    void saveVehicleDatabase(QString vehicle_name);
    void runSimulations();

private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_condition_clicked();

    void on_pushButton_simulate_clicked();

    void onGroupButtonClicked(int);

    void on_pushButton_loadvehicledata_clicked();

    void on_pushButton_confirmtest_clicked();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *loaderbuttons_layout;

    Engine *matEngine;

    std::vector<LoaderButtons*> loader_buttons;
    std::vector<TestCategory*> main_categories;
    std::vector<TestSubcategory*> selected_tests;
    std::vector<QString> selected_vehicles;
    QButtonGroup *loader_buttons_group;
    QStackedWidget *task_stacks;
    QWidget *step_loadfiles;
    QWidget *step_conditions;
    QWidget *step_simulation;
    QTableView *general_table;
    QTableView *wheel_table;
    QTableView *list_table;
    QListWidget *vehicle_list;

    //DataManager vehicle_data;
};

#endif // MAINWINDOW_H
