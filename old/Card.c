#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct Card {
    char value[2];
    bool visible;
    struct Card* next;
} card;


//Creates the deck of cards with the right cards of a standard card set.
card* createDeck (char filename[]) {
    char nameOfFile[28];
    card* head = NULL, *temp, *tail = NULL;

    FILE* f;
    if(filename == "") {

        strcpy(nameOfFile, "StandardDeck.txt");

        f = fopen(nameOfFile, "w");
        fprintf(f, "AC\n");
        fprintf(f, "2C\n");
        fprintf(f, "3C\n");
        fprintf(f, "4C\n");
        fprintf(f, "5C\n");
        fprintf(f, "6C\n");
        fprintf(f, "7C\n");
        fprintf(f, "8C\n");
        fprintf(f, "9C\n");
        fprintf(f, "TC\n");
        fprintf(f, "JC\n");
        fprintf(f, "QC\n");
        fprintf(f, "KC\n");
        fprintf(f, "AD\n");
        fprintf(f, "2D\n");
        fprintf(f, "3D\n");
        fprintf(f, "4D\n");
        fprintf(f, "5D\n");
        fprintf(f, "6D\n");
        fprintf(f, "7D\n");
        fprintf(f, "8D\n");
        fprintf(f, "9D\n");
        fprintf(f, "TD\n");
        fprintf(f, "JD\n");
        fprintf(f, "QD\n");
        fprintf(f, "KD\n");
        fprintf(f, "AH\n");
        fprintf(f, "2H\n");
        fprintf(f, "3H\n");
        fprintf(f, "4H\n");
        fprintf(f, "5H\n");
        fprintf(f, "6H\n");
        fprintf(f, "7H\n");
        fprintf(f, "8H\n");
        fprintf(f, "9H\n");
        fprintf(f, "TH\n");
        fprintf(f, "JH\n");
        fprintf(f, "QH\n");
        fprintf(f, "KH\n");
        fprintf(f, "AS\n");
        fprintf(f, "2S\n");
        fprintf(f, "3S\n");
        fprintf(f, "4S\n");
        fprintf(f, "5S\n");
        fprintf(f, "6S\n");
        fprintf(f, "7S\n");
        fprintf(f, "8S\n");
        fprintf(f, "9S\n");
        fprintf(f, "TS\n");
        fprintf(f, "JS\n");
        fprintf(f, "QS\n");
        fprintf(f, "KS\n");

        fclose(f);
    }
    else{
        strcpy(nameOfFile, filename);
        strcat(nameOfFile, ".txt");
    }

    f = fopen(nameOfFile, "r");

    temp = (card*)malloc(sizeof(card));
    while (fscanf(f, "%s,", temp -> value) != EOF){
        if (head == NULL){
            head = temp;
        }
        else{
            tail -> next = temp;
        }
        tail = temp;
        tail -> next = NULL;
        temp = (card*) malloc(sizeof(card));
    }
    fclose(f);
    return head;
}

//Shuffles the deck, splitting it into two piles based on the split-value.
struct card* commandSI(card* head, int split){

    card* head1 = NULL;
    card* head2 = NULL;
    card* tail1 = NULL;
    card* newDeck = NULL;
    card* tmp;
    int splitRest = 52-split;
    int shuffleNO;
    int biggestPile;

    head1 = head;
    head2 = head;
    tail1 = head1;
    if(split == 52 || split == 0){
        return head;
    }


    for (int i = 0; i < split; ++i) {
        head2 = head2->next;
    }

    for (int i = 0; i < split-1; ++i){
        tail1 = tail1->next;
    }

    if(split>splitRest){
        shuffleNO = splitRest;
        biggestPile = 1;
    } else{
        shuffleNO = split;
        biggestPile = 2;
    }

    newDeck = head1;
    tmp = newDeck;
    head1 = head1->next;
    for (int i = 0; i < shuffleNO*2-1; ++i) {
        if(i%2 == 1){
            tmp->next = head1;
            tmp = tmp->next;
            head1 = head1->next;
        } else{
            tmp->next = head2;
            tmp = tmp->next;
            head2 = head2->next;
        }

    }

    if(biggestPile == 1){
        while(head1 != tail1->next){
            tmp->next = head1;
            tmp = tmp->next;
            head1 = head1->next;

        }
    } else{
        while(head2 != NULL){
            tmp->next = head2;
            tmp = tmp->next;
            head2 = head2->next;
        }
    }

    tmp->next = NULL;
return newDeck;
}


//Saves the deck to a file.
void saveDeck(card* deck, char filename[]){
    char nameOfFile[28];
    FILE* f;
    strcpy(nameOfFile,filename);
    strcat(nameOfFile,".txt");
    f = fopen(nameOfFile,"w");

    while(deck->value!=NULL){
        fprintf(f,deck->value);
        fprintf(f,"\n");
        deck = deck->next;
    }
    fclose(f);
}
