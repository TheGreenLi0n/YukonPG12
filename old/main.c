#include <stdio.h>
#include <string.h>
#include "Card.c"

void printStartFormat();
card* loadDeck(char[],char[]);
void showCommand(char *command, card *deck);
void playGame(card *c1, card *c2, card *c3, card *c4, card *c5, card *c6, card *c7, card *deck, char *command);
void printInputStatus(char*, bool);
int getLongestList(card*,card*,card*,card*,card*,card*,card*);
void printGame(card *c1, card *c2, card *c3, card *c4, card *c5, card *c6, card *c7, int longest);
void printDefault(char*, char*);


//The main method that manages the gameflow through switch cases.
int main() {

    bool gameOngoing = true;
    int currentPhase = 0;
    printStartFormat();
    card* deck = NULL;
    card* c1;
    card* c2;
    card* c3;
    card* c4;
    card* c5;
    card* c6;
    card* c7;
    card* f1;
    card* f2;
    card* f3;
    card* f4;

    while(gameOngoing){
        char input[20];

        fgets(input,20,stdin);

        int dec = input[0] + input[1];
        int gameMove = input[2];
        int gameMove2 = input[5];
        int number = ((input[3]-48)*10) + (input[4]-48);

        switch (dec) {
            case 144:
                if(currentPhase == 0){
                    printf("\nLoad deck\n");
                    if (input[2] != 10) {
                        char *fileName;
                        fileName = strstr(input, " ") + 1;
                        strtok(fileName, "\n");
                        deck = loadDeck(fileName, input);
                    }
                    else
                        deck = loadDeck("", input);
                } else{
                    //need another way to print the output to the terminal
                    //so it's adaptive to where in the process the player is at
                    printEmpty(input,"ERROR");
                }

                break;
            case 90:
                if(currentPhase == 0){
                    printf("\nPlay\n");
                    currentPhase = 1;
                    playPhase(c1,c2,c3,c4,c5,c6,c7,deck,input);
                } else{
                    printf("\nCommand not available in the PLAY phase\n");
                }

                break;
            case 151:
                if(currentPhase == 0){
                    printf("\nSave deck\n");

                    if (input[2] != 10) {
                        char *fileName;
                        fileName = strstr(input, " ") + 1;
                        strtok(fileName, "\n");
                        saveDeck(deck, fileName);
                    } else{
                        saveDeck(deck, "cards");
                    }
                }else{
                    printf("\nCommand not available in the PLAY phase\n");
                }

                break;
            case 91:
                if(currentPhase == 1){
                    printf("\nQuit current game\n");
                    currentPhase = 0;
                }

                break;
            case 170:
                if(currentPhase == 0){
                    printf("\nShow\n");
                    show(input,deck);
                }else{
                    printf("\nCommand not available in the PLAY phase\n");
                }

                break;
            case 162:
                if(currentPhase == 0){
                    printf("Quit");
                    gameOngoing = false;
                }else{
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;

            case 156:
                if(currentPhase == 0){
                    if(deck == NULL){
                        printf("Error need to load deck first");
                    } else{
                        printf("\nSplit shuffle\n");
                        if(number < 52 && number >0){
                            deck = splitShuffle(deck,number);
                        } else{
                            number = rand() % 52;
                            deck = splitShuffle(deck,number);
                        }
                    }
                }else{
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;
            case 10:
                break;

            default:
                if(currentPhase == 1) {
                    if (gameMove == 45 || gameMove2 == 45) {
                        printf("\nGame moveCard\n");
                        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
                        printEndLines(input,true);
                    } else {

                    }
                }

                break;
        }
        //test if the player has won yet
    }

    return 0;
}

//prints out an empty version of the default output
void printDefault(char* lastCommand, char* message){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\t\t\t\t\t\t\t\t[]\tF1\n");
    printf("\t\t\t\t\t\t\t\t[]\tF2\n");
    printf("\t\t\t\t\t\t\t\t[]\tF3\n");
    printf("\t\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST command: %s",lastCommand);
    printf("Message: %s\n",message);
    printf("INPUT>");
}

//Loads the deck.
card* loadDeck(char filename[],char command[]){
    //Load the deck from the Card class
    //if the name given doesn't exist in the saved deck folder, it should return an error
    //if no file name is given it will use the default deck
    //if the file isn't valid then it should return an error as well
    //otherwise it should work and return with "OK"
    bool execute;
    card* deck = createDeck(filename);
    card* currentCard = deck;
    //currentCard = createDeck(filename);
    if(currentCard->value != NULL){
        execute = true;
    } else{
        execute = false;
    }
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int counter = 0;
    int lines = 0;

    while(currentCard->value!=NULL){
        printf("[]\t");
        counter++;
        if(counter == 7){
            if(lines == 0){
                printf("\t[]\tF1");
            } else if(lines == 2){
                printf("\t[]\tF2");
            } else if(lines == 4){
                printf("\t[]\tF3");
            } else if(lines == 6){
                printf("\t[]\tF4");
            }
            printf("\n");
            counter = 0;
            lines++;
        }
        currentCard = currentCard->next;
    }
    printEndLines(command,execute);
    return deck;
}

//Shows the current deck of cards in their shuffled (or unshuffled) order.
void showCommand(char command[], card* deck){
    bool execute;

    if(deck->value != NULL){
        execute = true;
    } else{
        execute = false;
    }
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int counter = 0;
    int lines = 0;

    while(deck->value!=NULL){
        printf("%s\t",deck->value);
        counter++;
        if(counter == 7){
            if(lines == 0){
                printf("\t[]\tF1");
            } else if(lines == 2){
                printf("\t[]\tF2");
            } else if(lines == 4){
                printf("\t[]\tF3");
            } else if(lines == 6){
                printf("\t[]\tF4");
            }
            printf("\n");
            counter = 0;
            lines++;
        }
        deck = deck->next;
    }
    printEndLines(command,execute);
}

//Initiates the PLAY phase for the game.
void playGame(card* c1, card* c2, card* c3, card* c4, card* c5, card* c6, card* c7, card* deck, char* command){
    card* tmp;
    c1 = deck;
    c1->visible = true;
    c2 = c1->next;
    c1->next = NULL;
    tmp = c2;
    for (int i = 0; i < 5; ++i) {
        tmp = tmp->next;
    }
    c3 = tmp->next;
    tmp->next = NULL;
    tmp = c3;
    for (int i = 0; i < 6; ++i) {
        tmp = tmp->next;
    }
    c4 = tmp->next;
    tmp->next = NULL;
    tmp = c4;
    for (int i = 0; i < 7; ++i) {
        tmp = tmp->next;
    }
    c5 = tmp->next;
    tmp->next = NULL;
    tmp = c5;
    for (int i = 0; i < 8; ++i) {
        tmp = tmp->next;
    }
    c6 = tmp->next;
    tmp->next = NULL;
    tmp = c6;
    for (int i = 0; i < 9; ++i) {
        tmp = tmp->next;
    }
    c7 = tmp->next;
    tmp->next = NULL;
    tmp = c7;
    for (int i = 0; i < 10; ++i) {
        tmp = tmp->next;
    }
    tmp->next = NULL;

    //Setup game to be ready to play, print the columns in the terminal with the right cards visible
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    //method to print each line of the columns and foundations
    printLines(c1,c2,c3,c4,c5,c6,c7, 11);

    printEndLines(command,true);


}

//Prints the three status lines: Last command, message and input.
void printInputStatus(char* lastCommand, bool success) {
    printf("\nLAST command: %\n", lastCommand);
    if (success) {
        printf("Message: OK\n");
    } else {
        printf("Message: ERROR\n");
    }
    printf("INPUT>");
}

//Method to get the longest column of cards.
int getLongestList(card* c1,card* c2,card* c3,card* c4,card* c5,card* c6,card* c7){
    card* tmp = c1;
    int largest = 0;
    int counter = 0;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    counter = 0;
    tmp = c2;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    counter = 0;
    tmp = c3;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    counter = 0;
    tmp = c4;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    counter = 0;
    tmp = c5;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    counter = 0;
    tmp = c6;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    counter = 0;
    tmp = c7;
    while(tmp != NULL){
        counter++;
        tmp = tmp->next;
    }
    if(counter>largest){
        largest = counter;
    }
    return largest;
}


//Prints out the columns to the terminal, doesn't take foundations into account.
void printGame(card* c1, card* c2, card* c3, card* c4, card* c5, card* c6, card* c7, int longest){
    card* tmp1 = c1;
    card* tmp2 = c2;
    card* tmp3 = c3;
    card* tmp4 = c4;
    card* tmp5 = c5;
    card* tmp6 = c6;
    card* tmp7 = c7;
    int num = 1;

    for (int i = 0; i < longest; ++i) {
        char c11,c12,c21,c22,c31,c32,c41,c42,c51,c52,c61,c62,c71,c72;
        if(tmp1 != NULL){
            c11 = tmp1->value[0];
            c12 = tmp1->value[1];
        } else{
            c11 = ' ';
            c12 = ' ';
        }
        if(tmp2 != NULL){
            c21 = tmp2->value[0];
            c22 = tmp2->value[1];
        } else{
            c21 = ' ';
            c22 = ' ';
        }
        if(tmp3 != NULL){
            c31 = tmp3->value[0];
            c32 = tmp3->value[1];
        } else{
            c31 = ' ';
            c32 = ' ';
        }
        if(tmp4 != NULL){
            c41 = tmp4->value[0];
            c42 = tmp4->value[1];
        } else{
            c41 = ' ';
            c42 = ' ';
        }
        if(tmp5 != NULL){
            c51 = tmp5->value[0];
            c52 = tmp5->value[1];
        } else{
            c51 = ' ';
            c52 = ' ';
        }
        if(tmp6 != NULL){
            c61 = tmp6->value[0];
            c62 = tmp6->value[1];
        } else{
            c61 = ' ';
            c62 = ' ';
        }
        if(tmp7 != NULL){
            c71 = tmp7->value[0];
            c72 = tmp7->value[1];
        } else{
            c71 = ' ';
            c72 = ' ';
        }
        if(i == 0||i == 2||i == 4||i == 6){
            printf("%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t\t%s\tF%i\n",c11, c12, c21,c22,c31,c32,c41,c42,c51,c52,c61,c62,c71,c72,"[]",num);
            num++;
        } else{
            printf("%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t\n",c11, c12, c21,c22,c31,c32,c41,c42,c51,c52,c61,c62,c71,c72);

        }
        if(tmp1 == NULL){
            tmp1 = NULL;
        } else {
            tmp1 = tmp1->next;
        }
        if(tmp2 == NULL){
            tmp2 = NULL;
        } else {
            tmp2 = tmp2->next;
        }
        if(tmp3 == NULL){
            tmp3 = NULL;
        } else {
            tmp3 = tmp3->next;
        }
        if(tmp4 == NULL){
            tmp4 = NULL;
        } else {
            tmp4 = tmp4->next;
        }
        if(tmp5 == NULL){
            tmp5 = NULL;
        } else {
            tmp5 = tmp5->next;
        }
        if(tmp6 == NULL){
            tmp6 = NULL;
        } else {
            tmp6 = tmp6->next;
        }
        if(tmp7 == NULL){
            tmp7 = NULL;
        } else {
            tmp7 = tmp7->next;
        }
    }
}