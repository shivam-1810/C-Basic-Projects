#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
int main() {
    char name[15];
    printf("\nLet's play number guessing game.\nComputer has thought of a number, you have to guess it, let's see how fast you can get it...\n\n");
    for(int i = 0; i <= 1; i++) {
        printf("Enter your name :\n");
        scanf("%s", name);
        printf("Seems that you aren't eligible to play with this name..! Try again!\n\n");
    }
        printf("Enter your name lastt time:\n");
        scanf("%s", name);
        printf("It seems lil bit good, ohk accepted, let's go now..!\n\n");
    while (1) {
        int gnumber, cnumber, moves = 0;
        srand(time(NULL));
        cnumber = rand() % 100;
        printf("Guess a number between 0 to 100.\n");
        scanf("%d", &gnumber);
        if(cnumber == gnumber) {
            printf("Wohoo..!, You got it right..!\n");
            moves++;
            printf("No. of tries taken = %d..!\n\n", moves);
        } else {
            while (1) {
                if(cnumber == gnumber) {
                    printf("Wohoo..!, You got it right..!\n");
                    moves++;
                    printf("No. of tries taken = %d..!\n\n", moves);
                    break;
                } else if(cnumber > gnumber) {
                    moves++;
                    printf("Its smaller, guess greater one.\n");
                    scanf("%d", &gnumber);
                } else if(cnumber < gnumber) {
                    moves++;
                    printf("Its greater, guess smaller one.\n");
                    scanf("%d", &gnumber);
                }
            }
        }
        printf("Press any key to replay or Esc to exit.\n");
        int replay = getch();
        if(replay == 27) {
            exit(0);
        } else {
            printf("\n");
        }
    }
    return 0;
}