//
// Created by 王泽钧 on 12/21/2019.
//
#include<cstring>
void init_map(int game_map[][150]){
    //Draw the horizonal walls
    for(int i=0; i<=100; i++)
        game_map[0][i] = 1;
    for(int i=0; i<=20; i++)
        game_map[40][i] = 1;
    for(int i=60; i<=120; i++)
        game_map[40][i] = 1;
    for(int i=0; i<=60; i++)
        game_map[60][i] = 1;
    for(int i=100; i<=110; i++)
        game_map[60][i] = 1;
    for(int i=20; i<=120; i++)
        game_map[100][i] = 1;
    //Draw the vertical walls
    for(int i=0; i<=60; i++)
        game_map[i][0] = 1;
    for(int i=40; i<=100; i++)
        game_map[i][20] = 1;
    for(int i=0; i<=60; i++)
        game_map[i][60] = 1;
    for(int i=0; i<=100; i++)
        game_map[i][100] = 1;
    for(int i=40; i<=60; i++)
        game_map[i][110] = 1;
    for(int i=40; i<=100; i++)
        game_map[i][120] = 1;
    //open some doors
    const int door_width = 4;
    for(int i=8; i<=7+door_width; i++)
        game_map[40][i] = 0;
    for(int i=30; i<=29+door_width; i++)
        game_map[60][i] = 0;
    for(int i=75; i<=74+door_width; i++)
        game_map[40][i] = 0;
    for(int i=70; i<=69+door_width; i++)
        game_map[i][100] = 0;
    for(int i=103; i<=102+door_width; i++)
        game_map[60][i] = 0;
    return;
}
//Regard the doors as walls
int judge_room(int x, int y){
    if((x>0&&x<40&&y>0&&y<60)||(x>=40&&x<60&&y>20&&y<60))
        return 1;
    else if(x>0&&x<40&&y>60&&y<100)
        return 2;
    else if(x>40&&x<60&&y>0&&y<20)
        return 3;
    else if((x>60&&x<100&&y>20&&y<100)||(x>40&&x<=60&&y>60&&y<100))
        return 4;
    else if((x>60&&x<100&&y>100&&y<120&&y>100)||(x>40&&x<=60&&y>110&&y<120))
        return 5;
    else if(x>40&&x<60&&y>100&&y<110)
        return 6;
    else
        return 0;
}
//return the left_top available position of each room
//id is the id of the room
void get_left_top(int id, int *x, int *y){
    int px[6] = {1,1,41,61,41,41}, py[6] = {1,61,1,21,111,101};
    *x = px[id];
    *y = py[id];
    return;
}
