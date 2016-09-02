#include "loaderbuttons.h"
#include "buttons.h"
#include <QString>

LoaderButtons::LoaderButtons()
{

}

LoaderButtons::LoaderButtons(QString _disp_name, QString _table_name, short _flag):Buttons(_disp_name), table_name(_table_name), data_contained_flag(_flag)
{
    database_name = DEFAULT_VEHICLE_DATABASE;
}

void LoaderButtons::loadTable()
{

}

QString LoaderButtons::getTableName()
{
    return table_name;
}

QString LoaderButtons::getDatabaseName()
{
    return database_name;
}

short LoaderButtons::getDataFlag()
{
    return data_contained_flag;
}
