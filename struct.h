#ifndef BOMBERMAN_STRUCT_H
#define BOMBERMAN_STRUCT_H
typedef struct {
    int bomb;
    int column;
    int row;
    int players;
    int move;
    char **grid;
} Map;

Map map_1 = {
        .bomb = 1,
        .column = 8,
        .row = 8,
        .players = 2,
        .move = 6,
};

Map map_2 = {
        .bomb = 2,
        .column = 10,
        .row = 10,
        .players = 3,
        .move = 5,
};

Map map_3 = {
        .bomb = 2,
        .column = 12,
        .row = 12,
        .players = 2,
        .move = 6,
};

Map map_4 = {
        .bomb = 3,
        .column = 16,
        .row = 16,
        .players = 4,
        .move = 6,
};

Map map_5 = {
        .bomb = 2,
        .column = 14,
        .row = 14,
        .players = 4,
        .move = 6,

};
Map map_6 = {
        .bomb = 3,
        .column = 16,
        .row = 16,
        .players = 4,
        .move = 6,
};

typedef struct Bomb Bomb;
struct Bomb {
    int x;
    int y;
    int timer;
    int range;
    int owner;
    struct Bomb *suivant;
};

typedef struct Liste Liste;
struct Liste {
    Bomb *premier;
};

typedef struct Player Player;
struct Player {
    int x;
    int y;
    int id;
    int isAlive;
    int isBot;
    int bomb;
    int flameRange;
    int life;
    int heart;
    int invincible;
    struct Player *suivant;
};

typedef struct ListePlayer ListePlayer;
struct ListePlayer {
    Player *premier;
};

#endif //BOMBERMAN_STRUCT_H
