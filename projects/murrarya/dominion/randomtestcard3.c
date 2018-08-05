#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

typedef enum {false, true} bool;

bool assertTrue(int var1, int var2, char* description) {
    bool expr = var1 == var2;
    if (!expr) {
        printf("%s - ", description);
        printf("\x1B[31mFAILED\x1B[0m\n");
        printf("Expected %d but got %d\n", var1, var2);
    }

    return expr;
}

void randomlyGenerateGameState(struct gameState* G) {
	// Set number of players
	int numPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;
	if (numPlayers < 2) {
		numPlayers = 2;
	}
    G->numPlayers = numPlayers;
	
    for (int i = adventurer; i <= treasure_map; i++) {
        G->supplyCount[i] = floor(Random() * 10);
    }

    // Set curses
    int maxCurseCards = (numPlayers - 1) * 10;
    G->supplyCount[curse] = floor(Random() * maxCurseCards);
    // Set lands
    int maxLands = numPlayers == 2 ? 8 : 12;
    G->supplyCount[estate] = floor(Random() * maxLands);
    G->supplyCount[duchy] = floor(Random() * maxLands);
    G->supplyCount[province] = floor(Random() * maxLands);

    // Set treasures
    G->supplyCount[copper] = floor(Random() * 60);
    G->supplyCount[silver] = floor(Random() * 40);
    G->supplyCount[gold] = floor(Random() * 30);

    // Set player decks, hands, and discard piles
    for (int p = 0; p < numPlayers; p++) {
        int pDeckCount = rand() % MAX_DECK;
        int pHandCount = rand() % MAX_HAND;
        int pDiscardCount = rand() % MAX_DECK;
        G->deckCount[p] = pDeckCount;
        G->handCount[p] = pHandCount;
        G->discardCount[p] = pDiscardCount;

        for (int i = 0; i < pDeckCount; i++) {
            G->deck[p][i] = rand() % (treasure_map + 1 - copper) + copper;
        }

        for (int i = 0; i < pHandCount; i++) {
            G->hand[p][i] = rand() % (treasure_map + 1 - copper) + copper;
        }

        for (int i = 0; i < pDiscardCount; i++) {
            G->discard[p][i] = rand() % (treasure_map + 1 - copper) + copper;
        }
    }

    // Set played cards
    int numPlayedCards = floor(Random() * MAX_DECK);
    G->playedCardCount = numPlayedCards;
    for (int i = 0; i < numPlayedCards; i++) {
        G->playedCards[i] = rand() % (treasure_map + 1 - adventurer) + adventurer;
    }

    // Set other state variables
    G->outpostPlayed = 0; // never used
    G->phase = floor(Random() * 3);
    G->numActions = floor(Random() * 10);
    G->numBuys = floor(Random() * 10);
    G->whoseTurn = floor(Random() * numPlayers);

    for (int p = 0; p < numPlayers; p++) {
        updateCoins(p, G, 0);
    }
}

void randomTestCouncilRoom() {
    printf("\n--- TESTING COUNCIL ROOM CARD ---\n");
    bool allTestsPassed = true;
    for (int i = 0; i < 2000; i++) {
        struct gameState G;
        memset(&G, 23, sizeof(struct gameState));
        randomlyGenerateGameState(&G);
        int result;

        int crPos = floor(Random() * G.handCount[G.whoseTurn]);
        G.hand[G.whoseTurn][crPos] = council_room;
        updateCoins(G.whoseTurn, &G, 0);

        int playerPreHandCounts[MAX_PLAYERS] = {0, 0, 0, 0};
        for (int p = 0; p < G.numPlayers; p++) {
            playerPreHandCounts[p] = G.handCount[p];
        }
        int preNumBuys = G.numBuys;
        int prePlayedCount = G.playedCardCount;
        G.hand[G.whoseTurn][0] = council_room;

        result = cardEffect(council_room, 0, 0, 0, &G, crPos, 0);
        assertTrue(result, 0, "Council room succeeds when played");
        assertTrue(G.handCount[G.whoseTurn], playerPreHandCounts[G.whoseTurn] + 4, "Player who played card gains 4 cards");
        assertTrue(G.numBuys, preNumBuys + 1, "Player who played card gets 1 more buy");

        // Test if all other players drew one card
        bool allOtherPlayersDrewACard = true;
        for (int p = 0; p < G.numPlayers; p++) {
            if (p == G.whoseTurn) {
                // Only interested in players who aren't the one who played the card
                continue;
            }
            allOtherPlayersDrewACard &= G.handCount[p] == playerPreHandCounts[p] + 1;
        }
        assertTrue(allOtherPlayersDrewACard, true, "All other players draw 1 card");
        assertTrue(G.playedCardCount, prePlayedCount + 1, "Council room is put in played pile after being played");
    }
    
    if (allTestsPassed) {
        printf("\x1B[32mALL TESTS PASSED\x1B[0m\n");
    } else {
        printf("Some tests failed\n");
    }
}

int main() {
    PutSeed(-1);
    srand(time(0));
    randomTestCouncilRoom();
    return 0;
}
