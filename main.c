#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "struct.h"
#define MAX_LEN 256

Liste* init();
void insertBomb(Liste* liste, int x, int y, int timer, int range, int owner);
void decreaseBombTimer(Liste* liste, char** gameGrid, ListePlayer* ListeDesJoueurs);
void explodeBomb(Liste *liste, char **gameGrid, ListePlayer *listPlayer);
void setBombTimerToZero(Liste* liste, int x, int y);
void deleteBomb(Liste *liste);


ListePlayer* initPlayer();
void insertPlayer(ListePlayer* liste, int x, int y, int id, int isAlive, int isBot, int bomb, int flameRange, int life, int heart, int invincible);
void deletePlayer(ListePlayer *liste);
void modifyPlayer(ListePlayer *liste, int id, int x, int y, int isAlive, int bomb, int flameRange, int life, int heart, int invincible);

void checkIfWin(Map map, char** gameGrid, Liste *ListeDesBombes, ListePlayer* ListeDesJoueurs);
void checkIfPlayerCanPlay(Map map, char** gameGrid, int* ptrTurn);
int checkIfPlayerCanMove(char** gameGrid, Map map, char direction, char turn, int isBomb, Liste* ListeDesBombes, ListePlayer* ListeDesJoueurs);
void checkIfPlayerCanRevive(ListePlayer* ListeDesJoueurs, char** gameGrid, Map map);
int getRangePlayer(ListePlayer* ListeDesJoueurs, int id);
int getBombPlayer(ListePlayer* ListeDesJoueurs, int id);
int getIsBotPlayer(ListePlayer* ListeDesJoueurs, int id);
void getBonus(ListePlayer* liste, char turn);

int botAction(char **gameGrid, Map map, char turn, Liste *ListeDesBombes, ListePlayer* ListeDesJoueurs, int moveLeft);

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

void randomMap(); // Adrien

void printMap(char letter);

void printAllMaps();

void changeGrid(char **gameGrid, Map map, int *ptrTurn, int botChoice);


int main() {
    printf("Bienvenu dans Bomberm...Casse briques !\n");

    startMenu();
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
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", filename);
        return;
    }

    print_image(fptr);

    fclose(fptr);
}

void clearTerminal() {
    printf("\033[2J\033[1;1H\n");

}

void clearStdin() {
    while (getchar() != '\n');
}

void startMenu() {
    showLogo();
    green();
    printf("1. Jouer\n");
    reset();
//    printf("coeur : \u2661 \u2665 \n");
    red();
    printf("2. Quitter\n");
    reset();
    blue();
    printf("3. Générer une map random\n"); // Adrien
    reset();

    int choice;
    scanf("%d", &choice);
    clearTerminal();
    switch (choice) {
        case 1:
            chooseMap();
            break;
        case 2:
            quitGame();
            break;
        case 3:
            randomMap(); // Adrien
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

void randomMap() { // Adrien
    const char* filename = "mapRandom.txt";
    const char *str = "X";
    FILE* output_file = fopen(filename, "w+");
    if (!output_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int l;
    int L;
    printf("Entrer taille tableau l et L\n");
    printf("Longeur : \n");
    scanf("%d", &l);
    printf("Largeur : \n");
    scanf("%d", &L);
    clearTerminal();
    //int Tab[l][L];
    srand(time(NULL));
    for (int i = 0; i <= l; i++) {
        for (int j = 0; j <= L; j++) {
            int randomBloc = rand() % 100;
            if ((i == 1) && (j == 1)) {
                const char *str = "1";
                fwrite(str, 1, strlen(str), output_file);
            } else if ((i == 2) && (j == 1)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            } else if ((i == 1) && (j == 2)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == 3) && (j == 1)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == 1) && (j == 3)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == 2) && (j == 2)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == l-1) && (j == L-1)) {
                const char *str = "2";
                fwrite(str, 1, strlen(str), output_file);
            } else if ((i == l-2) && (j == L-1)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            } else if ((i == l-1) && (j == L-2)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            } else if ((i == l-3) && (j == L-1)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == l-1) && (j == L-3)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == l-2) && (j == l-2)) {
                const char *str = "O";
                fwrite(str, 1, strlen(str), output_file);
            }else if ((i == 0) || (j == 0)) {
                //Tab[i][j] == 'X';
                const char *str = "X";
                fwrite(str, 1, strlen(str), output_file);
                if (j==L) {
                    const char *str = "\n";
                    fwrite(str, 1, strlen(str), output_file);
                }
            } else if ((i == l) || (j == L)) {
                //Tab[i][j] = 'X';
                const char *str = "X";
                fwrite(str, 1, strlen(str), output_file);
                if (j==L) {
                    const char *str = "\n";
                    fwrite(str, 1, strlen(str), output_file);
                }
            } else {
                if (randomBloc >=0 && randomBloc <= 50) {
                    const char *str = "M";
                    fwrite(str, 1, strlen(str), output_file);
                } else if (randomBloc >50 && randomBloc <= 100) {
                    const char *str = "O";
                    fwrite(str, 1, strlen(str), output_file);
                }
                //Tab[i][j] == 'O';
            }
            //printf("%c", Tab[i][j]);
            printf("Done Writing!\n");
        }
    }

    fclose(output_file);
    exit(EXIT_SUCCESS);
    startMenu();
}

