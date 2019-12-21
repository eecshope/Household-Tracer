//
// Created by 王泽钧 on 12/21/2019.
//

#ifndef NEW_SIMULATOR_HUMAN_H
#define NEW_SIMULATOR_HUMAN_H

class way
{
  public:
  int x, y;
  way * prev;
  way(int x_, int y_, way* prev_) :x(x_), y(y_), prev(prev_) {}
  way() {}
};

class human {
public:
    human(int x0, int y0);
    ~human();
    void get_next(int *x, int *y, const int game_map[][150]);
private:
    int x, y;
    int goalX, goalY;
    int last, now;
    way next[22600];
    int stepNow;
    void next_dst(int *x, int *y);
    void path_search(const int maze[][150]);
};


#endif //NEW_SIMULATOR_HUMAN_H
