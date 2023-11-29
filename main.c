#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct card{
    int cardSuit;
    int cardFace;
};

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

void displayDeck(struct card array[], int deckLength);
void removeElement(struct card deck[],int position, int* deckLength);
void displayHand(int suits[], int faces[]);
void drawHand(struct card deck[], int suitsInHand[], int facesInHand[], int* deckLength);
enum handType analyzeHand(int suits[], int faces[]);


int main() {

    // Set the seed for random() according to time.
    srand(time(NULL));

    // Set deck length.
    struct card deck[52];
    int deckLength = 52;

    int suitsInHandOne[] = {0, 0 ,0 ,0};
    int suitsInHandTwo[] = {0, 0 ,0 ,0};

    int facesInHandOne[] = {0, 0 ,0 ,0,0,0,0,0,0,0,0,0,0};
    int facesInHandTwo[] = {0, 0 ,0 ,0,0,0,0,0,0,0,0,0,0};


    // Fill deck with cards.
    for (int i = 0; i < deckLength; i++) {
        deck[i].cardSuit = i / 13 + 1;
        deck[i].cardFace = i % 13 + 1;
    }

    // Draw five cards from deck.
    drawHand(deck, suitsInHandOne, facesInHandOne, &deckLength);
    printf("HAND ONE:\n");
    displayHand(suitsInHandOne,facesInHandOne);
    enum handType handOne = analyzeHand(suitsInHandOne, facesInHandOne);
    printf("%d\n", handOne);
    printf("\n");

    drawHand(deck, suitsInHandTwo, facesInHandTwo, &deckLength);
    printf("HAND TWO:\n");
    displayHand(suitsInHandTwo,facesInHandTwo);
    enum handType handTwo = analyzeHand(suitsInHandTwo, facesInHandTwo);
    printf("%d\n", handTwo);
    printf("\n");

    if (handOne < handTwo) {
        printf("HAND ONE WINS\n");
    } else if (handTwo < handOne) {
        printf("HAND TWO WINS\n");
    } else {
        printf("DRAW\n");
    }

//    TEST CASES.
//    printf("EXPECTING FLUSH(4)\n");
//    int suitsInFlush[] = {0, 5, 0, 0};
//    int facesInFlush[] = {1, 0,1,0,0,1,1,0,1,0,0,0,0};
//    enum handType test = analyzeHand(suitsInFlush, facesInFlush);
//    printf("ENUM IS %d\n", test);
//
//
//    printf("EXPECTING STRAIGHT(6)\n");
//    int suitsInStraight[] = {1, 4, 0, 0};
//    int facesInStraight[] = {1, 1,1,1,1,0,0,0,0,0,0,0,0};
//    test = analyzeHand(suitsInStraight, facesInStraight);
//    printf("ENUM IS %d\n", test);
//
//
//    printf("EXPECTING STRAIGHT FLUSH(1)\n");
//    int suitsInStraightFlush[] = {0, 5, 0, 0};
//    int facesInStraightFlush[] = {1, 1,1,1,1,0,0,0,0,0,0,0,0};
//    test = analyzeHand(suitsInStraightFlush, facesInStraightFlush);
//    printf("ENUM IS %d\n", test);
//
//
//    printf("EXPECTING ROYALFLUSH(0)\n");
//    int suitsInRoyalFlush[] = {0, 5, 0, 0};
//    int facesInRoyalFlush[] = {1, 0,0,0,0,0,0,0,0,1,1,1,1};
//    test = analyzeHand(suitsInRoyalFlush, facesInRoyalFlush);
//    printf("ENUM IS %d\n", test);

    return 0;
}

enum handType analyzeHand(int suits[], int faces[]) {
    int num_consec = 0;
    int rank, suit;
    bool straight = false;
    bool royal = false;
    bool flush = false;
    bool four = false;
    bool three = false;
    int pairs = 0;

    // check for flush – 5 cards of the same suit
    for (suit = 0; suit < 4; suit++) {
        if (suits[suit] == 5) {
            flush = true;
        }
    }

    // Check for royal - straight of 10-ace.
    for (rank = 9; rank < 13 && faces[rank]; rank++) {
        num_consec++;
    }

    if (num_consec == 4 && faces[0] == 1) {
        royal = true;
    }




// check for straight – eg. One each of 5,6,7,8,9
// locate the first card
    rank = 0;
    num_consec = 0;
    while (faces[rank] == 0) {
        rank++;

    }
// count the consecutive non-zero faces
    for (; rank < 13 && faces[rank]; rank++) {
        num_consec++;
    }

    if (num_consec == 5) {
        straight = true;
    }

    //* check for 4-of-a-kind, 3-of-a-kind, and pairs */
    for (rank = 0; rank < 13; rank++) {
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

    // Check what type of hand it is and return.
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

void drawHand(struct card deck[], int suitsInHand[], int facesInHand[], int* ptrDeckLength) {
    int position = 0;
    for (int i = 0; i < 5; i++) {
        position = rand() % *ptrDeckLength;
        suitsInHand[deck[position].cardSuit - 1] += 1;
        facesInHand[deck[position].cardFace - 1] += 1;
        removeElement(deck, position, ptrDeckLength);
        (*ptrDeckLength)--;
    }
}

void displayDeck(struct card array[], int deckLength) {
    printf("CURRENT DECK:\n");
    for (int i = 0; i < deckLength; i++) {
        printf("[%d, %d]\n", array[i].cardSuit, array[i].cardFace);
    }
    printf("\n\n");

}

void removeElement(struct card deck[], int position, int* ptrDeckLength) {
    if (position >= *ptrDeckLength)
    {
        printf ("\nError");
    }
    else {
        for (int i = position; i < *ptrDeckLength - 1; i++) {
            deck[i] = deck[i + 1];
        }
    }
}

void displayHand(int suits[], int faces[]) {
    for (int i = 0; i < 4; i++) {
        printf("%d ", suits[i]);
    }
    printf("\n");
    for (int i = 0; i < 13; i++) {
        printf("%d ", faces[i]);
    }
    printf("\n");
}
