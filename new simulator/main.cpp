#include <iostream>
#include "utils.h"
int main() {
    freopen("test.txt", "w", stdout);
    std::cout << "Hello, World!" << std::endl;
    int tmp[150][150];
    memset(tmp, 0, sizeof(tmp));
    init_map(tmp);
    for(int i=0; i<150; i++){
        for(int j=0; j<150; j++)
            std::cout<<judge_room(i, j);
        std::cout<<'\n';
    }

    return 0;
}

