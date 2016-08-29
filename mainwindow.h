#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <QStackedWidget>
#include <QWidget>

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
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout;

    Engine *matEngine;

    std::vector<LoaderButtons> loader_buttons;
    std::vector<Buttons> plot_buttons;
    QStackedWidget *task_stacks;
    QWidget *step_loadfiles;
    QWidget *step_conditions;
    QWidget *step_simulation;
    //DataManager vehicle_data;
};

#endif // MAINWINDOW_H
