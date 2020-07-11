#ifndef BULLETMISSLE_H
#define BULLETMISSLE_H

#include "Bullet.h"
class BulletMissle: public Bullet{
public:
    BulletMissle(Towers* tower_);
    void draw(Window *window);
};


#endif
