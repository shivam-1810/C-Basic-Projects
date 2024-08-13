#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void gotoxy(short int col, short int row);
void setup();
void locator();
void gameplaym1();
void gameplaym2(int px, int py);
void gameplay2();
void dislocate();
int checkWin(int board[3][3]);
void declaration();
void computerMove();
void rematch();
void scoringSystem();

int board[3][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
};

static int x = 0;
static int y = 0;
static int cwins = 0;

int main() {
    printf("Let's play tic tac toe game, yayy..!\n");
    printf("General rules :\n");
    printf("1. This is a single-player game. You will play against the computer.\n");
    printf("2. Navigate through the boxes with arrow keys, press esc when u are done and press space to enter your input.\n");
    setup();
    scoringSystem();
    gameplaym1(); //Computer move 1
    int px = x;
    int py = y;
    dislocate();

    gotoxy(63, 21); //User move 1
    printf("Your turn");
    locator();
    gameplay2();

    gameplaym2(px, py);
    scoringSystem();
        
    gotoxy(48, 29);
    printf("Huhh! You're a bot, learn some skills kid..!\n");
    gotoxy(48, 31);
    printf("Press 'Enter' to replay and 'Esc' to exit.\n");
    int replay = getch();
    while (replay != 27 && replay != 0xd) {
        printf("\a");
        replay = getch();
    }
    if(replay == 27) {
        exit(0);
    }
    while (replay == 0xd) {
        for(int i = 0; i <= 2; i++) {
            for(int j = 0; j <= 2; j++) {
                board[i][j] = 0;
            }
        }
        x = 0;
        y = 0;
        system("cls");
        rematch();
    }
}

void gotoxy(short int col, short int row) { //gets console cursor position
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {col, row};
    SetConsoleCursorPosition (h, position);
}

void setup() {
    int r, c;
    for(c = 64; c <= 75; c+=6){ //vertical lines
        for(r = 7; r <= 17; r++) {
            gotoxy(c, r);
            printf("%c", 179);
        }
    }
    for(r = 10; r <= 17; r+=4) { //horizontal lines
        for(c = 59; c <= 75; c++) {
            gotoxy(c, r);
            printf("%c", 196);
        }
    }
    for(r = 10; r <= 17; r+=4) { //gaps
        for(c = 64; c <= 75; c+=6) {
            gotoxy(c, r);
            printf("%c", 197);
        }
    }
    return;
}

void locator() { 
    while (1) {
        gotoxy(59 + x * 6, 8 + y * 4);
        printf("%c%c", 196, 196);

        char key = getch();
        gotoxy(59 + x * 6, 8 + y * 4);
        printf("  ");

        switch(key) {
            case 72: //up arrow
                if (y > 0) {
                    if(y == 2 && board[y-1][x] != 0 && board[y-2][x] != 0) {
                        dislocate();
                        break;
                    } else if(y == 2 && board[y-1][x] != 0) {
                        y--;
                    } else if(y == 1 && board[y-1][x] != 0) {
                        dislocate();
                        break;
                    }
                    y--;
                } else {
                    printf("\a");
                }
                break;
            case 80: //down arrow
                if (y < 2) {
                    if(y == 0 && board[y+1][x] != 0 && board[y+2][x] != 0) {
                        dislocate();
                        break;
                    } else if(y == 0 && board[y+1][x] != 0) {
                        y++;
                    } else if(y == 1 && board[y+1][x] != 0) {
                        dislocate();
                        break;
                    }
                    y++;
                } else {
                    printf("\a");
                } 
                break;
            case 75: //left arrow
                if (x > 0) {
                    if(x == 2 && board[y][x-1] != 0 && board[y][x-2] != 0) {
                        dislocate();
                        break;
                    } else if(x == 2 && board[y][x-1] != 0) {
                        x--;
                    } else if(x == 1 && board[y][x-1] != 0) {
                        dislocate();
                        break;
                    }
                    x--;
                } else {
                    printf("\a");
                } 
                break;
            case 77: // right arrow
                if (x < 2) {
                    if(x == 0 && board[y][x+1] != 0 && board[y][x+2] != 0) {
                        dislocate();
                        break;
                    } else if(x == 0 && board[y][x+1] != 0) {
                        x++;
                    } else if(x == 1 && board[y][x+1] != 0) {
                        dislocate();
                        break;
                    }
                    x++;
                } else {
                    printf("\a");
                } 
                break;
            case 27 : //escape key
                return; 
        }
    }
    return;
}

