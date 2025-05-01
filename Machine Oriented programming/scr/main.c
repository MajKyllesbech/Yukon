// main.c
#include <stdio.h>
#include <string.h>
#include "card.h"

extern Node* load_deck_from_file(const char* filename);
extern void print_deck(Node* head);

int main() {
    char filename[100];
    printf("Enter file name to load deck: ");
    scanf("%s", filename);

    Node* deck = load_deck_from_file(filename);
    if (deck != NULL) {
        // Flip cards face up
        Node* temp = deck;
        while (temp != NULL) {
            temp->face_up = 1;
            temp = temp->next;
        }

        print_deck(deck);
    }

    return 0;
}

