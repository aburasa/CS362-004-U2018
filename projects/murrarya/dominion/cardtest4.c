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

void testCouncilRoom() {
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game
	printf("\n--- TESTING COUNCIL ROOOM CARD ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};
	int result;

	int preP1HandCount = G.handCount[0];
	int preP2HandCount = G.handCount[1];
	int preNumBuys = G.numBuys;
	int prePlayedCount = G.playedCardCount;
	G.hand[G.whoseTurn][0] = council_room;

	result = cardEffect(council_room, 0, 0, 0, &G, 0, 0);
	assertTrue(result == 0, "Council room succeeds when played");
	assertTrue(G.handCount[0] == preP1HandCount + 4, "Player who played card gains 4 cards");
	assertTrue(G.numBuys = preNumBuys + 1, "Player who played card gets 1 more buy");
	assertTrue(G.handCount[1] == preP2HandCount + 1, "Other player gains 1 card");
	assertTrue(G.playedCardCount == prePlayedCount + 1, "Council room is put in played pile after being played");
}

int main() {
	testCouncilRoom();
	return 0;
}