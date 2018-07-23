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
		printf("\x1B[32mPASSED\x1B[0m\n");
	} else {
		printf("\x1B[31mFAILED\x1B[0m\n");
	}
}

void testGainCard() {
	printf("\n--- TESTING gainCard() ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game

	// Check that card can be added to deck
	int preDeckCount = G.deckCount[G.whoseTurn];
	int preSupplyCount = G.supplyCount[smithy];
	gainCard(smithy, &G, 1, G.whoseTurn);
	assertTrue(G.deckCount[G.whoseTurn] == preDeckCount + 1, "Gained card is added to deck");
	assertTrue(G.supplyCount[smithy] == preSupplyCount - 1, "Gained card is removed from supply");
	
	// Check that card can be added to hand
	preSupplyCount = G.supplyCount[adventurer];
	int preHandCount = G.handCount[G.whoseTurn];
	gainCard(adventurer, &G, 2, G.whoseTurn);
	assertTrue(G.handCount[G.whoseTurn] == preHandCount + 1, "Gained card is added to hand");
	assertTrue(G.supplyCount[adventurer] == preSupplyCount - 1, "Gained card is removed from supply");

	// Check that card can be added to discard pile
	preSupplyCount = G.supplyCount[village];
	int preDiscardCount = G.discardCount[G.whoseTurn];
	gainCard(village, &G, 3, G.whoseTurn);
	assertTrue(G.discardCount[G.whoseTurn] == preDiscardCount + 1, "Gained card is added to discard pile");
	assertTrue(G.supplyCount[village] == preSupplyCount - 1, "Gained card is removed from supply");

	// Check that card cannot be gained if supply pile is empty
	G.supplyCount[smithy] = 0;
	preHandCount = G.handCount[G.whoseTurn];
	int result = gainCard(smithy, &G, 1, G.whoseTurn);
	assertTrue(result == -1, "gainCard() exits with error status if card supply is empty");
	assertTrue(G.supplyCount[smithy] == 0, "Card's supply is not decremented if pile is empty");
	assertTrue(G.handCount = preHandCount, "Card is not added to hand if supply pile is empty");

	// Check that card cannot be gained if it isn't in the game
	G.supplyCount[embargo] = -1; // Should be unnecessary but just to be safe...
	result = gainCard(embargo, &G, 1, G.whoseTurn);
	assertTrue(result == -1, "gainCard() exits with error status if card not in game");
	assertTrue(G.supplyCount[smithy] == -1, "Card's supply is not decremented if card not in game");
	assertTrue(G.handCount = preHandCount, "Card is not added to hand if card not in game");
}

int main() {
	testGainCard();
	return 0;
}