void chooseMap() {

    printAllMaps();
    int turn = 1;
    int *ptrTurn = &turn;
    printf("Choisissez une map (1 à 5, 4 = test, 5 = random):\n");
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
                fprintf(stderr, "Erreur d'ouverture du fichier %s\n", filename);
                exit(-1);
            }
            map_1.grid = malloc(map_1.row * sizeof(char *));
            for (int i = 0; i < map_1.row; i++)
                map_1.grid[i] = malloc(map_1.column * sizeof(char));
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
            map_2.grid = malloc(map_2.row * sizeof(char *));
            for (int i = 0; i < map_2.row; i++)
                map_2.grid[i] = malloc(map_2.column * sizeof(char));
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
            map_3.grid = malloc(map_3.row * sizeof(char *));
            for (int i = 0; i < map_3.row; i++)
                map_3.grid[i] = malloc(map_3.column * sizeof(char));
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
            fclose(fptr);
            launchGame(map_3.grid, map_3, ptrTurn);
            for (int i = 0; i < map_3.row; i++)
                free(map_3.grid[i]);
            free(map_3.grid);
            break;
        case 5:
            filename = "mapRandom.txt";
            fptr = NULL;

            if ((fptr = fopen(filename, "r")) == NULL) {
                fprintf(stderr, "error opening %s\n", filename);
                exit(-1);
            }
            //MAP 1
            //ASSIGNATION DE LA MAP 1
            map_Random.grid = malloc(map_Random.row * sizeof(char *));
            for (int i = 0; i < map_Random.row; i++)
                map_Random.grid[i] = malloc(map_Random.column * sizeof(char));
            //INITIALISATION DE LA MAP 1
            for (int i = 0; i < map_Random.row; i++)
                for (int j = 0; j < map_Random.column; j++) {
                    line = fgetc(fptr);
                    if (line == EOF) break;
                    if (line != '\n') {
                        map_Random.grid[i][j] = line;
                    } else {
                        j--;
                    }
                }
            fclose(fptr);
            launchGame(map_Random.grid, map_Random, ptrTurn);
            for (int i = 0; i < map_Random.row; i++)
                free(map_Random.grid[i]);

            free(map_Random.grid);
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
    yellow();
    printf("\nAttribut :\n");
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
    yellow();
    printf("\nAttribut :\n");
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
    yellow();
    printf("\nAttribut :\n");
    printf("Nombre de bombes par défaut : %d\n", map_3.bomb);
    printf("Taille de la grille : %dx%d\n", map_3.row, map_3.column);
    printf("Nombre de joueurs maximal : %d\n\n", map_3.players);
    reset();

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
        case 'S':
            blue();
            printf("\u0fcc ");
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
    for (int i = 0; i < map.row; i++) {
        for (int j = 0; j < map.column; j++) {
            printMap(grid[i][j]);
            if (j == map.column - 1) {
                printf("\n");
            }
        }
    }
    printf("\n");
    yellow();
    printf("Nombre de bombes par défaut : %d\n", map.bomb);
    printf("Commandes :\n");
    printf("1. Déplacer le joueur : Z = haut, S = bas, Q = gauche, D = droite\n");
    printf("2. Poser une bombe : B\n");
    printf("3. Abandonner : A\n");
    printf("4. Finir le tour avant la fin des mouvements : P\n\n");
    blue();
    printf("Voulez vous jouer en Joueur VS Joueur, ou Joueur vs Bot?\n");
    printf("1. Joueur VS Joueur\n");
    printf("2. Joueur VS Bot\n");
    reset();
    int botChoice;
    scanf("%d", &botChoice);
    clearStdin();
    clearTerminal();
    changeGrid(grid, map, ptrTurn, botChoice);
    clearStdin();
    clearTerminal();
}


void setOptions() {}


void quitGame() {
    printf("Merci d'avoir joué !\n");
    exit(0);
}

