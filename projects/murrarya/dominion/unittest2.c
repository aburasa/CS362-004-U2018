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

void setTreasuresInHand(int numCopper, int numSilver, int numGold, struct gameState* G, int player) {
	for (int i = 0; i < G->handCount[player]; i++) {
		if (numCopper) {
			G->hand[player][i] = copper;
			numCopper--;
		} else if (numSilver) {
			G->hand[player][i] = silver;
			numSilver--;
		} else if (numGold) {
			G->hand[player][i] = gold;
			numGold--;
		} else {
			G->hand[player][i] = feast; // Any non-treasure card will work
		}
	}
}

void testUpdateCoins() {
	printf("\n--- TESTING updateCoins() ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game

	// Check that coins are 0 when no treasures in hand
	setTreasuresInHand(0, 0, 0, &G, G.whoseTurn);
	updateCoins(G.whoseTurn, &G, 0);
	assertTrue(G.coins == 0, "Coins are 0 when no treasures in hand");

	// Check that bonus is applied
	setTreasuresInHand(0, 0, 0, &G, G.whoseTurn);
	updateCoins(G.whoseTurn, &G, 3);
	assertTrue(G.coins == 3, "Coins are increased by bonus");

	// Check that coins are 1 when only one copper in hand
	setTreasuresInHand(1, 0, 0, &G, G.whoseTurn);
	updateCoins(G.whoseTurn, &G, 0);
	assertTrue(G.coins == 1, "Coins are 1 when only one copper in hand");

	// Check that coins are 2 when only one silver in hand
	setTreasuresInHand(0, 1, 0, &G, G.whoseTurn);
	updateCoins(G.whoseTurn, &G, 0);
	assertTrue(G.coins == 2, "Coins are 2 when only one silver in hand");

	// Check that coins are 3 when only one gold in hand
	setTreasuresInHand(0, 0, 1, &G, G.whoseTurn);
	updateCoins(G.whoseTurn, &G, 0);
	assertTrue(G.coins == 3, "Coins are 3 when only one gold in hand");

	// Check that coins and bonus are properly combined
	setTreasuresInHand(3, 3, 4, &G, G.whoseTurn);
	updateCoins(G.whoseTurn, &G, 10);
	int totalTreasure = 3 + (3 * 2) + (3 * 4) + 10;
	assertTrue(G.coins == totalTreasure, "Coins and bonus are properly combined");
}

int main() {
	testUpdateCoins();
	return 0;
}