#ifndef BULLET_H
#define BULLET_H

#include "rsdl.h"
#include "Enemy.h"
#include "Towers.h"

class Bullet {
public:
    Bullet(Towers* tower_);

    virtual void draw(Window* window);
    void update_position(long time_steps);
    bool reached_target();
    bool get_reached();
    Towers *get_tower();
    Enemy *get_target();
    
protected:
    Enemy* target;
    Towers* tower;
    int current_position_x;
    int current_position_y;
    int speed_per_refresh;
    int image_width;
    int image_height;
    std::string project_path;
    std::string image_path;
    bool reached;
    int sign(int x);
};


#endif
