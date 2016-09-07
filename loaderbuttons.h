#ifndef LOADERBUTTONS_H
#define LOADERBUTTONS_H

#include "buttons.h"
#include "definitions.h"

class LoaderButtons : public Buttons
{
public:
    LoaderButtons();
    LoaderButtons(QString _disp_name, QString _table_name, short _flag);
    void loadTable();
    QString getTableName();
    QString getDatabaseName();
    short getDataFlag();
    void setDatabaseName(QString newname);
private:
    QString database_name;
    QString table_name;
    short data_contained_flag;
};

#endif // LOADERBUTTONS_H
