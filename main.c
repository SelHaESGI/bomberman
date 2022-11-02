#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

typedef struct {
    int bomb;
    int column;
    int row;
    int players;
    char **grid;
} Map;

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

//créer une structure Bomb pouvant être instanciée X fois
typedef struct s_bomb {
    int x;
    int y;
    int timer;
    int range;
    //chained list
    struct s_bomb *next;
} Bomb;

Bomb *addBomb(Bomb *bombList, int x, int y, int range, int timer);
void deleteBomb(Bomb *oldBomb);
void explodeBomb(Bomb *bombList, char** grid);

void startMenu();

void black();

void red();

void yellow();

void blue();

void green();

void purple();

void reset();

void quitGame();

void setOptions();

void launchGame(char **grid, Map map, int *ptrTurn);

void showLogo();

void print_image(FILE *pFile);

void chooseMap();


void printMap(char letter);

void printAllMaps();

void changeGrid(char **gameGrid, Map map, int *ptrTurn);

int main() {
    printf("Bienvenu dans Bomberm...Casse briques !\n");
    startMenu();
    //deleteBomb(bombList);
    return 0;
}

void black() {
    printf("\033[1;30m");
}

void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[1;32m");
}

void blue() {
    printf("\033[1;34m");
}

void yellow() {
    printf("\033[1;33m");
}

void purple() {
    printf("\033[1;35m");
}


void reset() {
    printf("\033[0m");
}

void print_image(FILE *pFile) {
    char line[MAX_LEN];
    printf("\n");
    while (fgets(line, sizeof(line), pFile)) {
        printf("%s", line);
    }
    printf("\n");

}

void showLogo() {
    char *filename = "logo.txt";
    FILE *fptr = NULL;

    if ((fptr = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "error opening %s\n", filename);
        return;
    }

    print_image(fptr);

    fclose(fptr);
}

void clearTerminal() {
    printf("\033[2J\033[1;1H");

}

void clearStdin() {
    while (getchar() != '\n');
}

void startMenu() {
    showLogo();
    green();
    printf("1. Jouer\n");
    reset();
    printf("\u25A0 \u25A0 \u25A0 \u25A0 \u25A0\n");
    printf("\u25A0 \u24e7 \u25A5 \u2297 \u25A0\n");
    printf("\u25A0 \u24e7 \u25A5  2\u25A0\n");
    printf("\u25A0 \u25A0 \u25A0 \u25A0 \u25A0\n");
    printf("coeur : \u2661 \u2665 \n");

    yellow();
    printf("2. Options\n");
    red();
    printf("3. Quitter\n");
    reset();

    int choice;
    scanf("%d", &choice);
    clearTerminal();
    switch (choice) {
        case 1:
            chooseMap();
            break;
        case 2:
            setOptions();
            break;
        case 3:
            quitGame();
            break;
        default:
            scanf("%*[^\n]");
            clearTerminal();
            red();
            printf("Choix invalide\n");
            reset();
            startMenu();
            break;

    }

}