void gameplay2() {
    int ch2 = getch();
    while(ch2 != 32) {
        printf("\a");
        ch2 = getch();
    }
    if(ch2 == 32) {
        printf("O");
        board[y][x] = -1;
    }
    return;
}

void dislocate() {
    int check = 1; //Checking whether all the boxes are filled
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                check = 0; //Still an unfilled box remains
                break;
            }
        }
    }
    if(check == 1) {
        return;
    }
    if (x == 2) {
        x = 0;
        y++;
    } else {
        x++;
    }
    if (y > 2) {
        y = 0;
    }
    while(board[y][x] != 0) {
        dislocate();
    }
    gotoxy(59 + x * 6, 8 + y * 4);
}

int checkWin(int board[3][3]) {
    // Checking rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
            return board[i][0];
        }
    } 

    // Checking columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0) {
            return board[0][i];
        }
    }

    // Checking diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != 0) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 0) {
        return board[0][2];
    }

    // Checking for tie
    int isTie = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                isTie = 0;
                break;
            }
        }
    }
    if (isTie == 1) {
        return 0;
    }

    return 2; // No winner yet
}

void gameplaym1() { //Computer move 1 function
    int random[] = {0, 2};
    srand(time(NULL));
    x = random[rand() % 2];
    y = random[rand() % 2];
    board[y][x] = 1;
    gotoxy(61 + x * 6, 8 + y * 4);
    printf("X");
}

