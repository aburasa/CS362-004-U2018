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

void testBuyCard() {
	printf("\n--- TESTING buyCard() ---\n");
	
	int seed = 1000;
	int numPlayers = 2;
	int maxBonus = 10;
	int player = 1;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
				 smithy, village, baron, great_hall};

	
	memset(&G, 23, sizeof(struct gameState)); // clear gameState
	initializeGame(numPlayers, k, seed, &G); // init a new game

	// Check that buying a card changes game state correctly
	G.numBuys = 1;
	G.coins = 5;
	int preCoins = G.coins;
	int preSupplyCount = G.supplyCount[1];
	int preDiscard = G.discardCount[G.whoseTurn];
	assertTrue(buyCard(1, &G) == 0, "buyCard allows a buy when all conditions met");
	assertTrue(G.coins == preCoins - getCost(1), "Coins are correctly decreased after a buy");
	assertTrue(G.numBuys == 0, "Number of buys is decremented after a buy");
	assertTrue(G.supplyCount[1] == preSupplyCount - 1, "Supply count of card is decremented after a buy");
	assertTrue(G.discardCount[G.whoseTurn] == preDiscard + 1, "Discard count incremented after buy");
	assertTrue(G.discard[G.whoseTurn][G.discardCount[G.whoseTurn] - 1] == 1, "Discard pile contains bought card");

	// Check that buying does not occur when no buys are left
	G.numBuys = 0;
	preCoins = G.coins;
	preSupplyCount = G.supplyCount[1];
	preDiscard = G.discardCount[G.whoseTurn];
	assertTrue(buyCard(0, &G) == -1, "buyCard does not allow a buy when no buys left");
	assertTrue(G.coins == preCoins, "Coins are not decreased after a failed buy due to no buys left");
	assertTrue(G.numBuys == 0, "Number of buys is not decremented after a failed buy due to no buys left");
	assertTrue(G.supplyCount[1] == preSupplyCount, "Supply count of card is not decremented due to no buys left");
	assertTrue(G.discardCount[G.whoseTurn] == preDiscard, "Discard count is not incremented after buy when no buys left");
	
	// Check that buying does not occur if there are no coins left
	G.numBuys = 1;
	G.coins = 0;
	preSupplyCount = G.supplyCount[1];
	preDiscard = G.discardCount[G.whoseTurn];
	assertTrue(buyCard(1, &G) == -1, "buyCard does not allow a buy when no coins are left");
	assertTrue(G.coins == 0, "Coins are not decreased after a failed buy due to no coins");
	assertTrue(G.numBuys == 1, "Number of buys is not decreased after a failed buy due to no coins");
	assertTrue(G.supplyCount[1] == preSupplyCount, "Supply count of card is not decremented due to no coins");
	assertTrue(G.discardCount[G.whoseTurn] == preDiscard, "Discard count is not incremented after buy when no coins");

	// Check that buying does not occur if there are insufficient coins
	G.numBuys = 1;
	G.coins = 1;
	preSupplyCount = G.supplyCount[1];
	preDiscard = G.discardCount[G.whoseTurn];
	assertTrue(buyCard(1, &G) == -1, "buyCard does not allow a buy when insufficient coins");
	assertTrue(G.coins == 1, "Coins are not decreased when insufficient coins");
	assertTrue(G.numBuys == 1, "Number of buys is not decreased when insufficient coins");
	assertTrue(G.supplyCount[1] == preSupplyCount, "Supply count of card is not decremented when insufficient coins");
	assertTrue(G.discardCount[G.whoseTurn] == preDiscard, "Discard count is not incremented after buy when insufficient coins");

	// Check that buying does not occur if there are no cards left
	G.numBuys = 1;
	G.coins = 5;
	G.supplyCount[1] = 0;
	preDiscard = G.discardCount[G.whoseTurn];
	assertTrue(buyCard(1, &G) == -1, "buyCard does not allow a buy when chosen card not left");
	assertTrue(G.coins == 0, "Coins are not decreased when chosen card not left");
	assertTrue(G.numBuys == 1, "Number of buys is not decreased when chosen card not left");
	assertTrue(G.supplyCount[1] == 0, "Cards are not decreased when chosen card is not left");
	assertTrue(G.discardCount[G.whoseTurn] == preDiscard, "Discard count is not incremented after buy when chosen card not left");
}

int main() {
	testBuyCard();
	return 0;
}