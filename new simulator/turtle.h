//
// Created by 王泽钧 on 12/21/2019.
// Modified by Doggy on 12/24
//

#ifndef NEW_SIMULATOR_TURTLE_H
#define NEW_SIMULATOR_TURTLE_H
#include <cstring>
#include <iostream>
//TODO:Implement this class. Free to add more variables and methods
inline int sgn(int n);
inline int abs(int n);
inline int max(int n1, int n2);
inline int max(int n1, int n2, int n3);
inline int min(int n1, int n2);
inline int min(int n1, int n2, int n3);
int judge_room(int, int);

class turtle
{
public:
    turtle(int x0, int y0, const int game_map[][150]);
    ~turtle();
    bool get_next(int &new_x, int &new_y, const int game_map[][150]);
private:
    int x, y;
    const int r = 5;
    int frequency[8][8][8];
    int freq_history[3];
    void init_freq();
    void learn(int room_no);
    int latest_sight[2];
    static const int door[8][2];
    static int dist_d2xy[8][150][150];
    static bool room_door[8][8];
    static int dist_d2d[8][8];
    static int dist_r2r[8][8];
    static int door_r2r[8][8];
    static int dist_inr[8][8][8];
    static int node_length[8][8][8];
    const void* get_sequence(int i, int da, int db);
    void pre_search(const int game_map[][150]);
    struct record
    {
        bool motive; // 0 = stat, 1 = move
        bool insight;
        int hx, hy;
        record(record* cmp, int _hx, int _hy, turtle* _t):hx(_hx),hy(_hy)
        {
            hx == -1 ? insight = false : insight = true;
            if (cmp)
            {
                motive = (!insight) || (hx != cmp->hx) || (hy != cmp->hy);
                if (motive < cmp->motive)
                    _t -> learn(judge_room(hx, hy));
            }
            else motive = 0;
        }
    }*last, *now;
    bool scan(int x0, int y0, int r0, int& x, int& y, const int game_map[][150]);
    void cheak_wall(int x0, int y0, int& x, int& y, const int game_map[][150]);

 // manipulate route
    const int route111[14][2] = {{37,9},{34,6},{6,6},{54,6},{17,54}, {17,17},{28,17},{28,54},{54,54},{54,26},
                        {43,26},{43,43},{39,43},{38,17}};
    const int route133[11][2] = {{17,32},{17,43},{54,43},{54,54},{6,54}, {6,6},{34,6},{34,17},{17,17},{17,22}, {54,26}};
    const int route113[18][2] = {{37,9},{34,6},{6,6},{6,54},{17,54}, {17,17},{34,17},{34,22},{28,28},{28,54}, 
                        {54,54},{54,43},{39,43},{39,38},{45,32}, {45,26},{54,26},{54,32}};
    const int route222[7][2] = {{34,66},{6,66},{6,94},{34,94},{34,83},{17,83},{17,77}};
    const int route311[4][2] = {{46,14}, {54,14}, {54,6}, {46,6}};
    const int route422[23][2] ={{46,71},{46,66},{55,66},{57,83},{61,83}, {66,71},{66,26},{94,26},{94,37},{77,37}, 
                        {77,48},{94,48},{94,59},{77,59},{77,70}, {94,70},{94,94},{83,94},{83,81},{72,81}, 
                        {72,94},{46,94},{46,82}};
    const int route433[21][2] = {{66,26},{94,26},{94,37},{77,37},{77,48}, {94,48},{94,59},{77,59},{72,83},{83,83},
                        {83,70},{94,70},{94,94},{46,94},{46,83}, {61,83},{61,72},{46,72},{46,66},{58,66}, {66,37}};
    const int route423[25][2] = {{46,83},{46,94},{94,94},{83,94},{57,83}, {46,72},{46,66},{57,66},{63,72},{94,72},
                        {94,61},{72,61},{66,55},{66,42},{71,37}, {77,37},{77,45},{82,50},{94,50},{94,39},
                        {92,39},{88,35},{94,29},{94,26},{66,26}};
    const int route455[22][2] ={{66,94},{46,94},{46,83},{61,83},{61,72}, {46,72},{46,66},{58,66},{66,26},{94,26}, 
                        {94,37},{77,37},{77,48},{94,48},{94,59}, {77,59},{72,83},{83,83},{83,70},{94,70}, {94,94},{77,94}};
    const int route425[22][2] ={{46,83},{46,94},{61,94},{61,83},{57,83}, {46,66},{57,66},{65,72},{66,26},{94,26},
                        {94,37},{77,37},{77,48},{94,48},{94,59}, {77,59},{77,70},{94,70},{94,94},{83,94}, {83,81},{72,81}};
    const int route435[26][2] = {{66,26},{94,26},{94,37},{76,37},{71,42}, {66,42},{66,53},{81,53},{86,48},{94,48},
                        {94,94},{83,94},{83,62},{74,62},{72,64}, {66,64},{64,66},{46,66},{46,94},{61,94},
                        {61,88},{57,84},{57,77},{63,77},{65,75}, {72,75}};
    const int route544[4][2] = {{62,104}, {94,106}, {94,114}, {46,114}};
    const int route555[6][2] = {{75,103}, {94,106}, {94,114}, {46,114}, {58,114}, {66,106}};
    const int route545[8][2] = {{62,104}, {64,106}, {64,108}, {58,114}, {46,114}, {94,114}, {94,106}, {75,103}};
    const int route644[1][2] = {{46,104}};

