#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For sleep function
#include <string.h>

// Function prototypes
void printWelcomeSign();
void instructions(char playerName[]);
void countdown(int seconds);
void checking(int correctArr[4], int compareArr[4]);
int checkExit(int correctArr[4], int compareArr[4]);
void exitGame(int correctArr[4], int compareArr[4]);
void saveScores(char playerName[], int score,char level[]);
void displayHistory();





int main() {
    int guessArr[4];
    int randomArray[4];
    int correctArr[4];
    int gameScore = 0;
    char answerForPlayAgain;
    char name[50];
    int round = 0;
    char lname[10];

    printWelcomeSign();

    printf("\nEnter your name: ");
    scanf("%s", name);

    FILE *scoreFile = fopen("scores.txt", "a");

    if (scoreFile == NULL) {
        printf("Error opening the score file.\n");
        return 1;
    }

    int menuChoice;
    do {
        printf("\n\t\t\t\t\t\t\t\t        ===========");
        printf("\n\t\t\t\t\t\t\t\t        |MAIN MENU|");
        printf("\n\t\t\t\t\t\t\t\t        ===========\n\n");
        printf("\t\t\t\t\t\t\t\t   1. Play the Game\n");
        printf("\t\t\t\t\t\t\t\t   2. View Game History\n");
        printf("\t\t\t\t\t\t\t\t   3. How to Play\n");
        printf("\t\t\t\t\t\t\t\t   4. Exit\n\n");
        printf("\t\t\t\t\t\t\t\t   Enter your choice: ");
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1: // To play the game
                do {
                    round++;
                    srand(time(NULL));
                    for (int i = 0; i < 4; i++) {
                        randomArray[i] = rand() % 10 + 1;
                    }



                    int tries = 0;
                    int correct = 0;
                    int tryCount;
                    int triesNumber;


                    printf("\n\t\t\t\t\t\t\t\t       1.Easy");
                    printf("\n\t\t\t\t\t\t\t\t       2.Medium");
                    printf("\n\t\t\t\t\t\t\t\t       3.Hard\n\n");
                    printf("Enter difficulty Level : ");
                    scanf("%d",&tryCount);

                    printf("\nRound %d of 5\n", round);
                    countdown(3);


                    switch (tryCount) {

                       case 1:
                           triesNumber =8;
                           break;

                       case 2:
                           triesNumber=6;
                           break;

                       case 3:
                           triesNumber=4;
                           break;

                       default:
                           printf("Invalid Game mode!");
                            break;

                    }

                    if(triesNumber==8){
                        strcpy(lname, "Easy");
                    }
                    if(triesNumber==6){
                        strcpy(lname, "Medium");
                    }
                    if(triesNumber==4){
                        strcpy(lname, "Hard");
                    }


                    while (tries < triesNumber) {
                        for (int i = 0; i < 4; i++) {
                            printf("\n\t\tEnter %d number: ", i + 1);
                            scanf("%d", &guessArr[i]);
                        }
                        printf("\n");

                        for (int i = 0; i < 4; i++) {
                            correctArr[i] = randomArray[i];
                        }

                        checking(correctArr, guessArr);
                        gameScore = 10*checkExit(correctArr, guessArr);


                        if (checkExit(correctArr, guessArr) == 4) {
                            correct = 1;
                            break;
                        }

                        tries++;

                        if (tries < triesNumber) {
                            printf("\t\tYou have %d tries remaining.\n", triesNumber - tries);
                            printf("\t\t____________________________\n\n");
                        }
                    }

                    if (correct) {
                        printf("\t\tYou guessed all numbers correctly! Well done!\n");
                    } else {
                        printf("\t\tYou have used all your tries. The correct numbers were: ");
                        for (int i = 0; i < 4; i++) {
                            printf("%d ", correctArr[i]);
                        }
                        printf("\n\n\t\t-------------------------\n");
                        printf("\t\t|    Your Score >>> %d \t|\n",gameScore);
                        printf("\t\t-------------------------\n");

                          }

                    saveScores(name, gameScore,lname);

                    if (round < 5) {
                        printf("\n\t\tDo you want to play again (y/n): ");
                        scanf(" %c", &answerForPlayAgain);
                    } else {
                        exitGame(correctArr, guessArr);
                        printf("\t\tYou've reached the maximum number of rounds. Thanks for playing!\n");
                        answerForPlayAgain = 'n';
                    }

                    system("cls");

                } while ((answerForPlayAgain == 'y' || answerForPlayAgain == 'Y') && round < 5);
                break;

            case 2: // To view game history
                displayHistory();
                break;

            case 3: // To see how to play
                instructions(name);
                break;

            case 4: //To exit the game
                printf("\n\t\tExiting the game. Thank you for playing!\n");
                printf("\n\t\t\t\t\t\t\t        ========================");
                printf("\n\t\t\t\t\t\t\t        |Thank you for playing!|");
                printf("\n\t\t\t\t\t\t\t        ========================\n\n");
                printf("\t________________________________________________________________________________________________\n\n");
                break;

            default:
                printf("\n\t\tInvalid choice. Please select a valid option.\n");
                break;
        }

    } while (menuChoice != 4);

    fclose(scoreFile);

    return 0;
}

