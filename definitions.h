#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define GENERAL_DATA    1
#define WHEEL_DATA  2
#define LIST_DATA   4

#define DEFAULT_VEHICLE_DATABASE  "D:/codes/qt/VisVehicle/defaultvehicles.db"
#define READ_BUTTON_LIST_PATH ":/new/lists/load_buttons_list"
#define READ_TEST_CATEGORY_LIST_PATH ":/new/lists/test_category_list"

enum DATATABLETYPE{
    GENERAL_TYPE = 1,
    WHEEL_TYPE = 2,
    LIST_TYPE = 4
};

// TOP is the left top corner, BOTTOM is the right bottom corner of the rectangle
#define COORD_BOTTOM_X 0.95
#define COORD_BOTTOM_Y 0.9
#define COORD_TOP_X 0.2
#define COORD_TOP_Y 0.1
#define COORD_TICK_SPACE 4

#endif // DEFINITIONS_H
