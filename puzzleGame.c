#include <stdio.h>
#include <conio.h>
#include <windows.h>

int getkey();
void gotoxy(short int col, short int row);
void boxes();
void display();
void check(char name[]);

int arr[4][4] = { //globally defined array
        {1, 4, 15, 7}, 
        {8, 10, 2, 11},
        {14, 3, 6, 13},
        {12, 9, 5, 0}
    };

int main() {
    printf("Let's solve a puzzle, let's see how fast do you solve:)\n\n");
    printf("General instructions -\n");
    printf("You are given a box with numbers from 1 to 15, you have to arrange it in ascending order.\n");
    printf("For moving numbers, you can use arrow keys(escape to exit), also the no. of moves will be recorded.\n");
    printf("Enter your name : ");
    char name[15];
    scanf("%s", name);
    int row = 3, col = 3, t, ch;
    boxes();
    display();
    while (1) {
        ch = getkey();
        switch (ch) {
            case 80 : //down arrow
            if(row == 0) {
                printf("\a");
                break;
            }
            t = arr[row][col];
            arr[row][col] = arr[row-1][col];
            arr[row-1][col] = t;
            row--;
            display();
            break;

            case 77 : //right arrow
            if(col == 0) {
                printf("\a");
                break;
            }
            t = arr[row][col];
            arr[row][col] = arr[row][col-1];
            arr[row][col-1] = t;
            col--;
            display();
            break;

            case 72 : //up arrow
            if(row == 3) {
                printf("\a");
                break;
            }
            t = arr[row][col];
            arr[row][col] = arr[row+1][col];
            arr[row+1][col] = t;
            row++;
            display();
            break;

            case 75 : //left arrow
            if(col == 3) {
                printf("\a");
                break;
            }
            t = arr[row][col];
            arr[row][col] = arr[row][col+1];
            arr[row][col+1] = t;
            col++;
            display();
            break;
            
            case 27 : //escape key
            exit(0);
        }
        check(name);
    }
    return 0;
}

void gotoxy(short int col, short int row) { //gets console cursor position
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {col, row};
    SetConsoleCursorPosition (h, position);
}

void boxes() {
    int r, c; //row and column
    for(c = 60; c<=72; c++) {
        for(r = 8; r <= 16; r+=2) {
            gotoxy(c, r);
            printf ("%c", 196);
        }
    }
    for(r = 8; r <= 16; r++) {
        for(c = 60; c <= 72; c+=3) {
            gotoxy(c, r);
            printf("%c", 179);
        }
    }
    for(c = 63; c <= 69; c+= 3) {
        gotoxy(c, 8);
        printf("%c", 194);
        gotoxy(c, 16);
        printf("%c", 193);
    }
    for(r = 10; r <= 14; r+=2) {
        gotoxy(60, r);
        printf("%c", 195);
        gotoxy(72, r);
        printf("%c", 180);
    }
    for(r = 10; r <= 14; r+=2) {
        for(c = 63; c <= 69; c+=3) {
            gotoxy(c, r);
            printf("%c", 197);
        }
    }
    gotoxy(60, 8);
    printf("%c", 218);
    gotoxy(72, 8);
    printf("%c", 191);
    gotoxy(60, 16);
    printf("%c", 192);
    gotoxy(72, 16);
    printf("%c", 217);
}

void display() {
    int r = 9, c = 61;
    for(int i = 0; i <= 3; i++) {
        for(int j = 0; j <= 3; j++) {
            if(arr[i][j] == 0) {
                gotoxy(c, r);
                printf("  ");
            } else {
                gotoxy(c, r);
                printf("%d", arr[i][j]);
            }
            c += 3;
        }
        r += 2;
        c = 61;
    }
}

int getkey()
{
    int ch;
    ch = getch();
    if(ch == 0) {
        ch = getch();
        return ch;
    }
    return ch;
}

void check(char name[]) {
    static int move = 0;
    int k = 1;
    move++;
    gotoxy(60,19);
    printf("No. of moves = %d", move);
    for(int i = 0; i <=3; i++) {
        for(int j = 0; j <= 3; j++) {
            if(arr[i][j] == 0) {
                continue;
            } else if(arr[i][j] == k) {
                k++;
            } else {
                return;
            }
        }
    }
    gotoxy(49, 22);
    printf("Congratulations! %s solved the puzzle in %d moves.\n ", name , move);
    exit(0);
}