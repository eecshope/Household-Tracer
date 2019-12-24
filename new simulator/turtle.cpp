//
// Created by 王泽钧 on 12/21/2019.
// Modified by Doggy on 12/24
//

#include "turtle.h"

inline int sgn(int n){
    if (n > 0) return 1;
    if (n < 0) return -1;
    return 0;
}
inline int abs(int n){
    if (n < 0) return -n;
    return n;
}
inline int min(int n1, int n2){
    return (n1 < n2 ? n1 : n2);
}
inline int min(int n1, int n2, int n3){
    if (n1 < n2)
        return n1 < n3 ? n1 : n3;
    else
        return n2 < n3 ? n2 : n3;
}
inline int max(int n1, int n2){
    return (n1 > n2 ? n1 : n2);
}
inline int max(int n1, int n2, int n3){
    if (n1 > n2)
        return n1 > n3 ? n1 : n3;
    else
        return n2 > n3 ? n2 : n3;
}

inline int dist_xy2xy(int x1, int y1, int x2, int y2)
{
    return max(abs(x1-x2), abs(y1-y2));
}

void turtle::init_freq()
{
    int init_value = 5;
    for (int i = 1; i < 7; i++)
    for (int j = 1; j < 7; j++)
    for (int k = 1; k < 7; k++)
        frequency[i][j][k] = init_value;
    for (int j = 1; j < 7; j++)
    for (int k = 1; k < 7; k++)
        frequency[0][j][k] = init_value*6;
    for (int k = 1; k < 7; k++)
        frequency[0][0][k] = init_value*36;
    frequency[0][0][0] = init_value*216;
    for (int i = 0; i < 3; i++)
        freq_history[i] = 0;
}

const void* turtle::get_sequence(int i, int da, int db)
{
    switch (i)
    {
        case 1:
        {
            switch (da | db)
            {
                case 1: return route111;// break;
                case 8: return route133;// break;
                case 9: return route113;// break;
            }
            break;
        }
        case 2:
        {
            return route222;// break;
        }
        case 3:
        {
            return route311;// break;
        }
        case 4:
        {
            switch (da | db)
            {
                case 4: return route422;// break;
                case 8: return route433;// break;
                case 12: return route423;// break;
                case 32: return route455;// break;
                case 36: return route425;// break;
                case 40: return route435;// break;
            }
            break;
        }
        case 5:
        {
            switch (da | db)
            {
                case 16: return route544;// break;
                case 32: return route555;// break;
                case 48: return route545;// break;
            }
            break;
        }
        case 6:
        {
            return route644;// break;
        }
    }
    return NULL;
}

// fill distance_door[8][150][150]
void turtle::pre_search(const int game_map[][150])
{
    {// door to everywhere
        int stack0[256][2]; int n0;
        int stack1[256][2]; int n1;
        bool visit[150][150];
        bool avail[150][150];
        memset(avail, -1, sizeof(avail));
        for (int i = 0; i < 150; i++)
        {
            avail[i][0] = avail[0][i] = false;
            avail[i][1] = avail[1][i] = false;
        }
        for (int i = 1; i < 150; i++)
        for (int j = 1; j < 150; j++)
        {
            if (game_map[i][j] == 1)
            {
                avail[i+1][j] = avail[i-1][j] = avail[i][j] = 
                avail[i][j+1] = avail[i][j-1] = false;
            }
        }
        for (int i = 1; i <= 5; i++)
        { // bfs
            memset(visit, 0, sizeof(visit));
            n1 = 1; memcpy(stack1[0], door[i], sizeof(door[i]));
            visit[door[i][0]][door[i][1]] = true;
            int step = 0;
            while (n1)
            {
                memcpy(stack0, stack1, sizeof(stack1));
                n0 = n1; n1 = 0;
                for (int i = 0; i < n0; i++)
                {
                    for (int j = stack0[i][0]-1; j <= stack0[i][0]+1; j++)
                    for (int k = stack0[i][1]-1; k <= stack0[i][1]+1; k++)
                    if (avail[j][k] && !visit[j][k])
                    {
                        stack1[n1][0] = j;
                        stack1[n1][1] = k;
                        visit[j][k] = true;
                        dist_d2xy[i][j][k] = step;
                        n1++;
                    }
                }
                step++;
            }
        }
    }

    {// door
    	memset(door, 0, sizeof(door));
        door[1][0] = 40;
        door[1][1] = 9;
        door[2][0] = 40;
        door[2][1] = 77;
        door[3][0] = 60;
        door[3][1] = 32;
        door[4][0] = 60;
        door[4][1] = 104;
        door[5][0] = 72;
        door[5][1] = 100;
    }

    {// room_door adjacency
        memset(room_door, 0, sizeof(room_door));
        room_door[1][1] = room_door[1][3] = true;
        room_door[2][2] = true;
        room_door[3][1] = true;
        room_door[4][2] = room_door[4][3] = room_door[4][5] =true;
        room_door[5][4] = room_door[5][5] = true;
        room_door[6][4] = true;
    }
    {// min dist_r2r ~ door_r2r ~ dist_d2d
        memset(dist_d2d, 0, sizeof(dist_d2d));
        for (int i = 1; i < 6; i++)
        for (int j = i+1; j <= 6; j++)
        {
            dist_d2d[i][j] = dist_d2d[j][i] = dist_d2xy[i][door[j][0]][door[j][1]];
        }
        memset(dist_r2r, 0, sizeof(dist_r2r));
        memset(door_r2r, 0, sizeof(door_r2r));
        for (int i = 1; i < 6; i++)
        for (int j = i+1; j <= 6; j++)
        {
            for (int di = 1; di <= 5; i++)
            {
                if (!room_door[i][di]) continue;
                for (int dj = 1; dj <= 5; j++)
                {
                    if (!room_door[j][dj]) continue;
                    if (!door_r2r[i][j] || dist_r2r[i][j] > dist_d2d[di][dj])
                    {
                        door_r2r[i][j] = di;
                        door_r2r[j][i] = dj;
                        dist_r2r[i][j] = dist_r2r[j][i] = dist_d2d[di][dj];
                    }
                }
            }
        }
    }

    {// amount of nodes
        memset(node_length, 0, sizeof(node_length));
        node_length[1][1][1] = 14;
        node_length[1][3][3] = 11;
        node_length[1][3][1] = node_length[1][1][3] = 18;
        node_length[2][2][2] = 7;
        node_length[3][1][1] = 4;
        node_length[4][2][2] = 23;
        node_length[4][3][3] = 21;
        node_length[4][2][3] = node_length[4][3][2] = 25;
        node_length[4][5][5] = 22;
        node_length[4][2][5] = node_length[4][5][2] = 22;
        node_length[4][5][3] = node_length[4][3][5] = 26;
        node_length[5][4][4] = 4;
        node_length[5][5][5] = 6;
        node_length[5][4][5] = 8;
        node_length[6][1][1] = 1;
    }
    {// dist needed for searching room i 
        memset(dist_inr, 0, sizeof(dist_inr));
        for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= 5; j++)
            {
                if (!room_door[i][j]) continue;
                for (int k = j; k <= 5; k++)
                {
                    if (!room_door[i][k]) continue;
                    int (*n)[2] = (int (*)[2])(get_sequence(i,j,k));
                    int l = node_length[i][j][k] - 1;
                    dist_inr[i][j][k] += dist_d2xy[j][n[0][0]][n[0][1]];
                    dist_inr[i][j][k] += dist_d2xy[k][n[l][0]][n[l][1]];
                    while (l)
                    {
                        l--;
                        dist_inr[i][j][k] += dist_xy2xy(n[l][0],n[l][1],n[l+1][0],n[l+1][1]);
                    }
                }
            }
        }
    }
}

