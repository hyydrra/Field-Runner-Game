#include "TowerGoo.h"

#include <iostream>
#include <math.h>
#include "Variables.h"

using namespace std;


Variables variables_go = Variables();

TowerGoo::TowerGoo(int position_x_, int position_y_) : Towers(position_x_, position_y_) {
    level = 0;
    reload_time = 2000;
    build_cost = 60;
    upgrade_cost = 45;
    upgrade_effect_lenght = 500;
    upgrade_spreed_redocuction = 0.1;
    spreed_redocuction = 0.4 + upgrade_spreed_redocuction * level;
    effect_lenght = 2500 + upgrade_effect_lenght *level;

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
    name ="goo";
}




string TowerGoo::render_tower_path(int x_tower, int y_tower, int x_enemy, int y_enemy){
    string level_fire = to_string(level);
    float teta = degree_between_two_point(x_tower, y_tower, x_enemy, y_enemy);
    float temp = 180.0/number_of_images_per_level[level_fire];
    int image_number;

    if (teta < 270){
        image_number = floor(abs(90.0 - teta)/temp);
        return variables_go.PROJECT_PATH + "/assets/extra_selected/goo/level" + level_fire +"/"+ to_string(int(number_of_images_per_level[level_fire]-image_number-1)) + ".png";
    }
    else{
        image_number = floor(abs(180.0 - teta)/temp);
        return variables_go.PROJECT_PATH + "/assets/extra_selected/goo/level" + level_fire +"/"+ to_string(int(image_number-floor(number_of_images_per_level[level_fire]/2))) + ".png";
    }
}

void TowerGoo::enter_damage(Enemy *target_, std::vector<Enemy *> live_enemies) {

    Point target_position = target_->get_location();

    for (int i=0; i<live_enemies.size(); i++){
        if (distance_between_two_point(target_position,live_enemies[i]->get_location()) <= blast_radius){
            if( live_enemies[i]->get_name() != "IceRunner"){
                live_enemies[i]->set_speed(spreed_redocuction);
                live_enemies[i]->set_go_effect_counter(int(effect_lenght/variables_go.update_delay));
            }
        }
    }
    if (target_->get_remaining_health() <= 0) { locked = false; }
}


bool TowerGoo::upgrade(){
    if (level < maxlevel){
        level++;
        spreed_redocuction = 0.4 + upgrade_spreed_redocuction * level;
        effect_lenght = 2500 + upgrade_effect_lenght *level;
        return 1;
    }
    return 0;
}