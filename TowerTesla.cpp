#include "TowerTesla.h"
#include <iostream>
#include <math.h>
#include "Variables.h"

using namespace std;


Variables variables_tes = Variables();

TowerTesla::TowerTesla(int position_x_, int position_y_) : Towers(position_x_, position_y_) {
    level = 0;
    reload_time = 1500;
    build_cost = 120;
    upgrade_cost = 100;
    upgrade_damage_increase = 1000;
    damage = 700 + level* upgrade_damage_increase;
    image_width = 40;
    image_height = 90;
    range =150;
    last_shot_counter = 0;
    locked = false;
    fire_to_no_fire_ratio = 0.1;
    name = "tesla";

}

string TowerTesla::render_tower_path(int x_tower, int y_tower, int x_enemy, int y_enemy){
    string level_fire = to_string(level) +"_"+ fire_nofire_image();
    return variables_tes.PROJECT_PATH + "/assets/extra_selected/tesla/level" + level_fire +"/"+ to_string(0) + ".png";
}

void TowerTesla::enter_damage(Enemy *target_, std::vector<Enemy *> live_enemies) {
    target_->update_health(damage);
    if (target_->get_remaining_health() <= 0){locked = false;}
}

bool TowerTesla::upgrade() {
    if (level < maxlevel ){
        level++;
        damage = 700 + level* upgrade_damage_increase;
        return 1;
    }
    return 0;
}
