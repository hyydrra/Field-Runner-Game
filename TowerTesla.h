#ifndef TOWERTESLA_H
#define TOWERTESLA_H


#include "Towers.h"
class TowerTesla : public Towers{
public:
    TowerTesla(int position_x_, int position_y_);
    std::string render_tower_path(int x_tower, int y_tower, int x2_enemy, int y_enemy);
    void enter_damage(Enemy* target_, std::vector<Enemy*> live_enemies);
    bool upgrade();
};
#endif
