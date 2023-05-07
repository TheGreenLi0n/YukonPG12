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
    card *nextCard;
    card *currentCard;
    card *prevCard;
    FILE* file;
    strcpy(nameOfFile, filename);
    strcat(nameOfFile, ".txt");
    file = fopen(nameOfFile, "r");
    currentCard = (card*)malloc(sizeof(card));

    for (int i = 0; i < 52; i++){
        fscanf(file, "%s", currentCard -> value);
        currentCard -> isVisible = true;
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
    printf("\nLAST command: %\n", lastCommand);
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
        execute = true;
    } else {
        execute = false;
    }
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int counter = 0;
    int lines = 0;

    while (currentCard->value != NULL) {
        printf("[]\t");
        counter++;
        if (counter == 7) {
            if (lines == 0) {
                printf("\t[]\tF1");
            } else if (lines == 2) {
                printf("\t[]\tF2");
            } else if (lines == 4) {
                printf("\t[]\tF3");
            } else if (lines == 6) {
                printf("\t[]\tF4");
            }
            printf("\n");
            counter = 0;
            lines++;
        }
        currentCard = currentCard->next;
    }
    printInputStatus(command, execute);
    return deck;
}

///
/// \param command
/// \param deck
void showCommand(char command[], card *deck) {
    bool execute;

    if (deck->value != NULL) {
        execute = true;
    } else {
        execute = false;
    }
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int counter = 0;
    int lines = 0;

    while (deck->value != NULL) {
        printf("%s\t", deck->value);
        counter++;
        if (counter == 7) {
            if (lines == 0) {
                printf("\t[]\tF1");
            } else if (lines == 2) {
                printf("\t[]\tF2");
            } else if (lines == 4) {
                printf("\t[]\tF3");
            } else if (lines == 6) {
                printf("\t[]\tF4");
            }
            printf("\n");
            counter = 0;
            lines++;
        }
        deck = deck->next;
    }
    printInputStatus(command, execute);
}

void printGame(card *c1, card *c2, card *c3, card *c4, card *c5, card *c6, card *c7, int longest) {
    card *tmp1 = c1;
    card *tmp2 = c2;
    card *tmp3 = c3;
    card *tmp4 = c4;
    card *tmp5 = c5;
    card *tmp6 = c6;
    card *tmp7 = c7;
    int num = 1;

    for (int i = 0; i < longest; ++i) {
        char c11, c12, c21, c22, c31, c32, c41, c42, c51, c52, c61, c62, c71, c72;
        if (tmp1 != NULL) {
            c11 = tmp1->value[0];
            c12 = tmp1->value[1];
        } else {
            c11 = ' ';
            c12 = ' ';
        }
        if (tmp2 != NULL) {
            c21 = tmp2->value[0];
            c22 = tmp2->value[1];
        } else {
            c21 = ' ';
            c22 = ' ';
        }
        if (tmp3 != NULL) {
            c31 = tmp3->value[0];
            c32 = tmp3->value[1];
        } else {
            c31 = ' ';
            c32 = ' ';
        }
        if (tmp4 != NULL) {
            c41 = tmp4->value[0];
            c42 = tmp4->value[1];
        } else {
            c41 = ' ';
            c42 = ' ';
        }
        if (tmp5 != NULL) {
            c51 = tmp5->value[0];
            c52 = tmp5->value[1];
        } else {
            c51 = ' ';
            c52 = ' ';
        }
        if (tmp6 != NULL) {
            c61 = tmp6->value[0];
            c62 = tmp6->value[1];
        } else {
            c61 = ' ';
            c62 = ' ';
        }
        if (tmp7 != NULL) {
            c71 = tmp7->value[0];
            c72 = tmp7->value[1];
        } else {
            c71 = ' ';
            c72 = ' ';
        }
        if (i == 0 || i == 2 || i == 4 || i == 6) {
            printf("%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t\t%s\tF%i\n", c11, c12, c21, c22, c31, c32, c41, c42, c51,
                   c52, c61, c62, c71, c72, "[]", num);
            num++;
        } else {
            printf("%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t%c%c\t\n", c11, c12, c21, c22, c31, c32, c41, c42, c51, c52,
                   c61, c62, c71, c72);

        }
        if (tmp1 == NULL) {
            tmp1 = NULL;
        } else {
            tmp1 = tmp1->next;
        }
        if (tmp2 == NULL) {
            tmp2 = NULL;
        } else {
            tmp2 = tmp2->next;
        }
        if (tmp3 == NULL) {
            tmp3 = NULL;
        } else {
            tmp3 = tmp3->next;
        }
        if (tmp4 == NULL) {
            tmp4 = NULL;
        } else {
            tmp4 = tmp4->next;
        }
        if (tmp5 == NULL) {
            tmp5 = NULL;
        } else {
            tmp5 = tmp5->next;
        }
        if (tmp6 == NULL) {
            tmp6 = NULL;
        } else {
            tmp6 = tmp6->next;
        }
        if (tmp7 == NULL) {
            tmp7 = NULL;
        } else {
            tmp7 = tmp7->next;
        }
    }
}

