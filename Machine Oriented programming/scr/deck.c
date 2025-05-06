// deck.c
#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// Create a new card node
Node* create_card(char rank, char suit) {
    Node* new_card = (Node*)malloc(sizeof(Node));
    new_card->card.rank = rank;
    new_card->card.suit = suit;
    new_card->face_up = 0; // Default to face down
    new_card->next = NULL;
    return new_card;
}

// Add card to the end of the deck
void append_card(Node** head, char rank, char suit) {
    Node* new_card = create_card(rank, suit);
    if (*head == NULL) {
        *head = new_card;
    } else {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_card;
    }
}

// Create a new ordered deck: AC to KC, then Diamonds, Hearts, Spades
Node* create_standard_deck() {
    char suits[] = {'C', 'D', 'H', 'S'};
    char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    
    Node* deck = NULL;
    for (int s = 0; s < 4; s++) {
        for (int r = 0; r < 13; r++) {
            append_card(&deck, ranks[r], suits[s]);
        }
    }
    return deck;
}

// Print the deck (for debugging)
void print_deck(Node* head) {
    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        if (temp->face_up)
            printf("%c%c ", temp->card.rank, temp->card.suit);
        else
            printf("[ ] ");
        count++;
        if (count % 13 == 0) printf("\n");
        temp = temp->next;
    }
    printf("\n");
}

#include <string.h>
#include <ctype.h>

int is_valid_card(char rank, char suit) {
    const char* valid_ranks = "A23456789TJQK";
    const char* valid_suits = "CDHS";
    return strchr(valid_ranks, rank) && strchr(valid_suits, suit);
}

Node* load_deck_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Message: Error - Cannot open file %s\n", filename);
        return NULL;
    }

    Node* deck = NULL;
    char line[10];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("DEBUG: line = '%s'\n", line);
        if (strlen(line) < 2) continue; // Skip empty or invalid lines

        char rank = toupper(line[0]);
        char suit = toupper(line[1]);

        if (!is_valid_card(rank, suit)) {
            printf("Message: Error - Invalid card '%c%c' on line %d\n", rank, suit, count + 1);
            fclose(file);
            return NULL;
        }

        append_card(&deck, rank, suit);
        count++;
    }

    fclose(file);

    if (count != 52) {
        printf("Message: Error - Deck must contain exactly 52 cards, got %d\n", count);
        return NULL;
    }

    printf("Message: OK - Deck loaded from %s\n", filename);
    return deck;
}

int getLength(Node* head){
    int count = 0;
    while(head){
        count++;
        head = head->next;
    }
    return count;
}

void insertCardRandomly(Node** head, Node* newNode, int index){
    if(index==0 || *head ==NULL){
        newNode->next=*head;
        *head=newNode;
        return;
    }
    Node* current = *head;
    for(int i = 0; i<index - 1; i++){
        if(current->next==NULL)
            break;
        current=current->next;
    }
        newNode->next=current->next;
        current->next=newNode;
}

Node* shuffleDeck(Node* deck){
    printf("Shuffle");
    Node* shuffled = NULL;
    int count = 0;
    while(deck !=NULL){
        Node* card = deck;
        deck = deck->next;
        card->next =NULL;
        int length = getLength(shuffled);
        int random = (length==0)?0:rand()%(length+1);
        //testing
        printf("Inserting %c%c at index %d\n", card->card.rank, card->card.suit,random);
        insertCardRandomly(&shuffled,card,random);
        count++;
    }
    //testing
    printf("Total inserted into shuffled deck: %d\n", count);
    return shuffled;
}

Node* siSplit(Node* deck){
    Node* splitDeck1 = deck;
    Node* splitDeck2 = NULL;
    Node* current = deck;
    int i = 1;
    int split = 26;
    while(current != NULL && i<split){
        current = current->next;
        i++;
    }
    if(current == NULL) return NULL;
    splitDeck2=current->next;
    current->next=NULL;
    Node* newShuffledDeck = NULL;
    Node* endNode = NULL;

    while(splitDeck1!=NULL||splitDeck2!=NULL){
        if(splitDeck1 != NULL){
            Node* next = splitDeck1->next;
            splitDeck1->next=NULL;

            if(newShuffledDeck==NULL){
                newShuffledDeck=endNode=splitDeck1;
            } else{
                endNode->next=splitDeck1;
                endNode=splitDeck1;
            }
            splitDeck1=next;
        }
        if(splitDeck2!=NULL){
            Node* next = splitDeck2->next;
            splitDeck2->next=NULL;

            if(newShuffledDeck==NULL){
                newShuffledDeck=endNode=splitDeck2;
            }else{
                endNode->next=splitDeck2;
                endNode=splitDeck2;
            }
            splitDeck2 = next;
        }
    }
    return newShuffledDeck;
}

Node* rebuildDeckStructure(Node* columns[7]){
    Node* completeDeck = NULL;
    Node* end = NULL;

    for(int col = 0; col<7; col++){
        Node* current = columns[col];
        while(current){
            Node* next=current->next;
            current->next=NULL;
            if(completeDeck==NULL){
                completeDeck=end=current;
            } else{
                end->next=current;
                end=current;
            }
            current = next;
        }
        columns[col]=NULL;
    }
    return completeDeck;
}