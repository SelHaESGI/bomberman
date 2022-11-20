#include "common.h"
#include "structures.h"

Liste* init();

void insertBomb(Liste* liste, int x, int y, int timer, int range);

void decreaseBombTimer(Liste* liste, char** gameGrid);

void explodeBomb(Liste *liste, char **gameGrid);

void startMenu();

void reset();

void quitGame();

void setOptions();

void launchGame(char **grid, Map map, int *ptrTurn, int vsChoice);

void showLogo();

void print_image(FILE *pFile);

void chooseMap();

void multijoueur();

void randomMap();

void printMap(char letter);

void printAllMaps();

void changeGrid(char **gameGrid, Map map, int *ptrTurn, int vsChoice);

void explodeBomb(Liste *liste, char **gameGrid);

int main() {
    printf("Bienvenu dans Bomberm...Casse briques !\n");
    startMenu();
    return 0;
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
    printf("1. Jouer (local)\n");
    reset();
    /**printf("\u25A0 \u25A0 \u25A0 \u25A0 \u25A0\n");
    printf("\u25A0 \u24e7 \u25A5 \u2297 \u25A0\n");
    printf("\u25A0 \u24e7 \u25A5  2\u25A0\n");
    printf("\u25A0 \u25A0 \u25A0 \u25A0 \u25A0\n");
    printf("coeur : \u2661 \u2665 \n");**/
    purple();
    printf("2. Jouer (serveur)\n");
    reset();
    yellow();
    printf("3. Options\n");
    red();
    printf("4. Quitter\n");
    reset();
    blue();
    printf("5. Map random\n");
    reset();

    int choice;
    scanf("%d", &choice);
    clearTerminal();
    switch (choice) {
        case 1:
            chooseMap();
            break;
        case 2:
            multijoueur();
            break;
        case 3:
            setOptions();
            break;
        case 4:
            quitGame();
            break;
        case 5:
            randomMap();
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

void randomMap() {
    int rows,columns;

    const char randomCharacters[]="MOOO";
    int randSize=sizeof(randomCharacters)-1;
    srand(time(0));

    printf("Entrer taille tableau l et L\n");
    printf("nombre de Lignes  : \n");
    scanf("%d", &rows);
    printf("nombre de Colonnes : \n");
    scanf("%d", &columns);
    clearTerminal();

    int Map[rows][columns];

    for (int i =0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //murs tout autour ( cadre ) : position 0 et l-1
            if ((i == 0) || (j == 0) || (i == rows-1) || (j == columns-1)) Map[i][j] = 'X';
                //position du joueur à l'indice (1,1)
            else if (i==1 && j==1) Map[i][j] = '1';
            else Map[i][j] = randomCharacters[rand()%randSize];

        }

    }


    FILE * fPtr;
    char fName[20] = "randomMap.txt";
    fPtr = fopen(fName, "w");

    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i =0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(fPtr,"%c", Map[i][j]);
        }
        fprintf(fPtr,"\n");
    }
    printf("Map created and saved successfully. :) \n");
    fclose(fPtr);



    int turn = 1;
    int *ptrTurn = &turn;

    struct Map random_map = rand_map(rows,columns);

    char line;

    random_map.grid = malloc(random_map.row * sizeof(char *));
    for (int i = 0; i < random_map.row; i++)
        random_map.grid[i] = malloc(random_map.column * sizeof(char));
    //INITIALISATION DE LA MAP 1
    for (int i = 0; i < random_map.row; i++)
        for (int j = 0; j < random_map.column; j++) {
            line = fgetc(fPtr);
            if (line == EOF) break;
            if (line != '\n') {
                random_map.grid[i][j] = line;
            } else {
                j--;
            }
        }

    launchGame(random_map.grid, random_map, ptrTurn, 1);

}


