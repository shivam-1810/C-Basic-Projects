#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(short int col, short int row);
void setup();
void locator();
void gameplay1();
void gameplay2();
void dislocate();
int checkWin(int board[3][3]);

int board[3][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
};

static int x = 0;
static int y = 0;

int main() {
    printf("Let's play tic tac toe game, yayy..!\n");
    printf("General rules :\n");
    printf("1. This is a two player game, you can navigate through the boxes with arrow keys and press esc key once you are done.\n");
    printf("2. Press space to enter your input, the game will run giving chances to both the players alternatively until the game comes to a result.\n");
    int n;
    setup();
    do{ 
        gotoxy(61, 21);
        printf("Player 1's turn");
        locator();
        gameplay1();
        dislocate();
        n = checkWin(board);
        if(n == 1) {
            gotoxy(61, 21);
            printf("Player 1 wins!!");
            for(int i = 61; i <= 75; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
            break;
        } else if(n == -1) {
            gotoxy(61, 21);
            printf("Player 2 wins!!");
            for(int i = 61; i <= 75; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
            break;
        } else if(n == 0) {
            gotoxy(61, 21);
            printf("  It's a tie!  ");
            for(int i = 63; i <= 73; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
            break;
        }

        gotoxy(61, 21);
        printf("Player 2's turn");
        locator();
        gameplay2();
        dislocate();
        n = checkWin(board);
        if(n == 1) {
            gotoxy(61, 21);
            printf("Player 1 wins!!");
            for(int i = 61; i <= 75; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
            break;
        } else if(n == -1) {
            gotoxy(61, 21);
            printf("Player 2 wins!!");
            for(int i = 61; i <= 75; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
            break;
        } else if(n == 0) {
            gotoxy(61, 21);
            printf("  It's a tie!  ");
            for(int i = 63; i <= 73; i++) {
                gotoxy(i, 22);
                printf("%c", 196);
            }
            break;
        }
    } while (n == 2);
    printf("\nPress 'Enter' to replay and 'Esc' to exit.\n");
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

void gameplay1() {
    int ch1 = getch();
    while(ch1 != 32) {
        printf("\a");
        ch1 = getch();
    }
    if(ch1 == 32) {
        printf("X");
        board[y][x] = 1;
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