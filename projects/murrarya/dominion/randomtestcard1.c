#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "dominion.h"

bool assertTrue(bool expr, char* description) {
	if (!expr) {
		printf("%s - ", description);
		printf("\x1B[31mFAILED\x1B[0m\n");
	}
}

void randomlyGenerateGameState(struct gameState* G) {
	// Set number of players
	int numPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;
	if (numPlayers < 2) {
		numPlayers = 2;
	}
	
	// Randomly choose the set of kingdom cards
	int randomCards[treasureMap];
	for (int i = 0; i < treasureMap; i++) {
		int randIdx = rand() % (treasureMap - i) + i;
		int tmp = randomCard[randIdx];
		randomCards[randIdx] = randomCards[i];
		randomCards[i] = tmp;
	}
	int kingdomCards[10];
	for (int i = 0; i < 10; i++) {
		kingdomCards[i] = randomCards[i]
	}

	initializeGame(numPlayers, kingdomCards, rand(), G);
	int p = G.whoseTurn;
	// Following ist aken from lecture 11 slide 9
	G.deckCount[p] = floor(Random() * MAX_DECK);
	G.discardCount[p] = floor(Random() * MAX_DECK);
	G.handCount[p] = floor(Random() * MAX_HAND);
}

void randomTestAdventurer() {
	for (int i = 0; i < 2000; i++) {
		struct gameState G;
		randomlyGenerateGameState(&G);

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

		assertTrue(postHandCount == preHandCount + 2, "Hand count inc'd by 2");
		assertTrue(postTreasuresInHand - preTreasuresInHand == 2, "2 treasures drawn");
		assertTrue(postDiscardCount - preDiscardCount == numCardsDrawn - 2, "All other cards put in discard pile");
	}

	printf("\x1B[32mPASSED\x1B[0m\n");

}

int main() {
	srand(time(0));
	randomTestAdventurer();
	return 0;
}