//
// Created by 王泽钧 on 12/21/2019.
//

#include "master.h"
#include "utils.h"

void master::rep_t() {
    follower->report();
}

master::master(int tx0, int ty0, int hx0, int hy0) {
    this->tx = tx0;
    this->ty = ty0;
    this->hx = hx0;
    this->hy = hy0;
    this->current_time = 0;
    init_map(this->game_map);
    game_map[tx][ty] = 2;
    game_map[hx][hy] = 3;
    if (tx == hx && ty == hy)
        game_map[tx][ty] = 4;
    follower = new turtle(tx0, ty0, game_map);
    onwer = new human(hx0, hy0);
    drawer = new plotter(
            _T("src\\shiCai\\img\\wall.gif"));

    initgraph(1000, 1000);
    drawer->plot_open_screen(
            _T("src\\background.gif"),
            _T("src\\title.png"),
            _T("src\\tip.png"));
    PlaySoundA(
            _T("src\\shiCai\\mysound\\start.wav"),
            NULL, SND_SYNC);

    _getch();

    drawer->draw_scene(game_map);
}

master::~master() {
    closegraph();
    delete follower;
    delete onwer;
    delete drawer;
}

void master::step_forward() {
    int tx0 = tx, ty0 = ty, hx0 = hx, hy0 = hy;
    drawer->delete_plot(tx, ty);
    drawer->delete_plot(hx, hy);
    current_time++;
    if (current_time % 2 == 0) {
        follower->get_next(tx, ty, game_map);
        onwer->get_next(hx, hy, game_map);
        game_map[tx0][ty0] = 0;
        game_map[hx0][hy0] = 0;
        if (tx == hx && ty == hy) {
            game_map[hx][hy] = 4;

        } else {
            game_map[hx][hy] = 3;
            game_map[tx][ty] = 2;
        }
    } else {
        onwer->get_next(hx, hy, game_map);
        game_map[tx0][ty0] = 0;
        game_map[hx0][hy0] = 0;
        if (tx == hx && ty == hy)
            game_map[hx][hy] = 4;
        else {
            game_map[hx][hy] = 3;
            game_map[tx][ty] = 2;
        }
    }
    drawer->print_man(hx, hy);
    drawer->print_turtle(tx, ty);
    if (hx == tx && hy == ty)
        PlaySoundA(
                _T("src\\shiCai\\mysound\\fire.wav"),
                NULL, SND_SYNC);
    // For debugging
}

void master::get_h_pos(int &x, int &y) {
    x = hx;
    y = hy;
}

void master::get_t_pos(int &x, int &y) {
    x = tx;
    y = ty;
}

void *master::get_map() {
    return game_map;
}