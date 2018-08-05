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
	
	// Randomly choose the set of kingdom cards
    // Shuffle deck and first 10 types are the kingdom cards
    /*
    int numKingCards = treasure_map - adventurer;
	int randomCards[numKingCards];
    for (int i = 0; i < numKingCards; i++) {
        randomCards[i] = i + adventurer;
    }
	for (int i = 0; i < numKingCards; i++) {
		int randIdx = rand() % (treasure_map + 1 - i) + i;
		int tmp = randomCards[randIdx];
		randomCards[randIdx] = randomCards[i];
		randomCards[i] = tmp;
	}
    */
    /*
	int kingdomCards[10];
	for (int i = 0; i < 10; i++) {
		kingdomCards[i] = randomCards[i];
	}
    */
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

//	initializeGame(numPlayers, kingdomCards, rand(), G);
}

void randomTestAdventurer() {
    bool allTestsPassed = false;
	for (int i = 0; i < 2000; i++) {
		struct gameState G;
        memset(&G, 23, sizeof(struct gameState));
		randomlyGenerateGameState(&G);

        int advPos = floor(Random() * G.handCount[G.whoseTurn]);
        G.hand[G.whoseTurn][advPos] = adventurer;
        updateCoins(G.whoseTurn, &G, 0);

        int preHandCount = G.handCount[G.whoseTurn];
        int preDiscardCount = G.discardCount[G.whoseTurn];
        int preDeckCount = G.deckCount[G.whoseTurn];
        int preTreasuresInHand = 0;
        for (int i = 0; i < G.handCount[G.whoseTurn]; i++) {
            int curCard = G.hand[G.whoseTurn][i];
            if (curCard == copper || curCard == silver || curCard == gold) {
                preTreasuresInHand++;
            }
        }

		cardEffect(adventurer, 0, 0, 0, &G, 0, 0); // play Adventurer
		// Effect of adventurer is to draw cards until 2 treasures
		// are found. Thus, hand size should be increased by 2,
		// teasure count increased by 2, and discard pile increased
		// and deck pile decreased by the number of other cards 
		// drawn and then discarded.

		int postHandCount = G.handCount[G.whoseTurn];
		int postDiscardCount = G.discardCount[G.whoseTurn];
		int postDeckCount = G.deckCount[G.whoseTurn];
		int postTreasuresInHand = 0;
		for (int i = 0; i < G.handCount[G.whoseTurn]; i++) {
			int curCard = G.hand[G.whoseTurn][i];
			if (curCard == copper || curCard == silver || curCard == gold) {
				postTreasuresInHand++;
			}
		}
		int numCardsDrawn = preDeckCount - postDeckCount;

        printf("\n---Iteration %d---\n", i);
		allTestsPassed &= assertTrue(postHandCount, preHandCount + 2, "Hand count inc'd by 2");
		allTestsPassed &= assertTrue(postTreasuresInHand - preTreasuresInHand, 2, "2 treasures drawn");
		allTestsPassed &= assertTrue(postDiscardCount - preDiscardCount, numCardsDrawn - 2, "All other cards put in discard pile");
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
	randomTestAdventurer();
	return 0;
}