void multijoueur() {
    blue();
    printf("1. Démarrer serveur\n");
    green();
    printf("2. Rejoindre serveur\n");
    reset();

    int choice;
    //int ip = '127.0.0.1';
    int ip;
    int port = 9001;
    scanf("%d", &choice);
    clearTerminal();
    switch (choice) {
        case 1:
            blue();
            printf("Saisir le port assigné (9001 de base)\n");
            scanf("%d", &port);
            printf("Port assigné %d\n", port);
            reset();
            // create server socket similar to what was done in
            // client program
            int servSockD = socket(AF_INET, SOCK_STREAM, 0);

            // string store data to send to client
            char serMsg[255] = "Message from the server to the "
                               "client \'Hello Client\' ";

            // define server address
            struct sockaddr_in servAddr;

            servAddr.sin_family = AF_INET;
            servAddr.sin_port = htons(port);
            servAddr.sin_addr.s_addr = INADDR_ANY;

            // bind socket to the specified IP and port
            bind(servSockD, (struct sockaddr*)&servAddr,
                 sizeof(servAddr));

            // listen for connections
            listen(servSockD, 1);

            // integer to hold client socket.
            int clientSocket = accept(servSockD, NULL, NULL);

            // send's messages to client socket
            send(clientSocket, serMsg, sizeof(serMsg), 0);

            break;
        case 2:
            green();
            printf("Saisir le port assigné (9001 de base)\n");
            scanf("%d", &port);
            printf("Port assigné %d\n", port);
            printf("Saisir l'ip'\n");
            scanf("%d", &ip);
            printf("ip : %d\n", ip);
            reset();

            int sockD = socket(AF_INET, SOCK_STREAM, 0);

            //struct sockaddr_in servAddr;

            servAddr.sin_family = AF_INET;
            servAddr.sin_port
                    = htons(port); // use some unused port number
            servAddr.sin_addr.s_addr = INADDR_ANY; // ip // INADDR_ANY

            int connectStatus
                    = connect(sockD, (struct sockaddr*)&servAddr,
                              sizeof(servAddr));

            if (connectStatus == -1) {
                printf("Error...\n");
            }

            else {
                char strData[255];

                recv(sockD, strData, sizeof(strData), 0);

                printf("Message: %s\n", strData);
            }

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
    int moveLeft = 4;
    int bombLeft = map.bomb;
    int invalidMove = 0;
    char turn;
    //int counter = 0;

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
                        for (int j = 0; j < map.column; j++) {
                            for (int i = 0; i < map.row; i++) {
                                if (gameGrid[i][j] == turn) {

                                    if (i==0){
                                        if (gameGrid[map.row-1][j] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[map.row-1][j] = turn;
                                            moveLeft--;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    }
                                    else if (gameGrid[i - 1][j] == 'O') {
                                        gameGrid[i][j] = 'O';
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
                                    if (j == 0) { // traverse mur
                                        if (gameGrid[i][map.column-1] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[i][map.column-1] = turn;
                                            moveLeft--;
                                            //counter = 1;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    } else if (gameGrid[i][j - 1] == 'O') {
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
                                    if (i==map.row-1){
                                        if (gameGrid[map.row-map.row][j] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[map.row-map.row][j] = turn;
                                            moveLeft--;
                                            //counter = 1;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    }
                                    else if (gameGrid[i + 1][j] == 'O') {
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
                                    if (j == map.column-1) { // traverse le mur
                                        if (gameGrid[i][map.column-map.column] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[i][map.column-map.column] = turn;
                                            moveLeft--;
                                            //counter = 1;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }

                                    } else if ((gameGrid[i][j + 1] == 'O')) {
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
                        //counter =0;
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
                printf("decreased\n");
                decreaseBombTimer(ListeDesBombes, gameGrid);
            }

            if (moveLeft == 0) {

                switch (*ptrTurn) {
                    case 1: // Place au BOT
                        printf("decreaseddelamort\n");
                        //decreaseBombTimer(ListeDesBombes, gameGrid);
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
                                        if (moveLeft > 2) {
                                            if ((gameGrid[posJ2x - 1][posJ2y ] == '1') || // pose une bombe si distance joueur = 1
                                                (gameGrid[posJ2x][posJ2y - 1] == '1') ||
                                                (gameGrid[posJ2x + 1][posJ2y ] == '1') ||
                                                (gameGrid[posJ2x][posJ2y  + 1] == '1')) {

                                                if ((gameGrid[posJ2x - 1][posJ2y] == 'O') && (gameGrid[posJ2x -1][posJ2y -1] == 'O')) {
                                                    gameGrid[posJ2x][posJ2y] = 'B';
                                                    insertBomb(ListeDesBombes,posJ2x, posJ2y, 4, 3);
                                                    gameGrid[posJ2x - 1][posJ2y -1] = turn;
                                                    printf("bombe 1");
                                                    moveLeft = 0;
                                                }
                                                else if ((gameGrid[posJ2x - 1][posJ2y] == 'O') && (gameGrid[posJ2x -1][posJ2y +1] == 'O')) {
                                                    gameGrid[posJ2x][posJ2y] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,posJ2x, posJ2y, 4, 3);
                                                    gameGrid[posJ2x - 1][posJ2y +1] = turn;
                                                    printf("bombe 2");
                                                    moveLeft = 0;
                                                }
                                                else if ((gameGrid[posJ2x + 1][posJ2y] == 'O') && (gameGrid[posJ2x +1][posJ2y -1] == 'O')) {
                                                    gameGrid[posJ2x][posJ2y] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,posJ2x, posJ2y, 4, 3);
                                                    gameGrid[posJ2x + 1][posJ2y -1] = turn;
                                                    printf("bombe 3");
                                                    moveLeft = 0;
                                                }
                                                else if ((gameGrid[posJ2x + 1][posJ2y] == 'O') && (gameGrid[posJ2x +1][posJ2y +1] == 'O')) {
                                                    gameGrid[posJ2x][posJ2y] = 'B';
                                                    //listBomb = addBomb(listBomb, i, j, 2, 3);
                                                    insertBomb(ListeDesBombes,posJ2x, posJ2y, 4, 3);
                                                    gameGrid[posJ2x + 1][posJ2y +1] = turn;
                                                    printf("bombe 4");
                                                    moveLeft = 0;
                                                }

                                                printf("Je suis la et je t'observe \n");
                                                break;
                                            }
                                        }
                                        if (posJ2x > posJ1x) {
                                            if (gameGrid[posJ2x - 1][posJ2y] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x - 1][posJ2y] = turn;
                                                posJ2x--;
                                                moveLeft--;
                                            }
                                            else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        }
                                        else if (posJ2x < posJ1x) {
                                            if (gameGrid[posJ2x + 1][posJ2y] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x + 1][posJ2y] = turn;
                                                posJ2x++;
                                                moveLeft--;
                                            } else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        }
                                        else if (posJ2y > posJ1y) {
                                            if (gameGrid[posJ2x][posJ2y - 1] == 'O') {
                                                gameGrid[posJ2x][posJ2y] = 'O';
                                                gameGrid[posJ2x][posJ2y - 1] = turn;
                                                posJ2y--;
                                                moveLeft--;
                                            } else {
                                                invalidMove = 1;
                                                break;
                                            }
                                        }
                                        else if (posJ2y < posJ1y) {
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

                                }

                            }
                        }
                        printf("decreaseddelamort\n");

                        *ptrTurn = 1;
                        changeGrid(gameGrid, map, ptrTurn, vsChoice);
                        break;
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

                                if (gameGrid[i][j] == turn) {
                                    if (i==0){
                                        if (gameGrid[map.row-1][j] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[map.row-1][j] = turn;
                                            moveLeft--;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    }
                                    else if (gameGrid[i - 1][j] == 'O') {
                                        gameGrid[i][j] = 'O';
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
                                    if (j == 0) { // traverse mur
                                        if (gameGrid[i][map.column-1] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[i][map.column-1] = turn;
                                            moveLeft--;
                                            //counter = 1;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    } else if (gameGrid[i][j - 1] == 'O') {
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
                                    if (i==map.row-1){
                                        if (gameGrid[map.row-map.row][j] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[map.row-map.row][j] = turn;
                                            moveLeft--;
                                            //counter = 1;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }
                                    }
                                    else if (gameGrid[i + 1][j] == 'O') {
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
                                    if (j == map.column-1) { // traverse le mur
                                        if (gameGrid[i][map.column-map.column] == 'O'){
                                            gameGrid[i][j] = 'O';
                                            gameGrid[i][map.column-map.column] = turn;
                                            moveLeft--;
                                            //counter = 1;
                                            break;
                                        }else {
                                            invalidMove = 1;
                                            break;
                                        }

                                    } else if ((gameGrid[i][j + 1] == 'O')) {
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

                printf("decreased\n");
                decreaseBombTimer(ListeDesBombes, gameGrid);

                if (moveLeft == 0) {
                    switch (*ptrTurn) {
                        case 1:
                            *ptrTurn = 2;
                            moveLeft = 4;
                            break;
                        case 2:
                            if (map.players == 2) {
                                *ptrTurn = 1;
                            } else {
                                *ptrTurn = 3;
                            }
                            moveLeft = 4;
                            break;
                        case 3:
                            if (map.players == 3) {
                                *ptrTurn = 1;
                            } else {
                                *ptrTurn = 4;
                            }
                            moveLeft = 4;
                            break;
                        case 4:
                            *ptrTurn = 1;
                            moveLeft = 4;
                            break;
                        default:
                            break;
                    }
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









