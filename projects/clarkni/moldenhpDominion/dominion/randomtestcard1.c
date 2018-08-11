/* ============================================================
 * CS362-400 - Summer 2018
 * Mui Clark
 * Assignment 4 - Random test generator
 *              Card used: council_room
 * Reference: testCard code given in the course github repo &
 *            class notes
 * ============================================================
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
int numBuysFail = 0;
int otherPlayerDeckHandFail = 0;

void council_roomCardCheck(int p, struct gameState *postgame){
    //variables for cardEffect and drawing cards
    int r, s, t, u, v, w, x;

    struct gameState pregame; //for manual test

//copy game to pregame state
    memcpy (&pregame, postgame, sizeof(struct gameState));
    int bonus = 0;  //set starting bonus to 0

//use council_room card to call the cardEffect function
    r = cardEffect(council_room, 0,0,0, postgame, 0, &bonus);

//drawCard calls
    s = drawCard(p,&pregame);
    t = drawCard(p, &pregame);
    u = drawCard(p, &pregame);
    v = drawCard(p, &pregame);

    pregame.numBuys++;

//discardCard call
   x = discardCard(0, p, &pregame, 0);

 //other players draw a card
   for(int i = 0; i < pregame.numPlayers; i++){
   		if(i != p){
   			w = drawCard(i, &pregame);
   			if(w == -1 && pregame.deckCount[i] != 0){
   				drawCardFail++;
   			}
   		}
   }

//values of handCount and deckCount
    int postHandCount = postgame->handCount[p];
    int postDeckCount = postgame->deckCount[p];
    int preHandCount = pregame.handCount[p];
    int preDeckCount = pregame.deckCount[p];

//check for numBuys
    if(pregame.numBuys != postgame->numBuys)
    	numBuysFail++;


//conditionals to check if any drawCards failed for each of the drawCard calls
    if(s == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

    if(t == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

    if(u == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

    if(v == -1 && pregame.deckCount[p] != 0)
        drawCardFail++;

//conditional to check if cardEffect and/or discardCard fails
    if(!(r == 0 && x == 0)){
        if(r){
            cardEffectFail++;
        }
        if(x){
            discardCardFail++;
        }
    }

//check handCount and deckCounts -> they should match

    if(!(postHandCount == preHandCount && postDeckCount == preDeckCount)){
        deckHandCountFail++;
    }

// check for other players' hand and deck counts matching
    for (int i = 0; i < pregame.numPlayers; i++) {
        if (i != p) {
            if (!(postgame->handCount[i] == pregame.handCount[i] &&
                  postgame->deckCount[i] == pregame.deckCount[i])) {
                      otherPlayerDeckHandFail++;
            }
        }
    }

}

//random test harness

int main(){

    printf(" Testing Council_room card\n====================\n");
    printf(" RANDOM TESTS\n==========================\n");

    int iteration = 20000; 
    int totPlayers[] = {2,3,4};
    struct gameState game;
    srand(time(NULL));

    //random initialization of game state

    for (int n = 0; n < iteration; n++){
        for (int i = 0; i < sizeof(struct gameState); i++){
            ((char*)&game)[i] = floor(Random() * 256);
        }

        //random values for each category
        game.numPlayers = totPlayers[rand() % 3];
        game.numBuys = 1;
        int player = game.numPlayers - 2;
        game.playedCardCount = floor(Random() * (MAX_DECK-1));

//variables to assign for other players
        int deckCount = floor(Random() * MAX_DECK);
        int handCount = floor(Random() * MAX_HAND);
        int discardCardCount = floor(Random() * MAX_DECK);
        game.whoseTurn = player;

//set other players hand and deck count
      for (int i = 0; i < game.numPlayers; i++) {
            game.deckCount[i] = deckCount;
            game.handCount[i] = handCount;
            game.discardCount[i] = discardCardCount;
        }  
       
      //call for council_room test function
      council_roomCardCheck(player, &game);
    }

    int totalFailures = cardEffectFail + drawCardFail + deckHandCountFail + discardCardFail + numBuysFail;

    printf("\n RESULTS\n===============\n");
    printf("TESTS PASSED: %d\n", iteration - totalFailures);
    printf("TESTS FAILED: %d\n", totalFailures);

    //function failed report
    if(totalFailures == 0){
        printf("ALL RANDOM TESTS PASSED FOR Council_room\n");
    }
    else{
        printf("Num times drawCard function calls failed: %d\n", drawCardFail);
        printf("Num times discardCard function calls failed: %d\n", discardCardFail);
        printf("Num times cardEffect function calls failed: %d\n", cardEffectFail);
        printf("Hand and deck count mismatch: %d\n", deckHandCountFail);
        printf("numBuys count mismatch: %d\n", numBuysFail);
        printf("Hand and deck count mismatch for other player: %d\n", otherPlayerDeckHandFail);

        printf (" COUNCIL_ROOM RANDOM TESTS FAILED: %d\n", totalFailures);
    }

    return 0;
}

