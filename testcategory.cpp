#include "testcategory.h"

TestCategory::TestCategory(QString name) : CategoryName(name)
{

}


QString TestCategory::getName()
{
    return CategoryName;
}
