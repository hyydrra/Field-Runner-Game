#ifndef VARIABLES_H
#define VARIABLES_H
#include "rsdl.h"

class Variables {

public:
    Variables();
    float SCALE;
    int WIDTH;
    int HEIGHT;
    Point top_left_home_center;
    int lengh_home;
    float update_delay;
    int num_column;
    int num_rows;
    std::string PROJECT_PATH;
    std::string BACKGROUND_PATH;
};


#endif
