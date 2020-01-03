//
// Created by 王泽钧 on 12/21/2019.
// Modified by Doggy on 12/24
//

#ifndef NEW_SIMULATOR_TURTLE_H
#define NEW_SIMULATOR_TURTLE_H
#include <cstring>
#include <iostream>
//TODO:Implement this class. Free to add more variables and methods
int sgn(int n);
int abs(int n);
int max(int n1, int n2);
int max(int n1, int n2, int n3);
int min(int n1, int n2);
int min(int n1, int n2, int n3);
int judge_room(int, int);

class turtle;

class record
{
public:
    bool motive; // 0 = stat, 1 = move
    bool insight;
    int hx, hy;
    record(record* cmp, int _hx, int _hy, turtle* _t);
};

class search_plan
{
public:
    int w[8], min_cost = 0x7fff;
    int door_order[8][2];
    int room_order[8];
    int room_searched;
    bool room_searching;
    int (*node_sequence)[2];
    int node_order;
    int node_max;
    int node_direction; // 1 or -1
    search_plan(turtle* _t);

    bool move(turtle* _t);
    void solve(int i, int t, int c, int di[8][2], int ri[8], int flag, turtle* _t);


};

class turtle
{
public:
    turtle(int x0, int y0, const int game_map[][150]);
    ~turtle();
    bool get_next(int &new_x, int &new_y, const int game_map[][150]);
    int x, y;
    const int r = 5;
    int frequency[8][8][8];
    int freq_history[3];
    void init_freq();
    void learn(int room_no);
    //int latest_sight[2];
    int door[8][2];
    int dist_d2xy[8][150][150];
    bool avail[150][150];
    bool room_door[8][8];
    int dist_d2d[8][8];
    int dist_r2r[8][8];
    int door_r2r[8][8];
    int dist_inr[8][8][8];
    int node_length[8][8][8];
    record *last, *now;
    search_plan *plan;
    const void* get_sequence(int i, int da, int db);
    void pre_search(const int game_map[][150]);

    bool flag_scan, flag_cheak_wall;
    bool scan(int x0, int y0, int r0, int& x, int& y, const int game_map[][150]);
    bool cheak_wall(int x0, int y0, int& x, int& y, const int game_map[][150]);

    // manipulate route
    const int route111[14][2] = {{37,9},{34,6},{6,6},{6,54},{17,54}, {17,17},{28,17},{28,54},{54,54},{54,26},
                                 {43,26},{43,43},{39,43},{38,17}};
    const int route133[11][2] = {{17,32},{17,43},{54,43},{54,54},{6,54}, {6,6},{34,6},{34,17},{17,17},{17,22}, {54,26}};
    const int route113[18][2] = {{37,9},{34,6},{6,6},{6,54},{17,54}, {17,17},{34,17},{34,22},{28,28},{28,54},
                                 {54,54},{54,43},{39,43},{39,38},{45,32}, {45,26},{54,26},{54,32}};
    const int route222[8][2] = {{34,66},{6,66},{6,94},{34,94},{34,83},{17,83},{17,77},{34,77}};
    const int route311[4][2] = {{46,14}, {54,14}, {54,6}, {46,6}};
    const int route422[23][2] ={{46,71},{46,66},{55,66},{57,83},{61,83}, {66,71},{66,26},{94,26},{94,37},{77,37},
                                {77,48},{94,48},{94,59},{77,59},{77,70}, {94,70},{94,94},{83,94},{83,81},{72,81},
                                {72,94},{46,94},{46,82}};
    const int route433[21][2] = {{66,26},{94,26},{94,37},{77,37},{77,48}, {94,48},{94,59},{77,59},{72,83},{83,83},
                                 {83,70},{94,70},{94,94},{46,94},{46,83}, {61,83},{61,72},{46,72},{46,66},{58,66}, {66,37}};
    const int route423[25][2] = {{46,83},{46,94},{94,94},{94,83},{57,83}, {46,72},{46,66},{57,66},{63,72},{94,72},
                                 {94,61},{72,61},{66,55},{66,42},{71,37}, {77,37},{77,45},{82,50},{94,50},{94,39},
                                 {92,39},{88,35},{94,29},{94,26},{66,26}};
    const int route455[22][2] ={{66,94},{46,94},{46,83},{61,83},{61,72}, {46,72},{46,66},{58,66},{66,26},{94,26},
                                {94,37},{77,37},{77,48},{94,48},{94,59}, {77,59},{72,83},{83,83},{83,70},{94,70}, {94,94},{77,94}};
    const int route425[22][2] ={{46,83},{46,94},{61,94},{61,83},{57,83}, {46,66},{57,66},{65,72},{66,26},{94,26},
                                {94,37},{77,37},{77,48},{94,48},{94,59}, {77,59},{77,70},{94,70},{94,94},{83,94}, {83,81},{72,81}};
    const int route435[27][2] = { {66,26},{94,26},{94,37},{76,37},{71,42}, {66,42},{66,53},{81,53},{86,48},{94,48},
                                 {94,94},{83,94},{83,62},{74,62},{72,64}, {66,64},{64,66},{46,66},{46,94},{61,94},
                                 {61,88},{57,84},{57,77},{63,77},{65,75}, {72,75},{72,94}};
    const int route544[4][2] = {{62,104}, {94,106}, {94,114}, {46,114}};
    const int route555[6][2] = {{75,103}, {94,106}, {94,114}, {46,114}, {58,114}, {66,106}};
    const int route545[8][2] = {{62,104}, {64,106}, {64,108}, {58,114}, {46,114}, {94,114}, {94,106}, {75,103}};
    const int route644[1][2] = {{46,104}};

    void report();
};


#endif //NEW_SIMULATOR_TURTLE_H
