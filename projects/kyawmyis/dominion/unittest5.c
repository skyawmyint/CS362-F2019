#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {

    int testMineEffect;
    int r;
    int checkGained;
    int checkGone;
    int discardUnwanted;
    int checkMineDiscard;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, tribute, great_hall
                };

    struct gameState G;
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 5: Testing mineEffect function.\n");
    printf ("*******************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Trash a silver, gain a gold /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 1 - Trash silver, gain gold:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 12, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = mine;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 2, gold, 0);
    
    // Test if card is added to the hand of player one
    checkGained = 0;
    checkGone = 0;
    for(int i =0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == gold){
            checkGained = 1;
        }
        if(G.hand[0][i] == mine){
            checkGone = 1;
        }
    }
    
    discardUnwanted = 0;
    checkMineDiscard = 0;
    // Check the discard pile
    for(int i =0; i<G.discardCount[0]; i++){
        if(G.discard[0][i] == gold){
            discardUnwanted = 1;
        }
        if(G.discard[0][i] == mine){
            checkMineDiscard = 1;
        }
    }
    
    if(checkGained == 1){
        printf("Subtest 1 Result...Player One gained correct card? Pass\n");
    }
    else{
        printf("Subtest 1 Result...Player One gained correct card? Fail\n");
    }
    
    if(checkGone == 0){
        printf("Subtest 1 Result...Player One hand does not contain mine card? Pass\n");
    }
    else{
        printf("Subtest 1 Result...Player One hand does not contain mine card? Fail\n");
    }

    if(checkMineDiscard == 1){
        printf("Subtest 1 Result...Player One discard contains mine card? Pass\n");
    }
    else{
        printf("Subtest 1 Result...Player One discard contains mine card? Fail\n");
    }
    
    if(discardUnwanted == 1){
        printf("Subtest 1 Result...Player One gained card in incorrect pile (Discard)? True\n");
    }
    else{
        printf("Subtest 1 Result...Player One gained card in incorrect pile (Discard)? False\n");
    }

    if(testMineEffect == 0){
        printf("Subtest 1 Result...Function return valid? True\n");
    }
    else{
        printf("Subtest 1 Result...Function return valid? False\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see trash copper, gain silver //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 2 - Trash copper, gain silver:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 16, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 2, silver, 0);
    
    // Test if card is added to the hand of player one
    checkGained = 0;
    checkGone = 0;
    for(int i =0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == silver){
            checkGained = 1;
        }
        if(G.hand[0][i] == mine){
            checkGone = 1;
        }
    }
    
    // Check the discard pile
    discardUnwanted = 0;
    checkMineDiscard = 0;
    for(int i =0; i<G.discardCount[0]; i++){
        if(G.discard[0][i] == silver){
            discardUnwanted = 1;
        }
        if(G.discard[0][i] == mine){
            checkMineDiscard = 1;
        }
    }
    
    if(checkGained == 1){
        printf("Subtest 2 Result...Player One gained correct card? Pass\n");
    }
    else{
        printf("Subtest 2 Result...Player One gained correct card? Fail\n");
    }
    
    if(checkGone == 0){
        printf("Subtest 2 Result...Player One hand does not contain mine card? Pass\n");
    }
    else{
        printf("Subtest 2 Result...Player One hand does not contain mine card? Fail\n");
    }
    
    if(checkMineDiscard == 1){
        printf("Subtest 2 Result...Player One discard contains mine card? Pass\n");
    }
    else{
        printf("Subtest 2 Result...Player One discard contains mine card? Fail\n");
    }
    
    if(discardUnwanted == 1){
        printf("Subtest 2 Result...Player One gained card in incorrect pile (Discard)? True\n");
    }
    else{
        printf("Subtest 2 Result...Player One gained card in incorrect pile (Discard)? False\n");
    }
    
    if(testMineEffect == 0){
        printf("Subtest 2 Result...Function return valid? True\n");
    }
    else{
        printf("Subtest 2 Result...Function return valid? False\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see trash gold, gain gold //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 3 - Trash gold, gain gold:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 17, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.hand[0][2] = gold;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 2, gold, 0);
    
    // Test if card is added to the hand of player one
    checkGained = 0;
    checkGone = 0;
    for(int i =0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == gold){
            checkGained = 1;
        }
        if(G.hand[0][i] == mine){
            checkGone = 1;
        }
    }
    
    // Check the discard pile
    discardUnwanted = 0;
    checkMineDiscard = 0;
    for(int i =0; i<G.discardCount[0]; i++){
        if(G.discard[0][i] == gold){
            discardUnwanted = 1;
        }
        if(G.discard[0][i] == mine){
            checkMineDiscard = 1;
        }
    }
    
    if(checkGained == 1){
        printf("Subtest 3 Result...Player One has correct card? Pass\n");
    }
    else{
        printf("Subtest 3 Result...Player One has correct card? Fail\n");
    }
    
    if(checkGone == 0){
        printf("Subtest 3 Result...Player One hand does not contain mine card? Pass\n");
    }
    else{
        printf("Subtest 3 Result...Player One hand does not contain mine card? Fail\n");
    }
    
    if(checkMineDiscard == 1){
        printf("Subtest 3 Result...Player One discard contains mine card? Pass\n");
    }
    else{
        printf("Subtest 3 Result...Player One discard contains mine card? Fail\n");
    }
    
    if(discardUnwanted == 1){
        printf("Subtest 3 Result...Player One discard contains a gold? Pass\n");
    }
    else{
        printf("Subtest 3 Result...Player One gained card in incorrect pile (Discard)? Fail\n");
    }
    
    if(testMineEffect == 0){
        printf("Subtest 3 Result...Function return valid? True\n");
    }
    else{
        printf("Subtest 3 Result...Function return valid? False\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to trash used mine card /////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 4 - Trash used mine card:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 18, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 1, silver, 0);
    
    if(testMineEffect == -1){
        printf("Subtest 4 Result...Function return invalid? True\n");
    }
    else{
        printf("Subtest 4 Result...Function return invalid? False\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to trash card worth less than a curse /////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 5 - Trash card worth less than a curse:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 18, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.hand[0][2] = curse-1;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 2, silver, 0);
    
    if(testMineEffect == -1){
        printf("Subtest 5 Result...Function return invalid? True\n");
    }
    else{
        printf("Subtest 5 Result...Function return invalid? False\n");
    }
 
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Trash a curse, gain a gold //////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 6 - Trash curse, gain gold:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 19, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.hand[0][2] = curse;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 2, gold, 0);
    
    // Test if card is added to the hand of player one
    checkGained = 0;
    checkGone = 0;
    for(int i =0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == gold){
            checkGained = 1;
        }
        if(G.hand[0][i] == mine){
            checkGone = 1;
        }
    }
    
    // Check the discard pile
    discardUnwanted = 0;
    checkMineDiscard = 0;
    for(int i =0; i<G.discardCount[0]; i++){
        if(G.discard[0][i] == curse){
            discardUnwanted = 1;
        }
        if(G.discard[0][i] == mine){
            checkMineDiscard = 1;
        }
    }
    
    if(checkGained == 1){
        printf("Subtest 6 Result...Player One does not gain gold? Fail\n");
    }
    else{
        printf("Subtest 6 Result...Player One does not gain gold? Pass\n");
    }
    
    if(checkGone == 0){
        printf("Subtest 6 Result...Player One hand contains mine card? Fail\n");
    }
    else{
        printf("Subtest 6 Result...Player One hand contains mine card? Pass\n");
    }
    
    if(checkMineDiscard == 1){
        printf("Subtest 6 Result...Player One discard does not contain mine card? Fail\n");
    }
    else{
        printf("Subtest 6 Result...Player One discard does not contain mine card? Pass\n");
    }
    
    if(discardUnwanted == 1){
        printf("Subtest 6 Result...Player One discard does not contain a curse? Fail\n");
    }
    else{
        printf("Subtest 6 Result...Player One discard does not contain a curse? Pass\n");
    }
    
    if(testMineEffect == -1){
        printf("Subtest 6 Result...Function return invalid? True\n");
    }
    else{
        printf("Subtest 6 Result...Function return invalid? False\n");
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // Test to trash card worth more than treasure map /////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 7 - Trash card worth more than treasure map:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 19, sizeof(struct gameState));
    r = initializeGame(2, k, 323, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.hand[0][2] = treasure_map+1;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    G.handCount[0] = 5;
    
    testMineEffect = mineEffect(&G, 1, 2, silver, 0);
    
    if(testMineEffect == -1){
        printf("Subtest 7 Result...Function return invalid? True\n");
    }
    else{
        printf("Subtest 7 Result...Function return invalid? False\n");
    }
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 5 COMPLETE\n");
    printf ("*******************************************\n");

    return 0;

}
