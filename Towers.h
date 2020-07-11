#ifndef TOWERS_H
#define TOWERS_H

#include <string>
#include <vector>
#include "rsdl.h"
#include "Enemy.h"





class Towers{

public:
    Towers(int position_x_, int position_y_);
    void draw(Window* window);
    Point get_location();
    void set_target(Enemy *target, float new_nearest_target_dist);
    bool shot_target(int update_delay);
    virtual void enter_damage(Enemy* target_, std::vector<Enemy*> live_enemies) = 0;
    virtual bool upgrade() = 0;
    Enemy* get_target();
    std::string get_name();
    int get_upgrade_cost();
    int get_build_cost();

protected:
    int position_x;
    int position_y;
    int level;
    int maxlevel;
    int build_cost;
    int upgrade_cost;
    int upgrade_damage_increase;
    float fire_to_no_fire_ratio;
    int damage;
    int reload_time;
    int last_shot_counter;
    Enemy *locked_target;
    bool locked;
    int blast_radius;
    int range;
    int image_width;
    int image_height;
    std::string name;
    struct flip_and_image_path{bool filp; std::string path;};
    std::map <std::string, int> number_of_images_per_level;
    virtual std::string render_tower_path(int x_tower, int y_tower, int x2_enemy, int y_enemy) = 0;
    bool tower_flip(int x_tower, int y_tower, int x_enemy, int y_enemy);
    float degree_between_two_point(int x1, int y1, int x2, int y2);
    float distance_between_two_point(Point p1, Point p2);
    std::string fire_nofire_image();
};




#endif
