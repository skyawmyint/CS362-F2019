#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {

    int testMinionEffect;
    int r;
    int numActionsOriginal;
    int numCoinsOriginal;
    int check = 0;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, minion, great_hall
                };

    struct gameState G;
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 2: Testing minionEffect function.\n");
    printf ("*******************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player chooses to gain +2 COINS ///////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 1 - Test if player chooses to gain 2 COINS:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    G.hand[0][0] = minion;
    G.hand[0][1] = gold;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    for(int i = 0; i<=4; i++){
        G.hand[1][i] = silver;
        G.hand[2][i] = silver;
    }
    G.handCount[0] = 5;
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    testMinionEffect = minionEffect(1, 0, &G, 0, 0);
    
    // Check if gained actions
    if(numActionsOriginal == G.numActions-1){
         printf ("Subtest 1 Result...Action+1 Gained?: Pass\n");
    }
    else{
         printf ("Subtest 1 Result...Action+1 Gained?: Fail\n");
    }
    
    // Check if coins were gained
    if(numCoinsOriginal == G.coins-2){
        printf ("Subtest 1 Result...Coins+2 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Coins+2 Gained?: Fail\n");
    }
    
    // Check if Minion card discarded
    check = 0;
    for(int i = 0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == minion){
            check = 1;
        }
    }
    if(check == 0){
        printf ("Subtest 1 Result...Minion Card Discarded?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Minion Card Discarded?: Fail\n");
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player chooses to discard hand and gain +4 cards///////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 2 - Test if player chooses to discard and gain cards:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 2, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    // Player 1 Hand
    G.hand[0][0] = minion;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    // Player 2 Hand
    for(int i = 0; i<=4; i++){
        G.hand[1][i] = silver;
    }
    // Player 3 Hand
    for(int i = 0; i<=2; i++){
        G.hand[2][i] = silver;
    }
    G.handCount[0] = 5;
    G.handCount[1] = 5;
    G.handCount[2] = 3;
    numActionsOriginal = G.numActions;
    numCoinsOriginal = G.coins;
    
    testMinionEffect = minionEffect(0, 1, &G, 0, 0);
    
    // Check if gained actions
    if(numActionsOriginal == G.numActions-1){
        printf ("Subtest 2 Result...Action+1 Gained?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Action+1 Gained?: Fail\n");
    }
    
    // Check if Minion card discarded
    check = 0;
    for(int i = 0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == minion){
            check = 1;
        }
    }
    if(check == 0){
        printf ("Subtest 2 Result...Minion Card Discarded?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Minion Card Discarded?: Fail\n");
    }
    
    // Check if player 1 gained correct number of cards
    check = 0;
    for(int i = 0; i<G.handCount[0]; i++){
        if((G.hand[0][i] != minion && G.hand[0][i] != silver)&&(G.hand[0][i]==copper || G.hand[0][i]==estate) ){
            check += 1;
        }
    }
    if(check == 4){
        printf ("Subtest 2 Result...Player One correct cards?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Player One correct cards?: Fail\n");
    }
    
    // Check if player 2 gained correct number of cards
    check = 0;
    for(int i = 0; i<G.handCount[1]; i++){
        if((G.hand[1][i] != silver)&&(G.hand[1][i]==copper || G.hand[1][i]==estate) ){
            check += 1;
        }
    }
    if(check == 4){
        printf ("Subtest 2 Result...Player Two correct cards?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Player Two correct cards?: Fail\n");
    }
    
    // Check if player 3 gained correct number of cards
    check = 0;
    for(int i = 0; i<G.handCount[2]; i++){
        if(G.hand[2][i] == silver ){
            check += 1;
        }
    }
    if(check == 3){
        printf ("Subtest 2 Result...Player Three correct cards?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Player Three correct cards?: Fail\n");
    }
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 2 COMPLETE\n");
    printf ("*******************************************\n");

    return 0;

}
