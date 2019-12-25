//
// Created by 王泽钧 on 12/26/2019.
//

#include "plotter.h"

plotter::plotter(){
    img = NULL;
    unit_w = -1;
    unit_h = -1;
}


plotter::plotter(LPCTSTR img_file){
    unit_w = 8;
    unit_h = 8;
    loadimage(&img, img_file, unit_w, unit_h);

}

void plotter::get_size(int &x, int &y){
    x = img.getheight();
    y = img.getwidth();
}

void plotter::draw_scene(int (*game_map)[150]) {
    for(int i=0; i<150; i++)
        for(int j=0; j<150; j++){
            if(game_map[i][j]==1)
                putimage(j*unit_w, i*unit_h, &img);
            else if(game_map[i][j]==2){
                setfillcolor(YELLOW);
                solidrectangle(j*unit_h, i*unit_w, (j+1)*unit_h, (i+1)*unit_w);
            }else if(game_map[i][j]==3){
                setfillcolor(RED);
                solidrectangle(j*unit_h, i*unit_w, (j+1)*unit_h, (i+1)*unit_w);
            }

        }
}