///
/// \param head
/// \param split
/// \return
struct card *commandSI(card *head, int split) {

    card *head1 = NULL;
    card *head2 = NULL;
    card *tail1 = NULL;
    card *newDeck = NULL;
    card *tmp;
    int splitRest = 52 - split;
    int shuffleNO;
    int biggestPile;

    head1 = head;
    head2 = head;
    tail1 = head1;
    if (split == 52 || split == 0) {
        return head;
    }


    for (int i = 0; i < split; ++i) {
        head2 = head2->next;
    }

    for (int i = 0; i < split - 1; ++i) {
        tail1 = tail1->next;
    }

    if (split > splitRest) {
        shuffleNO = splitRest;
        biggestPile = 1;
    } else {
        shuffleNO = split;
        biggestPile = 2;
    }

    newDeck = head1;
    tmp = newDeck;
    head1 = head1->next;
    for (int i = 0; i < shuffleNO * 2 - 1; ++i) {
        if (i % 2 == 1) {
            tmp->next = head1;
            tmp = tmp->next;
            head1 = head1->next;
        } else {
            tmp->next = head2;
            tmp = tmp->next;
            head2 = head2->next;
        }

    }

    if (biggestPile == 1) {
        while (head1 != tail1->next) {
            tmp->next = head1;
            tmp = tmp->next;
            head1 = head1->next;

        }
    } else {
        while (head2 != NULL) {
            tmp->next = head2;
            tmp = tmp->next;
            head2 = head2->next;
        }
    }

    tmp->next = NULL;
    return newDeck;
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

    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    printGame(c1, c2, c3, c4, c5, c6, c7, 11);

    printInputStatus(command, true);


}


void printStart(void) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\t\t\t\t\t\t\t\t[]\tF1\n");
    printf("\t\t\t\t\t\t\t\t[]\tF2\n");
    printf("\t\t\t\t\t\t\t\t[]\tF3\n");
    printf("\t\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST command:\n");
    printf("Message:\n");
    printf("INPUT>");
}


int main() {

    bool gameInProgress = true;
    int gamePhase = 0;
    printStart();
    card *deck = NULL;
    card *c1;
    card *c2;
    card *c3;
    card *c4;
    card *c5;
    card *c6;
    card *c7;
    card *f1;
    card *f2;
    card *f3;
    card *f4;

    while (gameInProgress) {
        char input[20];

        fgets(input, 20, stdin);

        int dec = input[0] + input[1];
        int gameCommand = input[2];
        int gameAction = input[5];
        int number = ((input[3] - 48) * 10) + (input[4] - 48);

        switch (dec) {
            case 144:
                if (gamePhase == 0) {
                    printf("\nLoad deck\n");
                    if (input[2] != 10) {
                        char *fileName;
                        fileName = strstr(input, " ") + 1;
                        strtok(fileName, "\n");
                        deck = loadDeck(fileName, input);
                    } else
                        deck = loadDeck("", input);
                } else {
                    defaultTemplate(input, "ERROR");
                }

                break;
            case 90:
                if (gamePhase == 0) {
                    printf("\nPlay\n");
                    gamePhase = 1;
                    playGame(c1, c2, c3, c4, c5, c6, c7, deck, input);
                } else {
                    printf("\nThis command is not available during the play phase\n");
                }

                break;
            case 151:
                if (gamePhase == 0) {
                    printf("\nSave deck\n");

                    if (input[2] != 10) {
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
            case 91:
                if (gamePhase == 1) {
                    printf("\nQuit current game\n");
                    gamePhase = 0;
                }

                break;
            case 170:
                if (gamePhase == 0) {
                    printf("\nShow\n");
                    showCommand(input, deck);
                } else {
                    printf("\nCommand not available in the PLAY phase\n");
                }

                break;
            case 162:
                if (gamePhase == 0) {
                    printf("Quit");
                    gameInProgress = false;
                } else {
                    printf("\nCommand not available in the PLAY phase\n");
                }
                break;

            case 156:
                if (gamePhase == 0) {
                    if (deck == NULL) {
                        printf("Error need to load deck first");
                    } else {
                        printf("\nSplit shuffle\n");
                        if (number < 52 && number > 0) {
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
                if (gamePhase == 1) {
                    if (gameCommand == 45 || gameAction == 45) {
                        printf("\nGame moveCard\n");
                        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
                        printInputStatus(input, true);
                    } else {

                    }
                }

                break;
        }

    }

    return 0;
}



