#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engine.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <QSqlTableModel>
#include "connection.h"

#include "loaderbuttons.h"
#include "datamanager.h"
#include "buttons.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    loaderbuttons_layout = ui->verticalLayout_loadFile;
    task_stacks = ui->stackedWidget;
    step_loadfiles = ui->page_load;
    step_conditions = ui->page_conditions;
    step_simulation = ui->page_simulation;
    general_table = ui->tableView_generaldata;
    addLoadButtons();

    //linkEngine();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/VisVehicle/defaultvehicles.db");
    if (!db.open()) return;
    qDebug() << "connection succeeded";

    QSqlTableModel *model;
    model = new QSqlTableModel(this);
    model->setTable("generaldata");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("Contents"));
    model->setHeaderData(1, Qt::Horizontal, tr("Unit"));
    model->setHeaderData(2, Qt::Horizontal, tr("Number"));

    general_table->setModel(model);
    general_table->resizeColumnsToContents();
    general_table->setAlternatingRowColors(true);
    general_table->setStyleSheet("alternate-background-color: gray");
    connect(ui->pushButton_undo, SIGNAL(clicked()), model, SLOT(revertAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addLoadButtons()
{
    QPushButton *button_loadSummary = new QPushButton("Edit Summary Sheet");
    loaderbuttons_layout->addWidget(button_loadSummary);

    QPushButton *button_loadINFO = new QPushButton("Edit Vehicle INFO");
    loaderbuttons_layout->addWidget(button_loadINFO);

    QPushButton *button_loadParameters = new QPushButton("Edit Vehicle Parameters");
    loaderbuttons_layout->addWidget(button_loadParameters);

    QPushButton *button_loadSuspension = new QPushButton("Edit Suspension Parameters");
    loaderbuttons_layout->addWidget(button_loadSuspension);

    QPushButton *button_loadDamper = new QPushButton("Edit Damper (optional)");
    loaderbuttons_layout->addWidget(button_loadDamper);

    QPushButton *button_loadSpring = new QPushButton("Edit Spring (optional)");
    loaderbuttons_layout->addWidget(button_loadSpring);
}

void MainWindow::linkEngine()
{
    qDebug() << "Prepare to load engine" << endl;
    matEngine = engOpen(NULL);
    qDebug() << "Engine loaded successfully" << endl;
}

void MainWindow::on_pushButton_load_clicked()
{
    task_stacks->setCurrentWidget(step_loadfiles);
}

void MainWindow::on_pushButton_condition_clicked()
{
    task_stacks->setCurrentWidget(step_conditions);

}

void MainWindow::on_pushButton_simulate_clicked()
{
    task_stacks->setCurrentWidget(step_simulation);
}
