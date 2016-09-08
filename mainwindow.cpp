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
#include "buttons.h"
#include "glwidget.h"

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

    addTestButtons();

    //ui->horizontalLayout_test->addWidget(new GLWidget(this));
    linkEngine();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addLoadButtons()
{
    QFile button_list(READ_BUTTON_LIST_PATH);
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
        new_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        loader_buttons_group->addButton(new_button, ++buttons_cnt);
        loaderbuttons_layout->addWidget(new_button);
        loader_buttons.push_back(new LoaderButtons(lineStr, fields.takeFirst(), fields.takeLast().toInt()));
    }
    connect(loader_buttons_group, SIGNAL(buttonClicked(int)), this, SLOT(onGroupButtonClicked(int)));
    button_list.close();
}

void MainWindow::addTestButtons()
{
    QFile button_list(":/new/lists/test_category_list");
    if(!button_list.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed.";
        return;
    }

    QTextStream txtInput(&button_list);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        QStringList fields = lineStr.split(',');
        TestCategory *newCategory = new TestCategory(fields.takeFirst());
        int n_subcats = fields.takeFirst().toInt();
        while(n_subcats--)
        {
            TestSubcategory *newSubcategory = new TestSubcategory();
            QString sublineStr;
            sublineStr = txtInput.readLine();
            QStringList subfields = sublineStr.split(',');

            // Read subcategory name and descriptions
            newSubcategory->SubcategoryName = subfields.takeFirst();
            //int n_short = subfields.takeFirst().toInt();
            newSubcategory->ShortDescriptions = subfields.takeFirst();
            newSubcategory->FullDescriptions = txtInput.readLine();

            // Read function name and database path
            sublineStr = txtInput.readLine();
            subfields = sublineStr.split(',');
            newSubcategory->FunctionName = subfields.takeFirst();
            newSubcategory->DatabasePath = subfields.takeFirst();

            // Read graph database names
            sublineStr = txtInput.readLine();
            subfields = sublineStr.split(',');
            int n_graph = subfields.takeFirst().toInt();
            while (n_graph--)
            {
                newSubcategory->ResGraphNames.push_back(subfields.takeFirst());
            }
            // Read table database name
            sublineStr = txtInput.readLine();
            subfields = sublineStr.split(',');
            int n_table = subfields.takeFirst().toInt();
            while (n_table--)
            {
                newSubcategory->ResTableNames.push_back(subfields.takeFirst());
            }

            // Finish reading this subcategory
            newCategory->subcats.push_back(newSubcategory);
        }
        // Finish reading this main category
        main_categories.push_back(newCategory);
    }
}

void MainWindow::linkEngine()
{
    qDebug() << "Prepare to load engine" << endl;
    matEngine = engOpen(NULL);
    engSetVisible(matEngine, true);
    qDebug() << "Engine loaded successfully" << endl;

    /*
    mxArray *cell_array_ptr;
    mwIndex i;
    int nrhs = 2;

    double time[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    mxArray *prhs[2];
    prhs[0] = mxCreateDoubleMatrix(1, 10, mxREAL);
    memcpy((char *) mxGetPr(prhs[0]), (char *) time, 10*sizeof(double));
    prhs[1] = mxCreateString("test string");

    cell_array_ptr = mxCreateCellMatrix((mwSize)nrhs,1);
    for( i=0; i<(mwIndex)nrhs; i++){
            mxSetCell(cell_array_ptr,i,mxDuplicateArray(prhs[i]));
    }
    engPutVariable(matEngine, "mycell", cell_array_ptr);
    */


    mxArray *buffer;
    engEvalString(matEngine, "teststr=cell(2,1); teststr{1}=['winter',char(9),' is',char(9), 'coming']; teststr{2}=['winter',char(9),'is',char(9),'not',char(9), 'coming']");
    buffer = mxGetCell(engGetVariable(matEngine, "teststr"), 0);
    QString str = mxArrayToString(buffer);
    //qDebug() << str;
    QStringList strlist = str.split('\t');
    while (!strlist.empty())
    {
        qDebug() << strlist.takeFirst();
    }
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
    //qDebug() << "Clicked button is:" << id << " " << loader_buttons[id-1]->getTableName() << " " << loader_buttons[id-1]->getDataFlag();
    setDisplayTable(id);
}

void MainWindow::setDisplayTable(int button_id)
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    LoaderButtons *currentLoader = loader_buttons[button_id - 1];
    db.setDatabaseName(currentLoader->getDatabaseName());
    if (!db.open()) return;
    //qDebug() << "connection succeeded";

    if (general_table != NULL)
    {
        delete general_table;
        general_table = NULL;
    }
    if (wheel_table != NULL)
    {
        delete wheel_table;
        wheel_table = NULL;
    }
    if (list_table != NULL)
    {
        delete list_table;
        list_table = NULL;
    }

    if (currentLoader->getDataFlag() & WHEEL_TYPE)
    {
        QSqlTableModel *wheel_model;
        wheel_model = new QSqlTableModel(this);
        wheel_model->setTable(currentLoader->getTableName());
        wheel_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        wheel_model->setFilter("flag = \"WHEEL\"");
        if (!wheel_model->select()) return;
        wheel_table = new QTableView;
        ui->verticalLayout_display->insertWidget(0, wheel_table);
        wheel_table->setModel(wheel_model);
        wheel_table->hideColumn(wheel_model->fieldIndex("Number"));
        wheel_table->hideColumn(wheel_model->fieldIndex("flag"));
        wheel_table->resizeColumnsToContents();
        wheel_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        wheel_table->setAlternatingRowColors(true);
        wheel_table->setStyleSheet("alternate-background-color: gray");
        connect(ui->pushButton_confirm, SIGNAL(clicked()), wheel_model, SLOT(submitAll()));
        connect(ui->pushButton_undo, SIGNAL(clicked()), wheel_model, SLOT(revertAll()));
    }

    if (currentLoader->getDataFlag() & GENERAL_TYPE)
    {
        QSqlTableModel *general_model;
        general_model = new QSqlTableModel(this);
        general_model->setTable(currentLoader->getTableName());
        general_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        general_model->setFilter("flag = \"GENERAL\"");
        if (!general_model->select()) return;

        general_table = new QTableView;
        ui->verticalLayout_display->insertWidget(0, general_table);
        general_table->setModel(general_model);
        general_table->hideColumn(general_model->fieldIndex("FL"));
        general_table->hideColumn(general_model->fieldIndex("FR"));
        general_table->hideColumn(general_model->fieldIndex("RL"));
        general_table->hideColumn(general_model->fieldIndex("RR"));
        general_table->hideColumn(general_model->fieldIndex("flag"));
        general_table->resizeColumnsToContents();
        general_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
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
        if (!list_model->select()) return;

        list_table = new QTableView;
        ui->verticalLayout_display->insertWidget(0, list_table);
        list_table->setModel(list_model);
        list_table->hideColumn(list_model->fieldIndex("flag"));
        list_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        list_table->setAlternatingRowColors(true);
        list_table->setStyleSheet("alternate-background-color: gray");
        connect(ui->pushButton_confirm, SIGNAL(clicked()), list_model, SLOT(submitAll()));
        connect(ui->pushButton_undo, SIGNAL(clicked()), list_model, SLOT(revertAll()));
    }

}