void changeGrid(char **gameGrid, Map map, int *ptrTurn, int botChoice) {
    Liste *ListeDesBombes = init();
    ListePlayer* ListeDesJoueurs = initPlayer();

    for(int x = 0; x < map.players; x++){
        int playerInt = x + 1;
        int isBot = 0;
        char playerChar = playerInt + '0';
        for (int i = 0; i < map.row; i++) {
            for (int j = 0; j < map.column; j++) {
                if(gameGrid[i][j] == playerChar) {
                    printf("Le joueur %d a été placé %d, %d\n", playerInt, i, j);
                    if(playerInt==1 && botChoice==2){
                        isBot = 0;
                    }else if (botChoice==1){
                        isBot = 0;
                    }else{
                        isBot = 1;
                    }
                    insertPlayer(ListeDesJoueurs, i, j, playerInt, 1, isBot, map.bomb, 0, 0, 0, 0);
                }

            }
        }
    }

    char choosedAction;
    int moveLeft = map.move;
    int bombLeft = map.bomb;
    int playerBomb = 0;
    int verifyMove = 0;
    int isBomb = 0;
    int invalidMove = 0;
    int invalidChar = 0;
    char turn;
    int botValidation = 0;
    while (moveLeft > 0) {
        yellow();
        printf("Tour du joueur %d\n", *ptrTurn);
        reset();
        checkIfPlayerCanPlay(map, gameGrid, ptrTurn);
        turn = *ptrTurn + '0';
        playerBomb = getBombPlayer(ListeDesJoueurs, *ptrTurn);
        int isBot = getIsBotPlayer(ListeDesJoueurs, *ptrTurn);
        red();
        if(playerBomb == 1){
            printf("Le joueur %c à %d bombe restante\n", turn, playerBomb);
        } else{
            printf("Le joueur %c à %d bombes restantes\n", turn, playerBomb);
        }
        reset();
        for (int i = 0; i < map.row; i++) {
            for (int j = 0; j < map.column; j++) {
                printMap(gameGrid[i][j]);
                if (j == map.column - 1) {
                    printf("\n");
                }
            }
        }
        if(moveLeft>2){
            green();
        }else{
            red();
        }
        if(moveLeft==1){
            printf("Vous avez %d mouvement restant\n", moveLeft);
        }else{
            printf("Vous avez %d mouvements restants\n", moveLeft);
        }
        reset();
//        if (invalidMove == 1) {
//            red();
//            printf("Vous ne pouvez pas vous déplacer ici\n");
//            reset();
//            invalidMove = 0;
//        }
        printf("Joueur %d, choisissez vos actions : ", *ptrTurn);
        //TODO: EMPECHER LE BOT DE SCANF
        if( isBot == 0 ){
            scanf(" %c", &choosedAction);
        }else{
            botValidation = botAction(gameGrid, map, turn, ListeDesBombes, ListeDesJoueurs, moveLeft);
            if(botValidation == 1){
                moveLeft = 0;
                invalidMove = 0;
            }

        }
        if(moveLeft != 0){
            switch (toupper(choosedAction)) {
                case 'A':
                    quitGame();
                    break;
                case 'P':
                    printf("Vous avez fini votre tour\n");
                    *ptrTurn = *ptrTurn + 1;
                    if (*ptrTurn > map.players) {
                        *ptrTurn = 1;
                    }
                    moveLeft = map.move;
                    break;
                case 'Z':
                    verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(choosedAction), turn, 0, ListeDesBombes, ListeDesJoueurs);
                    if(verifyMove == 1) {
                        moveLeft--;
                    } else {
                        invalidMove = 1;
                    }
                    break;
                case 'Q':
                    verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(choosedAction), turn, 0, ListeDesBombes, ListeDesJoueurs);
                    if(verifyMove == 1) {
                        moveLeft--;
                    } else {
                        invalidMove = 1;
                    }
                    break;
                case 'S':
                    verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(choosedAction), turn, 0, ListeDesBombes, ListeDesJoueurs);
                    if(verifyMove == 1) {
                        moveLeft--;
                    } else {
                        invalidMove = 1;
                    }
                    break;
                case 'D':
                    verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(choosedAction), turn, 0, ListeDesBombes, ListeDesJoueurs);
                    if(verifyMove == 1) {
                        moveLeft--;
                    } else {
                        invalidMove = 1;
                    }
                    break;
                case 'B':
                    if (moveLeft > 1 && playerBomb > 0) {
                        printf("Choisissez votre déplacement : \n");
                        char bombMove;
                        scanf(" %c", &bombMove);
                        switch (toupper(bombMove)) {
                            case 'Z':
                                verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(bombMove), turn, 1, ListeDesBombes, ListeDesJoueurs);
                                if(verifyMove == 1) {
                                    moveLeft--;
                                } else {
                                    invalidMove = 1;
                                }
                                break;
                            case 'Q':
                                verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(bombMove), turn, 1, ListeDesBombes, ListeDesJoueurs);
                                if(verifyMove == 1) {
                                    moveLeft--;
                                } else {
                                    invalidMove = 1;
                                }
                                break;
                            case 'S':
                                verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(bombMove), turn, 1, ListeDesBombes, ListeDesJoueurs);
                                if(verifyMove == 1) {
                                    moveLeft--;
                                } else {
                                    invalidMove = 1;
                                }
                                break;
                            case 'D':
                                verifyMove = checkIfPlayerCanMove(gameGrid, map, toupper(bombMove), turn, 1, ListeDesBombes, ListeDesJoueurs);
                                if(verifyMove == 1) {
                                    moveLeft--;
                                } else {
                                    invalidMove = 1;
                                }
                                break;
                            default:
                                red();
                                printf("Votre bombe n'a pas pu être placée\n");
                                reset();
                                invalidMove = 1;
                                break;

                        }
                    } else {
                        printf("Vous ne pouvez pas poser de bombe.\n");
                    }
                    break;
                default:
                    red();
                    printf("Votre déplacement n'est pas valide\n");
                    reset();
                    invalidMove = 1;
                    invalidChar = 1;
                    break;


            }
        }
        printf("Vous avez %d déplacements restants\n", moveLeft);
        clearTerminal();
        verifyMove = 0;
        isBomb = 0;
        if (invalidMove ==0) {
            decreaseBombTimer(ListeDesBombes, gameGrid, ListeDesJoueurs);
            checkIfPlayerCanRevive(ListeDesJoueurs, gameGrid, map);
            checkIfWin(map, gameGrid, ListeDesBombes, ListeDesJoueurs);
        }else{
            red();
            printf("Vous ne pouvez pas vous déplacer ici\n");
            if (invalidChar == 1) {
                printf("Vous avez entré un caractère invalide\n");
            }
            reset();
            invalidMove = 0;
            invalidChar = 0;
        }
        if (moveLeft == 0) {
            *ptrTurn = *ptrTurn + 1;
            if (*ptrTurn > map.players) {
                *ptrTurn = 1;
            }
            moveLeft = map.move;
        }
        fflush(stdin);
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