void turtle::learn(int room_no)
{
    int *h = freq_history;
    int (*f)[8][8] = frequency;
    h[0] = h[1];
    h[1] = h[2];
    h[2] = room_no;
    f[0][0][h[2]]++;
    f[0][h[1]][h[2]]++;
    f[h[0]][h[1]][h[2]]++;    
}


turtle::turtle(int x0, int y0, const int game_map[][150])
{
    x = x0;
    y = y0;
    init_freq();
    pre_search(game_map);
    //Other things that needed to be implemented.
}

bool turtle::scan(int x0, int y0, int r0, int& x, int& y, const int game_map[][150])
{
    for (int i = x0 - r0; i <= x0 + r0; i++)
    for (int j = y0 - r0; j <= y0 + r0; j++)
        if (game_map[i][j] == 3)
        {
            x = i; y = j;
            return true;
        }
    return false;
}

void turtle::cheak_wall(int x0, int y0, int& x, int& y, const int game_map[][150])
{
    int ration = max(abs(x0-x), abs(y0-y));
    for (int i,j,k = 1; k < ration; k++)
    {
        i = (x0 * k + x * (ration - k));
        j = (y0 * k + y * (ration - k));
        if ((i % ration)*2 >= ration)
        {
            if ((j % ration)*2 >= ration && game_map[i/ration+1][j/ration+1] == 1)
                {x = y = -1; return;}
            if ((j % ration)*2 <= ration && game_map[i/ration+1][j/ration] == 1)
                {x = y = -1; return;}
        }
        if ((i % ration)*2 <= ration)
        {
            if ((j % ration)*2 >= ration && game_map[i/ration][j/ration+1] == 1)
                {x = y = -1; return;}
            if ((j % ration)*2 <= ration && game_map[i/ration][j/ration] == 1)
                {x = y = -1; return;}
        }
        return;
    }
}

turtle::~turtle()
{
    if (now) delete(now);
    if (last) delete(last);
}
//the result should be passed by the pointers. The inner state of x and y should also be updated.
bool turtle::get_next(int &new_x, int &new_y, const int game_map[][150])
{
    // record passing on
    if (last) delete last;
    last = now; now = NULL;
    // same place - stop
    if (game_map[x][y] == 4)
    {
        now = new turtle::record(last, x, y, this);
        new_x = x; new_y = y;
        return true;
    }
    // human in robot's sight?
    int hx, hy;
    bool around = turtle::scan(x, y, r, hx, hy, game_map);
    if (around) turtle::cheak_wall(x, y, hx, hy, game_map);
    now = new turtle::record(last, hx, hy, this);
    // human in sight - track
    if (now -> insight)
    {
        if (plan) delete plan;
        x += sgn(now->hx - x);
        y += sgn(now->hy - y);
        new_x = x; new_y = y;
        return true;
    }
    // human out of sight - search
    else
    {
        if (!plan) plan = new turtle::search_plan(this);
        if (!plan->move(this)) return false;
        new_x = x; new_y = y;
        return true;
    }
}
