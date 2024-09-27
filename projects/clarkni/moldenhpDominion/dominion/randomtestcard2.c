
/* ==============================================================
 * CS362-400 - Summer 2018
 * Mui Clark
 * Assignment 4 - Random test generator
 *              Card used: smithy
 * Reference: testDrawCard code given in the course github repo &
              Class notes
 * ==============================================================
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"  //random number generator
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


// Counter variables to test failure rates
int cardEffectFail = 0;
int discardCardFail = 0;
int drawCardFail = 0;
int deckHandCountFail = 0;

//smithy card test function
void smithyCardCheck(int p, struct gameState *postgame){
    //variables for cardEffect and drawing cards
    int r, s, t, u, v;

    struct gameState pregame; //for manual test

//copy game to pregame state
    memcpy (&pregame, postgame, sizeof(struct gameState));
    int bonus = 0;  //set starting bonus to 0

//use smithy card to call the cardEffect function
    r = cardEffect(smithy, 0,0,0, postgame, 0, &bonus);

//drawCard calls
    s = drawCard(p,&pregame);
    t = drawCard(p, &pregame);
    u = drawCard(p, &pregame);

//discardCard call
    v = discardCard(0, p, &pregame, 0);

//values of handCount and deckCount
    int postHandCount = postgame->handCount[p];
    int postDeckCount = postgame->deckCount[p];
    int preHandCount = pregame.handCount[p];
    int preDeckCount = pregame.deckCount[p];

//conditionals to check if any drawCards failed for each of the drawCard calls
    if(s == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

    if(t == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

    if(u == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

//conditional to check if cardEffect and/or discardCard fails
    if(!(r == 0 && v == 0)){
        if(r){
            cardEffectFail++;
        }
        if(v){
            discardCardFail++;
        }
    }

//check handCount and deckCounts -> they should match

    if(!(postHandCount == preHandCount && postDeckCount == preDeckCount)){
        deckHandCountFail++;
    }

}


//random test harness

int main(){

    printf(" Testing Smithy card\n====================\n");
    printf(" RANDOM TESTS\n==========================\n");

    int iteration = 20000; 
    int n, player;
    struct gameState game;
    srand(time(NULL));

    //random initialization of game state

    for (n = 0; n < iteration; n++){
        for (int i = 0; i < sizeof(struct gameState); i++){
            ((char*)&game)[i] = floor(Random() * 256);
        }

        //random values for each category
        player = floor(Random() * MAX_PLAYERS);
        game.deckCount[player] = floor(Random() * MAX_DECK);
        game.handCount[player] = floor(Random() * MAX_HAND);
        game.playedCardCount = floor(Random() * (MAX_DECK-1));
        game.discardCount[player] = floor(Random() * MAX_DECK);
        game.whoseTurn = player;
        smithyCardCheck(player, &game);

    }

    int totalFailures = cardEffectFail + drawCardFail + deckHandCountFail + discardCardFail;

    printf("\n RESULTS\n===============\n");
    printf("TESTS PASSED: %d\n", iteration - totalFailures);
    printf("TESTS FAILED: %d\n", totalFailures);

    //function failed report
    if(totalFailures == 0){
        printf("ALL RANDOM TESTS PASSED FOR SMITHY\n");
    }
    else{
        printf("Num times drawCard function calls failed: %d\n", drawCardFail);
        printf("Num times discardCard function calls failed: %d\n", discardCardFail);
        printf("Num times cardEffect function calls failed: %d\n", cardEffectFail);
        printf("Hand and deck count mismatch: %d\n", deckHandCountFail);
        printf (" SMITHY RANDOM TESTS FAILED: %d\n", totalFailures);
    }

    

    return 0;
}

