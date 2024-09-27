/* ============================================================
 * CS362-400 - Summer 2018
 * Mui Clark
 * Assignment 4 - Random test generator
 *              Card used: adventurer
 * Reference: testCard code given in the course github repo &
 *             class notes
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
int shuffleFail = 0;
int drawCardFail = 0;
int deckHandCountFail = 0;
int treasureCountFail = 0;

void adventurerCardCheck(int p, struct gameState *postgame){

    //treasure count test variables
    int postTreasCount = 0;
    int preTreasCount = 0;
    int tempHand[MAX_HAND];
    int drawnTreas = 0;

    //variables for cardEffect and drawing cards
    int cardDrawn, card;
    int u = 0;

    struct gameState pregame; //for manual test

    //copy game to pregame state
    memcpy (&pregame, postgame, sizeof(struct gameState));
    int bonus = 0;  //set starting bonus to 0

    //cardEffect function call for adventurer
   int r = cardEffect(adventurer,0,0,0,postgame,0,&bonus);

    //test did cardEffect work?
    if(r)
        cardEffectFail++;

//adventurer card functionality
    while (drawnTreas < 2){
        if(pregame.deckCount[p] < 1){
            int s = shuffle(p, &pregame);
            if(s == -1 && pregame.deckCount[p] >= 1)
                shuffleFail++;
        }
        int t = drawCard(p, &pregame);

        if(t == -1 && pregame.deckCount[p] != 0)
            drawCardFail++;

        //assign top card as recently drawn card
        cardDrawn = pregame.hand[p][pregame.handCount[p] - 1];
        if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawnTreas++;
        else{
            tempHand[u] = cardDrawn;
            pregame.handCount[p]--;  //to remove most recently drawn card
            u++;

        }
    }

    while( u - 1 >= 0){
        pregame.discard[p][pregame.discardCount[p]++] = tempHand[u - 1]; 
            u = u-1;
    }

//get treasure counts for pre and post games
   for (int i = 0; i < pregame.handCount[p]; i++) {
        card = pregame.hand[p][i];
        if (card == copper || card == silver || card == gold) {
            preTreasCount++;
        }
    } 
    for (int i = 0; i < postgame->handCount[p]; i++) {
            card = postgame->hand[p][i];
            if (card == copper || card == silver || card == gold) {
                postTreasCount++;
            }
        }
//test whether pre and post treasure counts tally
        if(postTreasCount != preTreasCount)
            treasureCountFail++;

//values of handCount and deckCount
    int postHandCount = postgame->handCount[p];
    int postDeckCount = postgame->deckCount[p];
    int postDiscardCount = postgame->discardCount[p];
    int preHandCount = pregame.handCount[p];
    int preDeckCount = pregame.deckCount[p];
    int preDiscardCount = pregame.discardCount[p];

//check the tallies
    if(!(postHandCount == preHandCount && postDeckCount == preDeckCount && postDiscardCount == preDiscardCount))
        deckHandCountFail++;

}


//random test harness

int main(){

    printf(" Testing Adventurer card\n====================\n");
    printf(" RANDOM TESTS\n==========================\n");

    int iteration = 20000; 
    struct gameState game;
    srand(time(NULL));

    int treasure[] = {copper, silver, gold};
    int minCards = 3;
    int numTreasure;
    int player;

    //random initialization of game state

    for (int n = 0; n < iteration; n++){
        for (int i = 0; i < sizeof(struct gameState); i++){
            ((char*)&game)[i] = floor(Random() * 256);
        }
}
    //random values for each category
        player = floor(Random() * MAX_PLAYERS);
        game.deckCount[player] = floor(Random() * ((MAX_DECK - minCards) + 1) + minCards);
        numTreasure = floor(Random() * ((game.deckCount[player] - minCards) + 1) + minCards);

       //randomly assign 3 treasure cards to the deck
        for(int i = 0; i < numTreasure; i++)
            game.deck[player][i] = treasure[rand() % 3];
        
        game.discardCount[player] = 0;
        game.handCount[player] = floor(Random() * ((MAX_HAND - minCards) + 1) + minCards);
        game.whoseTurn = player;

//call adventure card test function
        adventurerCardCheck(player, &game);

int totalFailures = cardEffectFail + drawCardFail + deckHandCountFail + shuffleFail + treasureCountFail;

    printf("\n RESULTS\n===============\n");
    printf("TESTS PASSED: %d\n", iteration - totalFailures);
    printf("TESTS FAILED: %d\n", totalFailures);

    //function failed report
    if(totalFailures == 0){
        printf("ALL RANDOM TESTS PASSED FOR Adventurer\n");
    }
    else{
        printf("Num times drawCard function calls failed: %d\n", drawCardFail);
        printf("Num times cardEffect function calls failed: %d\n", cardEffectFail);
        printf("shuffle failed: %d\n", shuffleFail);
        printf("Treasure count mismatch: %d\n", treasureCountFail);
        printf("Hand and deck count mismatch: %d\n", deckHandCountFail);

        printf (" ADVENTURER RANDOM TESTS FAILED: %d\n", totalFailures);
    }
        

        return 0;
}

    

