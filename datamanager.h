#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <map>
#include <QString>

struct dataprop
{
    QString name;
    QString unit;
    double value;
};

class DataManager
{
public:
    DataManager();
    void changeData(QString dataname, double value);
    void importData(QString datalist);
    const dataprop &queryData(QString dataname);

private:
    std::map<QString, dataprop> datamap;
};

#endif // DATAMANAGER_H
