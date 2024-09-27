/* CS362 - Assignment 3
 * cardtest1.c --> test for card smithy
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

     printf("**********TESTING FOR SMITHY****************\n");
     
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;
    

    int handPosition = 0;
    int choice1 = 0,  choice2 = 0, choice3 = 0, bonus = 0;

    //kingdom cards
    int k[10] = {adventurer, smithy, great_hall, council_room, 
                 embargo, steward, feast, baron, village, gardens};

    int seed = 1000;

    struct gameState game, originalGame;

    memset(&game, 25, sizeof(struct gameState));
    memset(&originalGame, 25, sizeof(struct gameState));

    //initialize game
    initializeGame(numPlayers, k, seed, &game);

    //copy to preserve it
    memcpy(&originalGame, &game, sizeof(struct gameState));

    printf("TEST FOR SMITHY\n");

    choice1 = 1;
    cardEffect(smithy, choice1, choice2, choice3, &game, handPosition, &bonus);

    printf("\nDid Player 0 gain 3 cards?\n");
    assertTrue(game.handCount[player0], originalGame.handCount[player0] + 2);

    printf("\nPlayer 0 gains 3 cards from own pile\n");
    assertTrue(game.deckCount[player0], originalGame.deckCount[player0] - 3);

    printf("Any change to victory card piles?\n");
    printf("Duchy Pile\n");
    assertTrue(game.supplyCount[duchy],originalGame.supplyCount[duchy]);
    printf("\nProvince Pile\n");
    assertTrue(game.supplyCount[province],originalGame.supplyCount[province]);
    printf("\nEstate Pile\n");
    assertTrue(game.supplyCount[estate],originalGame.supplyCount[estate]);

    printf("\nAny change to kingdom card piles?\n");
    for (int i = 0; i < 10; i++){
        printf("\nChecking kingdom card piles?\n");
        assertTrue(game.supplyCount[k[i]],originalGame.supplyCount[k[i]]);
    }

    printf("\nCheck to see if Player 1 was affected\n");
    printf("Hand count for player 1 - is it valid?\n");
    assertTrue(game.handCount[player1],originalGame.handCount[player1]);
    printf("\nDeck count for player 1 - is is valid?\n");
    assertTrue(game.deckCount[player1],originalGame.deckCount[player1]);


    if (failuresCount) {
        printf("\nNUMBER OF TESTS FAILED\n");
        printf("Fails: %d\n",failuresCount);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;

}