void declaration() {
    int n = checkWin(board);
        if(n == 1) {
            gotoxy(59, 21);
            printf("Oops, Computer won!!");
            for(int i = 59; i <= 78; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
        } else if(n == -1) {
            gotoxy(59, 21);
            printf("Congrats, you won!!");
            for(int i = 59; i <= 78; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
        } else if(n == 0) {
            gotoxy(61, 21);
            printf("  It's a tie!  ");
            for(int i = 63; i <= 73; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
        }
}

void gameplaym2(int px, int py) {
    cwins++;
    if(board[1][1] != 0) { //Player played in middle, computer move 2
        int p2x, p2y;
        if(px == 0) {
            p2x = 2;
        } else { p2x = 0;}
        if(py == 0) {
            p2y = 2;
        } else { p2y = 0;}
        board[p2y][p2x] = 1;
        gotoxy(61 + p2x * 6, 8 + p2y * 4);
        printf("X");
        dislocate();

        gotoxy(63, 21);
        printf("Your turn"); //User move 2
        locator();
        gameplay2();

        if(board[0][0] == -1 || board[2][2] == -1 || board[2][0] == -1 || board[0][2] == -1) {
            for(int i = 0; i<= 2; i+=2) {
                for(int j = 0; j<= 2; j+=2) {
                    if(board[i][j] == 0) {
                        y = i;
                        x = j;
                        break;
                    }
                }
            }
            board[y][x] = 1;
            gotoxy(61 + x * 6, 8 + y * 4);
            printf("X");
            
            dislocate();

            gotoxy(63, 21);
            printf("Your turn"); //User move 3
            locator();
            gameplay2();

            if(board[1][p2x] == 0 && board[0][p2x] == 1 && board[2][p2x] == 1) {
                board[1][p2x] = 1;
                gotoxy(61 + p2x * 6, 8 + 1 * 4);
                printf("X");
                declaration();
                return; //Game end
            } else if(board[p2y][1] == 0 && board[p2y][0] == 1 && board[p2y][2] == 1) {
                board[p2y][1] = 1;
                gotoxy(61 + 1 * 6, 8 + p2y * 4);
                printf("X");
                declaration(); //Game end
                return;
            } else if(board[1][px] == 0 && board[0][px] == 1 && board[2][px] == 1) {
                board[1][px] = 1;
                gotoxy(61 + px * 6, 8 + 1 * 4);
                printf("X");
                declaration();
                return; //Game end
            } else if(board[py][1] == 0 && board[py][0] == 1 && board[py][2] == 1) {
                board[py][1] = 1;
                gotoxy(61 + 1 * 6, 8 + py * 4);
                printf("X");
                declaration(); //Game end
                return;
            }
        } else {
            computerMove(); // computer move 3
            dislocate();
            declaration();
            if(checkWin(board) == 1 || checkWin(board) == -1) {
                return;
            }
            locator();
            gameplay2(); //User move 3
            declaration();
            if(checkWin(board) == 1 || checkWin(board) == -1) {
                return;
            }

            computerMove(); // computer move 4
            dislocate();
            declaration();
            if(checkWin(board) == 1 || checkWin(board) == -1) {
                return;
            } 
            locator();  //User move 4
            gameplay2();
            declaration();
            if(checkWin(board) == 1 || checkWin(board) == -1) {
                return;
            }

            computerMove(); // computer move 5
            declaration();
            if(checkWin(board) == 0) {
                cwins--;
            }
            return;
        }
    } else {    //Computer move 2
        int p2x, p2y;
        if((px == 0 && py == 0) || (px == 2 && py == 2)) { //Player didn't play in the middle
            if(x == 0 && y == 2) {
                x = 2;
                y = 0;
            } else if(x == 2 && y == 0) {
                x = 0;
                y = 2;
            } else if(y == 1 && x == 0) {
                if(px == 0 && py == 0) {
                    x = 2;
                    y = 0;
                } else {
                x = 0;
                y = 2;
                }
            } else if(x == 1 && y == 2) {
                if(px == 0 && py == 0) {
                    x = 0;
                    y = 2;
                } else {
                x = 2;
                y = 0;
                }
            } else if(x == 1 && y == 0) {
                if(px == 0 && py == 0) {
                    x = 0;
                    y = 2;
                } else {
                x = 2;
                y = 0;
                }
            } else if(x == 2 && y == 1) {
                if(px == 0 && py == 0) {
                    x = 2;
                    y = 0;
                } else {
                x = 0;
                y = 2;
                }
            } else if((x == 2 && y == 2) || (x == 0 && y == 0)) {
                x = 2;
                y = 0;
            }
            board[y][x] = 1;
            p2x = x;
            p2y = y;
            gotoxy(61 + p2x * 6, 8 + p2y * 4);
            printf("X");
        } else {
            if(x == 0 && y == 0) {
                x = 2;
                y = 2;
            } else if(x == 2 && y == 2) {
                x = 0;
                y = 0;
            } else if(y == 1 && x == 0) {
                if(px == 0 && py == 2) {
                    x = 2;
                    y = 2;
                } else {
                x = 0;
                y = 0;
                }
            } else if (x == 1 && y == 0) {
                if(px == 0 && py == 2) {
                    x = 0;
                    y = 0;
                } else {
                x = 2;
                y = 2;
                }
            } else if (y == 1 && x == 2) {
                if(px == 0 && py == 2) {
                    x = 2;
                    y = 2;
                } else {
                x = 0;
                y = 0;
                }
            } else if(x == 1 && y == 2) {
                if(px == 0 && py == 2) {
                    x = 0;
                    y = 0;
                } else {
                x = 2;
                y = 2;
                }
            } else if ((x == 0 && y == 2) || (x == 2 && y == 0)) {
                x = 0;
                y = 0;
            }
            p2x = x;
            p2y = y;
            board[p2y][p2x] = 1;
            gotoxy(61 + p2x * 6, 8 + p2y * 4);
            printf("X");
        }
        dislocate();

        gotoxy(63, 21);
        printf("Your turn"); //User move 2
        locator();
        gameplay2();
        //Computer move 3
        if(board[1][px] == 0 && board[0][px] == 1 && board[2][px] == 1) {
            board[1][px] = 1;
            gotoxy(61 + px * 6, 8 + 1 * 4);
            printf("X");
            declaration();
            return; //Game end
        } else if(board[py][1] == 0 && board[py][0] == 1 && board[py][2] == 1) {
            board[py][1] = 1;
            gotoxy(61 + 1 * 6, 8 + py * 4);
            printf("X");
            declaration(); //Game end
            return;
        } else {
            int count = 0;
            for (int i = 0; i <= 2; i += 2) {
                for (int j = 0; j <= 2; j += 2) {
                    if (board[i][j] == 0) {
                        y = i;
                        x = j;
                        count++;
                    }
                }
            }
            if (count == 1) {
                board[y][x] = 1;
                gotoxy(61 + x * 6, 8 + y * 4);
                printf("X");
                dislocate();
            } else if(count == 2) {
                if(board[0][1] == 0) {
                    board[0][1] = 1;
                }
                if(board[1][0] == 0) {
                    board[1][0] = 1;
                }
                if(board[2][1] == 0) {
                    board[2][1] = 1;
                }
                if(board[1][2] == 0) {
                    board[1][2] = 1;
                }
                computerMove();
                dislocate();
                if(board[0][1] == 1) {
                    board[0][1] = 0;
                }
                if(board[1][0] == 1) {
                    board[1][0] = 0;
                }
                if(board[2][1] == 1) {
                    board[2][1] = 0;
                }
                if(board[1][2] == 1) {
                    board[1][2] = 0;
                }
            }
        }

        gotoxy(63, 21);
        printf("Your turn"); //User move 3
        locator();
        gameplay2();

        if(board[1][1] == 0) { //Computer move 4
            x = 1; y = 1;
            board[1][1] = 1;
            gotoxy(61 + x * 6, 8 + y * 4);
            printf("X");
            declaration();
        } else {
            if(board[1][p2x] == 0 && board[0][p2x] == 1 && board[2][p2x] == 1) {
                board[1][p2x] = 1;
                gotoxy(61 + p2x * 6, 8 + 1 * 4);
                printf("X");
                declaration();
                return; //Game end
            } else if(board[p2y][1] == 0 && board[p2y][0] == 1 && board[p2y][2] == 1) {
                board[p2y][1] = 1;
                gotoxy(61 + 1 * 6, 8 + p2y * 4);
                printf("X");
                declaration(); //Game end
                return;
            } else if(board[1][px] == 0 && board[0][px] == 1 && board[2][px] == 1) {
                board[1][px] = 1;
                gotoxy(61 + px * 6, 8 + 1 * 4);
                printf("X");
                declaration();
                return; //Game end
            } else if(board[py][1] == 0 && board[py][0] == 1 && board[py][2] == 1) {
                board[py][1] = 1;
                gotoxy(61 + 1 * 6, 8 + py * 4);
                printf("X");
                declaration(); //Game end
                return;
            }
        }
    }
    return;
}

void computerMove() {
    // Checking if computer can win in the next move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                board[i][j] = 1;
                if (checkWin(board) == 1) {
                    gotoxy(61 + j * 6, 8 + i * 4);
                    printf("X");
                    return;
                }
                board[i][j] = 0;
            }
        }
    }
    // Checking if player can win in the next move, and block if necessary
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                board[i][j] = -1;
                if (checkWin(board) == -1) {
                    board[i][j] = 1;
                    gotoxy(61 + j * 6, 8 + i * 4);
                    printf("X");
                    return;
                }
                board[i][j] = 0;
            }
        }
    }
    // If neither player can win in the next move, making a random move
    int emptySpaces[9][2];
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                emptySpaces[count][0] = i;
                emptySpaces[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int randomIndex = rand() % count; // Choosing a random empty space
        int row = emptySpaces[randomIndex][0];
        int col = emptySpaces[randomIndex][1];
        board[row][col] = 1;
        gotoxy(61 + col * 6, 8 + row * 4);
        printf("X");
    }
}