void chooseMap() {


    printAllMaps();
    int turn = 1;
    int *ptrTurn = &turn;
    printf("Choisissez une map (1 à 3):\n");
    int choice;
    int read_chars = scanf("%d", &choice);
    if (read_chars == 0) {
        printf("Erreur de saisie !\n");
        scanf("%*[^\n]");
    }
    char *filename;
    char line;
    switch (choice) {

        case 1:
            filename = "map1.txt";
            FILE *fptr = NULL;

            if ((fptr = fopen(filename, "r")) == NULL) {
                fprintf(stderr, "error opening %s\n", filename);
                exit(-1);
            }
            //MAP 1
            //ASSIGNATION DE LA MAP 1
            map_1.grid = malloc(map_1.row * sizeof(char *));
            for (int i = 0; i < map_1.row; i++)
                map_1.grid[i] = malloc(map_1.column * sizeof(char));
            //INITIALISATION DE LA MAP 1
            for (int i = 0; i < map_1.row; i++)
                for (int j = 0; j < map_1.column; j++) {
                    line = fgetc(fptr);
                    if (line == EOF) break;
                    if (line != '\n') {
                        map_1.grid[i][j] = line;
                    } else {
                        j--;
                    }
                }
            //AFFICHAGE DE LA MAP 1
//            for (int i = 0; i < map_1.row; i++){
//                for (int j = 0; j < map_1.column; j++) {
//                    printMap(map_1.grid[i][j]);
//                    if( j == map_1.column-1) {
//                        printf("\n");
//                    }
//                }
//            }
            fclose(fptr);
            launchGame(map_1.grid, map_1, ptrTurn);
            for (int i = 0; i < map_1.row; i++)
                free(map_1.grid[i]);

            free(map_1.grid);
            break;
        case 2:
            filename = "map2.txt";
            fptr = NULL;

            if ((fptr = fopen(filename, "r")) == NULL) {
                fprintf(stderr, "error opening %s\n", filename);
                exit(-1);
            }
            //MAP 2
            //ASSIGNATION DE LA MAP 2
            map_2.grid = malloc(map_2.row * sizeof(char *));
            for (int i = 0; i < map_2.row; i++)
                map_2.grid[i] = malloc(map_2.column * sizeof(char));
            //INITIALISATION DE LA MAP 2
            for (int i = 0; i < map_2.row; i++)
                for (int j = 0; j < map_2.column; j++) {
                    line = fgetc(fptr);
                    if (line == EOF) break;
                    if (line != '\n') {
                        map_2.grid[i][j] = line;
                    } else {
                        j--;
                    }
                }
            //AFFICHAGE DE LA MAP 2
//            for (int i = 0; i < map_2.row; i++){
//                for (int j = 0; j < map_2.column; j++) {
//                    printMap(map_2.grid[i][j]);
//                    if( j == map_2.column-1) {
//                        printf("\n");
//                    }
//                }
//            }
            fclose(fptr);
            launchGame(map_2.grid, map_2, ptrTurn);
            for (int i = 0; i < map_2.row; i++)
                free(map_2.grid[i]);
            free(map_2.grid);
            break;
        case 3:
            filename = "map3.txt";
            fptr = NULL;

            if ((fptr = fopen(filename, "r")) == NULL) {
                fprintf(stderr, "error opening %s\n", filename);
                exit(-1);
            }
            //MAP 3
            //ASSIGNATION DE LA MAP 3
            map_3.grid = malloc(map_3.row * sizeof(char *));
            for (int i = 0; i < map_3.row; i++)
                map_3.grid[i] = malloc(map_3.column * sizeof(char));
            //INITIALISATION DE LA MAP 3
            for (int i = 0; i < map_3.row; i++)
                for (int j = 0; j < map_3.column; j++) {
                    line = fgetc(fptr);
                    if (line == EOF) break;
                    if (line != '\n') {
                        map_3.grid[i][j] = line;
                    } else {
                        j--;
                    }
                }
            //AFFICHAGE DE LA MAP 3
//            for (int i = 0; i < map_3.row; i++){
//                for (int j = 0; j < map_3.column; j++) {
//                    printMap(map_3.grid[i][j]);
//                    if( j == map_3.column-1) {
//                        printf("\n");
//                    }
//                }
//            }
            fclose(fptr);
            launchGame(map_3.grid, map_3, ptrTurn);
            for (int i = 0; i < map_3.row; i++)
                free(map_3.grid[i]);
            free(map_3.grid);
            break;
//        case 4:
//            //MAP 4
//            //ASSIGNATION DE LA MAP 4
//            map_4.grid = malloc(map_4.row * sizeof(char*));
//            for (int i = 0; i < map_4.row; i++)
//                map_4.grid[i] = malloc(map_4.column * sizeof(char));
//            //INITIALISATION DE LA MAP 4
//            for (int i = 0; i < map_4.row; i++)
//                for (int j = 0; j < map_4.column; j++)
//                    map_4.grid[i][j] = 'x';
//            //AFFICHAGE DE LA MAP 4
//            for (int i = 0; i < map_4.row; i++){
//                for (int j = 0; j < map_4.column; j++) {
//                    printf("%c ", map_4.grid[i][j]);
//                    if (j == map_4.column - 1) {
//                        printf("\n");}
//                }
//            }
//            for (int i = 0; i < map_4.row; i++)
//                free(map_4.grid[i]);
//
//            free(map_4.grid);
//            return map_4.grid;
//        case 5:
//            //MAP 5
//            //ASSIGNATION DE LA MAP 5
//            map_5.grid = malloc(map_5.row * sizeof(char*));
//            for (int i = 0; i < map_5.row; i++)
//                map_5.grid[i] = malloc(map_5.column * sizeof(char));
//            //INITIALISATION DE LA MAP 5
//            for (int i = 0; i < map_5.row; i++)
//                for (int j = 0; j < map_5.column; j++)
//                    map_5.grid[i][j] = 'x';
//            //AFFICHAGE DE LA MAP 5
//            for (int i = 0; i < map_5.row; i++){
//                for (int j = 0; j < map_5.column; j++) {
//                    printf("%c ", map_5.grid[i][j]);
//                    if (j == map_5.column - 1) {
//                        printf("\n");}
//                }
//            }
//            for (int i = 0; i < map_5.row; i++)
//                free(map_5.grid[i]);
//
//            free(map_5.grid);
//            return map_5.grid;
//        case 6:
//            //MAP 6
//            //ASSIGNATION DE LA MAP 6
//            map_6.grid = malloc(map_6.row * sizeof(char*));
//            for (int i = 0; i < map_6.row; i++)
//                map_6.grid[i] = malloc(map_6.column * sizeof(char));
//            //INITIALISATION DE LA MAP 6
//            for (int i = 0; i < map_6.row; i++)
//                for (int j = 0; j < map_6.column; j++)
//                    map_6.grid[i][j] = 'x';
//            //AFFICHAGE DE LA MAP 6
//            for (int i = 0; i < map_6.row; i++){
//                for (int j = 0; j < map_6.column; j++) {
//                    printf("%c ", map_6.grid[i][j]);
//                    if (j == map_6.column - 1) {
//                        printf("\n");}
//                }
//            }
//            for (int i = 0; i < map_6.row; i++)
//                free(map_6.grid[i]);
//
//            free(map_6.grid);
//            return map_6.grid;
        default:
            scanf("%*[^\n]");
            clearTerminal();
            red();
            printf("Choix invalide\n");
            reset();
            chooseMap();
            break;

    }
    /* Code for further processing and free the
       dynamically allocated memory */

}

