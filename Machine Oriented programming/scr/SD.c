#include <stdio.h>
#include <string.h>
#include "card.h"  // Include your card and Node definitions

// Function to save the deck to a file
void save_deck_to_file(const char *filename, Node *deck) {
    if (!deck) {
        printf("Deck is empty! Nothing to save.\n");
        return;
    }

    FILE *file = fopen(filename, "w"); // Open file for writing
    if (!file) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    Node *temp = deck;
    while (temp) {
        fprintf(file, "%c%c\n", temp->card.rank, temp->card.suit); // Write each card to file
        temp = temp->next;
    }

    fclose(file); // Close the file
    printf("Deck successfully saved to file: %s\n", filename);
}