ListePlayer* initPlayer(){
    ListePlayer* liste = malloc(sizeof(*liste));
    if(liste == NULL){
        exit(EXIT_FAILURE);
    }
    liste->premier = NULL;

    return liste;
}

void insertBomb(Liste* liste, int x, int y, int timer, int range, int owner){
    Bomb* nouveau = malloc(sizeof(*nouveau));
    if(liste == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->x = x;
    nouveau->y = y;
    nouveau->timer = timer;
    nouveau->range = range;
    nouveau->owner = owner;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void insertPlayer(ListePlayer* liste, int x, int y, int id, int isAlive, int isBot, int bomb, int flameRange, int life, int heart, int invincible){
    Player* nouveau = malloc(sizeof(*nouveau));
    if(liste == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->x = x;
    nouveau->y = y;
    nouveau->id = id;
    nouveau->isAlive = isAlive;
    nouveau->isBot = isBot;
    nouveau->bomb = bomb;
    nouveau->flameRange = flameRange;
    nouveau->life = life;
    nouveau->heart = heart;
    nouveau->invincible = invincible;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}



void decreaseBombTimer(Liste* liste, char** gameGrid, ListePlayer* ListeDesJoueurs){
    Bomb* bomb = liste->premier;
    if(bomb == NULL){
        return;
    }
    while(bomb != NULL){
        int condition = --(bomb->timer);
        if(condition == 0){
            printf("Explosion\n");
            explodeBomb(liste, gameGrid, ListeDesJoueurs);
        }
        bomb = bomb->suivant;
    }
}

void modifyPlayer(ListePlayer* liste, int id, int x, int y, int isAlive, int bomb, int flameRange, int life, int heart, int invincible){
    Player* player = liste->premier;
    while(player != NULL){
        if(player->id == id){
            if(x != -1){
                player->x = x;
            }
            if(y != -1){
                player->y = y;
            }
            if(isAlive != -1){
                player->isAlive = isAlive;
            }
            player->bomb = player->bomb + bomb;
            player->flameRange = player->flameRange + flameRange;
            player->life = player->life + life;
            if(player->heart != -1 && player->heart != 1){
                player->heart = heart;
            }
            player->invincible = invincible;
        }
        player = player->suivant;
    }
}

void explodeBomb(Liste* liste, char** gameGrid, ListePlayer* ListeDesJoueurs){
    int tauxDropBonus = 100;
    int owner = 0;
    if(liste == NULL){
        exit(EXIT_FAILURE);
    }
    Bomb* actual = liste->premier;
    srand ( time(NULL) );
    int randomBonus = 0;
    while(actual != NULL){
        if(actual->timer == 0){
            owner = actual->owner;
            gameGrid[actual->x][actual->y] = 'O';
            modifyPlayer(ListeDesJoueurs, owner, -1, -1, -1, 1, 0, 0, 0, 0);
            actual->timer = -1;
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x][actual->y - i] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x][actual->y - i] == 'M'){
                    randomBonus = rand() % 100;
                    if(randomBonus > tauxDropBonus){
                        gameGrid[actual->x][actual->y - i] = 'S';
                    }else{
                        gameGrid[actual->x][actual->y - i] = 'O';
                    }
                    break;
                }
                else if(gameGrid[actual->x][actual->y - i] == '1' || gameGrid[actual->x][actual->y - i] == '2' || gameGrid[actual->x][actual->y - i] == '3' || gameGrid[actual->x][actual->y - i] == '4'){
                    int deadPlayer = gameGrid[actual->x][actual->y - i] - '0';
                    modifyPlayer(ListeDesJoueurs, deadPlayer, -1, -1, 0, 0, 0, 0, 0, 0);
                    gameGrid[actual->x][actual->y - i] = 'O';
                    break;
                }else if(gameGrid[actual->x][actual->y - i] == 'B'){
                    setBombTimerToZero(liste, actual->x, actual->y - i);
                    explodeBomb(liste, gameGrid, ListeDesJoueurs);
                }
            }
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x][actual->y + i] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x][actual->y + i] == 'M'){
                    randomBonus = rand() % 100;
                    if(randomBonus > tauxDropBonus){
                        gameGrid[actual->x][actual->y + i] = 'S';
                    }else{
                        gameGrid[actual->x][actual->y + i] = 'O';
                    }
                    break;
                }
                else if(gameGrid[actual->x][actual->y + i] == '1' || gameGrid[actual->x][actual->y + i] == '2' || gameGrid[actual->x][actual->y + i] == '3' || gameGrid[actual->x][actual->y + i] == '4'){
                    int deadPlayer = gameGrid[actual->x][actual->y + i] - '0';
                    printf("Le joueur %d est mort\n", deadPlayer);
                    modifyPlayer(ListeDesJoueurs, deadPlayer, -1, -1, 0, 0, 0, 0, 0, 0);
                    gameGrid[actual->x][actual->y + i] = 'O';
                    break;
                }else if(gameGrid[actual->x][actual->y + i] == 'B'){
                    setBombTimerToZero(liste, actual->x, actual->y - i);
                    explodeBomb(liste, gameGrid, ListeDesJoueurs);
                }
            }
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x - i][actual->y] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x - i][actual->y] == 'M'){
                    randomBonus = rand() % 100;
                    if(randomBonus > tauxDropBonus){
                        gameGrid[actual->x-i][actual->y] = 'S';
                    }else{
                        gameGrid[actual->x-i][actual->y] = 'O';
                    }
                    break;
                }
                else if(gameGrid[actual->x - i][actual->y] == '1' || gameGrid[actual->x - i][actual->y] == '2' || gameGrid[actual->x - i][actual->y] == '3' || gameGrid[actual->x - i][actual->y] == '4'){
                    int deadPlayer = gameGrid[actual->x - i][actual->y] - '0';
                    printf("Le joueur %d est mort\n", deadPlayer);
                    modifyPlayer(ListeDesJoueurs, deadPlayer, -1, -1, 0, 0, 0, 0, 0, 0);
                    gameGrid[actual->x - i][actual->y] = 'O';
                    break;
                }else if(gameGrid[actual->x - i][actual->y] == 'B'){
                    setBombTimerToZero(liste, actual->x, actual->y - i);
                    explodeBomb(liste, gameGrid, ListeDesJoueurs);
                }
            }
            for(int i = 1; i <= actual->range-1; i++){
                if(gameGrid[actual->x + i][actual->y] == 'X'){
                    break;
                }
                else if(gameGrid[actual->x + i][actual->y] == 'M'){
                    randomBonus = rand() % 100;
                    if(randomBonus > tauxDropBonus){

                        gameGrid[actual->x + i][actual->y] = 'S';
                    }else{
                        gameGrid[actual->x + i][actual->y] = 'O';
                    }
                    break;
                }
                else if(gameGrid[actual->x + i][actual->y] == '1' || gameGrid[actual->x + i][actual->y] == '2' || gameGrid[actual->x + i][actual->y] == '3' || gameGrid[actual->x + i][actual->y] == '4'){
                    int deadPlayer = gameGrid[actual->x + i][actual->y] - '0';
                    modifyPlayer(ListeDesJoueurs, deadPlayer, -1, -1, 0, 0, 0, 0, 0, 0);
                    gameGrid[actual->x + i][actual->y] = 'O';
                    break;
                }else if(gameGrid[actual->x + i][actual->y] == 'B'){
                    setBombTimerToZero(liste, actual->x, actual->y - i);
                    explodeBomb(liste, gameGrid, ListeDesJoueurs);
                }
            }

            actual = actual->suivant;
        }else{
            actual = actual->suivant;
        }
    }
}

