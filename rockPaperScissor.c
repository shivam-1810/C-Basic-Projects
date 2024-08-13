#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game();
void replay();
void gameplay(char ch, char _cturn);

int main() {
    printf("Let's play rock, paper and scissors.\n");
    game();
    return 0;
}

void game() {
    char ch;
    printf("Press 'R' for rock, 'P' for paper and 'S' for scissor.\n");
    scanf("%c", &ch);
    getchar();
    if(ch != 'r' && ch != 'p' && ch != 's' && ch != 'R' && ch != 'P' && ch != 'S') {
        printf("Invalid input.\n");
    } else if(ch == 's') {
        ch = 'S';
    } else if(ch == 'r') {
        ch = 'R';
    } else if(ch == 'p') {
        ch = 'P';
    }
    srand(time(NULL));
    int random_index = rand() % 3;
    int cturn[] = {80, 82, 83};
    char _cturn = cturn[random_index];
    if(_cturn == 'S') {
        printf("Computer plays 'Scissors (S)'.\n");
    } else if(_cturn == 'R') {
        printf("Computer plays 'Rock (R)'.\n");
    } else if(_cturn == 'P') {
        printf("Computer plays 'Paper (P)'..!\n");
    }
    static int cscore = 0, urscore = 0;
    gameplay(ch, _cturn);
    replay();
    return;
}

void gameplay(char ch, char _cturn) {
    static int cscore = 0, urscore = 0;
    if(ch == _cturn) {
        printf("Oops! Its a tie.\n\n");
        cscore ++;
        urscore ++;
    } else if (ch == 'R' && _cturn == 'S') {
        printf("Congrats you won..!\n\n");
        urscore ++;
    } else if(ch == 'R' && _cturn == 'P') {
        printf("Sorry, you lost..!\n\n");
        cscore ++;
    } else if(ch == 'P' && _cturn == 'R') {
        printf("Congrats you won..!\n\n");
        urscore ++;
    } else if(ch == 'P' && _cturn == 'S') {
        printf("Sorry, you lost..!\n\n");
        cscore ++;
    } else if(ch == 'S' && _cturn == 'P') {
        printf("Congrats you won..!\n\n");
        urscore ++;
    } else if(ch == 'S' && _cturn == 'R') {
        printf("Sorry, you lost..!\n\n");
        cscore ++;
    } else {
        printf("Error!!\n\n");
    }
    printf("Scores :\nYou : %d \tComputer : %d\n", urscore, cscore);
    return;
}

void replay() {
    char choice;
    printf("Wanna replay? Y/N\n");
    scanf("%c", &choice);
    getchar();
    if(choice == 'Y' || choice == 'y') {
        printf("\n");
        game();
        return;
    } else if(choice == 'N' || choice == 'n') {
        printf("Thanks for playing..!\nSee uh later :)");
    } else {
        printf("Sorry, invalid input..!\n");
    }
}