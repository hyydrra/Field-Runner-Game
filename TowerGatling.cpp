#include "TowerGatling.h"
#include <iostream>
#include <math.h>
#include "Variables.h"

using namespace std;


Variables variables_g = Variables();

TowerGatling::TowerGatling(int position_x_, int position_y_) : Towers(position_x_, position_y_) {
    level = 0;
    reload_time = 1000;
    build_cost = 55;
    upgrade_cost = 40;
    upgrade_damage_increase = 35;
    damage = 35 + level* upgrade_damage_increase;
    image_width = 90;
    image_height = 90;
    range =150;
    last_shot_counter = 0;
    locked = false;
    fire_to_no_fire_ratio = 0.1;
    number_of_images_per_level["0_nofire"] = 19;
    number_of_images_per_level["1_nofire"] = 7;
    number_of_images_per_level["2_nofire"] = 7;
    number_of_images_per_level["0_fire"] = 7;
    number_of_images_per_level["1_fire"] = 7;
    number_of_images_per_level["2_fire"] = 7;
    name = "gatling";
}

string TowerGatling::render_tower_path(int x_tower, int y_tower, int x_enemy, int y_enemy){
    string level_fire = to_string(level) +"_"+ fire_nofire_image();
    float teta = degree_between_two_point(x_tower, y_tower, x_enemy, y_enemy);
    float temp = 180.0/number_of_images_per_level[level_fire];
    int image_number;

    if (teta < 270){
        image_number = floor(abs(90.0 - teta)/temp);
        return variables_g.PROJECT_PATH + "/assets/extra_selected/gattling/level" + level_fire +"/"+ to_string(int(number_of_images_per_level[level_fire]-image_number-1)) + ".png";
    }
    else{
        image_number = floor(abs(180.0 - teta)/temp);
        return variables_g.PROJECT_PATH + "/assets/extra_selected/gattling/level" + level_fire +"/"+ to_string(int(image_number-floor(number_of_images_per_level[level_fire]/2))) + ".png";
    }
}

void TowerGatling::enter_damage(Enemy *target_, std::vector<Enemy *> live_enemies) {
    target_->update_health(damage);
    if (target_->get_remaining_health() <= 0){locked = false;}
}

bool TowerGatling::upgrade() {
    if (level < maxlevel ){
        level++;
        damage = 35 + level* upgrade_damage_increase;
        return 1;
    }
    return 0;
}