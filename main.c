#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printhint(int guess, int secret);
void printhistory(int history[], int count);
void play(int secret, int guess, int attempts, const int MAX_TRY, int history[]);

int main () {
    while(1){
        int secret, guess, attempts = 0;
        int history[100];
        const int MAX_TRY = 10;
        char choice[] = "";
        play(secret, guess, attempts, MAX_TRY, history);
        scanf("want play again?(y/n)%d", &choice);
        if (choice == "y") {
            continue;
        }
        else if (choice == "n") {
            break;
        }
        else {
            printf("please input your choice!\n");
        }
    }

}


void printhint(int guess, int secret) {
    if (guess > secret) {
        printf("Too big, more smaller!\n\n");
    }

    else if (guess < secret) {
        printf("Too small! more bigger!\n\n");
    }

}


void printhistory(int history[], int count) {
    printf("\n=======guess history======\n");
    for (int i = 0; i < count; i++) {
        printf("%dth: %d \n", i + 1, history[i]);
    }
    printf("\n==========================\n");
}


void play(int secret, int guess, int attempts, const int MAX_TRY, int history[]){
    srand((unsigned)time(NULL));
    secret = rand() % 100 + 1;
    printf("I have 1~100 number, guess it!\n\n");
    while(attempts < MAX_TRY) {
        printf("please input your guess number: \n\n");
        int ret = scanf("%d", &guess);
        if (ret != 1) {
            printf("please input vaild integar!\n");
            while(getchar() != '\n');
            continue;
        }
        history[attempts] = guess;
        attempts++;
        if (guess == secret) {
            printf("Congratulations! you are right!\n\n");
            break;
        }

        printhint(guess, secret);
    }
    if (attempts >= MAX_TRY){
        printf("game over! no more chances! the sceret number is %d", secret);
    }
    printhistory(history, attempts);
}