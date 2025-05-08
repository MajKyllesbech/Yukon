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
    Node* endNode[7]={NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    Node* current = deck;

    for(int col = 0; col < 7; col++){
        for(int i = 0; i<sizes[col]; i++) {
            if (!current) break;

            Node *next = current->next;
            current->next = NULL;
            if (!columns[col]) {
                columns[col] = current;
                endNode[col] = current;
            } else if (endNode[col]){
                endNode[col]->next = current;
                endNode[col] = current;
            } else{
                columns[col]=current;
                endNode[col]=current;
            }
            current = next;
                 }
        }
    for(int col = 0; col<7; col++){
        int numberOfHiddenCards=col;
        int counter = 0;
        Node* temp = columns[col];
        while(temp){
            temp->face_up=(counter>=numberOfHiddenCards)?1:0;
            temp = temp->next;
            counter++;
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

void foundationsLayout(Node* foundationSpaces[4]){
    printf("\nF1   F2   F3   F4\n");
    for(int i = 0; i < 4; i++){
        if(foundationSpaces[i]){
            Node* top = foundationSpaces[i];
            while (top->next) top = top->next;
            printf(" %c%c  ", top->card.rank, top->card.suit);
        }else{
            printf("[ ]  ");
        }
    }
    printf("\n");
}

int movingCards(Node* columns[7], int fromColumn, char rank, char suit, int toColumn) {
    Node *current = columns[fromColumn];
    Node* prev = NULL;

    while(current){
        if(current->card.rank==rank && current->card.suit==suit){
            break;
        }
        prev=current;
        current=current->next;
    }
    if(!current){
        printf("Card not in column.%d\n", fromColumn+1);
        return 0;
    }
    if(prev==NULL){
        columns[fromColumn]=NULL;
    }else{
        prev->next=NULL;
    }
    if(columns[toColumn]==NULL){
        columns[toColumn]=current;
    } else{
        Node* endOf = columns[toColumn];
        while(endOf->next)endOf=endOf->next;
        endOf->next=current;
    }
    printf("Moved cards from C%d:%c%c to C%d\n", fromColumn+1, rank, suit, toColumn+1);
    return 1;
}
int main() {
    //  char filename[100];
    //  printf("Enter file name to load deck: ");
    // scanf("%s", filename);
    int playPhase = 0;
    srand(time(NULL));
    Node *deck = load_deck_from_file("deck.txt");
    Node* columns[7]={NULL};
    Node* foundationSpaces[4] = {NULL};
    layout(deck, columns);
    //layoutPrint(columns);
    flipCards(columns,1); //hidden cards
    char input[32];

    while (1) {
        //system("cls");
        for (int i = 0; i < 10; i++) printf("\n");

        layoutPrint(columns);
        foundationsLayout(foundationSpaces);
        //print_deck(deck);
        if(playPhase==0) {
            printf("\nEnter SW to Show Cards, HC to Hide Cards, SR to Shuffle Cards, SI to Split and Shuffle Cards, SD <filename> to Save Deck and P to enter the Play Phase or QQ to EXIT.\n");
        } else{
            printf("Game is in Start Up Phase. Enter Q to exit to the start up phase.\n");
        }
        printf("Enter Input:  ");
        scanf("%32s", input);

        if (strcmp(input, "SW") == 0) {
            if(playPhase==1){
                printf("Cant use this command, game is in play phase. Press Q to exit the Play Phase.");
            } else {
                flipCards(columns, 1);
                printf("Cards Shown");
            }
        } else if (strcmp(input, "HC") == 0) {
            if(playPhase==1){
                printf("Cant use this command, game is in play phase. Press Q to exit the Play Phase.");
            } else {
                flipCards(columns, 0);
                printf("Cards Hidden");
            }
        } else if (strcmp(input, "SI") == 0) {
            if(playPhase==1){
                printf("Cant use this command, game is in play phase. Press Q to exit the Play Phase.");
            } else {
                deck = rebuildDeckStructure(columns);
                deck = siSplit(deck);
                layout(deck, columns);
                printf("Cards Split Shuffled");
            }
        } else if (strcmp(input, "P") == 0) {
            if(!playPhase){
                playPhase=1;
                layout(deck, columns);
                printf("Play phase has begun.");
            } else {
                printf("Game is currently in play phase.");
            }
        } else if (strcmp(input, "Q") == 0) {
            if(playPhase==1) {
                playPhase = 0;
                printf("The Play Phase has been exited.");
            } else {
                printf("Game is not currently in Play phase.");
            }
        } else if (strcmp(input, "SR") == 0) {
            if(playPhase==1){
                printf("Cant use this command, game is in play phase. Press Q to exit the Play Phase.");
            } else {
                deck = load_deck_from_file("deck.txt");
                deck = shuffleDeck(deck);
                layout(deck, columns);
                //flipCards(columns,1);
                printf("Deck Shuffled");
            }
        } else if (strcmp(input, "QQ") == 0) {
            if(playPhase==1){
                printf("Cant use this command, game is in play phase. Press Q to exit the Play Phase.");
            } else {
                break;
            }
        }
        else if (strncmp(input, "SD", 2) == 0) {
            char filename[50] = "cards.txt"; // Default filename
            if (strlen(input) > 3) {
                // Extract the filename (skip "SD" and the space)
                sscanf(input + 3, "%s", filename);
            }
            save_deck_to_file(filename, deck);
        }
        int fromColumn, toColumn;
        char rank, suit;
        if(sscanf(input, "C%d:%c%c->C%d", &fromColumn,&rank,&suit,&toColumn)==4){
            if(fromColumn>=1&&fromColumn<=7&&toColumn>=1&&toColumn<=7){
                int result = movingCards(columns,fromColumn-1,rank,suit,toColumn-1);
                if(result)
                    printf("Completed\n");
            }else{
                printf("Columns between 1 and 7.");
            }
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