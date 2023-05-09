#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct Card {
    char value[2];
    struct Card *next;
    bool isVisible;
};
typedef struct Card card;

///
/// \param filename
/// \return
card* makeDeck (char filename[]){
    char nameOfFile[80];
    card *nextCard = NULL;
    card *currentCard = NULL;
    card *prevCard = NULL;
    FILE* file;
    strcpy(nameOfFile, filename);
    strcat(nameOfFile, ".txt");
    file = fopen(nameOfFile, "r");
    currentCard = (card*)malloc(sizeof(card));

    for (int i = 0; i < 52; i++){
        fscanf(file, "%s", currentCard -> value);
        currentCard -> isVisible = false;
        if (nextCard != NULL){
            prevCard -> next = currentCard;
        }
        else{
            nextCard = currentCard;
        }
        prevCard = currentCard;
        prevCard -> next = NULL;
        currentCard = (card*) malloc(sizeof(card));
    }
    fclose(file);
    return nextCard;
}

void moveCard(card **sourcePile, card **destinationPile){
    if (*sourcePile == NULL)
        return;

    card* current = *sourcePile;
    card* prev = NULL;

    // Traverse to the last node of the source list
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        // The source list contains only one node
        *sourcePile = NULL;
    } else {
        // Remove the last node from the source list
        prev->next = NULL;
    }

    // Insert the last node at the end of the destination list
    if (*destinationPile == NULL) {
        *destinationPile = current;
    } else {
        card* destCurrent = *destinationPile;
        while (destCurrent->next != NULL) {
            destCurrent = destCurrent->next;
        }
        destCurrent->next = current;
    }
}

///
/// \param deck
/// \param filename
/*void saveDeck(card *deck, char filename[]) {
    char nameOfFile[28];
    FILE *f;
    strcpy(nameOfFile, filename);
    strcat(nameOfFile, ".txt");
    f = fopen(nameOfFile, "w");

    while (deck->value != NULL) {
        fprintf(f, deck->value);
        fprintf(f, "\n");
        deck = deck->next;
    }
    fclose(f);
}*/
///
/// \param lastCommand
/// \param success
void printInputStatus(char *lastCommand, bool validInput) {
    printf("\nLAST command: %s\n", lastCommand);
    if (validInput) {
        printf("Message: OK\n");
    } else {
        printf("Message: ERROR\n");
    }
    printf("INPUT>");
}

///
/// \param lastCommand
/// \param statusMessage
void defaultTemplate(char *lastCommand, char *statusMessage) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\t\t\t\t\t\t\t\t[]F1\n");
    printf("\t\t\t\t\t\t\t\t[]F2\n");
    printf("\t\t\t\t\t\t\t\t[]F3\n");
    printf("\t\t\t\t\t\t\t\t[]F4\n");
    printInputStatus(lastCommand, statusMessage);
}

///
/// \param filename
/// \param command
/// \return
card *loadDeck(char filename[], char command[]) {
    bool validInput;
    card *deck = makeDeck(filename);
    card *currentCard = deck;
    if (currentCard->value != NULL) {
        validInput = true;
    } else {
        validInput = false;
    }
    return deck;
}

///
/// \param command
/// \param deck
void showCommand(char command[], card *deck) {
    bool validInput;
    if (deck->value != NULL) {
        validInput = true;
    } else {
        validInput = false;
    }

    while (deck->value != NULL) {
        deck->isVisible = true;
        deck = deck->next;
    }
}

