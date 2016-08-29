#ifndef LOADERBUTTONS_H
#define LOADERBUTTONS_H

#include "buttons.h"
class LoaderButtons : public Buttons
{
public:
    LoaderButtons();
    LoaderButtons(QString _button_name, QString _target_name);
    void loadData();
};

#endif // LOADERBUTTONS_H
