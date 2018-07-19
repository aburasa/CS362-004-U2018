#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define VERBOSE 1

enum bool{false, true};

bool assertTrue(bool expr, char* description) {
	printf("%s - ", description);
	if (expr) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n")
	}
}

void testSmithy() {
	printf("\n--- TESTING SMITHY CARD ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game
	G.hand[0] = smithy; // insert smithy card into hand

	int preHandCount = G.handCount[G.whoseTurn];
	int preDeckCount = G.deckCount[G.whoseTurn];
	int prePlayedCount = G.playedCardCount;
	cardEffect(smithy, 0, 0, 0, &G, 0, 0); // play smithy
	// new hand count = preHandCount + 3 - 1
	assertTrue(G.handCount[G.whoseTurn] == preHandCount + 2, "Three cards are drawn and one discarded");
	assertTrue(G.deckCount[G.whoseTurn] == preDeckCount - 3, "Three cards are drawn from deck");
	assertTrue(G.playedCardCount == prePlayedCount + 1, "Played pile count incremented by one");
	assertTrue(G.playedCards[prePlayedCount] == smithy, "Smithy placed at top of played pile");
}

int main() {
	testSmithy();
	return 0;
}