void setBombTimerToZero(Liste* liste, int x, int y){
    if(liste == NULL){
        exit(EXIT_FAILURE);
    }
    Bomb* actual = liste->premier;
    while(actual != NULL){
        if(actual->x == y && actual->y == x){
            actual->timer = 0;
        }
        actual = actual->suivant;
    }
}

int checkIfPlayerCanMove(char** gameGrid, Map map, char direction, char turn, int isBomb, Liste* ListeDesBombes, ListePlayer* ListeDesJoueurs){
    int id = turn - 48;
    int canMove = 0;
    int a = 0;
    int b = 0;
    int rangeBombPlayer = 0;
    switch (direction) {
        case 'Z':
            a = -1;
            b = 0;
            break;
        case 'Q':
            a = 0;
            b = -1;
            break;
        case 'S':
            a = 1;
            b = 0;
            break;
        case 'D':
            a = 0;
            b = 1;
            break;
    }
    //=2 de portée de bombe
    int initialRange = 3;
    int initialTimer = 4;

    if(direction != 'S'){
        for (int i = 0; i < map.row; i++) {
            for (int j = 0; j < map.column; j++) {
                if (gameGrid[i][j] == turn) {
                    if (gameGrid[i + a][j + b] == 'O') {
                        if(isBomb == 1){
                            gameGrid[i][j] = 'B';
                            rangeBombPlayer = getRangePlayer(ListeDesJoueurs, id);
                            insertBomb(ListeDesBombes,i, j, initialTimer, initialRange + rangeBombPlayer, id);
                            modifyPlayer(ListeDesJoueurs, id, -1, -1, -1, -1, 0, 0, 0, 0);
                        }else{
                            gameGrid[i][j] = 'O';
                        }
                        gameGrid[i + a][j + b] = turn;
                        modifyPlayer(ListeDesJoueurs, id, i + a, j + b, -1, 0, 0, 0, 0, 0);
                        canMove = 1;
                        break;
                    } else if(gameGrid[i + a][j + b] == 'S') {
                        if(isBomb == 1){
                            gameGrid[i][j] = 'B';
                            rangeBombPlayer = getRangePlayer(ListeDesJoueurs, id);
                            insertBomb(ListeDesBombes,i, j, initialTimer, initialRange + rangeBombPlayer, id);
                            modifyPlayer(ListeDesJoueurs, id, -1, -1, -1, -1, 0, 0, 0, 0);

                        }else{
                            gameGrid[i][j] = 'O';
                        }
                        gameGrid[i + a][j + b] = turn;
                        modifyPlayer(ListeDesJoueurs, id, i + a, j + b, -1, 0, 0, 0, 0, 0);
                        getBonus(ListeDesJoueurs, id);
                        canMove = 1;
                        break;
                    }else {
                        canMove = 0;
                        break;
                    }
                }
            }
        }
    }else{
        for (int j = 0; j < map.column; j++) {
            for (int i = 0; i < map.row; i++) {
                if (gameGrid[i][j] == turn) {
                    if (gameGrid[i + a][j + b] == 'O') {
                        if(isBomb == 1){
                            gameGrid[i][j] = 'B';
                            rangeBombPlayer = getRangePlayer(ListeDesJoueurs, id);
                            insertBomb(ListeDesBombes,i, j, initialTimer, initialRange + rangeBombPlayer,id);
                            modifyPlayer(ListeDesJoueurs, id, -1, -1, -1, -1, 0, 0, 0, 0);
                        }else{
                            gameGrid[i][j] = 'O';
                        }
                        gameGrid[i + a][j + b] = turn;
                        modifyPlayer(ListeDesJoueurs, id, i + a, j + b, -1, 0, 0, 0, 0, 0);
                        canMove = 1;
                        break;
                    } else if(gameGrid[i + a][j + b] == 'S') {
                        if(isBomb == 1){
                            gameGrid[i][j] = 'B';
                            rangeBombPlayer = getRangePlayer(ListeDesJoueurs, id);
                            insertBomb(ListeDesBombes,i, j, initialTimer, initialRange + rangeBombPlayer, id);
                            modifyPlayer(ListeDesJoueurs, id, -1, -1, -1, -1, 0, 0, 0, 0);
                        }else{
                            gameGrid[i][j] = 'O';
                        }
                        gameGrid[i + a][j + b] = turn;
                        modifyPlayer(ListeDesJoueurs, id, i + a, j + b, -1, 0, 0, 0, 0, 0);
                        getBonus(ListeDesJoueurs, id);
                        canMove = 1;
                        break;
                    } else {
                        canMove = 0;
                        break;
                    }
                }
            }
        }
    }

    return canMove;
}

