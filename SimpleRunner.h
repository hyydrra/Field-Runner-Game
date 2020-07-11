#ifndef SIMPLERUNNER_H
#define SIMPLERUNNER_H

#include "Enemy.h"


class SimpleRunner: public Enemy{
public:
    SimpleRunner(int n_wave_, std::vector<Point> path_);
};


#endif
