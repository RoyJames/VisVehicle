#include "loaderbuttons.h"
#include "buttons.h"
#include <QString>

LoaderButtons::LoaderButtons()
{

}

LoaderButtons::LoaderButtons(QString _disp_name, QString _table_name):Buttons(_disp_name), table_name(_table_name)
{
    database_name = DEFAULT_VEHICLE_DATABASE;
}

void LoaderButtons::loadTable()
{

}
