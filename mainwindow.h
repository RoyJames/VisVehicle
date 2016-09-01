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

#include "buttons.h"
#include "loaderbuttons.h"
#include "datamanager.h"
#include "engine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addLoadButtons();
    void linkEngine();

private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_condition_clicked();

    void on_pushButton_simulate_clicked();
    void onGroupButtonClicked(int);

private:
    Ui::MainWindow *ui;
    QVBoxLayout *loaderbuttons_layout;

    Engine *matEngine;

    std::vector<LoaderButtons*> loader_buttons;
    QButtonGroup *loader_buttons_group;
    QStackedWidget *task_stacks;
    QWidget *step_loadfiles;
    QWidget *step_conditions;
    QWidget *step_simulation;
    QTableView *general_table;
    QTableView *wheel_table;

    //DataManager vehicle_data;
};

#endif // MAINWINDOW_H