void checkIfPlayerCanRevive(ListePlayer* ListeDesJoueurs, char** gameGrid, Map map){
    char player;
    int notDead = 0;
    if(ListeDesJoueurs == NULL){
        exit(EXIT_FAILURE);
    }
    Player* actual = ListeDesJoueurs->premier;
    while(actual != NULL){
        if((actual->isAlive == 0 && actual->heart > 0) || (actual->isAlive == 0 && actual->life > 0)){
            player = actual->id + 48;
            for (int i = 0; i < map.row; i++) {
                for (int j = 0; j < map.column; j++) {
                    if(gameGrid[i][j] == player){
                        notDead = 1;
                    }
                }
            }
            if(notDead !=1){
                if(actual->heart > 0 && actual->life == 0){
                    actual->heart = -1;
                    actual->isAlive = 1;
                    gameGrid[actual->x][actual->y] = player;
                }else if(actual->life > 0 && actual->heart < 1){
                    actual->life--;
                    actual->isAlive = 1;
                    gameGrid[actual->x][actual->y] = player;
                }else if (actual->heart > 0 && actual->life > 0){
                    actual->heart = -1;
                    actual->isAlive = 1;
                    gameGrid[actual->x][actual->y] = player;
                }
            }
        }
        actual = actual->suivant;
    }
}

int getRangePlayer(ListePlayer* ListeDesJoueurs, int id){
    int range = 0;
    Player* actual = ListeDesJoueurs->premier;
    while(actual != NULL){
        if(actual->id == id){
            range = actual->flameRange;
            break;
        }else{
            actual = actual->suivant;
        }
    }
    return range;
}

int getBombPlayer(ListePlayer* ListeDesJoueurs, int id){
    int bomb = 0;
    Player* actual = ListeDesJoueurs->premier;
    while(actual != NULL){
        if(actual->id == id){
            bomb = actual->bomb;
            break;
        }else{
            actual = actual->suivant;
        }
    }
    return bomb;
}

int getIsBotPlayer(ListePlayer* ListeDesJoueurs, int id){
    int isBot = 0;
    Player* actual = ListeDesJoueurs->premier;
    while(actual != NULL){
        if(actual->id == id){
            isBot = actual->isBot;
            break;
        }else{
            actual = actual->suivant;
        }
    }
    return isBot;
}

void checkIfWin(Map map, char** gameGrid, Liste *ListeDesBombes, ListePlayer* ListeDesJoueurs){
    int nbPlayer = map.players;
    int nbPlayerAlive = 0;
    char possibleWinner;
    for(int i = 0; i < map.row; i++){
        for(int j = 0; j < map.column; j++){
            if(gameGrid[i][j] == '1' || gameGrid[i][j] == '2' || gameGrid[i][j] == '3' || gameGrid[i][j] == '4'){
                nbPlayerAlive++;
                possibleWinner = gameGrid[i][j];
            }
        }
    }
    if(nbPlayerAlive == 1){
        deleteBomb(ListeDesBombes);
        deletePlayer(ListeDesJoueurs);
        green();
        printf("Le joueur %c a gagné !\n", possibleWinner);
        red();
        printf("FIN DE PARTIE\n");
        reset();
        quitGame();
    }
}

