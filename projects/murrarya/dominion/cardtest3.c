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

void testMine() {
	printf("\n--- TESTING MINE CARD ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game
}

int main() {
	testMine();
	return 0;
}