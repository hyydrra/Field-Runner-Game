#ifndef TOWERMISSLE_H
#define TOWERMISSLE_H

#include "Towers.h"

class TowerMissle: public Towers{
public:
    TowerMissle(int position_x_, int position_y_);
    std::string render_tower_path(int x_tower, int y_tower, int x_enemy, int y_enemy);
    void enter_damage(Enemy *target_, std::vector<Enemy *> live_enemies);
    bool upgrade();
};


#endif
