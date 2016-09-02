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

    addLoadButtons();
    general_table = NULL;
    wheel_table = NULL;
    list_table = NULL;
    setDisplayTable(1);


    //linkEngine();

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
        QStringList fields = lineStr.split(',');
        QPushButton *new_button = new QPushButton(fields.takeFirst());
        loader_buttons_group->addButton(new_button, ++buttons_cnt);
        loaderbuttons_layout->addWidget(new_button);
        loader_buttons.push_back(new LoaderButtons(lineStr, fields.takeFirst(), fields.takeLast().toInt()));
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
    qDebug() << "Clicked button is:" << id << " " << loader_buttons[id-1]->getTableName() << " " << loader_buttons[id-1]->getDataFlag();
    setDisplayTable(id);
}

void MainWindow::setDisplayTable(int button_id)
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    LoaderButtons *currentLoader = loader_buttons[button_id - 1];
    db.setDatabaseName(currentLoader->getDatabaseName());
    if (!db.open()) return;
    qDebug() << "connection succeeded";

    if (general_table != NULL) delete general_table;
    if (wheel_table != NULL) delete wheel_table;
    if (list_table != NULL) delete list_table;

    if (currentLoader->getDataFlag() & WHEEL_TYPE)
    {
        QSqlTableModel *wheel_model;
        wheel_model = new QSqlTableModel(this);
        wheel_model->setTable(currentLoader->getTableName());
        wheel_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        wheel_model->setFilter("flag = \"WHEEL\"");
        qDebug() << wheel_model->select();

        wheel_table = new QTableView;
        ui->verticalLayout_display->insertWidget(0, wheel_table);
        wheel_table->setModel(wheel_model);
        wheel_table->hideColumn(wheel_model->fieldIndex("Number"));
        wheel_table->hideColumn(wheel_model->fieldIndex("flag"));
        wheel_table->resizeColumnsToContents();
        wheel_table->setAlternatingRowColors(true);
        wheel_table->setStyleSheet("alternate-background-color: gray");
        connect(ui->pushButton_confirm, SIGNAL(clicked()), wheel_table, SLOT(submitAll()));
        connect(ui->pushButton_undo, SIGNAL(clicked()), wheel_table, SLOT(revertAll()));
    }

    if (currentLoader->getDataFlag() & GENERAL_TYPE)
    {
        QSqlTableModel *general_model;
        general_model = new QSqlTableModel(this);
        general_model->setTable(currentLoader->getTableName());
        general_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        general_model->setFilter("flag = \"GENERAL\"");
        qDebug() << general_model->select();

        general_table = new QTableView;
        ui->verticalLayout_display->insertWidget(0, general_table);
        general_table->setModel(general_model);
        general_table->hideColumn(general_model->fieldIndex("FL"));
        general_table->hideColumn(general_model->fieldIndex("FR"));
        general_table->hideColumn(general_model->fieldIndex("RL"));
        general_table->hideColumn(general_model->fieldIndex("RR"));
        general_table->hideColumn(general_model->fieldIndex("flag"));
        general_table->resizeColumnsToContents();
        general_table->setAlternatingRowColors(true);
        general_table->setStyleSheet("alternate-background-color: gray");
        connect(ui->pushButton_confirm, SIGNAL(clicked()), general_model, SLOT(submitAll()));
        connect(ui->pushButton_undo, SIGNAL(clicked()), general_model, SLOT(revertAll()));
    }

    if (currentLoader->getDataFlag() & LIST_TYPE)
    {
        QSqlTableModel *list_model;
        list_model = new QSqlTableModel(this);
        list_model->setTable(currentLoader->getTableName());
        list_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        list_model->setFilter("flag = \"LIST\"");
        qDebug() << list_model->select();

        list_table = new QTableView;
        ui->verticalLayout_display->insertWidget(0, list_table);
        list_table->setModel(list_model);
        list_table->hideColumn(list_model->fieldIndex("flag"));
        list_table->resizeColumnsToContents();
        list_table->setAlternatingRowColors(true);
        list_table->setStyleSheet("alternate-background-color: gray");
        connect(ui->pushButton_confirm, SIGNAL(clicked()), list_model, SLOT(submitAll()));
        connect(ui->pushButton_undo, SIGNAL(clicked()), list_model, SLOT(revertAll()));
    }

}
