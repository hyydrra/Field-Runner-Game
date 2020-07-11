#include "Enemy.h"
#include "Variables.h"
using namespace std;


Variables variables_e = Variables();

Enemy::Enemy(int n_wave_, std::vector<Point> path_) {
    n_wave = n_wave_;
    path = path_;
    goo_effect_counter = 0;
    running_effect_speed = 0.5;
    reached_path_end = false;
}

void Enemy::draw(Window *window) {
    window->draw_img(
            render_image(),
            Rectangle(current_position_x - 0.5*image_width, current_position_y -0.5*image_height, image_width, image_height));
}

Point Enemy::home_number_to_pixel(Point row_col){
    int x = variables_e.top_left_home_center.x + (row_col.x * variables_e.lengh_home);
    int y = variables_e.top_left_home_center.y + (row_col.y * variables_e.lengh_home);
    return Point(x,y);
}

int Enemy::sign(int x){
    if (x > 0) {return 1;}
    if (x < 0) {return -1;}
    return 0;
}

void Enemy::update_position(long time_steps) {
    reset_speed();
    if (time_steps%speed == 0 && !reached_path_end){
        Point next_point = home_number_to_pixel(path[index_next_home]);
        step_counter++;
        pre_position_x = current_position_x + 0;
        pre_position_y = current_position_y + 0;

        if (path[index_next_home-1].y - path[index_next_home].y == 0 ){
            current_position_x = current_position_x + sign(path[index_next_home].x - path[index_next_home-1].x);
        }
        if (path[index_next_home-1].x - path[index_next_home].x == 0 ){
            current_position_y = current_position_y + sign(path[index_next_home].y - path[index_next_home-1].y);
        }
        int num_home_between_two_destination = abs(path[index_next_home].x - path[index_next_home-1].x) +
                abs(path[index_next_home].y - path[index_next_home-1].y);

        if (step_counter % (num_home_between_two_destination*variables_e.lengh_home) == 0) {
            step_counter = 0;
            index_next_home++;
        }
        if (index_next_home == path.size()){reached_path_end = true;}
    }
}

void Enemy::runner_direction(){
    if(!reached_path_end){
        if (path[index_next_home-1].y - path[index_next_home].y == 0 ) {
            if (path[index_next_home].x - path[index_next_home-1].x > 0) {last_direction = "right";}
            else {last_direction = "left";}
        }
        if (path[index_next_home-1].x - path[index_next_home].x == 0 ){
            if (path[index_next_home].y - path[index_next_home-1].y > 0) {last_direction =  "down";}
            else {last_direction =  "up";}
        }
    }
}

string Enemy::render_image(){
    int step = int(running_effect_speed*step_counter)%number_of_images;
    runner_direction();
    return variables_e.PROJECT_PATH + photos_path + last_direction + "/" + to_string(step) + ".png";
}

void Enemy::update_health(int damage){
    remaining_health = remaining_health - damage;
}

Point Enemy::get_location(){ return Point(current_position_x, current_position_y);}

int Enemy::get_remaining_health(){ return remaining_health;}

void Enemy::reset_speed(){
    goo_effect_counter--;
    if (goo_effect_counter <=0) {speed = 1 * initail_speed;}
}

void Enemy::set_speed(float speed_percent) {speed = int((1 + speed_percent) * initail_speed);}

void Enemy::set_go_effect_counter(int counter) {goo_effect_counter = counter;}

string Enemy::get_name(){ return name;}

bool Enemy::reached_end() { return reached_path_end;}

int Enemy::get_damage() { return damge; }

int Enemy::get_killing_prize() { return killing_prize; }
