#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define VERBOSE 1

typedef enum {false, true} bool;

bool assertTrue(bool expr, char* description) {
	printf("%s - ", description);
	if (expr) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}

void testAdventurer() {
	printf("\n--- TESTING ADVENTURER CARD ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game
	
	int preHandCount = G.handCount;
	int preDiscardCount = G.discardCount;
	int preDeckCount = G.deckCount;
	int preTreasuresInHand = 0;
	for (int i = 0; i < G.handCount; i++) {
		CARD curCard = G.hand[G.whoseTurn][i];
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

	int postHandCount = G.handCount;
	int postDiscardCount = G.discardCount;
	int postDeckCount = G.deckCount;
	int postTreasuresInHand = 0;
	for (int i = 0; i < G.handCount; i++) {
		CARD curCard = G.hand[G.whoseTurn][i];
		if (curCard == copper || curCard == silver || curCard == gold) {
			postTreasuresInHand++;
		}
	}
	int numCardsDrawn = preDeckCount - postDeckCount;

	assertTrue(postHandCount == preHandCount + 2, "Hand count inc'd by 2");
	assertTrue(postTreasuresInHand - preTreasuresInHand == 2, "2 treasures drawn");
	assertTrue(postDiscardCount - preDiscardCount == numCardsDrawn - 2, "All other cards put in discard pile");
}

int main() {
	testAdventurer();
	return 0;
}