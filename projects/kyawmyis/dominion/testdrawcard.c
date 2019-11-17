#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {
    
    int testBaronEffect;
    int r;
    int numBuysOriginal;
    int numCoinsOriginal;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall
    };
    
    struct gameState G;
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 1: Testing baronEffect function.\n");
    printf ("*******************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player chooses to not discard -- estate card available in supply//
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 1 - Test if player chooses to not discard ESTATE card (Supply OK):\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.numBuys = 1;
    G.handCount[0] = 5;
    numBuysOriginal = G.numBuys;
    
    testBaronEffect = baronEffect(&G, 0, 0);
    
    // Check if the player has an ESTATE card in his hand
    int checker = 0;
    for(int i=0; i<=G.handCount[0]; i++){
        if(G.hand[0][i] == estate){
            checker = 1;
        }
    }
    if(checker == 1){
        printf ("Subtest 1 Result...Estate card gained?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result... Estate card gained?: Fail\n");
    }
    // Check if the player has the correct number of Buys in hand
    if(numBuysOriginal == G.numBuys-1){
        printf ("Subtest 1 Result...Buy+1 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Buy+1 Gained?: Fail\n");
    }
    
    /*
     for(int i=0; i<G.handCount[0]; i++){
     G.discard[0][G.discardCount[0]++] = G.hand[0][i];
     G.hand[0][i] = -1;
     }
     G.handCount[0] = 0;
     G.outpostPlayed = 0;
     G.phase = 0;
     G.numActions = 1;
     G.numBuys = 1;
     G.playedCardCount = 0;
     */
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player chooses to not discard -- estate card available in supply//
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("-------------------------------------------------------------------------------\n");
    printf ("Subtest 2 - Test if player chooses to not discard ESTATE card (Supply not ok):\n");
    printf ("-------------------------------------------------------------------------------\n");
    memset(&G, 2, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    G.numBuys = 1;
    numBuysOriginal = G.numBuys;
    G.supplyCount[estate] = 0;
    
    testBaronEffect = baronEffect(&G, 0, 0);
    
    // Check if the player does not have ESTATE card in hand
    checker = 1;
    for(int i=0; i<=G.handCount[0]; i++){
        if(G.hand[0][i] == estate){
            checker = 0;
        }
    }
    if(checker == 0){
        printf ("Subtest 2 Result...Estate card not gained?: Fail\n");
    }
    else{
        printf ("Subtest 2 Result...Estate card not gained?: Pass\n");
    }
    // Check if the player has the correct number of Buys in hand
    if(numBuysOriginal == G.numBuys-1){
        printf ("Subtest 2 Result...Buy+1 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Buy+1 Gained?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////
    // Check if the player chooses to discard Estate -- no estate card in hand  ////
    ////////////////////////////////////////////////////////////////////////////////
    printf ("-------------------------------------------------------------------------------\n");
    printf ("Subtest 3 - Test if choose to discard ESTATE, but no ESTATE in hand:\n");
    printf ("-------------------------------------------------------------------------------\n");
    memset(&G, 3, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    G.numBuys = 1;
    numBuysOriginal = G.numBuys;
    G.coins = 0;
    numCoinsOriginal = G.coins;
    G.supplyCount[estate] = 10;
    
    testBaronEffect = baronEffect(&G, 1, 0);
    
    // Check if the player does not have ESTATE card in hand
    checker = 0;
    for(int i=0; i<=G.handCount[0]; i++){
        if(G.hand[0][i] == estate){
            checker = 1;
        }
    }
    if(checker == 1){
        printf ("Subtest 3 Result...Estate card gained?: Pass\n");
    }
    else{
        printf ("Subtest 3 Result...Estate card gained?: Fail\n");
    }
    // Check if the player has the correct number of Buys in hand
    if(numBuysOriginal == G.numBuys-1){
        printf ("Subtest 3 Result...Buy+1 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 3 Result...Buy+1 Gained?: Fail\n");
    }
    // Check if the player has the correct number of coins in hand
    if(numCoinsOriginal == G.coins){
        printf ("Subtest 3 Result...Coins+4 not Gained?: Pass\n");
    }
    else{
        printf ("Subtest 3 Result...Coins+4 not Gained?: Fail\n");
    }
    
    ////////////////////////////////////////////////////////////////////////////////
    // Check if player chooses to discard Estate -- estate card in hand ////////////
    ////////////////////////////////////////////////////////////////////////////////
    printf ("-------------------------------------------------------------------------------\n");
    printf ("Subtest 4 - Test if choose to discard ESTATE, with ESTATE in hand:\n");
    printf ("-------------------------------------------------------------------------------\n");
    memset(&G, 4, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = copper;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = estate;
    G.handCount[0] = 5;
    G.numBuys = 1;
    numBuysOriginal = G.numBuys;
    G.coins = 1;
    numCoinsOriginal = G.coins;
    
    testBaronEffect = baronEffect(&G, 1, 0);
    
    // Check if ESTATE card discarded
    checker = 0;
    for(int i=0; i<=G.handCount[0]; i++){
        if(G.hand[0][i] == estate){
            checker = 1;
        }
    }
    if(checker == 1){
        printf ("Subtest 4 Result...Estate card discarded?: Fail\n");
    }
    else{
        printf ("Subtest 4 Result...Estate card discarded?: Pass\n");
    }
    // Check if the player has the correct number of Buys in hand
    if(numBuysOriginal == G.numBuys-1){
        printf ("Subtest 4 Result...Buy+1 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 4 Result...Buy+1 Gained?: Fail\n");
    }
    // Check if the player has the correct number of coins in hand
    if(numCoinsOriginal == G.coins-4){
        printf ("Subtest 4 Result...Coins+4 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 4 Result...Coins+4 Gained?: Fail\n");
    }
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 1 COMPLETE\n");
    printf ("*******************************************\n");
    
    return 0;
    
}
