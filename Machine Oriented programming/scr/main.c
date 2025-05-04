// main.c
#include <stdio.h>
#include <string.h>
#include "card.h"
#include <stdlib.h>
#include <time.h>


extern Node* load_deck_from_file(const char* filename);
extern void print_deck(Node* head);

void flipCards(Node* columns[7], int face_up){
    for(int col=0; col<7; col++){
        Node* temp = columns[col];
        while(temp!=NULL){
            temp->face_up=face_up;
            temp=temp->next;
        }
    }
   /* Node* temp = deck;
    while(temp != NULL){
        temp->face_up=face_up;
        temp = temp->next;
    }*/
}

void layout(Node* deck, Node* columns[7]){
    int sizes[7]={1, 6, 7, 8, 9, 10, 11};
    Node* tails[7]={NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    Node* current = deck;

    for(int col = 0; col < 7; col++){
        for(int i = 0; i<sizes[col]; i++) {
            if (!current) break;

            Node *next = current->next;
            current->next = NULL;
            if (!columns[col]) {
                columns[col] = current;
                tails[col] = current;
            } else if (tails[col]){
                tails[col]->next = current;
                tails[col] = current;
            } else{
                columns[col]=current;
                tails[col]=current;
            }
            current = next;
                 }
        }
}

void layoutPrint(Node* columns[7]) {
    printf(" C1   C2   C3   C4   C5   C6   C7\n");

    int max_rows = 0;
    for (int col = 0; col < 7; col++) {
        int height = 0;
        Node *temp = columns[col];
        while (temp) {
            height++;
            temp = temp->next;
        }
        if (height > max_rows)
            max_rows = height;
    }
    int more = 1;
    int row = 0;
   for(int row=0; row<max_rows; row++){
       for(int col = 0;col<7;col++){
           Node *temp = columns[col];
           for(int i = 0; i<row; i++){
               if(temp) temp=temp->next;
           }
           if(temp){
               if(temp->face_up)
                   printf(" %c%c  ",temp->card.rank,temp->card.suit);
               else
                   printf("[ ]  ");
           } else{
               printf("     ");
           }
       }
       printf("\n");
   }
}

int main() {
    //  char filename[100];
    //  printf("Enter file name to load deck: ");
    // scanf("%s", filename);
    srand(time(NULL));
    Node *deck = load_deck_from_file("deck.txt");
    Node* columns[7]={NULL};
    layout(deck, columns);
    //layoutPrint(columns);
    flipCards(columns,1); //hidden cards
    char input[8];

    while (1) {
        //system("cls");
        for (int i = 0; i < 40; i++) printf("\n");

        layoutPrint(columns);
        //print_deck(deck);
        printf("\nEnter SW to Show Cards, Enter HC to Hide Cards, SR to Shuffle Cards, Enter QQ to EXIT.\n");
        printf("Enter Input:  ");
        scanf("%3s", input);

        if (strcmp(input, "SW") == 0) {
            flipCards(columns, 1);
            printf("Cards Shown");
        } else if (strcmp(input, "HC") == 0) {
            flipCards(columns, 0);
            printf("Cards Hidden");
        } else if (strcmp(input, "SR") == 0) {
            deck = load_deck_from_file("deck.txt");
            deck=shuffleDeck(deck);
            layout(deck,columns);
            //flipCards(columns,1);
            printf("Deck Shuffled");
        } else if (strcmp(input, "QQ") == 0) {
            break;
        }
}


    /*  if (deck != NULL) {
        Node* temp = deck;
        print_deck(deck);
         //Flip cards face up
         char input[10];
         printf("Type ""SW"" to flip cards:  ");
        scanf("%3s",input);

        if(strcmp(input, "SW")==0){
         //   Node* temp = deck;
            while (temp != NULL) {
                temp->face_up = 1;
                temp = temp->next;
            }
        }

        print_deck(deck);
   }*/

  return 0;
}

