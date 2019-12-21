//
// Created by 王泽钧 on 12/21/2019.
//

#ifndef NEW_SIMULATOR_HUMAN_H
#define NEW_SIMULATOR_HUMAN_H


class human {
public:
    human(int x0, int y0);
    ~human();
    void get_next(int *x, int *y, const int game_map[][150]);
private:
    int x, y;
};


#endif //NEW_SIMULATOR_HUMAN_H
