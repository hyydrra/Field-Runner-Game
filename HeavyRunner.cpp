#include "HeavyRunner.h"
#include "Variables.h"

using namespace std;


Variables variables_heavy = Variables();

HeavyRunner::HeavyRunner(int n_wave_, std::vector<Point> path_):Enemy(n_wave_, path_) {
    speed = int(1000.0/(25*variables_heavy.update_delay));
    initail_speed = int(1000.0/(25*variables_heavy.update_delay));
    initial_healph = 500;
    killing_prize = 18;
    damge = 4;
    remaining_health = (0.9 + 0.1*n_wave_) * initial_healph;
    image_width = 55;
    image_height = 61;
    current_position_x = home_number_to_pixel(path[0]).x;
    current_position_y = home_number_to_pixel(path[0]).y;
    index_next_home =1;
    step_counter = 0;
    photos_path = "/assets/extra_selected/enemies/heavy_runner/";
    number_of_images = 6;
    name = "HeavyRunner";
}

