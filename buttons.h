#ifndef BUTTONS_H
#define BUTTONS_H

#include <QString>

class Buttons
{
public:
    Buttons();
    Buttons(QString _button_name, QString _target_name);
private:
    QString button_name;
    QString target_name;
};

#endif // BUTTONS_H