///
/// \param deck
/// \param command
void printGame(card *deck, char command[], bool validInput) {
    printf("\n\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int xPos = 0;
    int yPos = 0;

    while (deck->value != NULL) {
        if(deck->isVisible){
            printf("%s\t", deck->value);
        } else {
            printf("[]\t");
        }
        xPos++;
        if (xPos == 7) {
            if (yPos == 0) {
                printf("\t[]\tF1");
            } else if (yPos == 2) {
                printf("\t[]\tF2");
            } else if (yPos == 4) {
                printf("\t[]\tF3");
            } else if (yPos == 6) {
                printf("\t[]\tF4");
            }
            printf("\n");
            xPos = 0;
            yPos++;
        }
        deck = deck->next;
    }
    printInputStatus(command, validInput);
}

///
/// \param next
/// \param split
/// \return
struct card *commandSI(card *next, int split) {
    card *next1 = NULL, *next2 = NULL, *prev1 = NULL, *newDeck = NULL, *currentCard;
    int numOfShuffle;
    int splitRest = 52 - split;
    next1 = next;
    next2 = next;
    prev1 = next1;
    int pileBiggest;

    for (int i = 0; i < split; ++i) {
        next2 = next2->next;
    }
    for (int i = 0; i < split - 1; ++i) {
        prev1 = prev1->next;
    }
    if (split > splitRest) {
        numOfShuffle = splitRest;
        pileBiggest = 1;
    } else {
        numOfShuffle = split;
        pileBiggest = 2;
    }

    newDeck = next1;
    currentCard = newDeck;
    next1 = next1->next;
    for (int i = 0; i < numOfShuffle * 2 - 1; ++i) {
        if (i % 2 == 1) {
            currentCard->next = next1;
            currentCard = currentCard->next;
            next1 = next1->next;
        } else {
            currentCard->next = next2;
            currentCard = currentCard->next;
            next2 = next2->next;
        }
    }
    if (pileBiggest == 1) {
        while (next1 != prev1->next) {
            currentCard->next = next1;
            currentCard = currentCard->next;
            next1 = next1->next;
        }
    } else {
        while (next2 != NULL) {
            currentCard->next = next2;
            currentCard = currentCard->next;
            next2 = next2->next;
        }
    }
    currentCard->next = NULL;
    return newDeck;
}

bool deckValid(card *deck){
    int numOfDiamond = 0;
    int numOfHeart = 0;
    int numOfClub = 0;
    int numOfSpade = 0;

    while (deck->value != NULL) {
        if(deck->value[1] == 68)
            numOfDiamond++;
        if(deck->value[1] == 67)
            numOfClub++;
        if(deck->value[1] == 72)
            numOfHeart++;
        if(deck->value[1] == 83)
            numOfSpade++;
        deck = deck->next;
    }
    if(numOfSpade == 13 && numOfHeart == 13 && numOfDiamond == 13 && numOfClub == 13) {
        return true;
    } else{
        return false;
    }
}

///
/// \param c1
/// \param c2
/// \param c3
/// \param c4
/// \param c5
/// \param c6
/// \param c7
/// \param deck
/// \param command
void playGame(card *c1, card *c2, card *c3, card *c4, card *c5, card *c6, card *c7, card *deck, char *command) {
    card *tmp;
    c1 = deck;
    c1->isVisible = true;
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
}

///
/// \return
int main() {

    bool gameInProgress = true;
    bool validInput;
    int gameState = 0;
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\t\t\t\t\t\t\t\t[]F1\n");
    printf("\t\t\t\t\t\t\t\t[]F2\n");
    printf("\t\t\t\t\t\t\t\t[]F3\n");
    printf("\t\t\t\t\t\t\t\t[]F4\n");
    printf("LAST command:\n");
    printf("Message:\n");
    printf("INPUT>");

    card *deck = NULL, *c1, *c2, *c3, *c4, *c5, *c6, *c7, *f1, *f2, *f3, *f4;

    while (gameInProgress) {
        char input[20];
        fgets(input, 20, stdin);
        int command = input[0] + input[1];
        int gameCommand = input[2];
        int gameAction = input[5];
        int number = ((input[3] - 48) * 10) + (input[4] - 48);
        validInput = false;

        switch (command) {
            //LD
            case 144:
                if (gameState == 0) {
                    validInput = true;
                    if (input[2] != 10) {
                        char *fileName;
                        fileName = strstr(input, " ") + 1;
                        strtok(fileName, "\n");
                        deck = loadDeck(fileName, input);
                        if (!deckValid(deck))
                            validInput = false;
                    } else
                        deck = loadDeck("Deck", input);
                } else {
                    defaultTemplate(input, "ERROR");
                }
                break;
                //P
            case 90:
                if (gameState == 0) {
                    validInput = true;
                    gameState = 1;
                    //playGame(c1, c2, c3, c4, c5, c6, c7, deck, input);
                } else {
                    printf("\nThis command is not available during the play phase\n");
                }

                break;
                //SD
            case 151:
                if (gameState == 0) {
                    if (input[2] != 10) {
                        validInput = true;
                        char *fileName;
                        fileName = strstr(input, " ") + 1;
                        strtok(fileName, "\n");
                        //saveDeck(deck, fileName);
                    } else {
                        //saveDeck(deck, "cards");
                    }
                } else {
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;
                //Q
            case 91:
                if (gameState == 1) {
                    validInput = true;
                    printf("\nQuitting\n");
                    gameState = 0;
                } else {
                    printf("\nCommand not available in the STARTUP phase\n");
                }
                break;
                //SW
            case 170:
                if (gameState == 0) {
                    showCommand(input, deck);
                    validInput = true;
                } else {
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;
                //QQ
            case 162:
                if (gameState == 0) {
                    validInput = true;
                    printf("Goodbye o/");
                    gameInProgress = false;
                    continue;
                } else {
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;
                //SI
            case 156:
                if (gameState == 0) {
                    if (deck == NULL) {
                        printf("Deck needs to be loaded first!");
                    } else {
                        validInput = true;
                        printf("\nSplit shuffle\n");
                        if (number <= 52 && number >= 0) {
                            deck = commandSI(deck, number);
                        } else {
                            number = rand() % 52;
                            deck = commandSI(deck, number);
                        }
                    }
                } else {
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;
            case 10:
                break;

            default:
                if (gameState == 1) {
                    if (gameCommand == 45 || gameAction == 45) {
                        validInput = true;

                    } else {
                    }
                }
                break;
        }
        //Input should maybe be changed to command.
        printGame(deck, input, validInput);

    }
    return 0;
}



