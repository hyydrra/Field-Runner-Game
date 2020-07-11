#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include "rsdl.h"

class Enemy {
public:
    Enemy(int n_wave_, std::vector<Point> path_);
    void draw(Window* window);
    void update_position(long time_steps);
    void update_health(int damage);
    Point get_location();
    int get_remaining_health();
    void set_speed(float speed_percent);
    void set_go_effect_counter(int counter);
    std::string get_name();
    bool reached_end();
    int get_damage();
    int get_killing_prize();

protected:
    int current_position_x;
    int current_position_y;
    int pre_position_x;
    int pre_position_y;
    int speed;
    int initail_speed;
    int killing_prize;
    int damge;
    int goo_effect_counter;
    int initial_healph;
    int remaining_health;
    int n_wave;
    int image_width;
    int image_height;
    std::vector<Point> path;
    int step_counter;
    int index_next_home;
    int sign(int input);
    Point home_number_to_pixel(Point row_col);
    std::string photos_path;
    void runner_direction();
    std::string render_image();
    void reset_speed();
    int number_of_images;
    float running_effect_speed;
    std::string name;
    bool reached_path_end;
    std::string last_direction;
};



#endif
