/* CS362 - Assignment 3
 * unittest4.c --> tests whether the game is over because there are no province card 
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

int main(){

	printf("*************TESTING isGameOver Function*****************\n");
	struct gameState game;
	int numSupply = 25;
	int actual, expected;

	//initialize
	for (int i = 0; i < numSupply; i++){
		game.supplyCount[i] = 1;
	}

	printf("Tests for: isGameOver? \n");

	printf("Test 1: \n");
	expected = 0;
	actual = isGameOver(&game);
	printf("%s", (actual == expected) ? "PASS" : "FAIL");
	printf("\nShuld return 0, since province card is present and there are no empty piles\n");

	printf("Test 2: \n");
	expected = 1;
	game.supplyCount[province] = 0;
	actual = isGameOver(&game);
	printf("%s", (actual == expected) ? "PASS" : "FAIL");
	printf("\nshuld return 1, since no province card is present \n");

	printf("Test 3: ");
	expected = 1;
	game.supplyCount[feast] = game.supplyCount[baron] = game.supplyCount[village] = 0;
	actual = isGameOver(&game);
	printf("%s", (actual == expected) ? "PASS" : "FAIL");
	printf("\nshuld return 1, because there 3 empty piles, but there is one province card\n");

	if (failuresCount) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",failuresCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    printf("\n*** TESTING COMPLETED*** \n ");

	return 0;
}
