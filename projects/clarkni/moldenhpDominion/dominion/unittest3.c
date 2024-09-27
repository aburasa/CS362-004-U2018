/* CS362 - Assignment 3
 * unittest3.c --> tests the next player's turn
 *                 to see whether another player is still in play
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(){


	printf("*************TESTING whoseTurn Function*****************\n");
	struct gameState game;

 	int numPlayers = 2;
 	int seed = 1000;

	//kingdom cards
	int k[10] = {adventurer, smithy, council_room, remodel,
				 embargo, steward, feast, baron, village, gardens};

	printf("Unit test 3: Who plays next? \n");
	printf("============================== \n");

	printf("Base game set to 4 players, so running test thrice\n");
	printf("other players still legal targets? \n");

	

	for (int i = 2; i < 5; i++){
		int ab = initializeGame(numPlayers, k, seed, &game);
		ab = whoseTurn(&game);
		assert(ab == game.whoseTurn);
		printf("%d test passed \n", i);
	}

	printf("\n *** TEST COMPLETED ***\n ");


	return 0;
}

