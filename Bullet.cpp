#include "Bullet.h"
#include "Variables.h"
using namespace std;

Variables variables_b = Variables();



Bullet::Bullet(Towers *tower_) {
    tower = tower_;
    target = tower_->get_target();
    current_position_x = tower->get_location().x + (sign(target->get_location().x - tower->get_location().x) * variables_b.lengh_home/2);
    current_position_y = tower->get_location().y + (sign(target->get_location().y - tower->get_location().y) * variables_b.lengh_home/2);
    project_path = variables_b.PROJECT_PATH;
    reached =false;
}

void Bullet::draw(Window *window) {
    window->draw_img(
            image_path,
            Rectangle(current_position_x - 0.5*image_width, current_position_y -0.5*image_height, image_width, image_height));
}

int Bullet::sign(int x){
    if (x > 0) {return 1;}
    if (x < 0) {return -1;}
    return 0;
}

void Bullet::update_position(long time_steps) {
    current_position_x = current_position_x + (sign(target->get_location().x - current_position_x ) *speed_per_refresh);
    current_position_y = current_position_y  + (sign(target->get_location().y - current_position_y ) *speed_per_refresh);
    reached_target();
}

bool Bullet::reached_target() {
    if (target->get_location().x == current_position_x && target->get_location().y == current_position_y){
        reached = true;
        return true;
    }
    return false;
}

bool Bullet::get_reached(){ return reached;}
Towers* Bullet::get_tower(){ return tower;}
Enemy* Bullet::get_target(){ return target;}


