#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {

    int testTributeEffect;
    int r;
    int numActionsOriginal;
    int numCoinsOriginal;
    int numHandcountOriginal;
    int check;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, tribute, great_hall
                };

    struct gameState G;
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 4: Testing tributeEffect function.\n");
    printf ("*******************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see differently named action and treasure card //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 1 - Reveal of action + treasure card:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 12, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deck[1][1] = silver;
    G.deck[1][0] = mine;
    G.deckCount[1] = 2;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions-2){
        printf("Subtest 1 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 1 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins-2){
        printf("Subtest 1 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 1 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }

    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]){
        printf("Subtest 1 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 1 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == mine || G.discard[1][i] == silver){
            check+=1;
        }
    }
    if(check == 2){
        printf("Subtest 1 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 1 Result...Player Two has correct discard?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see differently named treasure and victory card //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 2 - Reveal of treasure + victory card:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 14, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deck[1][1] = province;
    G.deck[1][0] = silver;
    G.deckCount[1] = 2;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 2 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 2 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins-2){
        printf("Subtest 2 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 2 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]-2){
        printf("Subtest 2 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 2 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == province || G.discard[1][i] == silver){
            check+=1;
        }
    }
    if(check == 2){
        printf("Subtest 2 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 2 Result...Player Two has correct discard?: Fail\n");
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see same named victory card //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 3 - Reveal of same victory + victory card:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 15, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deck[1][1] = estate;
    G.deck[1][0] = estate;
    G.deckCount[1] = 2;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 3 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 3 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins){
        printf("Subtest 3 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 3 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]-2){
        printf("Subtest 3 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 3 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == estate){
            check+=1;
        }
    }
    if(check == 2){
        printf("Subtest 3 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 3 Result...Player Two has correct discard?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see no cards in deck of player 2, but proper in discard /////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 4 - No cards in deck, but cards in discard:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 15, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deckCount[1] = 0;
    G.discard[1][1] = gold;
    G.discard[1][0] = silver;
    G.discardCount[1] = 2;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 4 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 4 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins-4){
        printf("Subtest 4 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 4 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]){
        printf("Subtest 4 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 4 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == gold || G.discard[1][i] == silver){
            check+=1;
        }
    }
    if(check == 2){
        printf("Subtest 4 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 4 Result...Player Two has correct discard?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see only one card in deck of player 2 /////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 5 - Only one card in deck:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 16, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deckCount[1] = 1;
    G.discardCount[1] = 0;
    G.discard[1][0] = silver;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 5 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 5 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins-2){
        printf("Subtest 5 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 5 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]){
        printf("Subtest 5 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 5 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == silver){
            check+=1;
        }
    }
    if(check == 1){
        printf("Subtest 5 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 5 Result...Player Two has correct discard?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see only one card in discard of player 2 /////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 6 - Only one card in discard player 2:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 16, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deckCount[1] = 0;
    G.discardCount[1] = 1;
    G.discard[1][0] = silver;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 6 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 6 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins-2){
        printf("Subtest 6 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 6 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]){
        printf("Subtest 6 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 6 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == silver){
            check+=1;
        }
    }
    if(check == 1){
        printf("Subtest 6 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 6 Result...Player Two has correct discard?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if no card in discard or deck of player 2 /////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 7 - No cards in deck and discard player 2:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 16, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    G.deckCount[1] = 0;
    G.discardCount[1] = 0;
    
    testTributeEffect = tributeEffect(&G, 0, 1);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 7 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 7 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == G.coins){
        printf("Subtest 7 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    else{
        printf("Subtest 7 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, G.coins);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]){
        printf("Subtest 7 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 7 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    if(G.discardCount[1] == 0){
        printf("Subtest 7 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 7 Result...Player Two has correct discard?: Fail\n");
    }

    printf ("*******************************************\n");
    printf ("UNIT TEST 4 COMPLETE\n");
    printf ("*******************************************\n");

    return 0;

}
