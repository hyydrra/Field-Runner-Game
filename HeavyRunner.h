#ifndef HEAVYRUNNER_H
#define HEAVYRUNNER_H


#include "Enemy.h"

class HeavyRunner: public Enemy{
public:
    HeavyRunner(int n_wave_, std::vector<Point> path_);
};


#endif