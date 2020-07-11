#include "BikeRunner.h"
#include "Variables.h"

using namespace std;


Variables variables_bike = Variables();

BikeRunner::BikeRunner(int n_wave_, std::vector<Point> path_):Enemy(n_wave_, path_) {
    speed = int(1000.0/(90*variables_bike.update_delay));
    initail_speed = int(1000.0/(90*variables_bike.update_delay));
    initial_healph = 100;
    killing_prize = 4;
    damge = 2;
    remaining_health = (0.9 + 0.1*n_wave_) * initial_healph;
    image_width = 61;
    image_height = 61;
    current_position_x = home_number_to_pixel(path[0]).x;
    current_position_y = home_number_to_pixel(path[0]).y;
    index_next_home =1;
    step_counter = 0;
    photos_path = "/assets/extra_selected/enemies/bike_runner/";
    number_of_images = 1;
    name = "BikeRunner";
}

