#include <cstdio>
#include "master.h"
#include <conio.h>
int main() {
    freopen("log.txt", "w", stdout);
    master game_core(61,21, 61, 30);

    for(int i=0; i<100000; i++) {
        int timer = 0;
        while (timer <= 1000000)
            timer++;
        game_core.step_forward();
        int hx, hy, tx, ty;
        game_core.get_h_pos(hx, hy);
        game_core.get_t_pos(tx, ty);
        printf("After %d steps, the human stands at %d %d and the turtle stands at %d %d\n",i+1, hx, hy, tx, ty );
    }

    _getch();

    return 0;
}

