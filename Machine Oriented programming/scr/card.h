// card.h
#ifndef CARD_H
#define CARD_H

typedef struct {
    char rank;   // A, 2-9, T, J, Q, K
    char suit;   // C, D, H, S
} Card;

typedef struct Node {
    Card card;
    int face_up; // 1 = face up, 0 = face down
    struct Node* next;
} Node;

#endif

Node* load_deck_from_file(const char* filename);

Node* shuffleDeck(Node* deck);

Node* siSplit(Node* deck);

Node* rebuildDeckStructure(Node* columns[7]);
void save_deck_to_file(const char *filename, Node *deck);