void rematch() {
    printf("Let's play tic tac toe game, yayy..!\n");
    printf("General rules :\n");
    printf("1. This is a single-player game. You will play against the computer.\n");
    printf("2. Navigate through the boxes with arrow keys, press esc when u are done and press space to enter your input.\n");
    setup();
    scoringSystem();
    x = 0;
    y = 0;
    gotoxy(63, 21); //User move 1
    printf("Your turn");
    locator();
    gameplay2();

    if(board[1][1] == 0) {
        board[1][1] = 1;
        gotoxy(61 + 1 * 6, 8 + 1 * 4); //Computer move 1
        printf("X");
        dislocate();

        gotoxy(63, 21); //User move 2
        printf("Your turn");
        locator();
        gameplay2();

    int pwin = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                board[i][j] = -1;
                if (checkWin(board) == -1) {
                    board[i][j] = 1;
                    gotoxy(61 + j * 6, 8 + i * 4);
                    printf("X");
                    dislocate();
                    pwin = 1;
                    break;
                }
                board[i][j] = 0;
            }
        }
    }
    if(pwin == 0) {
        for(int i = 0; i <= 2; i+=2) {
            for(int j = 0; j <= 2; j+=2) {
                if(board[i][j] == 0) {
                    board[i][j] = 3;
                }
            }
        }
        computerMove(); //Computer move 2
        dislocate();
        declaration();
        for(int i = 0; i <= 2; i+=2) {
            for(int j = 0; j <= 2; j+=2) {
                if(board[i][j] == 3) {
                    board[i][j] = 0;
                }
            }
        }
    }

        gotoxy(63, 21); //User move 3
        printf("Your turn");
        locator();
        gameplay2();
        declaration();
        scoringSystem();
        if(checkWin(board) == 1 || checkWin(board) == -1) {
            return;
        }

        for(int i = 0; i <= 1; i++) {
            computerMove(); //Computer move 3
            dislocate();
            declaration();
            if(checkWin(board) == 1) {
                cwins++;
                scoringSystem();
                break;
            }

            locator();  //User move 4
            gameplay2();
            declaration();
            if(checkWin(board) == 1) {
                cwins++;
                scoringSystem();
                break;
            }
        }
    } else { //If user plays in middle
        gameplaym1(); //Computer move 1
        dislocate();
            
        locator();  //User move 2
        gameplay2();

        int flag = 0;   //Computer move 2
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = -1;
                    if (checkWin(board) == -1) {
                        board[i][j] = 1;
                        gotoxy(61 + j * 6, 8 + i * 4);
                        printf("X");
                        flag = 1;
                        break;
                    }
                    board[i][j] = 0;
                }
            }
        }
        if(flag == 0) {  //Computer move 2 (conditional)
            for(int i = 0; i <= 2; i+=2) {
                for(int j = 0; j <= 2; j+=2) {
                    if(board[i][j] == 0) {
                        board[i][j] = 1;
                        gotoxy(61 + j * 6, 8 + i * 4);
                        printf("X");
                        flag = 1;
                        break;
                    }
                }
                if(flag == 1) {
                    break;
                }
            }
        }
        dislocate();

        locator();  //User move 3
        gameplay2();
        declaration();

        for(int i = 0; i < 2; i++) {
            computerMove(); //Computer move 3
            dislocate();
            declaration();
            if(checkWin(board) == 1) {
                cwins++;
                scoringSystem();
                break;
            }
            
            locator();  //User move 4
            gameplay2();
            declaration();
            if(checkWin(board) == 1) {
                cwins++;
                scoringSystem();
                break;
            }
        }
    }

    gotoxy(48, 29);
    printf("Huhh! You're a bot, learn some skills kid..!\n");
    gotoxy(48, 31);
    printf("Press 'Enter' to replay and 'Esc' to exit.\n");
    int replay = getch();
    while (replay != 27 && replay != 0xd) {
        printf("\a");
        replay = getch();
    }
    if(replay == 27) {
        exit(0);
    }
    while (replay == 0xd) {
        for(int i = 0; i <= 2; i++) {
            for(int j = 0; j <= 2; j++) {
                board[i][j] = 0;
            }
        }
        x = 0;
        y = 0;
        system("cls");
        main();
    }
}

void scoringSystem() {
    gotoxy(65, 24);
    printf("Score");
    for(int i = 64; i <= 70; i++) {
        gotoxy(i, 25);
        printf("%c", 196);
    }
    gotoxy(54, 26);
    printf("Computer : %d  \t  You : %d", cwins, 0);
}