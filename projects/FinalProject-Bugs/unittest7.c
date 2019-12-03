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
    
    int k[10] = {minion, steward, cutpurse, embargo, mine,
        remodel, smithy, village, baron, great_hall
    };
    
    struct gameState G; // set a gameState
    
    printf ("*****************************************************\n");
    printf ("UNIT TEST 5: scoreFor Test\n");
    printf ("*****************************************************\n");
    
    // Set up variables for the scoreFor function
    
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 1, &G);

    // Set up player hand
    // Hand
    G.hand[0][0] = minion;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = estate;
    G.handCount[0] = 5;
    
    // Discard
    G.discard[0][0] = minion;
    G.discard[0][1] = duchy;
    G.discard[0][2] = province;
    G.discardCount[0] = 3;
    
    // Deck
    G.deck[0][0] = minion;
    G.deck[0][1] = duchy;
    G.deck[0][2] = province;
    G.deck[0][3] = province;
    G.deck[0][4] = province;
    G.deckCount[0] = 5;

    // Get player's score    
    scoreReturned = scoreFor(0, &G);

    // Check correct
    if(scoreReturned == 31){
        printf ("Player score correct?: PASS\n");
    }
    else{
        printf ("Player score correct?: FAIL\n\n");
    } 
    
    return 0;
    
}
