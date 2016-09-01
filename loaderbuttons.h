#ifndef LOADERBUTTONS_H
#define LOADERBUTTONS_H

#include "buttons.h"
#include "definitions.h"

class LoaderButtons : public Buttons
{
public:
    LoaderButtons();
    LoaderButtons(QString _disp_name);
    void loadTable();

private:
    QString table_name;
    char data_contained_flag;
};

#endif // LOADERBUTTONS_H
