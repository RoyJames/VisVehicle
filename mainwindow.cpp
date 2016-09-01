#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "engine.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <QSqlTableModel>
#include <QFile>
#include <QButtonGroup>
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

    //model->setHeaderData(0, Qt::Horizontal, tr("Contents"));
    //model->setHeaderData(1, Qt::Horizontal, tr("Unit"));
    //model->setHeaderData(2, Qt::Horizontal, tr("Number"));

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
    QFile button_list(":/new/lists/load_buttons_list");
    if(!button_list.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed.";
        return;
    }

    QTextStream txtInput(&button_list);
    QString lineStr;

    loader_buttons_group = new QButtonGroup;
    int buttons_cnt = 0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QPushButton *new_button = new QPushButton(lineStr);
        loader_buttons_group->addButton(new_button, ++buttons_cnt);
        loaderbuttons_layout->addWidget(new_button);
        loader_buttons.push_back(new LoaderButtons(lineStr, "unknown table name"));
    }
    connect(loader_buttons_group, SIGNAL(buttonClicked(int)), this, SLOT(onGroupButtonClicked(int)));
    button_list.close();
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

void MainWindow::onGroupButtonClicked(int id)
{
    qDebug() << id;
}
