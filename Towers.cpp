#include "Towers.h"
#include "Enemy.h"
#include "Variables.h"

using namespace std;


Variables variables_t = Variables();

Towers::Towers(int position_x_, int position_y_) {
    position_x = position_x_;
    position_y = position_y_;
    maxlevel = 2;
}

void Towers::draw(Window *window) {
    int enemy_x, enemy_y;
    if (locked){
        enemy_x = locked_target->get_location().x;
        enemy_y = locked_target->get_location().y;
    }
    else{
        enemy_x = 0;
        enemy_y = 0;
    }
    window->draw_img(
            render_tower_path(position_x, position_y, enemy_x, enemy_y),
            Rectangle(position_x - 0.5*image_width, position_y -0.5*image_height, image_width, image_height),
            NULL_RECT,
            0,
            tower_flip(position_x, position_y, enemy_x, enemy_y));
}

float Towers::degree_between_two_point(int x1, int y1, int x2, int y2) {
    float teta = (atan2(y2-y1, x2-x1)*180/M_PI);
    if (teta>=0)
        return teta;
    else
        return 360.0 + teta;
}

bool Towers::tower_flip(int x_tower, int y_tower, int x_enemy, int y_enemy) {
    float teta = degree_between_two_point(x_tower, y_tower, x_enemy, y_enemy);
    if (teta > 90 && teta < 270) {return true;}
    else {return false;}
}

string Towers::fire_nofire_image(){
    if(locked){
        if ((last_shot_counter > ((1-fire_to_no_fire_ratio) * reload_time/variables_t.update_delay)) ||
            (last_shot_counter < (fire_to_no_fire_ratio * reload_time/variables_t.update_delay))){
            return "fire";
        }
//    if(last_shot_counter%3 == 0){
//        return "fire";
//    }
    }
    return "nofire";
}


Point Towers::get_location(){ return Point(position_x, position_y);}

float Towers::distance_between_two_point(Point p1, Point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void Towers::set_target(Enemy* target, float new_nearest_target_dist) {
    if (locked) {
        if ((distance_between_two_point(Point(position_x, position_y), locked_target->get_location()) > range) || locked_target->get_remaining_health() <=0 ) {
            locked = false;
        }
    }
    if (!locked) {
        if (new_nearest_target_dist < range) {
            locked_target = target;
            locked = true;
        }
    }
}

bool Towers::shot_target(int update_delay){
    last_shot_counter++;
    if (last_shot_counter-1 > int(reload_time/update_delay)){
        if(locked){
            last_shot_counter = 0;
            return true;
        }
    }
    return false;
}

Enemy* Towers::get_target() { return locked_target; }

string Towers::get_name() { return name; }

int Towers::get_upgrade_cost() { return upgrade_cost;}

int Towers::get_build_cost() { return build_cost;}