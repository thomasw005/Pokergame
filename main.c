// Thomas Wilson
// 11/29/2023
// Lecture 5 Assignment 1 Program 1
// This program fills a deck of cards, picks a hand of 5 cards randomly from the deck twice, and then decides who has the better hand according to poker rules.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Common numbers for deck length, number of suits/faces, and size of hand.
#define CARDSINDECK 52
#define SUITS 4
#define FACES 13
#define HANDSIZE 5

// Card structure, contains what type of suit and face the card has according to an integer value (suit 1-4)(face 1-13).
struct card{
    int cardSuit;
    int cardFace;
};

// Enum containing types of hands in poker.
enum handType {
    RoyalFlush,
    StraightFlush,
    FourOfAKind,
    FullHouse,
    Flush,
    Straight,
    ThreeOfAKind,
    TwoPair,
    Pair,
    HighCard
};

void drawHand(struct card deck[], int suitsInHand[], int facesInHand[], int* deckLength);
void removeElement(struct card deck[],int position, int* deckLength);
void displayHand(int suits[], int faces[]);
void displayDeck(struct card array[], int deckLength);
enum handType analyzeHand(int suits[], int faces[]);

int main() {

    // Set the seed for random() according to time.
    srand(time(NULL));

    // Creates 52 objects of structure type card. Sets deck length to 52.
    struct card deck[CARDSINDECK];
    int deckLength = CARDSINDECK;

    // Create and initialize hand one.
    int suitsInHandOne[] = {0, 0 ,0 ,0};
    int suitsInHandTwo[] = {0, 0 ,0 ,0};

    // Create and initialize hand two.
    int facesInHandOne[] = {0, 0 ,0 ,0,0,0,0,0,0,0,0,0,0};
    int facesInHandTwo[] = {0, 0 ,0 ,0,0,0,0,0,0,0,0,0,0};


    // Fill deck with cards.
    for (int i = 0; i < deckLength; i++) {
        deck[i].cardSuit = i / FACES + 1;
        deck[i].cardFace = i % FACES + 1;
    }

    // Display starting deck.
    // displayDeck(deck, deckLength);

    // Draw first hand of five cards from deck.
    drawHand(deck, suitsInHandOne, facesInHandOne, &deckLength);
    printf("HAND ONE:\n");
    displayHand(suitsInHandOne,facesInHandOne);

    // Checks type of hand and saves it as an enum.
    enum handType handOne = analyzeHand(suitsInHandOne, facesInHandOne);
    printf("\n");

    // Draw second hand of five cards from deck.
    drawHand(deck, suitsInHandTwo, facesInHandTwo, &deckLength);
    printf("HAND TWO:\n");
    displayHand(suitsInHandTwo,facesInHandTwo);

    // Checks type of hand and saves it as an enum.
    enum handType handTwo = analyzeHand(suitsInHandTwo, facesInHandTwo);
    printf("\n");

    // Compare enum values of each hand to determine which one wins according to position within enum structure.
    if (handOne < handTwo) {
        printf("HAND ONE WINS\n");
    } else if (handTwo < handOne) {
        printf("HAND TWO WINS\n");
    } else {
        printf("DRAW\n");
    }

    // Display final deck.
    // displayDeck(deck, deckLength);

    return 0;
}

// Chooses a random card from the deck and updates the hand depending on which card was pulled.
// Removes that card from the deck and makes "deckLength" smaller.
void drawHand(struct card deck[], int suitsInHand[], int facesInHand[], int* ptrDeckLength) {
    int position = 0;
    for (int i = 0; i < HANDSIZE; i++) {
        position = rand() % *ptrDeckLength;
        suitsInHand[deck[position].cardSuit - 1] += 1;
        facesInHand[deck[position].cardFace - 1] += 1;
        removeElement(deck, position, ptrDeckLength);
        (*ptrDeckLength)--;
    }
}

// Starting at the position where the card is removed, shuffles all cards after one spot forward, effectively "shortening" the list.
void removeElement(struct card deck[], int position, int* ptrDeckLength) {
    for (int i = position; i < *ptrDeckLength - 1; i++) {
        deck[i] = deck[i + 1];
    }
}

// Loops through suits and faces array, outputting the values for each integer.
void displayHand(int suits[], int faces[]) {
    for (int i = 0; i < SUITS; i++) {
        printf("%d ", suits[i]);
    }
    printf("\n");
    for (int i = 0; i < FACES; i++) {
        printf("%d ", faces[i]);
    }
    printf("\n");
}

// Loops through deck card array and prints out each objects suit and face.
void displayDeck(struct card array[], int deckLength) {
    printf("CURRENT DECK:\n");
    for (int i = 0; i < deckLength; i++) {
        printf("[%d, %d]\n", array[i].cardSuit, array[i].cardFace);
    }
    printf("\n\n");
}

// Takes in a hand's suits and faces array, then returns an enum of what type of hand it is.
enum handType analyzeHand(int suits[], int faces[]) {
    int num_consec = 0;
    int rank, suit;
    bool straight = false;
    bool royal = false;
    bool flush = false;
    bool four = false;
    bool three = false;
    int pairs = 0;

    // Checks for a flush – five cards of the same suit.
    for (suit = 0; suit < SUITS; suit++) {
        if (suits[suit] == HANDSIZE) {
            flush = true;
        }
    }

    // Checks for a royal - straight of 10-ace.
    for (rank = 9; rank < FACES && faces[rank]; rank++) {
        num_consec++;
    }
    if (num_consec == SUITS && faces[0] == 1) {
        royal = true;
    }

    // Locates the first card.
    // Checks for a straight – one each of 5,6,7,8,9.
    rank = 0;
    num_consec = 0;
    while (faces[rank] == 0) {
        rank++;

    }

    // Counts the consecutive non-zero faces.
    for (; rank < FACES && faces[rank]; rank++) {
        num_consec++;
    }
    if (num_consec == HANDSIZE) {
        straight = true;
    }

    // Checks for four of a kind, three of a kind, and how many pairs there are.
    for (rank = 0; rank < FACES; rank++) {
        switch (faces[rank]) {
            case 4:
                four = true;
                break;
            case 3:
                three = true;
                break;
            case 2:
                pairs++;
                break;
        }
    }

    // Check what type of hand it is and return enum value.
    if (royal && flush) {
        printf("ROYAL FLUSH\n");
        return RoyalFlush;
    } else if (straight && flush) {
        printf("STRAIGHT FLUSH\n");
        return StraightFlush;
    } else if (four) {
        printf("FOUR OF A KIND\n");
        return FourOfAKind;
    } else if (three && pairs == 1) {
        printf("FULL HOUSE\n");
        return FullHouse;
    } else if (flush) {
        printf("FLUSH\n");
        return Flush;
    } else if (straight) {
        printf("STRAIGHT\n");
        return Straight;
    } else if (three) {
        printf("THREE OF A KIND\n");
        return ThreeOfAKind;
    } else if (pairs == 2) {
        printf("TWO PAIR\n");
        return TwoPair;
    } else if (pairs == 1) {
        printf("PAIR\n");
        return Pair;
    } else {
        printf("HIGH CARD\n");
        return HighCard;
    }
}