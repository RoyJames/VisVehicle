#ifndef TESTCATEGORY_H
#define TESTCATEGORY_H

#include "testsubcategory.h"
#include <vector>
class TestCategory
{
public:
    TestCategory(QString name);
    std::vector<TestSubcategory*> subcats;
    QString getName();
private:
    QString CategoryName;
};

#endif // TESTCATEGORY_H
