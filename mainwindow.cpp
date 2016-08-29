#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engine.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>

#include "loaderbuttons.h"
#include "datamanager.h"
#include "buttons.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    layout = ui->verticalLayout_loadFile;
    task_stacks = ui->stackedWidget;
    step_loadfiles = ui->page_load;
    step_conditions = ui->page_conditions;
    step_simulation = ui->page_simulation;
    addLoadButtons();

    //linkEngine();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addLoadButtons()
{
    QPushButton *button_loadSummary = new QPushButton("Load Summary Sheet");
    layout->addWidget(button_loadSummary);

    QPushButton *button_loadINFO = new QPushButton("Load Vehicle INFO");
    layout->addWidget(button_loadINFO);

    QPushButton *button_loadParameters = new QPushButton("Load Vehicle Parameters");
    layout->addWidget(button_loadParameters);

    QPushButton *button_loadSuspension = new QPushButton("Load Suspension Parameters");
    layout->addWidget(button_loadSuspension);

    QPushButton *button_loadDamper = new QPushButton("Load Damper (optional)");
    layout->addWidget(button_loadDamper);

    QPushButton *button_loadSpring = new QPushButton("Load Spring (optional)");
    layout->addWidget(button_loadSpring);
}

void MainWindow::linkEngine()
{
    qDebug() << "Prepare to load engine" << endl;
    matEngine = engOpen(NULL);
    qDebug() << "Engine loaded successfully" << endl;
}

void MainWindow::on_pushButton_clicked()
{
    task_stacks->setCurrentWidget(step_loadfiles);
}

void MainWindow::on_pushButton_3_clicked()
{
    task_stacks->setCurrentWidget(step_conditions);

}

void MainWindow::on_pushButton_2_clicked()
{
    task_stacks->setCurrentWidget(step_simulation);
}
