#include "IceRunner.h"
#include "Variables.h"

using namespace std;


Variables variables_ice = Variables();

IceRunner::IceRunner(int n_wave_, std::vector<Point> path_):Enemy(n_wave_, path_) {
    speed = int(1000.0/(30*variables_ice.update_delay));
    initail_speed = int(1000.0/(30*variables_ice.update_delay));
    initial_healph = 400;
    killing_prize = 10;
    damge = 4;
    remaining_health = (0.9 + 0.1*n_wave_) * initial_healph;
    image_width = 41;
    image_height = 61;
    current_position_x = home_number_to_pixel(path[0]).x;
    current_position_y = home_number_to_pixel(path[0]).y;
    index_next_home =1;
    step_counter = 0;
    photos_path = "/assets/extra_selected/enemies/ice_runner/";
    number_of_images = 6;
    name = "IceRunner";
}


