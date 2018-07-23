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

void setHand(struct gameState *G, card treasure) {
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game

	G.hand[G.whoseTurn][0] = treasure;
	G.hand[G.whoseTurn][1] = mine;
}

void testMine() {
	printf("\n--- TESTING MINE CARD ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};
	int result;

	// Choice1 needs to be the treasure to trash
	// Choice2 is the desired treasure to replace it with

	// Test that mine fails if choice1 is not a treasure card
	setHand(&G, smithy);
	result = cardEffect(mine, 0, silver, 0, &G, 1, 0);
	assertTrue(result < 0, "Mine fails if trashed card is not a treasure card");
	assertTrue(G.hand[G.whoseTurn][0] == smithy, "If mine fails no change is made to hand");

	// Test that mine fails if choice1 is not a valid card
	setHand(&G, -1);
	result = cardEffect(mine, 0, silver, 0, &G, 1, 0);
	assertTrue(result < 0, "Mine fails if trashed card is not a valid card");

	// Test that mine fails if choice2 is not a treasure card
	setHand(&G, copper);
	result = cardEffect(mine, 0, smithy, 0, &G, 1, 0);
	assertTrue(result < 0, "Mine fails if chosen card is not a treasure card");

	// Test that mine fails if choice2 is not a valid card
	setHand(&G, copper);
	result = cardEffect(mine, 0, 500, 0, &G, 1, 0);
	assertTrue(result < 0, "Mine fails if chosen card is not a valid card");

	// Test that copper can be replaced with silver
	setHand(&G, copper);
	int prePlayedCount = G.playedCardCount;
	int preDeckSize = G.deckCount;
	result = cardEffect(mine, 0, silver, 0, &G, 1, 0);
	assertTrue(result == 0, "Mine succeeds if cards are valid treasure choices");
	assertTrue(G.hand[G.whoseTurn][0] == silver, "Copper can be replaced with silver");
	assertTrue(G.playedCardCount == G.prePlayedCount + 1, "Played card count increased by 1");
	assertTrue(G.played[prePlayedCount] == copper, "Played card is discarded");
	assertTrue(G.deckSize == preDeckSize - 1, "Deck size decreased by one after success");

	// Test that copper cannot be replaced with gold
	setHand(&G, copper);
	prePlayedCount = G.playedCardCount;
	preDeckSize = G.deckCount;
	result = cardEffect(mine, 0, gold, 0, &G, 1, 0);
	assertTrue(result < 0, "Mine fails if replacement treasure worth more than 3 gold more than trashed treausre");
	assertTrue(G.hand[G.whoseTurn][0] == copper, "Card is not trashed after failure");
	assertTrue(G.deckCount == preDeckSize, "Deck count not changed after failure");
	assertTrue(G.playedCardCount == prePlayedCount, "Trashed card count is not changed after failure");

	// Test that silver can be replaced with gold
	setHand(&G, silver);
	result = cardEffect(mine, 0, gold, 0, &G, 1, 0);
	assertTrue(result == 0, "Silver can be replaced with gold");

	// Test that gold can be replaced with any treasure
	setHand(&G, gold);
	result = cardEffect(mine, 0, gold, 0, &G, 1, 0);
	assertTrue(result == 0, "Treasures can be replaced by same treasure");

	// Test treasures can be replaced with a lower value treasure
	setHand(&G, gold);
	result = cardEffect(mine, 0, copper, 0, &G, 1, 0);
	assertTrue(result == 0, "Treasures can be replaced with lower value treasures");
}

int main() {
	testMine();
	return 0;
}