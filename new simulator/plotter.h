//
// Created by 王泽钧 on 12/26/2019.
//

#ifndef NEW_SIMULATOR_PLOTTER_H
#define NEW_SIMULATOR_PLOTTER_H
#include <easyx.h>

class plotter {

public:
    plotter();
    plotter(LPCTSTR img_file);
    void get_size(int &x, int &y);
    void draw_scene(int game_map[][150]);

private:
    IMAGE img;
    int unit_w, unit_h;
};


#endif //NEW_SIMULATOR_PLOTTER_H
