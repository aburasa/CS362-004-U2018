/*/* CS362 - Assignment 3
 * unittest1.c --> UpdateCoins()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


//count of test failures - global count
int failuresCount = 0;

//own asserttrue function
void assertTrue(int a, int b){
	if (a == b)
		printf("Test: PASS");
	else {
		printf("Test: FAIL\n");
		failuresCount++;
	}
}

//main function to run tests
int main(){

	printf("*************TESTING updateCoins Function*****************\n");

	struct gameState game;
	int numPlayers = 2;
	int player = 0;
	int handCount;
	//kingdom cards
	int k[10] = {adventurer, smithy, great_hall, council_room, 
				 embargo, steward, feast, baron, village, gardens};

	int seed = 2000;
	int bonus = 1;
	int expected, actual;

	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	//array to hold treasure
	for (int i = 0; i< MAX_HAND; i++){
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	// test how updateCoins handles each treasure card, bonus and hand count
    for (handCount = 0; handCount <= 5; handCount = handCount + 5) {
        printf("\nTreasure cards: %d\n",handCount);
        printf("Bonus: %d\n", bonus);
}
	printf("Testing for updateCoins()\n");

	//initialize game with 2 players with seed of 2000

	initializeGame(numPlayers, k, seed, &game);

	printf("Test 1: standard initial game state for player 0, with no bonus, coins should be 4\n");
	expected = 4;
	updateCoins(player, &game, bonus);
	actual = game.coins;
	printf("Does the initial hand consist of 4 coins?\n");
	printf("actual is %d\n", game.coins);
	printf("%s", (actual == expected) ? "PASS" : "FAIL");
	printf("\n");
	

	//changing player 0 to 1 gold, 1 silver and 2 copper.  Give 1 bonus
	game.hand[player][0] = gold;
	game.hand[player][1] = silver;
	bonus = 1;

	printf("\nTest 2: expect the coins to be updated to 8\n");
	expected = 8;
	updateCoins(player, &game, bonus);
	actual = game.coins;
	printf("actual is %d\n", game.coins);
	printf("Did the Update coins increase to 8 for the second hand?\n");
	printf("%s", (actual == expected) ? "PASS" : "FAIL");
	printf("\n");

	printf("\nTest 3: Copper coins count,\n");
	printf("actual in copper is %d\n", game.coins);
	printf("expected in copper is %d\n", handCount*1+bonus);
	assertTrue(game.coins,handCount*1+bonus);


	printf("\nTest 4: Silver coins count,\n");
	printf("actual in silver is %d\n", game.coins);
	printf("expected in silver is %d\n", handCount*2+bonus);
	assertTrue(game.coins,handCount*2+bonus);

	printf("\nTest 5: Gold coins count,\n");
	printf("actual in gold is %d\n", game.coins);
	printf("expected in gold is %d\n", handCount*3+bonus);
	assertTrue(game.coins,handCount*3+bonus);

	printf("\n*** TESTING COMPLETED  *** \n ");

	return 0;

}