void printAllMaps() {
    red();
    printf("MAP 1\n");
    reset();
    printf("■ ■ ■ ■ ■ ■ ■ ■\n");
    printf("■ 웃    ▥     ■\n");
    printf("■     ▥   ▥   ■\n");
    printf("■   ▥       ▥ ■\n");
    printf("■ ▥       ▥   ■\n");
    printf("■   ▥   ▥     ■\n");
    printf("■     ▥     웃■\n");
    printf("■ ■ ■ ■ ■ ■ ■ ■\n");
    red();
    printf("\nAttribut :\n");
    reset();
    printf("Nombre de bombes par défaut : %d\n", map_1.bomb);
    printf("Taille de la grille : %dx%d\n", map_1.row, map_1.column);
    printf("Nombre de joueurs maximal : %d\n\n", map_1.players);

    red();
    printf("MAP 2\n");
    reset();
    printf("■ ■ ■ ■ ■ ■ ■ ■ ■ ■\n");
    printf("■ 웃      ▥       ■\n");
    printf("■         ▥     웃■\n");
    printf("■         ▥       ■\n");
    printf("■       ▥ ■ ▥     ■\n");
    printf("■     ▥ ■   ■ ▥   ■\n");
    printf("■   ▥         ▥   ■\n");
    printf("■ ▥             ▥ ■\n");
    printf("■        웃       ■\n");
    printf("■ ■ ■ ■ ■ ■ ■ ■ ■ ■\n");
    blue();
    printf("\nAttribut :\n");
    reset();
    printf("Nombre de bombes par défaut : %d\n", map_2.bomb);
    printf("Taille de la grille : %dx%d\n", map_2.row, map_2.column);
    printf("Nombre de joueurs maximal : %d\n\n", map_2.players);

    red();
    printf("MAP 3\n");
    reset();
    printf("■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■\n");
    printf("■ 웃    ▥   ▥   ▥   ▥ ■\n");
    printf("■     ▥   ▥   ▥   ▥   ■\n");
    printf("■   ▥   ▥   ▥   ▥   ▥ ■\n");
    printf("■ ▥   ▥   ▥   ▥   ▥   ■\n");
    printf("■   ▥   ▥   ▥   ▥   ▥ ■\n");
    printf("■ ▥   ▥   ▥   ▥   ▥   ■\n");
    printf("■   ▥   ▥   ▥   ▥   ▥ ■\n");
    printf("■ ▥   ▥   ▥   ▥   ▥   ■\n");
    printf("■   ▥   ▥   ▥   ▥     ■\n");
    printf("■ ▥   ▥   ▥   ▥     웃■\n");
    printf("■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■\n");
    blue();
    printf("\nAttribut :\n");
    reset();
    printf("Nombre de bombes par défaut : %d\n", map_3.bomb);
    printf("Taille de la grille : %dx%d\n", map_3.row, map_3.column);
    printf("Nombre de joueurs maximal : %d\n\n", map_3.players);


}

