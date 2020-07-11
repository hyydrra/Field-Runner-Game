#ifndef TOWERGOO_H
#define TOWERGOO_H


#include "Towers.h"
class TowerGoo: public Towers{
public:
    TowerGoo(int position_x_, int position_y_);
    std::string render_tower_path(int x_tower, int y_tower, int x2_enemy, int y_enemy);
    void enter_damage(Enemy* target_, std::vector<Enemy*> live_enemies);
    bool upgrade();

private:
    float spreed_redocuction;
    float upgrade_spreed_redocuction;
    int effect_lenght;
    int upgrade_effect_lenght;
};


#endif
