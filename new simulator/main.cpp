#include <iostream>
#include <cstdio>
#include "utils.h"
#include "master.h"
#include <easyx.h>			// Reference graphics library header file
#include <conio.h>
#include "plotter.h"
int main() {
    //freopen("test.txt", "w", stdout);
    master game_core(61,21, 61, 30);

    initgraph(2000, 2000);
    plotter drawer = plotter(_T("D:\\PKU\\school work\\Grade3 Autumn\\An Introduction to AI\\final project\\new simulator\\src\\shiCai\\img\\wall.gif"));
    drawer.draw_scene((int(*)[150])game_core.get_map());
    for(int i=0; i<100000; i++){
        int timer = 0;
        while(timer<=100000000)
            timer++;
        game_core.step_forward();
        drawer.draw_scene((int(*)[150])game_core.get_map());
    }
    _getch();
    closegraph();
    /*
    for(int i=0; i<2000; i++){
        game_core.step_forward();
        int x, y;
        printf("After step %d\n", i+1);
        game_core.get_h_pos(x, y);
        printf("Human's position is %d, %d in room %d\n", x, y, judge_room(x,y));
        game_core.get_t_pos(x, y);
        game_core.rep_t();
        //printf("Turtle's position is %d, %d in room %d\n", x, y, judge_room(x,y));
    }*/
    return 0;
}