void printMap(char letter) {
    switch (letter) {
        case 'X':
            black();
            printf("\u25A0 ");
            break;
        case 'O':
            reset();
            printf("  ");
            break;
        case 'M':
            reset();
            printf("\u25A5 ");
            break;
        case 'B':
            red();
            printf("\u2297 ");
            break;
        case '1':
            green();
            printf("\uc6c3");
            break;
        case '2':
            red();
            printf("\uc6c3");
            break;
        case '3':
            yellow();
            printf("\uc6c3");
            break;
        case '4':
            blue();
            printf("\uc6c3");
            break;
        default:
            break;
    }
    reset();

}

void launchGame(char **grid, Map map, int *ptrTurn) {

    //AFFICHAGE DE LA MAP CHOISIE
    for (int i = 0; i < map.row; i++) {
        for (int j = 0; j < map.column; j++) {
            printMap(grid[i][j]);
            if (j == map.column - 1) {
                printf("\n");
            }
        }
    }
    printf("\n");
    printf("Nombre de bombes par défaut : %d\n", map.bomb);
    //afficher les commandes du jeu
    printf("Commandes :\n");
    printf("1. Déplacer le joueur : Z = haut, S = bas, Q = gauche, D = droite\n");
    printf("2. Poser une bombe : B\n");
    printf("3. Abandonner : A\n");
    printf("4. Finir le tour avant les 5 mouvements : P\n");
    clearStdin();
    clearTerminal();
    changeGrid(grid, map, ptrTurn);

    //relaunch the function
    clearStdin();
    clearTerminal();
    //launchGame(grid, map, ptrTurn);

//    for (int i = 0; i < map.row; i++)
//        free(map.grid[i]);
//    free(map.grid);
}


void setOptions() {}


void quitGame() {
    printf("Merci d'avoir joué !\n");
    //deleteBomb(Bomb *bomb);
    exit(0);
}