void checkIfPlayerCanPlay(Map map, char** gameGrid, int *ptrTurn){
    int nbPlayer = map.players;
    char turn = *ptrTurn + '0';
    for(int i = 0; i < map.row; i++){
        for(int j = 0; j < map.column; j++){
            if(gameGrid[i][j] == turn ){
                return;
            }
        }
    }
    if(*ptrTurn == nbPlayer || *ptrTurn > nbPlayer){
        *ptrTurn = 1;
    }else{
        printf("Le joueur %d ne peut plus jouer, il passe son tour\n", *ptrTurn);
        *ptrTurn = *ptrTurn + 1;
    }
}

void getBonus(ListePlayer* liste, char turn){
    int id = turn;
    srand(time(NULL));
    int randomBonus = rand() % 100;
    int bombBonus = 0;
    int rangeBonus = 0;
    int passeBonus = 0;
    int kickBonus = 0;
    int invincibleBonus = 0;
    int heartBonus = 0;
    int lifeBonus = 0;


    if(randomBonus >=0 && randomBonus < 15){
        //bomb up
        bombBonus = 1;
        printf("Le joueur %d a gagné un bonus de bombe\n", id);
    } else if(randomBonus >= 15 && randomBonus < 27){
        //bomb down
        bombBonus = -1;
        printf("Le joueur %d a perdu un bonus de bombe\n", id);
    } else if(randomBonus >= 27 && randomBonus < 46){
        //flame up
        rangeBonus = 1;
        printf("Le joueur %d a gagné un bonus de portée\n", id);
    } else if(randomBonus >= 46 && randomBonus < 54){
        //flame down
        rangeBonus = -1;
        printf("Le joueur %d a perdu un bonus de portée\n", id);
    } else if(randomBonus >= 54 && randomBonus < 58){
        //flame max
        rangeBonus = 30;
        printf("Le joueur %d a gagné un bonus de portée max\n", id);
    } else if(randomBonus >= 58 && randomBonus < 66){
        //passe bomb
        passeBonus = 1;
        printf("Le joueur %d a gagné un bonus de passe bombe\n", id);
    } else if(randomBonus >= 66 && randomBonus < 74){
        //bomb kick
        kickBonus = 1;
        printf("Le joueur %d a gagné un bonus de kick bombe\n", id);
    } else if(randomBonus >= 74 && randomBonus < 82){
        //invincible
        invincibleBonus = 2;
        printf("Le joueur %d a gagné un bonus d'invincibilité de 2 tour\n", id);
    } else if(randomBonus >= 82 && randomBonus < 88){
        //heart
        heartBonus = 1;
        printf("Le joueur %d a gagné un bonus de coeur\n", id);
    } else if(randomBonus >= 88 && randomBonus < 99){
        //life
        lifeBonus = 1;
        printf("Le joueur %d a gagné un bonus de vie\n", id);
    }
    heartBonus = 1;
    lifeBonus = 1;

    modifyPlayer(liste, id, -1, -1, -1, bombBonus, rangeBonus, lifeBonus, heartBonus, invincibleBonus);
}

