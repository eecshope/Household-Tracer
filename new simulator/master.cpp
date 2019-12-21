//
// Created by 王泽钧 on 12/21/2019.
//

#include "master.h"
#include "utils.h"
#include "turtle.h"
#include "human.h"

master::master(int tx0, int ty0, int hx0, int hy0) {
    this->tx = tx0;
    this->ty = ty0;
    this->hx = hx0;
    this->hy = hy0;
    this->current_time = 0;
    init_map(this->game_map);
    game_map[tx][ty] = 2;
    game_map[hx][hy] = 3;
    follower = new turtle(tx0, ty0);
    onwer = new human(hx0, hy0);
}

master::~master() {
    delete follower;
    delete onwer;
}

void master::step_forward() {
    int tx0 = tx, ty0 = ty, hx0 = hx, hy0 = hy;
    current_time++;
    if(current_time%2==0){
        follower->get_next(&tx, &ty, game_map);
        onwer->get_next(&hx, &hy, game_map);
        game_map[tx0][ty0] = 0;
        game_map[hx0][hy0] = 0;
        if(tx==ty&&hx==hy)
            game_map[hx][hy] = 4;
        else{
            game_map[hx][hy] = 3;
            game_map[tx][ty] = 2;
        }
    }else{
        onwer->get_next(&hx, &hy, game_map);
        game_map[tx0][ty0] = 0;
        game_map[hx0][hy0] = 0;
        if(tx==ty&&hx==hy)
            game_map[hx][hy] = 4;
        else{
            game_map[hx][hy] = 3;
            game_map[tx][ty] = 2;
        }
    }
    return;
}