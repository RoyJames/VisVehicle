#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <map>
#include <QString>

typedef struct wheel_data_struct
{
    QString name;
    QString unit;
    double value[4]; // in the order FL, FR, RL, RR
} wheel_data;

typedef struct general_data_struct
{
    QString name;
    QString unit;
    double value;
} general_data;

class DataManager
{
public:
    DataManager();
    void changeData(QString dataname, double value);
    void importData(QString datalist);
    //const dataprop &queryData(QString dataname);

private:
    std::map<QString, wheel_data> datamap_wheel;
    std::map<QString, general_data> datamap_general;
};

#endif // DATAMANAGER_H
