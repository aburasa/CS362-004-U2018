/* CS362 - Assignment 3
 * unittest1.c --> tests whether player is able to buy the card
 *                 Selected this function because it affects all players
 */
  

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int main(int arg, char** argv){

	printf("*************TESTING buyCard Function*****************\n");
	printf("Unit test: \n");

	struct gameState game;

	game.numBuys = 2;
	game.coins = 2;

	printf("Not enough coins to buy? \n");
	int testBuy = buyCard(2, &game);

	if (testBuy == -1)
		printf("test passed");
	else
		printf("test failed");

	printf("\n try to buy specific card\n");
	game.coins = 10;
	testBuy = buyCard(2, &game);
		if (testBuy == 0)
			printf("test passed");
		else
			printf("test failed");

	printf("\n checking amount \n");
	testBuy = buyCard(2, &game);
		if (testBuy == 0)
			printf("test passed");
		else
			printf("test failed");

	printf("\n Does user have enough buying power?\n");
	game.coins = 6;
	testBuy = buyCard(2, &game);
		if (testBuy == -1)
			printf("test passed");
		else
			printf("test failed");	

	printf("\n*** TESTING COMPLETED SUCCESSFULLY*** \n ");

	return 0;
}
