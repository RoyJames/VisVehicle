#include "datamanager.h"

DataManager::DataManager()
{

}


void DataManager::changeData(QString dataname, double value)
{
    datamap[dataname].value = value;
}

void DataManager::importData(QString datalist)
{

}

const dataprop& DataManager::queryData(QString dataname)
{
    return datamap[dataname];
}
