#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int main () {
    
    int numPlayer = 2; // Set the number of players
    int r;
    int startNumActions;
    int endNumActions;
    
    int k[10] = {tribute, steward, cutpurse, embargo, mine,
        remodel, smithy, village, baron, great_hall
    };
    
    struct gameState G; // set a gameState
    
    printf ("*****************************************************\n");
    printf ("UNIT TEST 7: Tribute Revealed Cards\n");
    printf ("*****************************************************\n");
    
    // Set up variables for the scoreFor function
    
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, 1, &G);

    // Play tribute card
    int p = 19;

    // Set next Player deck
    G.deckCount[1] = 5;
    G.deck[1][0] = 1;
    G.deck[1][1] = 1;
    G.deck[1][2] = 1;
    G.deck[1][3] = 9; // Action card
    G.deck[1][4] = 8; // Action card

    startNumActions = G.numActions;

    // Play tribute card
    cardEffect(p, 1, 0, 0, &G, 0, 0);

    endNumActions = G.numActions;

    // Check 4 actions have been added
    if(startNumActions != (endNumActions - 4)){
        printf ("Player actions correct?: PASS\n");
    } else {
        printf ("Player actions correct?: FAIL\n");
    }
    
    return 0;
    
}
