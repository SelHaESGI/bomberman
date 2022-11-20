#include "common.h"

//structure for storing address information

typedef struct {
    int bomb;
    int column;
    int row;
    int players;
    char **grid;
} Map;

Map map_Test = {
        .bomb = 1,
        .column = 8,
        .row = 8,
        .players = 2,
};

Map map_1 = {
        .bomb = 1,
        .column = 8,
        .row = 8,
        .players = 2,
};

Map map_2 = {
        .bomb = 2,
        .column = 10,
        .row = 10,
        .players = 3,
};

Map map_3 = {
        .bomb = 2,
        .column = 12,
        .row = 12,
        .players = 2,
};

Map map_4 = {
        .bomb = 3,
        .column = 16,
        .row = 16,
        .players = 4,
};

Map map_5 = {
        .bomb = 2,
        .column = 14,
        .row = 14,
        .players = 4,

};
Map map_6 = {
        .bomb = 3,
        .column = 16,
        .row = 16,
        .players = 4,
};

Map rand_map(int column, int row){
    if(column < 12 ||  row < 12 ){
        Map map = {
                .bomb = 2,
                .column = column,
                .row = row,
                .players = 4,
        };
        return map;
    }
    else{
        Map map = {
                .bomb = 3,
                .column = column,
                .row = row,
                .players = 4,
        };
        return map;
    }
}

//créer une structure Bomb pouvant être instanciée X fois
typedef struct Bomb Bomb;
struct Bomb {
    int x;
    int y;
    int timer;
    int range;
    struct Bomb *suivant;
};

typedef struct Liste Liste;
struct Liste {
    Bomb *premier;
};
