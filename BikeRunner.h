#ifndef BIKERUNNER_H
#define BIKERUNNER_H


#include "Enemy.h"

class BikeRunner: public Enemy{
public:
    BikeRunner(int n_wave_, std::vector<Point> path_);
};

#endif
