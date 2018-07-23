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
		printf("[32mPASSED[0m\n");
	} else {
		printf("[31mFAILED[0m\n");
	}
}

void testIsGameOver() {
	printf("\n--- TESTING isGameOver() ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game

	int gameOver;
	// Check that game doesn't end if a province card is left and no supply piles gone
	gameOver = isGameOver(&G);
	assertTrue(!gameOver, "game doesn't end if a province card is left and no supply piles gone");

	// Game doesn't end if less than three supply piles are gone
	G.supplyCount[smithy] = 0;
	G.supplyCount[adventurer] = 0;
	gameOver = isGameOver(&G);
	assertTrue(!gameOver, "Game doesn't end if < 3 supply piles gone");
	G.supplyCount[smithy] = 10;
	G.supplyCount[adventurer] = 10;

	// Check that game ends if all province cards are gone
	G.supplyCount[province] = 0;
	gameOver = isGameOver(&G);
	assertTrue(gameOver, "Game ends if province cards are gone");
	G.supplyCount[province] = 10;

	// Check that game ends if three supply piles are gone
	G.supplyCount[smithy] = 0;
	G.supplyCount[adventurer] = 0;
	G.supplyCount[feast] = 0;
	gameOver = isGameOver(&G);
	assertTrue(gameOver, "Game ends if three supply piles are gone");
}	