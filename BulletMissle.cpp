#include "BulletMissle.h"


BulletMissle::BulletMissle(Towers *tower_) : Bullet(tower_) {
    image_width = 35;
    image_height = 35;
    speed_per_refresh = 1;
    image_path = project_path + "/assets/extra_selected/stuff/gat.jpg";
}

void BulletMissle::draw(Window *window) {
    window->fill_circle(Point(current_position_x,current_position_y),5,RED);
}



