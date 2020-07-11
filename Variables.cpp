#include "Variables.h"
using namespace std;

Variables::Variables(){
    SCALE = 1;
    WIDTH = 1365 * SCALE;
    HEIGHT = 1024 * SCALE;
    top_left_home_center = Point(150*SCALE,203*SCALE);
    lengh_home = 60*SCALE;
    update_delay = 2.5;
    num_column = 19;
    num_rows =11;
    PROJECT_PATH = "/home/amirhosein/visual stadio code/ap/project5";
}