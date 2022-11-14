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

//Bomb *addBomb(Bomb *bombList, int x, int y, int range, int timer);

//void deleteBomb(Bomb *oldBomb);

//void explodeBomb(Bomb *bombList, char **grid);

Liste* init();
void insertBomb(Liste* liste, int x, int y, int timer, int range);
void decreaseBombTimer(Liste* liste, char** gameGrid);
void explodeBomb(Liste *liste, char **gameGrid);
void deleteBomb(Liste *liste);

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

void launchGame(char **grid, Map map, int *ptrTurn, int vsChoice);

void showLogo();

void print_image(FILE *pFile);

void chooseMap();


void printMap(char letter);

void printAllMaps();

void changeGrid(char **gameGrid, Map map, int *ptrTurn, int vsChoice);

void explodeBomb(Liste *liste, char **gameGrid);

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

    int vsChoice;
    printAllMaps();
    int turn = 1;
    int *ptrTurn = &turn;
    printf("Choisissez une map (1 à 4, 4 = mapTest):\n");
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


            //Choix vs ia ou vs player //
            blue();
            printf("\n vs IA ou vs Player ?\n");
            reset();
            purple();
            printf("1. vsIA\n");
            reset();
            yellow();
            printf("2. vsPlayer\n");
            reset();
            scanf("%d", &vsChoice);

            switch (vsChoice) {
                case 1:
                    launchGame(map_1.grid, map_1, ptrTurn, vsChoice);
                    break;
                case 2:
                    launchGame(map_1.grid, map_1, ptrTurn, vsChoice);
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

            //launchGame(map_1.grid, map_1, ptrTurn);
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

            blue();
            printf("\nvs IA ou vs Player ?\n");
            reset();
            purple();
            printf("1. vsIA\n");
            reset();
            yellow();
            printf("2. vsPlayer\n");
            reset();
            scanf("%d", &vsChoice);

            switch (vsChoice) {
                case 1:
                    launchGame(map_2.grid, map_2, ptrTurn, vsChoice);
                    break;
                case 2:
                    launchGame(map_2.grid, map_2, ptrTurn, vsChoice);
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

            blue();
            //printf("\n");
            printf("vs IA ou vs Player ?\n");
            reset();
            purple();
            printf("1. vsIA\n");
            reset();
            yellow();
            printf("2. vsPlayer\n");
            reset();
            scanf("%d", &vsChoice);

            switch (vsChoice) {
                case 1:
                    launchGame(map_3.grid, map_3, ptrTurn, vsChoice);
                    break;
                case 2:
                    launchGame(map_3.grid, map_3, ptrTurn, vsChoice);
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

            for (int i = 0; i < map_3.row; i++)
                free(map_3.grid[i]);
            free(map_3.grid);
            break;

        case 4:
            filename = "mapTest.txt";
            fptr = NULL;

            if ((fptr = fopen(filename, "r")) == NULL) {
                fprintf(stderr, "error opening %s\n", filename);
                exit(-1);
            }
            //MAP Test
            //ASSIGNATION DE LA MAP Test
            map_Test.grid = malloc(map_Test.row * sizeof(char *));
            for (int i = 0; i < map_Test.row; i++)
                map_Test.grid[i] = malloc(map_Test.column * sizeof(char));
            //INITIALISATION DE LA MAP Test
            for (int i = 0; i < map_Test.row; i++)
                for (int j = 0; j < map_Test.column; j++) {
                    line = fgetc(fptr);
                    if (line == EOF) break;
                    if (line != '\n') {
                        map_Test.grid[i][j] = line;
                    } else {
                        j--;
                    }
                }
            fclose(fptr);


            //Choix vs ia ou vs player //
            blue();
            printf("\n vs IA ou vs Player ?\n");
            reset();
            purple();
            printf("1. vsIA\n");
            reset();
            yellow();
            printf("2. vsPlayer\n");
            reset();
            scanf("%d", &vsChoice);

            switch (vsChoice) {
                case 1:
                    launchGame(map_Test.grid, map_Test, ptrTurn, vsChoice);
                    break;
                case 2:
                    launchGame(map_Test.grid, map_Test, ptrTurn, vsChoice);
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

            //launchGame(map_1.grid, map_1, ptrTurn);
            for (int i = 0; i < map_Test.row; i++)
                free(map_Test.grid[i]);

            free(map_Test.grid);
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

void launchGame(char **grid, Map map, int *ptrTurn, int vsChoice) {

    switch (vsChoice) {
        case 1:

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
            changeGrid(grid, map, ptrTurn, vsChoice);

            //relaunch the function
            clearStdin();
            clearTerminal();
            //launchGame(grid, map, ptrTurn);

//    for (int i = 0; i < map.row; i++)
//        free(map.grid[i]);
//    free(map.grid);

            break;
        case 2:

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
            changeGrid(grid, map, ptrTurn, vsChoice);

            //relaunch the function
            clearStdin();
            clearTerminal();
            //launchGame(grid, map, ptrTurn);

//    for (int i = 0; i < map.row; i++)
//        free(map.grid[i]);
//    free(map.grid);

            break;
    }
}


void setOptions() {}


void quitGame() {
    printf("Merci d'avoir joué !\n");
    //deleteBomb(Bomb *bomb);
    exit(0);
}

void changeGrid(char **gameGrid, Map map, int *ptrTurn, int vsChoice) {

    //Bomb *listBomb;
    Liste *ListeDesBombes = init();
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

    // Lance code player VS player si 2 et lance code VS ia si 1
    switch (vsChoice) {
        case 1: // ia
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
                                //printf("position de recherche = %d %d\n", i, j);
                                //printf("(char)*ptrTurn = %c\n", turn);
                                //printMap(gameGrid[i][j]);
                                if (gameGrid[i][j] == turn) {
                                    //printf("Joueur trouvé a %d %d\n", i, j);
                                    //printf("COUCOU2");
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
                                    //printf("Joueur trouvé a %d %d\n", i, j);
                                    if (gameGrid[i + 1][j] == 'O') {
                                        gameGrid[i][j] = 'O';
                                        gameGrid[i + 1][j] = turn;
                                        //printf("DESCENDU");
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
                                    //printf("Joueur trouvé a %d %d\n", i, j);
                                    if (gameGrid[i][j + 1] == 'O') {
                                        gameGrid[i][j] = 'O';
                                        gameGrid[i][j + 1] = turn;
                                        //printf("DROITE");
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
                        if (moveLeft > 1) {
                            printf("Choisissez votre déplacement : ");
                            char bombMove;
                            scanf(" %c", &bombMove);
                            printf("Déplacement choisi : (%c)\n", bombMove);
                            switch (bombMove) {
                                case 'Z':
                                    for (int i = 0; i < map.row; i++) {
                                        for (int j = 0; j < map.column; j++) {
                                            if (gameGrid[i][j] == turn) {
                                                if (gameGrid[i - 1][j] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);
                                                    gameGrid[i - 1][j] = turn;

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
                                case 'Q':
                                    for (int i = 0; i < map.row; i++) {
                                        for (int j = 0; j < map.column; j++) {
                                            if (gameGrid[i][j] == turn) {
                                                if (gameGrid[i][j - 1] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);
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
                                                if (gameGrid[i + 1][j] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);
                                                    gameGrid[i + 1][j] = turn;
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
                                    for (int i = 0; i < map.row; i++) {
                                        for (int j = 0; j < map.column; j++) {
                                            if (gameGrid[i][j] == turn) {
                                                if (gameGrid[i][j + 1] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);

                                                    gameGrid[i][j + 1] = turn;
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

                            }
                        } else {
                            printf("Vous ne pouvez pas poser de bombe\n");
                        }
                        break;




                }
                //explodeBomb(listBomb, gameGrid);
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
                    case 1: // Place au BOT
                        *ptrTurn = 2;
                        turn = '2';
                        moveLeft=4;
                        int posJ1x;
                        int posJ1y;
                        int posJ2x;
                        int posJ2y;
                            // déplacer le bot
                            for (int i = 0; i < map.row; i++) {
                                for (int j = 0; j < map.column; j++) {
                                    if (gameGrid[i][j]=='1'){
                                        posJ1x = i; // récup pos joueurs
                                        posJ1y = j;
                                    }
                                    if (gameGrid[i][j]=='2'){
                                        posJ2x = i; // récup pos joueurs
                                        posJ2y = j;
                                    }

                                    if (gameGrid[i][j] == turn) {
                                    while (moveLeft > 0) { // bouge vers le joueur tant qu'il y a des moubLeft
                                        /**if ((gameGrid[posJ2x - 1][posJ2y] == gameGrid[posJ1x][posJ1y]) || // pose une bombe si distance joueur = 1
                                            (gameGrid[posJ2x][posJ2y - 1] == gameGrid[posJ1x][posJ1y]) ||
                                            (gameGrid[posJ2x + 1][posJ2y] == gameGrid[posJ1x][posJ1y]) ||
                                            (gameGrid[posJ2x][posJ2y + 1] == gameGrid[posJ1x][posJ1y])) {
                                            listBomb = addBomb(listBomb, posJ2y, posJ2x, 2, 3);
                                            moveLeft--;
                                            break;
                                        }
                                        if ((gameGrid[posJ2x - 2][posJ2y] == gameGrid[posJ1x][posJ1y]) || // pose une bombe si distance joueur = 2
                                            (gameGrid[posJ2x][posJ2y - 2] == gameGrid[posJ1x][posJ1y]) ||
                                            (gameGrid[posJ2x + 2][posJ2y] == gameGrid[posJ1x][posJ1y]) ||
                                            (gameGrid[posJ2x][posJ2y + 2] == gameGrid[posJ1x][posJ1y])) {
                                            listBomb = addBomb(listBomb, posJ2y, posJ2x, 2, 3);
                                            moveLeft--;
                                            break;
                                        }**/
                                        if (posJ2x > posJ1x) {
                                            //printf("Joueur trouvé a %d %d\n", i, j);
                                            if (gameGrid[posJ2x - 1][posJ2y] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x - 1][posJ2y] = turn;
                                                posJ2x--;
                                                moveLeft--;
                                            } else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        } else if (posJ2x < posJ1x) {
                                            //printf("Joueur trouvé a %d %d\n", i, j);
                                            if (gameGrid[posJ2x + 1][posJ2y] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x + 1][posJ2y] = turn;
                                                posJ2x++;
                                                moveLeft--;
                                            } else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        } else if (posJ2y > posJ1y) {
                                            //printf("Joueur trouvé a %d %d\n", i, j);
                                            if (gameGrid[posJ2x][posJ2y - 1] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x][posJ2y - 1] = turn;
                                                posJ2y--;
                                                moveLeft--;
                                            } else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        } else if (posJ2y < posJ1y) {
                                            //printf("Joueur trouvé a %d %d\n", i, j);
                                            if (gameGrid[posJ2x][posJ2y + 1] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x][posJ2y + 1] = turn;
                                                posJ2y++;
                                                moveLeft--;
                                            } else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        }
                                    }
                                        //explodeBomb(listBomb, gameGrid); // fait exploser les bombes
                                    }
                                    /** if (gameGrid[i][j] == turn) {
                                        printf("Joueur trouvé a %d %d\n", i, j);
                                        if (gameGrid[i][j - 1] == 'O') {
                                            gameGrid[i][j] = 'O';
                                            gameGrid[i][j - 1] = turn;
                                            moveLeft--;
                                            break;
                                        } else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    } **/

                                }
                            }
                        /** while (moveLeft > 0){
                            if (gameGrid[posJ2x][posJ2y] == turn) {
                                //printf("Joueur trouvé a %d %d\n", i, j);
                                if (posJ2y> posJ1y){
                                    if (gameGrid[posJ2x][posJ2y - 1] == '0'){
                                        printf("gnrhjf");
                                    }
                                }
                                if ((posJ2y > posJ1y) && (gameGrid[posJ2x][posJ2y - 1] == '0')) {
                                    gameGrid[posJ2x][posJ2y] = 'O';
                                    gameGrid[posJ2x][posJ2y - 1] = turn;
                                    moveLeft--;
                                    break;
                                } else {
                                    invalidMove = 1;
                                    break;
                                }

                                if (posJ2y < posJ1y && posJ2y + 1 == '0') {
                                    gameGrid[posJ2x][posJ2y] = 'O';
                                    gameGrid[posJ2x][posJ2y + 1] = turn;
                                    moveLeft--;
                                    break;
                                } else {
                                    invalidMove = 1;
                                    break;
                                }

                                if (posJ2x > posJ1x && posJ2x - 1 == '0') {
                                    gameGrid[posJ2x][posJ2y] = 'O';
                                    gameGrid[posJ2x - 1][posJ2y] = turn;
                                    moveLeft--;
                                    break;
                                } else {
                                    invalidMove = 1;
                                    break;
                                }

                                if (posJ2x < posJ1x && posJ2x + 1 == '0') {
                                    gameGrid[posJ2x][posJ2y] = 'O';
                                    gameGrid[posJ2x + 1][posJ2y] = turn;
                                    moveLeft--;
                                    break;
                                } else {
                                    invalidMove = 1;
                                    break;
                                }
                            }
                        } **/
                            /** while (moveLeft>0){
                                if (posJ2x>posJ1x){
                                    if (gameGrid[posJ2x][posJ2y - 1] == 'O') {
                                        gameGrid[posJ2x][posJ2y] = 'O';
                                        gameGrid[posJ2x][posJ2y - 1] = turn;
                                        moveLeft--;
                                    }
                                }
                        } **/

                        // déplace le bot d'une case à gauche
                        /** for (int i = 0; i < map.row; i++) {
                            for (int j = 0; j < map.column; j++) {
                                //printf("position de recherche = %d %d\n", i, j);
                                //printf("(char)*ptrTurn = %c\n", turn);
                                if (gameGrid[i][j] == turn) {
                                    printf("Joueur trouvé a %d %d\n", i, j);
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
                        } **/

                        //turn = 1;
                        *ptrTurn = 1;
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    /** case 2:
                        if (map.players == 2) {
                            *ptrTurn = 1;
                        } else {
                            *ptrTurn = 3;
                        }
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    case 3:
                        if (map.players == 3) {
                            *ptrTurn = 1;
                        } else {
                            *ptrTurn = 4;
                        }
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    case 4:
                        *ptrTurn = 1;
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    default:
                        break; **/
                }
            }
            break;


        case 2: // player

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
                        if (moveLeft > 1) {
                            printf("Choisissez votre déplacement : ");
                            char bombMove;
                            scanf(" %c", &bombMove);
                            printf("Déplacement choisi : (%c)\n", bombMove);
                            switch (bombMove) {
                                case 'Z':
                                    for (int i = 0; i < map.row; i++) {
                                        for (int j = 0; j < map.column; j++) {
                                            if (gameGrid[i][j] == turn) {
                                                if (gameGrid[i - 1][j] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);
                                                    gameGrid[i - 1][j] = turn;

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
                                case 'Q':
                                    for (int i = 0; i < map.row; i++) {
                                        for (int j = 0; j < map.column; j++) {
                                            if (gameGrid[i][j] == turn) {
                                                if (gameGrid[i][j - 1] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);
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
                                                if (gameGrid[i + 1][j] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);
                                                    gameGrid[i + 1][j] = turn;
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
                                    for (int i = 0; i < map.row; i++) {
                                        for (int j = 0; j < map.column; j++) {
                                            if (gameGrid[i][j] == turn) {
                                                if (gameGrid[i][j + 1] == 'O') {
                                                    gameGrid[i][j] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,i, j, 4, 3);

                                                    gameGrid[i][j + 1] = turn;
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

                            }
                        } else {
                            printf("Vous ne pouvez pas poser de bombe\n");
                        }
                        break;


                }
                //explodeBomb(listBomb, gameGrid);
//        if(listBomb->next != NULL){
//
//            decreaseBombTimer(listBomb, gameGrid);
//        }
                printf("decreased\n");
                decreaseBombTimer(ListeDesBombes, gameGrid);


                }
                //explodeBomb(listBomb, gameGrid);

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
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    case 2:
                        if (map.players == 2) {
                            *ptrTurn = 1;
                        } else {
                            *ptrTurn = 3;
                        }
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    case 3:
                        if (map.players == 3) {
                            *ptrTurn = 1;
                        } else {
                            *ptrTurn = 4;
                        }
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    case 4:
                        *ptrTurn = 1;
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
                    default:
                        break;
                }
            }
            break;

    }
}

Liste* init(){
    Liste* liste = malloc(sizeof(*liste));
    if(liste == NULL){
        exit(EXIT_FAILURE);
    }
    liste->premier = NULL;

    return liste;
}

void insertBomb(Liste* liste, int x, int y, int timer, int range){
    Bomb* nouveau = malloc(sizeof(*nouveau));
    if(liste == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->x = x;
    nouveau->y = y;
    nouveau->timer = timer;
    nouveau->range = range;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void decreaseBombTimer(Liste* liste, char** gameGrid){
    Bomb* bomb = liste->premier;
    printf("cassis\n");
    while(bomb != NULL){
        int condition = --(bomb->timer);
        printf("%d\n", condition);
        if(condition == 0){
            printf("3\n");
            explodeBomb(liste, gameGrid);
        }
        bomb = bomb->suivant;
    }
    printf("4\n");
}

void explodeBomb(Liste* liste, char** gameGrid){
    if(liste == NULL){
        exit(EXIT_FAILURE);
    }
    Bomb* actual = liste->premier;
//    while(actual != NULL){
//        if(actual->timer == 0){
//            actual->timer = -1;
//            gameGrid[actual->x][actual->y] = 'O';
//            for(int i = 1; i <= actual->range; i++){
//                if(gameGrid[actual->x][actual->y + i] == 'O'){
//                    gameGrid[actual->x][actual->y + i] = 'O';
//                } else if(gameGrid[actual->x][actual->y + i] == 'B'){
//                    gameGrid[actual->x][actual->y + i] = 'O';
//                } else if(gameGrid[actual->x][actual->y + i] == '1'){
//                    gameGrid[actual->x][actual->y + i] = 'O';
//                } else if(gameGrid[actual->x][actual->y + i] == '2'){
//                    gameGrid[actual->x][actual->y + i] = 'O';
//                } else if(gameGrid[actual->x][actual->y + i] == '3'){
//                    gameGrid[actual->x][actual->y + i] = 'O';
//                } else if(gameGrid[actual->x][actual->y + i] == '4'){
//                    gameGrid[actual->x][actual->y + i] = 'O';
//                } else {
//                    break;
//                }
//            }
//            for(int i = 1; i <= actual->range; i++){
//                if(gameGrid[actual->x][actual->y - i] == 'O'){
//                    gameGrid[actual->x][actual->y - i] = 'O';
//                } else if(gameGrid[actual->x][actual->y - i] == 'B'){
//                    gameGrid[actual->x][actual->y - i] = 'O';
//                } else if(gameGrid[actual->x][actual->y - i] == '1'){
//                    gameGrid[actual->x][actual->y - i] = 'O';
//                } else if(gameGrid[actual->x][actual->y - i] == '2'){
//                    gameGrid[actual->x][actual->y - i] = 'O';
//                } else if(gameGrid[actual->x][actual->y - i] == '3'){
//                    gameGrid[actual->x][actual->y - i] = 'O';
//                } else if(gameGrid[actual->x][actual->y - i] == '4'){
//                    gameGrid[actual->x][actual->y - i] = 'O';
//                } else {
//                    break;
//                }
//            }
//            for(int i = 1; i <= actual->range; i++){
//                if(gameGrid[actual->x + i][actual->y] == 'O'){
//                    gameGrid[actual->x + i][actual->y] = 'O';
//                } else if(gameGrid[actual->x + i][actual->y] == 'B'){
//                    gameGrid[actual->x + i][actual->y] = 'O';
//                } else if(gameGrid[actual->x + i][actual->y] == '1'){
//                    gameGrid[actual->x + i][actual->y] = 'O';
//                } else if(gameGrid[actual->x + i][actual->y] == '2'){
//                    gameGrid[actual->x + i][actual->y] = 'O';
//                } else if(gameGrid[actual->x + i][actual->y] == '3'){
//                    gameGrid[actual->x + i][actual->y] = 'O';
//                } else if(gameGrid[actual->x + i][actual->y] == '4'){
//                    gameGrid[actual->x + i][actual->y] = 'O';
//                } else {
//                    break;
//                }
//            }
//            for(int i = 1; i <= actual->range; i++){
//                if(gameGrid[actual->x - i][actual->y] == 'O'){
//                    gameGrid[actual->x - i][actual->y] = 'O';
//                } else if(gameGrid[actual->x - i][actual->y] == 'B'){
//                    gameGrid[actual->x - i][actual->y] = 'O';
//                } else if(gameGrid[actual->x - i][actual->y] == '1'){
//                    gameGrid[actual->x - i][actual->y] = 'O';
//                } else if(gameGrid[actual->x - i][actual->y] == '2'){
//                    gameGrid[actual->x - i][actual->y] = 'O';
//                } else if(gameGrid[actual->x - i][actual->y] == '3'){
//                    gameGrid[actual->x - i][actual->y] = 'O';
//                } else if(gameGrid[actual->x - i][actual->y] == '4'){
//                    gameGrid[actual->x - i][actual->y] = 'O';
//                } else {
//                    break;
//                }
//            }
//        }
//        actual = actual->suivant;
//    }

    while(actual != NULL){
        if(actual->timer == 0){
            gameGrid[actual->x][actual->y] = 'O';
            //check left
            actual->timer = -1;
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x][actual->y - i] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x][actual->y - i] == 'M'){
                    gameGrid[actual->x][actual->y - i] = 'O';
                    break;
                }
                else if(gameGrid[actual->x][actual->y - i] == '1' || gameGrid[actual->x][actual->y - i] == '2' || gameGrid[actual->x][actual->y - i] == '3' || gameGrid[actual->x][actual->y - i] == '4'){
                    gameGrid[actual->x][actual->y - i] = 'O';
                    break;
                }
            }
            //check right
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x][actual->y + i] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x][actual->y + i] == 'M'){
                    gameGrid[actual->x][actual->y + i] = 'O';
                    break;
                }
                else if(gameGrid[actual->x][actual->y + i] == '1' || gameGrid[actual->x][actual->y + i] == '2' || gameGrid[actual->x][actual->y + i] == '3' || gameGrid[actual->x][actual->y + i] == '4'){
                    gameGrid[actual->x][actual->y + i] = 'O';
                    break;
                }
            }
            //check up
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x - i][actual->y] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x - i][actual->y] == 'M'){
                    gameGrid[actual->x - i][actual->y] = 'O';
                    break;
                }
                else if(gameGrid[actual->x - i][actual->y] == '1' || gameGrid[actual->x - i][actual->y] == '2' || gameGrid[actual->x - i][actual->y] == '3' || gameGrid[actual->x - i][actual->y] == '4'){
                    gameGrid[actual->x - i][actual->y] = 'O';
                    break;
                }
            }
            //check down
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x + i][actual->y] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x + i][actual->y] == 'M'){
                    gameGrid[actual->x + i][actual->y] = 'O';
                    break;
                }
                else if(gameGrid[actual->x + i][actual->y] == '1' || gameGrid[actual->x + i][actual->y] == '2' || gameGrid[actual->x + i][actual->y] == '3' || gameGrid[actual->x + i][actual->y] == '4'){
                    gameGrid[actual->x + i][actual->y] = 'O';
                    break;
                }
            }

            actual = actual->suivant;
        }
//        if(currentBomb == NULL){
//            break;
//        }

    }
}

void deleteBomb(Liste *liste){
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while(liste->premier != NULL)
    {
        Bomb *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}









