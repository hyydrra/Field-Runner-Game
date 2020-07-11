#include "BulletGoo.h"

BulletGoo::BulletGoo(Towers *tower_) : Bullet(tower_) {
    image_width = 20;
    image_height = 20;
    speed_per_refresh = 1;
    image_path = project_path + "/assets/extra_selected/stuff/goobullet.png";
}
