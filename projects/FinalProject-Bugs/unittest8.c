#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int main () {
    
    int numPlayer = 2; // set the number of players
    int playCardTest; // return of the playCard function
    int r;
    
    int choice1; // tracker for which choice1 player chose
    int choice2; // tracker for which choice2 player chose
    int choice3; // tracker for which choice3 player chose
    
    // Track state of coins
    int coinsBefore;
    
    int k[10] = {minion, steward, cutpurse, embargo, mine,
        remodel, smithy, village, baron, great_hall
    };
    
    struct gameState G; // set a gameState
    
    printf ("*****************************************************\n");
    printf ("UNIT TEST 8: Bonus coins test\n");
    printf ("*****************************************************\n");
    

    printf ("-------------------------------------------------------------------\n");
    printf ("Subtest 1: Check if playCard works for coins state on Minion card.\n");
    printf ("-------------------------------------------------------------------\n");
    
    // Set up variables for the playCard function
    
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 1, &G);

    G.whoseTurn = 0; // Set current turn to first player
    G.hand[0][0] = minion;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = estate;
    G.handCount[0] = 5;
    G.numActions = 1;
    G.phase = 0;
    coinsBefore = 0;
    G.coins = coinsBefore;
    
    choice1 = 1;
    choice2 = 0;
    choice3 = 0;
    
    playCardTest = playCard(0, choice1, choice2, choice3, &G);
    
    // Pass or Fail checks at the end of the tests.
    if(coinsBefore == G.coins-11){
        printf ("Subtest 1: Number of coins after playCard for Minion ok?: Pass\n");
    }
    else{
        printf ("Subtest 1: Number of coins after playCard for Minion ok?: Fail\n\n");
    }
    
    printf ("-------------------------------------------------------------------\n");
    printf ("Subtest 2: Check if playCard works for coins state on Steward card.\n");
    printf ("-------------------------------------------------------------------\n");
    
    // Set up variables for the playCard function
    
    memset(&G, 2, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 2, &G);
    
    G.whoseTurn = 0; // Set current turn to first player
    G.hand[0][0] = steward;
    G.hand[0][1] = estate;
    G.hand[0][2] = estate;
    G.hand[0][3] = estate;
    G.hand[0][4] = estate;
    G.handCount[0] = 5;
    G.numActions = 1;
    G.phase = 0;
    coinsBefore = 0;
    G.coins = coinsBefore;
    
    choice1 = 2;
    choice2 = 0;
    choice3 = 0;
    
    playCardTest = playCard(0, choice1, choice2, choice3, &G);
    
    // Pass or Fail checks at the end of the tests.
    if(coinsBefore == G.coins-2){
        printf ("Subtest 2: Number of coins after playCard for Steward ok?: Pass\n");
    }
    else{
        printf ("Subtest 2: Number of coins after playCard for Steward ok?: Fail\n\n");
    }
    
    printf ("-------------------------------------------------------------------\n");
    printf ("Subtest 3: Check if playCard works for coins state on Cutpurse card.\n");
    printf ("-------------------------------------------------------------------\n");
    
    // Set up variables for the playCard function
    
    memset(&G, 3, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 3, &G);
    
    G.whoseTurn = 0; // Set current turn to first player
    G.hand[0][0] = cutpurse;
    G.hand[0][1] = gold;
    G.hand[0][2] = gold;
    G.hand[0][3] = gold;
    G.hand[0][4] = gold;
    G.handCount[0] = 5;
    G.numActions = 1;
    G.phase = 0;
    coinsBefore = 0;
    G.coins = coinsBefore;
    
    choice1 = 0;
    choice2 = 0;
    choice3 = 0;
    
    playCardTest = playCard(0, choice1, choice2, choice3, &G);
    
    // Pass or Fail checks at the end of the tests.
    if(coinsBefore == G.coins-22){
        printf ("Subtest 3: Number of coins after playCard for Cutpurse ok?: Pass\n");
    }
    else{
        printf ("Subtest 3: Number of coins after playCard for Cutpurse ok?: Fail\n\n");
    }
    
    printf ("-------------------------------------------------------------------\n");
    printf ("Subtest 4: Check if playCard works for coins state on Embargo card.\n");
    printf ("-------------------------------------------------------------------\n");
    
    // Set up variables for the playCard function
    
    memset(&G, 4, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 4, &G);
    
    G.whoseTurn = 0; // Set current turn to first player
    G.hand[0][0] = embargo;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    G.numActions = 1;
    G.phase = 0;
    coinsBefore = 0;
    G.coins = coinsBefore;
    
    choice1 = 1;
    choice2 = 0;
    choice3 = 0;
    
    playCardTest = playCard(0, choice1, choice2, choice3, &G);
    
    // Pass or Fail checks at the end of the tests.
    if(coinsBefore == G.coins-6){
        printf ("Subtest 4: Number of coins after playCard for Embargo ok?: Pass\n");
    }
    else{
        printf ("Subtest 4: Number of coins after playCard for Embargo ok?: Fail\n\n");
    }
    
    printf ("****************************************************************\n");
    printf ("UNIT TEST 8 COMPLETE\n");
    printf ("****************************************************************\n");
    
    return 0;
    
}