//print welcome sign
void printWelcomeSign() {
    printf("\t\t\t\t\t\t\t     ******************************\n");
    printf("\t\t\t\t\t\t\t     *       WELCOME TO THE       *\n");
    printf("\t\t\t\t\t\t\t     *    NUMBER GUESSING GAME    *\n");
    printf("\t\t\t\t\t\t\t     *         GOOD LUCK!         *\n");
    printf("\t\t\t\t\t\t\t     ******************************\n");
}

//countdown for game start
void countdown(int seconds) {
    for (int i = seconds; i > 0; i--) {
        printf("\t\tStarting in %d seconds...\r", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\t\tStarting now! Good luck!\n");
}


//show instructions
void instructions(char playerName[]) {
    printf("\t\tHello %s !!\n\n", playerName);
    printf("\t\t\t\t\t     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("\t\t\t\t\t\t\t\t #####  INSTRUCTIONS  ####\n\n");
    printf("\t\t\t\t\t\t 1. The computer will generate a random 4-digit number.\n");
    printf("\t\t\t\t\t\t 2. Your task is to guess the correct number.\n");
    printf("\t\t\t\t\t\t 3. Enter your guesses one by one when prompted.\n");
    printf("\t\t\t\t\t\t 4. After each guess, the game will provide feedback.\n");
    printf("\t\t\t\t\t\t 5. Try to guess all four numbers correctly!\n\n");
    printf("\t\t\t\t\t      >>> score will be counted ONLY in the FINAL Round (Last Attempt) <<<\n\n\n");
    printf("\t\t\t\t\t     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
    printf("\t\t\t\t\t\t\t        #### Difficulty Levels ####\n\n");
    printf("\t\t\t\t\t\t\t\t    EASY   > 8 Attempts\n");
    printf("\t\t\t\t\t\t\t\t    MEDIUM > 6 Attempts\n");
    printf("\t\t\t\t\t\t\t\t    HARD   > 4 Attempts\n");
    printf("\n\n\t\t\t\t\t     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
}


//To check user inputs are correct or not
void checking(int correctArr[4], int compareArr[4]) {
    for (int i = 0; i < 4; i++) {
        if (compareArr[i] == correctArr[i]) {
            printf("\t\t%d number is CORRECT!! :)\n\n", i + 1);
        } else {
            printf("\t\t%d number is WRONG!! :( \n\n", i + 1);
        }
    }
}


//to find correct count
int checkExit(int correctArr[4], int compareArr[4]) {
    int correctCount = 0;
    for (int i = 0; i < 4; i++) {
        if (compareArr[i] == correctArr[i]) {
            correctCount++;
        }
    }
    return correctCount;
}


//To show the final correct numbers
void exitGame(int correctArr[4], int compareArr[4]) {
    if (checkExit(correctArr, compareArr) == 4) {
        printf("\t\tNICE JOB!!  WELL DONE! :)\n");
    } else {
        printf("\t\tThe correct numbers are: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", correctArr[i]);
        }
        printf("\n\n");
        printf("\t________________________________________________________________________________________________\n\n\n\n");
    }
}


//To save player history
void saveScores(char playerName[], int score, char level[]) {
    FILE *scoreFile = fopen("scores.txt", "a");
    if (scoreFile == NULL) {
        printf("Error opening the score file for saving.\n");
        return;
    }
    if(score==40){
        fprintf(scoreFile, "Player: %s|level: %s | WON!!",playerName,level);
    }
    else{
    fprintf(scoreFile, "Player: %s | Score: %d | Level: %s\n", playerName, score,level);
    fclose(scoreFile);
    }
}


//To show display game history
void displayHistory() {
    FILE *scoreFile = fopen("scores.txt", "r");
    if (scoreFile == NULL) {
        printf("Error opening the score file for viewing history.\n");
        return;
    }

    printf("\n\t\tGAME HISTORY\n");

    char line[100];
    while (fgets(line, sizeof(line), scoreFile)) {
        printf("\t\t%s", line);
    }

    fclose(scoreFile);
}