    struct search_plan
    {
        int w[8], min_cost = 0x7fff;
        int door_order[8][2];
        int room_order[8];
        int room_searched;
        bool room_searching;
        int (*node_sequence)[2];
        int node_order;
        int node_max;
        int node_direction; // 1 or -1
        void solve(int i, int t, int c, int di[8][2], int ri[8], int flag)
        {
            if (i > 6)
            {
                di[6][1] = di[6][0];
                c += (t*2 + dist_inr[ri[6]][di[6][0]][di[6][1]]) * w[ri[6]];
                if (c < min_cost)
                {
                    memcpy(door_order, di, sizeof(door_order));
                    memcpy(room_order, ri, sizeof(room_order));
                    min_cost = c;
                }
                return;
            }
            for (int j = 1; j <= 6; j++)
            {
                if (flag & (1<<j)) continue;
                ri[i] = j;
                di[i-1][1] = door_r2r[ri[i-1]][ri[i]];
                di[i][0] = door_r2r[ri[i]][ri[i-1]];
                solve(i+1, t + dist_inr[ri[i-1]][di[i-1][0]][di[i-1][1]] +
                    dist_d2d[di[i-1][1]][di[i][0]],
                    c+w[ri[i-1]]*(t*2+dist_inr[ri[i-1]][di[i-1][0]][di[i-1][1]]),
                    di, ri, flag | (1 << j));
            }
        }

        search_plan(turtle* _t)
        {
            memcpy(w, _t->frequency[_t->freq_history[1]][_t->freq_history[2]], sizeof(w));
            int time_door[8];
            for (int i = 1; i <= 5; i++)
                time_door[i] = dist_d2xy[i][_t->x][_t->y];
            for (int i = 1; i <= 6; i++)
            {
                int room_temp[8], door_temp[8][2], t;
                memset(room_temp, 0, sizeof(room_temp));
                memset(door_temp, 0, sizeof(door_temp));
                for (int j = 1; j <= 5; j++)
                {
                    if (!room_door[i][j]) continue;
                    if (!door_temp[1][0] || t > time_door[j])
                    {
                        door_temp[1][0] = j;
                        t = time_door[j];
                    }
                }
                solve(2, t, 0, door_temp, room_temp, 1<<i);
            }
            room_searched = 0;
            room_searching = false;
        }
        bool move(turtle* _t)
        {
            int x0 = _t->x, y0 = _t->y;
            if (room_searched > 6)
            {
                std::cerr << "Error: Search Complete. Human NOT Found.\n";
                return false;
            }
            else
            {
                if (room_searching)
                {
                    int tx = node_sequence[node_order][0];
                    int ty = node_sequence[node_order][1];
                    if (x0 == tx && y0 == ty)
                    {
                        node_order += node_direction;
                        if (node_order < 0 || node_order > node_max)
                        {
                            room_searching = false;
                            room_searched ++;
                            return move(_t);
                        }
                        else
                        {
                            _t->x += sgn(tx - x0);
                            _t->y += sgn(ty - y0);
                            return true;
                        }
                    }
                    else
                    {
                        _t->x += sgn(tx - x0);
                        _t->y += sgn(ty - y0);
                        return true;
                    }
                }
                else
                {
                    const int* target = door[door_order[room_searched][0]];
                    if (x0 == target[0] && y0 == target[1])
                    { // searching
                        room_searching = true;
                        int r = room_order[room_searched];
                        int*d = door_order[room_searched];
                        node_sequence = (int(*)[2])(_t->get_sequence(r, d[0], d[1]));
                        node_max = node_length[r][d[0]][d[1]];
                        if (d[0] <= d[1])
                        {
                            node_direction = 1;
                            node_order = 0;
                        }
                        else
                        {
                            node_direction = -1;
                            node_order = node_max - 1;
                        }
                        return move(_t);
                    }
                    else
                    { // moving towards next door
                        int dx, dy, (*map)[150] = dist_d2xy[door_order[room_searched][0]];
                        dx = sgn(target[0] - x0);
                        dy = sgn(target[1] - y0);
                        for (int k = 0; k < 4; k++)
                        {
                            for (int i = max(0,k-2); i <= min(2,k); i++)
                            {
                                int j = k - i;
                                int x1, y1;
                                if (abs(dx+i) <= 1)
                                {
                                    if (abs(dy+j) <= 1)
                                    {
                                        x1 = x0+dx+i; y1 = y0+dy+j;
                                        if (map[x1][y1] < map[x0][y0])
                                        {_t->x = x1; _t->y = y1; return true;}
                                    }
                                    if (abs(dy-j) <= 1)
                                    {
                                        x1 = x0+dx+i; y1 = y0+dy-j;
                                        if (map[x1][y1] < map[x0][y0])
                                        {_t->x = x1; _t->y = y1; return true;}
                                    }
                                }
                                if (abs(dx-i) <= 1)
                                {
                                    if (abs(dy+j) <= 1)
                                    {
                                        x1 = x0+dx-i; y1 = y0+dy+j;
                                        if (map[x1][y1] < map[x0][y0])
                                        {_t->x = x1; _t->y = y1; return true;}
                                    }
                                    if (abs(dy-j) <= 1)
                                    {
                                        x1 = x0+dx-i; y1 = y0+dy-j;
                                        if (map[x1][y1] < map[x0][y0])
                                        {_t->x = x1; _t->y = y1; return true;}
                                    }
                                }
                            }
                        }
                        std::cerr << "Error: Stuck in Walls. Cheak Your Input or Array dist_d2xy.\n";
                        return false;
                    }
                }
            }
        }

        ~search_plan()
        {
            ;
        }
    }*plan;
};

const int turtle::door[8][2] = {{0,0}, 
    {40,9}, {40,77}, {60,32}, {60,104}, {72,100}, {0,0}, {0,0}};


#endif //NEW_SIMULATOR_TURTLE_H
