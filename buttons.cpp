#include "buttons.h"


Buttons::Buttons()
{
    button_name = "";
    target_name = "";
}


Buttons::Buttons(QString _button_name, QString _target_name):button_name(_button_name), target_name(_target_name)
{
}

