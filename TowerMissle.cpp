#include "TowerMissle.h"

#include <iostream>
#include <math.h>
#include "Variables.h"

using namespace std;


Variables variables_m = Variables();

TowerMissle::TowerMissle(int position_x_, int position_y_) : Towers(position_x_, position_y_) {
    level = 0;
    reload_time = 3000;
    build_cost = 70;
    upgrade_cost = 60;
    upgrade_damage_increase = 75;
    damage = 75 + level* upgrade_damage_increase;
    image_width = 90;
    image_height = 90;
    range =150;
    blast_radius = 50;
    last_shot_counter = 0;
    locked = false;
    fire_to_no_fire_ratio = 0.1;
    number_of_images_per_level["0"] = 7;
    number_of_images_per_level["1"] = 7;
    number_of_images_per_level["2"] = 7;
    name = "missile";

}

string TowerMissle::render_tower_path(int x_tower, int y_tower, int x_enemy, int y_enemy){
    string level_fire = to_string(level);
    float teta = degree_between_two_point(x_tower, y_tower, x_enemy, y_enemy);
    float temp = 180.0/number_of_images_per_level[level_fire];
    int image_number;

    if (teta < 270){
        image_number = floor(abs(90.0 - teta)/temp);
        return variables_m.PROJECT_PATH + "/assets/extra_selected/missile/level" + level_fire +"/"+ to_string(int(number_of_images_per_level[level_fire]-image_number-1)) + ".png";
    }
    else{
        image_number = floor(abs(180.0 - teta)/temp);
        return variables_m.PROJECT_PATH + "/assets/extra_selected/missile/level" + level_fire +"/"+ to_string(int(image_number-floor(number_of_images_per_level[level_fire]/2))) + ".png";
    }
}

void TowerMissle::enter_damage(Enemy *target_, std::vector<Enemy *> live_enemies) {

    Point target_position = target_->get_location();

    for (int i=0; i<live_enemies.size(); i++){
        if (distance_between_two_point(target_position,live_enemies[i]->get_location()) <= blast_radius){
            live_enemies[i]->update_health(damage);
        }
    }
    if (target_->get_remaining_health() <= 0) { locked = false; }
}


bool TowerMissle::upgrade() {
    if (level < maxlevel ){
        level++;
        damage = 75 + level* upgrade_damage_increase;
        return 1;
    }
    return 0;
}

