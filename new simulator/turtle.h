//
// Created by 王泽钧 on 12/21/2019.
//

#ifndef NEW_SIMULATOR_TURTLE_H
#define NEW_SIMULATOR_TURTLE_H

//TODO:Implement this class. Free to add more variables and methods
class turtle {
public:
    turtle(int x0, int y0);
    ~turtle();
    void get_next(int *x, int *y, const int game_map[][150]);
private:
    int x, y;
    void load_memory();
    void save_memory();
};


#endif //NEW_SIMULATOR_TURTLE_H
