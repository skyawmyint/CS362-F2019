#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int main () {
    
    int numPlayer = 2; // Set the number of players
    int scoreReturned; // Player's score
    int r;
    int startCoinCount;
    int endCoinCount;
    
    int k[10] = {feast, steward, cutpurse, embargo, mine,
        remodel, smithy, village, baron, great_hall
    };

    int p = 9; // Play feast
    
    struct gameState G; // set a gameState
    
    printf ("*****************************************************\n");
    printf ("UNIT TEST 6: Feast Coin Count\n");
    printf ("*****************************************************\n");
    
    // Set up variables for the scoreFor function
    
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 1, &G);

    // Set up player hand
    G.hand[0][0] = minion;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = estate;
    G.handCount[0] = 5;

    // Starting coins
    startCoinCount = G.coins;

    // Play tribute card
    // Request remodel
    cardEffect(p, 12, 0, 0, &G, 0, 0);

    // Ending coins
    endCoinCount = G.coins;

    // Check coin count unchanged
    if(startCoinCount == endCoinCount){
        printf ("Coin count correct?: PASS\n");
    } else {
        printf ("Coin count correct?: FAIL\n");
    }
    
    return 0;
    
}
