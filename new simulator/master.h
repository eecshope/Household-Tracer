//
// Created by 王泽钧 on 12/21/2019.
//

#ifndef NEW_SIMULATOR_MASTER_H
#define NEW_SIMULATOR_MASTER_H

#include "turtle.h"
#include "human.h"

class master {
public:
    master(int tx0, int ty0, int hx0, int hy0);
    ~master();
    void step_forward();

private:
    int tx,  ty, hx, hy;
    int game_map[150][150];
    int current_time;
    turtle *follower;
    human *onwer;
};


#endif //NEW_SIMULATOR_MASTER_H
