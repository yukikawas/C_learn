#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printhint(int guess, int secret);
void printhistory(int history[], int count);
void play(const int MAX_TRY);

int main () {
    srand((unsigned)time(NULL));
    while(1){
        const int MAX_TRY = 10;
        int ch;
        play(MAX_TRY);
        printf("\nwant play again?(y/n)\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        ch = getchar();
        
        if (ch == 'y' || ch == 'Y') {
            continue;
        }
        else if (ch == 'n' || ch == 'N') {
            printf("see you next time~\n");
            break;
        }
        else {
            printf("please input your choice!\n");
            continue;
        }
    }
    return 0;
}


void printhint(int guess, int secret) {
    if (guess > secret) {
        printf("Too big, try smaller!\n\n");
    }

    else if (guess < secret) {
        printf("Too small! try bigger!\n\n");
    }

}


void printhistory(int history[], int count) {
    printf("\n=======guess history======\n");
    for (int i = 0; i < count; i++) {
        printf("%dth: %d \n", i + 1, history[i]);
    }
    printf("\n==========================\n");
}


void play(const int MAX_TRY){
    int secret, guess, attempts = 0;
    int history[100];
    secret = rand() % 100 + 1;
    printf("I have 1~100 number, guess it!\n\n");
    while(attempts < MAX_TRY) {
        printf("please input your guess number: \n\n");
        int ret = scanf("%d", &guess);

        if (ret != 1) {
            printf("please input valid integer!\n");
            int ch2;
            while((ch2 = getchar()) != '\n' && ch2 != EOF);
            continue;
        }
        if (guess < 1 || guess > 100) {
            printf("over range! number range must be 1~100, your number is %d!\n", guess);
            continue;
        }
        if (guess == 66) {
            printf("cheat mode! the secret is %d\n", secret);
        }
        history[attempts] = guess;
        attempts++;
        if (guess == secret) {
            printf("Congratulations! you are right!\n\n");
            printf("your score is %d\n", 10 - attempts);
            break;
        }

        printhint(guess, secret);
    }
    if (attempts >= MAX_TRY){
        printf("game over! no more chances! the secret number is %d", secret);
    }
    printhistory(history, attempts);
}