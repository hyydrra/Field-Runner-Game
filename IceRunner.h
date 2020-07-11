#ifndef ICERUNNER_H
#define ICERUNNER_H


#include "Enemy.h"

class IceRunner: public Enemy{
public:
    IceRunner(int n_wave_, std::vector<Point> path_);
};


#endif