int botAction(char **gameGrid, Map map, char turn,Liste *ListeDesBombes, ListePlayer* ListeDesJoueurs, int moveLeft){
    char move;
    int nbPlayer = map.players;
    int *posX = malloc(nbPlayer * sizeof(int));
    int *posY = malloc(nbPlayer * sizeof(int));
    float *distance = malloc(nbPlayer * sizeof(int));
    int movebot = moveLeft;
    for(int e = 0; e < movebot; e++){
        Player* actual = ListeDesJoueurs->premier;
        int i = 0;
        int id = turn-48;
        while(actual != NULL){
            if(actual->id != id){
                posX[i] = actual->x;
                posY[i] = actual->y;
                actual = actual->suivant;
                printf("un joueur a été détecté en %d %d\n", posX[i], posY[i]);
                i++;
            }else{
                actual = actual->suivant;
            }
        }
        int posBotX = 0;
        int posBotY = 0;
        actual = ListeDesJoueurs->premier;
        while(actual != NULL){
            if(actual->id == id){
                posBotX = actual->x;
                posBotY = actual->y;
                printf("un bot a été détecté en %d %d\n", posBotX, posBotY);
                break;
            }else{
                actual = actual->suivant;
            }
        }

        for(int j = 0; j < nbPlayer-1; j++){
            distance[j] = sqrt(pow(posX[j] - posBotX, 2) + pow(posY[j] - posBotY, 2));
            printf("distance[%d] = %f\n", j, distance[j]);
        }
        float min = 100.00;
        int index = 0;
        for(int x = 0; x < nbPlayer-1; x++){
            if(distance[x] < min){
                min = distance[x];
                index = x;
            }
        }
        printf("la distance est de %f\n", min);
        if(min == 1){
            printf("Le joueur le plus proche est à une case de distance\n");
            //return 1;
        }
        srand(time(NULL));
        int random = rand() % 100;
        int invalidMove;
        if ((gameGrid[posBotX - 1][posBotY] == gameGrid[posX[index]][posY[index]]) ||
            (gameGrid[posBotX][posBotY - 1] == gameGrid[posX[index]][posY[index]]) ||
            (gameGrid[posBotX + 1][posBotY] == gameGrid[posX[index]][posY[index]]) ||
            (gameGrid[posBotX][posBotY + 1] == gameGrid[posX[index]][posY[index]])) {

            if ((gameGrid[posBotX - 1][posBotY] == 'O') &&
                (gameGrid[posBotX - 1][posBotY - 1] == 'O')) {
                gameGrid[posBotX][posBotY] = 'B';
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'G', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
            } else if ((gameGrid[posBotX - 1][posBotY] == 'O') &&
                       (gameGrid[posBotX - 1][posBotY + 1] == 'O')) {
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
            } else if ((gameGrid[posBotX + 1][posBotY] == 'O') &&
                       (gameGrid[posBotX + 1][posBotY - 1] == 'O')) {
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'G', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
            } else if ((gameGrid[posBotX + 1][posBotY] == 'O') &&
                       (gameGrid[posBotX + 1][posBotY + 1] == 'O')) {
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
            }}
        if (posBotX > posX[index]) {
            if (gameGrid[posBotX - 1][posBotY] == 'O') {
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 0, ListeDesBombes, ListeDesJoueurs);
                moveLeft--;
            } else if ((gameGrid[posBotX - 1][posBotY] == 'M') && (gameGrid[posBotX + 1][posBotY] == 'O') && (gameGrid[posBotX + 1][posBotY + 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
                moveLeft = moveLeft -2;
            } else if ((gameGrid[posBotX - 1][posBotY] == 'M') && (gameGrid[posBotX + 1][posBotY] == 'O') && (gameGrid[posBotX + 1][posBotY - 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'Q', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
                moveLeft = moveLeft -2;
            } else {
                invalidMove = 1;
                break;
            }
        } else if (posBotX < posX[index]) {
            if (gameGrid[posBotX + 1][posBotY] == 'O') {
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 0, ListeDesBombes, ListeDesJoueurs);
                moveLeft--;
            } else if ((gameGrid[posBotX + 1][posBotY] == 'M') && (gameGrid[posBotX - 1][posBotY] == 'O') && (gameGrid[posBotX - 1][posBotY + 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
                moveLeft = moveLeft -2;
            } else if ((gameGrid[posBotX + 1][posBotY] == 'M') && (gameGrid[posBotX - 1][posBotY] == 'O') && (gameGrid[posBotX - 1][posBotY - 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'Q', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
                moveLeft = moveLeft -2;
            } else {
                invalidMove = 1;
                break;
            }
        } else if (posBotY > posY[index]) {
            if (gameGrid[posBotX][posBotY - 1] == 'O') {
                checkIfPlayerCanMove(gameGrid, map, 'Q', turn, 0, ListeDesBombes, ListeDesJoueurs);
                moveLeft--;
            } else if ((gameGrid[posBotX][posBotY - 1] == 'M') && (gameGrid[posBotX][posBotY + 1] == 'O') && (gameGrid[posBotX + 1][posBotY + 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
                moveLeft = moveLeft -2;
            } else if ((gameGrid[posBotX][posBotY - 1] == 'M') && (gameGrid[posBotX][posBotY + 1] == 'O') && (gameGrid[posBotX - 1][posBotY + 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 0, ListeDesBombes, ListeDesJoueurs);
                return 1;
                moveLeft = moveLeft -2;
            } else {
                invalidMove = 1;
                break;
            }
        } else if (posBotY < posY[index]) {
            if (gameGrid[posBotX][posBotY + 1] == 'O') {
                checkIfPlayerCanMove(gameGrid, map, 'D', turn, 0, ListeDesBombes, ListeDesJoueurs);
                moveLeft--;
            } else if ((gameGrid[posBotX][posBotY + 1] == 'M') && (gameGrid[posBotX][posBotY - 1] == 'O') && (gameGrid[posBotX + 1][posBotY - 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'Q', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'S', turn, 0, ListeDesBombes, ListeDesJoueurs);
                moveLeft = moveLeft -2;
            } else if ((gameGrid[posBotX][posBotY + 1] == 'M') && (gameGrid[posBotX][posBotY - 1] == 'O') && (gameGrid[posBotX - 1][posBotY - 1] == 'O') && moveLeft>1) {
                checkIfPlayerCanMove(gameGrid, map, 'Q', turn, 1, ListeDesBombes, ListeDesJoueurs);
                checkIfPlayerCanMove(gameGrid, map, 'Z', turn, 0, ListeDesBombes, ListeDesJoueurs);
                moveLeft = moveLeft -2;
            } else {
                invalidMove = 1;
                break;
            }
        }
        decreaseBombTimer(ListeDesBombes, gameGrid,ListeDesJoueurs);
        //todo : voir pq ça bug checkIfWin(map, gameGrid, ListeDesBombes,ListeDesJoueurs);

    }
    free(posX);
    free(posY);
    free(distance);
    return 1;
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

void deletePlayer(ListePlayer *liste){
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while(liste->premier != NULL)
    {
        Player *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}
