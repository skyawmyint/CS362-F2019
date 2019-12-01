#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {
    
    // Note, unit test taken from my (Stuart Kyawmyint's) assignment 3 on tribute and reworked.
    
    int testCardEffect;
    int r;
    int numActionsOriginal;
    int numCoinsOriginal;
    int numHandcountOriginal;
    int check;
    int coin_bonus;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, tribute, great_hall
    };
    
    struct gameState G;
    
    printf ("************************************************************************\n");
    printf ("UNIT TEST 9: Testing tribute case in cardEffect function for duplicates.\n");
    printf ("************************************************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see same action card//////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 1 - Reveal of action + action card:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 12, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.whoseTurn = 0;
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    coin_bonus = 0;
    numCoinsOriginal = coin_bonus;
    
    G.deck[1][1] = mine;
    G.deck[1][0] = mine;
    G.deckCount[1] = 2;
    
    testCardEffect = cardEffect(tribute, 0, 0, 0, &G, 1, &coin_bonus);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions-2){
        printf("Subtest 1 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 1 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == coin_bonus){
        printf("Subtest 1 Result...Player One gained correct coins?: Pass - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    else{
        printf("Subtest 1 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]+1){
        printf("Subtest 1 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 1 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == mine){
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
    // Test to see same named Treasure card //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 2 - Reveal of treasure + treasure card:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 14, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.whoseTurn = 0;
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    coin_bonus = 0;
    numCoinsOriginal = coin_bonus;
    
    G.deck[1][1] = silver;
    G.deck[1][0] = silver;
    G.deckCount[1] = 2;
    
    testCardEffect = cardEffect(tribute, 0, 0, 0, &G, 1, &coin_bonus);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 2 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 2 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == coin_bonus-2){
        printf("Subtest 2 Result...Player One gained correct coins?: Pass - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    else{
        printf("Subtest 2 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]+1){
        printf("Subtest 2 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 2 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == silver){
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
    G.whoseTurn = 0;
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    coin_bonus = 0;
    numCoinsOriginal = coin_bonus;
    
    G.deck[1][1] = estate;
    G.deck[1][0] = estate;
    G.deckCount[1] = 2;
    
    testCardEffect = cardEffect(tribute, 0, 0, 0, &G, 1, &coin_bonus);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 3 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 3 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == coin_bonus){
        printf("Subtest 3 Result...Player One gained correct coins?: Pass - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    else{
        printf("Subtest 3 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]-1){
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
    printf ("Subtest 4 - No cards in deck, but cards in discard for duplicates:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 15, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.whoseTurn = 0;
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    coin_bonus = 0;
    numCoinsOriginal = coin_bonus;
    
    G.deckCount[1] = 0;
    G.discard[1][1] = gold;
    G.discard[1][0] = gold;
    G.discardCount[1] = 2;
    
    testCardEffect = cardEffect(tribute, 0, 0, 0, &G, 1, &coin_bonus);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 4 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 4 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == coin_bonus-2){
        printf("Subtest 4 Result...Player One gained correct coins?: Pass - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    else{
        printf("Subtest 4 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]+1){
        printf("Subtest 4 Result...Player One has correct handCount?: Pass - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    else{
        printf("Subtest 4 Result...Player One has correct handCount?: Fail - Original(%d) Current(%d) \n", numHandcountOriginal, G.handCount[0]);
    }
    
    // Check if the next player revealed cards went into discard pile
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == gold){
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
    printf ("Subtest 5 - Only one card in deck and multiple cards in discard:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 16, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.whoseTurn = 0;
    G.hand[0][0] = silver;
    G.hand[0][1] = tribute;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numHandcountOriginal = G.handCount[0];
    numActionsOriginal = G.numActions;
    coin_bonus = 0;
    numCoinsOriginal = coin_bonus;
    
    G.deckCount[1] = 1;
    G.deck[1][0] = silver;
    G.discardCount[1] = 3;
    G.discard[1][0] = silver;
    G.discard[1][1] = silver;
    G.discard[1][2] = silver;
    
    testCardEffect = cardEffect(tribute, 0, 0, 0, &G, 1, &coin_bonus);
    
    // Check if number of actions is gained
    if(numActionsOriginal == G.numActions){
        printf("Subtest 5 Result...Player One gained correct actions?:Pass - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    else{
        printf("Subtest 5 Result...Player One gained correct actions?:Fail - Original(%d) and Current(%d)\n", numActionsOriginal, G.numActions);
    }
    
    // Check if number of coins is gained
    if(numCoinsOriginal == coin_bonus-2){
        printf("Subtest 5 Result...Player One gained correct coins?: Pass - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    else{
        printf("Subtest 5 Result...Player One gained correct coins?: Fail - Original(%d) and Current(%d)\n", numCoinsOriginal, coin_bonus);
    }
    
    // Check if number of cards gained
    if(numHandcountOriginal == G.handCount[0]+1){
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
    if(check == 4){
        printf("Subtest 5 Result...Player Two has correct discard?: Pass\n");
    }
    else{
        printf("Subtest 5 Result...Player Two has correct discard?: Fail\n");
    }
    

    printf ("*******************************************\n");
    printf ("UNIT TEST 9 COMPLETE\n");
    printf ("*******************************************\n");
    
    return 0;
    
}
