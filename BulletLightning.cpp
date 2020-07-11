#include "BulletLightning.h"

BulletLightning::BulletLightning(Towers *tower_) : Bullet(tower_) {
    image_width = 40;
    image_height = 40;
    speed_per_refresh = 1;
    image_path = project_path + "/assets/extra_selected/stuff/lightning.png";
}
