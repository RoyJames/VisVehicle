#ifndef TESTSUBCATEGORY_H
#define TESTSUBCATEGORY_H

#include <vector>
#include <QBoxLayout>
#include <QPushButton>

class TestSubcategory
{
public:
    TestSubcategory();
    void DisplayResult(QBoxLayout *display_window);

    QString ShortDescriptions;
    QString FullDescriptions;
    QString SubcategoryName;
    QString FunctionName;
    QString DatabasePath;
    std::vector<QString> ResGraphNames;
    std::vector<QString> ResTableNames;
    QPushButton *display_button;
};

#endif // TESTSUBCATEGORY_H