void changeGrid(char **gameGrid, Map map, int *ptrTurn) {
    Bomb* listBomb;
    char choosedAction;
//        for (int i = 0; i < map.row; i++){
//            for (int j = 0; j < map.column; j++) {
//                printMap(gameGrid[i][j]);
//                if (j == map.column - 1) {
//                    printf("\n");}
//            }
//        }
//        printf("Joueur %d, choisissez vos actions : ", *ptrTurn);
//        scanf("%c", &choosedAction);
    int moveLeft = 4;
    int bombLeft = map.bomb;
    //printf("Vous êtes le joueur %d\n", *ptrTurn);
//        char player = (char)*ptrTurn;
//        printf("Vous êtes le joueur %c\n", player);
    //player turn is contained in ptrTurn, if it's 1, it's player 1's turn, if it's 2, it's player 2's turn
    //action is the action the player wants to do
    //gameGrid is the grid of the game
    //map.bomb is the number of bombs the player can put, it resets at the explosion of the bomb
    //if player choose to move (Z, S, Q, D), check if there is a O in the direction he wants to go, if there is, move the player and set is previous position to O
    //if he can't move, print "Vous ne pouvez pas vous déplacer ici" and ask for another action
    //when he moves, remove 1 to moveLeft
    //if player choose to put a bomb (B), check if there is bomb left in bombLeft, if bombLeft>0, ask for a movement first, then put B in his position before moving, then bombLeft--
    //if bombLeft = 0, print "Vous ne pouvez plus poser de bombes" and ask for another action
    //if player choose to abandon (A), print "Vous avez abandonné la partie" and exit the game
    //if player choose to finish his turn (P), print "Vous avez fini votre tour" and change the turn
    //if moveLeft == 0, print "Vous avez fini votre tour" and change the turn
    //if player choose to do something else, print "Commande invalide" and ask for another action
    int invalidMove = 0;
    char turn;
    while (moveLeft > 0) {
        //AFFICHAGE DE LA MAP CHOISIE
        clearStdin();
        clearTerminal();

        for (int i = 0; i < map.row; i++) {
            for (int j = 0; j < map.column; j++) {
                printMap(gameGrid[i][j]);
                if (j == map.column - 1) {
                    printf("\n");
                }
            }
        }
        printf("Vous avez %d mouvements restants\n", moveLeft);
        if (invalidMove == 1) {
            red();
            printf("Vous ne pouvez pas vous déplacer ici\n");
            reset();
            invalidMove = 0;
        }
        printf("Joueur %d, choisissez vos actions : ", *ptrTurn);
//            if(*ptrTurn == 1){
//                turn = '1';
//                printf("Vous êtes le joueur %c\n", turn);
//            }else{
//                turn = '2';
//            }
        switch (*ptrTurn) {
            case 1:
                turn = '1';
                break;
            case 2:
                turn = '2';
                break;
            case 3:
                turn = '3';
                break;
            case 4:
                turn = '4';
                break;
            default:
                break;
        }

        choosedAction = getchar();
        printf("Action choisie : (%c)\n", choosedAction);
        switch (toupper(choosedAction)) {
            case 'A':
                quitGame();
                break;
            case 'P':
                printf("Vous avez fini votre tour\n");
                switch (*ptrTurn) {
                    case 1:
                        *ptrTurn = 2;
                        break;
                    case 2:
                        if (map.players == 2) {
                            *ptrTurn = 1;
                        } else {
                            *ptrTurn = 3;
                        }
                        break;
                    case 3:
                        if (map.players == 3) {
                            *ptrTurn = 1;
                        } else {
                            *ptrTurn = 4;
                        }
                        break;
                    case 4:
                        *ptrTurn = 1;
                        break;
                    default:
                        break;
                }
                break;

            case 'Z':
                for (int i = 0; i < map.row; i++) {
                    for (int j = 0; j < map.column; j++) {
                        printf("position de recherche = %d %d\n", i, j);
                        printf("(char)*ptrTurn = %c\n", turn);
                        //printMap(gameGrid[i][j]);
                        if (gameGrid[i][j] == turn) {
                            printf("Joueur trouvé a %d %d\n", i, j);
                            printf("COUCOU2");
                            if (gameGrid[i - 1][j] == 'O') {
                                gameGrid[i][j] = 'O';
                                gameGrid[i - 1][j] = turn;

                                moveLeft--;
                                break;
                            } else {
                                invalidMove = 1;
                                break;
                            }
                        }
                        //break;
                    }
                }
                break;
            case 'Q':
                for (int i = 0; i < map.row; i++) {
                    for (int j = 0; j < map.column; j++) {
                        if (gameGrid[i][j] == turn) {
                            if (gameGrid[i][j - 1] == 'O') {
                                gameGrid[i][j] = 'O';
                                gameGrid[i][j - 1] = turn;
                                moveLeft--;
                                break;
                            } else {
                                invalidMove = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            case 'S':
                for (int j = 0; j < map.column; j++) {
                    for (int i = 0; i < map.row; i++) {

                        if (gameGrid[i][j] == turn) {
                            printf("Joueur trouvé a %d %d\n", i, j);
                            if (gameGrid[i + 1][j] == 'O') {
                                gameGrid[i][j] = 'O';
                                gameGrid[i + 1][j] = turn;
                                printf("DESCENDU");
                                moveLeft--;
                                break;
                            } else {
                                invalidMove = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            case 'D':
                //check all the map to find the player designated by turn
                //if the player is found, check if the player can move to the right
                //if he can, move him to the right case only if it's an O
                //move him only one time, and set is previous position to O
                //remove 1 to moveLeft
                for (int i = 0; i < map.row; i++) {
                    for (int j = 0; j < map.column; j++) {
                        if (gameGrid[i][j] == turn) {
                            printf("Joueur trouvé a %d %d\n", i, j);
                            if (gameGrid[i][j + 1] == 'O') {
                                gameGrid[i][j] = 'O';
                                gameGrid[i][j + 1] = turn;
                                printf("DROITE");
                                moveLeft--;
                                break;
                            } else {
                                invalidMove = 1;
                                break;
                            }
                        }
                    }
                }
                break;
            case 'B':
                //check all the grid to find the player designated by turn
                //check if the player have more than 1 moveLeft
                //if he have more than 1 moveLeft, ask him where he want to go, change his position and set his previous position to B
                //if the player have 1 moveLeft, printf "Vous ne pouvez pas poser de bombe"

                if (moveLeft > 1) {
                    for (int i = 0; i < map.row; i++) {
                        for (int j = 0; j < map.column; j++) {
                            if (gameGrid[i][j] == turn) {
                                listBomb = addBomb(listBomb, i, j, 2, 3);
                                printf("Choissisez une position pour vous déplacer : ");
                                char choosedPosition;
                                choosedPosition = getchar();
                                printf("Position choisie : (%c)\n", choosedPosition);
                                switch (toupper(choosedPosition)) {
                                    case 'Z':
                                        if (gameGrid[i - 1][j] == 'O') {
                                            gameGrid[i][j] = 'B';
                                            gameGrid[i - 1][j] = turn;
                                            moveLeft--;
                                            break;
                                        } else {
                                            invalidMove = 1;
                                            break;
                                        }
                                        break;
                                    case 'Q':
                                        if (gameGrid[i][j - 1] == 'O') {
                                            gameGrid[i][j] = 'B';
                                            gameGrid[i][j - 1] = turn;
                                            moveLeft--;
                                            break;
                                        } else {
                                            invalidMove = 1;
                                            break;
                                        }
                                        break;
                                    case 'S':
                                        if (gameGrid[i + 1][j] == 'O') {
                                            gameGrid[i][j] = 'M';
                                            gameGrid[i + 1][j] = turn;
                                            printf("bouclefonctionnelle");
                                            moveLeft--;
                                            break;
                                        } else {
                                            invalidMove = 1;
                                            break;
                                        }
                                        break;
                                    case 'D':
                                        if (gameGrid[i][j + 1] == 'O') {
                                            gameGrid[i][j] = 'B';
                                            gameGrid[i][j + 1] = turn;
                                            moveLeft--;
                                            break;
                                        } else {
                                            invalidMove = 1;
                                            break;
                                        }
                                        break;
                                    default:
                                        break;
                                }
                                //gameGrid[i][j] = 'B';
s
                                //moveLeft--;
                                break;
                            }
                        }
                    }
                } else {
                    printf("Vous ne pouvez pas poser de bombe\n");
                }


        }
        explodeBomb(listBomb, gameGrid);
    }
//        for(int i = 0; i < map.row; i++){
//            for(int j = 0; j < map.column; j++){
//                printMap(gameGrid[i][j]);
//                printf("ici");
//            }
//            printf("\n");}
    if (moveLeft == 0) {
//            if(*ptrTurn==1){
//                *ptrTurn = 2;
//                changeGrid(gameGrid, map, ptrTurn);
//            }
//            else if(*ptrTurn==2){
//                *ptrTurn = 1;
//                changeGrid(gameGrid, map, ptrTurn);
//            }
        switch (*ptrTurn) {
            case 1:
                *ptrTurn = 2;
                changeGrid(gameGrid, map, ptrTurn);
                break;
            case 2:
                if (map.players == 2) {
                    *ptrTurn = 1;
                } else {
                    *ptrTurn = 3;
                }
                changeGrid(gameGrid, map, ptrTurn);
                break;
            case 3:
                if (map.players == 3) {
                    *ptrTurn = 1;
                } else {
                    *ptrTurn = 4;
                }
                changeGrid(gameGrid, map, ptrTurn);
                break;
            case 4:
                *ptrTurn = 1;
                changeGrid(gameGrid, map, ptrTurn);
                break;
            default:
                break;
        }
    }

}

void explodeBomb(Bomb *bombList, char** grid){
    Bomb* currentBomb = bombList;
    while(currentBomb != NULL){
        if(currentBomb->timer == 0){
            grid[currentBomb->x][currentBomb->y] = 'O';
            //check 2 case to the left right up and down, if it's a X stop, if it's a M set is to O, if it's 1 2 3 or 4 set it to O

            //check left
            for(int i = 1; i <= currentBomb->range; i++){
                if(grid[currentBomb->x][currentBomb->y - i] == 'X'){
                    break;
                }
                else if(grid[currentBomb->x][currentBomb->y - i] == 'M'){
                    grid[currentBomb->x][currentBomb->y - i] = 'O';
                    break;
                }
                else if(grid[currentBomb->x][currentBomb->y - i] == '1' || grid[currentBomb->x][currentBomb->y - i] == '2' || grid[currentBomb->x][currentBomb->y - i] == '3' || grid[currentBomb->x][currentBomb->y - i] == '4'){
                    grid[currentBomb->x][currentBomb->y - i] = 'O';
                    break;
                }
            }
            //check right
            for(int i = 1; i <= currentBomb->range; i++){
                if(grid[currentBomb->x][currentBomb->y + i] == 'X'){
                    break;
                }
                else if(grid[currentBomb->x][currentBomb->y + i] == 'M'){
                    grid[currentBomb->x][currentBomb->y + i] = 'O';
                    break;
                }
                else if(grid[currentBomb->x][currentBomb->y + i] == '1' || grid[currentBomb->x][currentBomb->y + i] == '2' || grid[currentBomb->x][currentBomb->y + i] == '3' || grid[currentBomb->x][currentBomb->y + i] == '4'){
                    grid[currentBomb->x][currentBomb->y + i] = 'O';
                    break;
                }
            }
            //check up
            for(int i = 1; i <= currentBomb->range; i++){
                if(grid[currentBomb->x - i][currentBomb->y] == 'X'){
                    break;
                }
                else if(grid[currentBomb->x - i][currentBomb->y] == 'M'){
                    grid[currentBomb->x - i][currentBomb->y] = 'O';
                    break;
                }
                else if(grid[currentBomb->x - i][currentBomb->y] == '1' || grid[currentBomb->x - i][currentBomb->y] == '2' || grid[currentBomb->x - i][currentBomb->y] == '3' || grid[currentBomb->x - i][currentBomb->y] == '4'){
                    grid[currentBomb->x - i][currentBomb->y] = 'O';
                    break;
                }
            }
            //check down
            for(int i = 1; i <= currentBomb->range; i++){
                if(grid[currentBomb->x + i][currentBomb->y] == 'X'){
                    break;
                }
                else if(grid[currentBomb->x + i][currentBomb->y] == 'M'){
                    grid[currentBomb->x + i][currentBomb->y] = 'O';
                    break;
                }
                else if(grid[currentBomb->x + i][currentBomb->y] == '1' || grid[currentBomb->x + i][currentBomb->y] == '2' || grid[currentBomb->x + i][currentBomb->y] == '3' || grid[currentBomb->x + i][currentBomb->y] == '4'){
                    grid[currentBomb->x + i][currentBomb->y] = 'O';
                    break;
                }
            }

            currentBomb = currentBomb->next;
        }
        else{
            currentBomb->timer--;
            currentBomb = currentBomb->next;
        }
    }
}

Bomb *createBomb(int x, int y, int range, int timer) {
    Bomb *newBomb = malloc(sizeof(Bomb));
    if (NULL != newBomb) {
        newBomb->x = x;
        newBomb->y = y;
        newBomb->range = range;
        newBomb->timer = timer;
        newBomb->next = NULL;
    }
    return newBomb;
}

Bomb *addBomb(Bomb *bombList, int x, int y, int range, int timer) {
    Bomb *newBomb = createBomb(x, y, range, timer);
    if (NULL == newBomb) {
        newBomb->next = bombList;
    }
    return newBomb;
}

void deleteBomb(Bomb *oldBomb) {
    if (NULL != oldBomb->next) {
        deleteBomb(oldBomb->next);
    }
    free(oldBomb);
}






