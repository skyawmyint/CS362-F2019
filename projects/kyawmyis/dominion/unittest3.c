#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {

    int testAmbassadorEffect;
    int r;
    int numSupplySilverOriginal;
    int check = 0;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, ambassador, great_hall
                };

    struct gameState G;
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 3: Testing ambassadorEffect function.\n");
    printf ("*******************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if revealed card from player is trashed and gained by others ////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 1 - Test if player's card is trashed and gained by others:\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 1, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    
    testAmbassadorEffect = ambassadorEffect(&G, 0, 0, 1, 2);
    
    // Check if Ambassador card discarded player One
    check = 0;
    for(int i = 0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == ambassador){
            check = 1;
        }
    }
    if(check == 0){
        printf ("Subtest 1 Result...Ambassador Card Discarded Player One?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Ambassador Card Discarded Player One?: Fail\n");
    }
    
    // Check if player One has correct handCount
    if(G.handCount[0] == 2){
        printf ("Subtest 1 Result...Correct number handCount Player One?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Correct number handCount Player One?: Fail\n");
    }
    
    // Check if player One discard pile does not contain any Silver
    check = 0;
    for(int i = 0; i<G.discardCount[0]; i++){
        if(G.discard[0][i] == silver){
            check = 1;
        }
    }
    if(check == 0){
        printf ("Subtest 1 Result...Player One discard pile OK?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Player One discard pile OK?: Fail\n");
    }
    
     // Check if player One has gained correct number of Silver in their hand
    check = 0;
    for(int i = 0; i<G.handCount[0]; i++){
        if(G.hand[0][i] == silver){
            check += 1;
        }
    }
    if(check == 2){
        printf ("Subtest 1 Result...Player One correct card hand?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Player One correct card hand?: Fail\n");
    }
    
    // Check if player Two has gained Silver in their discard
    check = 0;
    for(int i = 0; i<G.discardCount[1]; i++){
        if(G.discard[1][i] == silver){
            check = 1;
        }
    }
    if(check == 1){
        printf ("Subtest 1 Result...Player Two discard pile OK?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Player Two discard pile OK?: Fail\n");
    }
    
    // Check if player Three has gained Silver in their discard
    check = 0;
    for(int i = 0; i<G.discardCount[2]; i++){
        if(G.discard[2][i] == silver){
            check = 1;
        }
    }
    if(check == 1){
        printf ("Subtest 1 Result...Player Three discard pile OK?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Player Three discard pile OK?: Fail\n");
    }
    
    // Check if correct number of Silver in the Supply
    if(numSupplySilverOriginal == G.supplyCount[silver]){
        printf ("Subtest 1 Result...Correct number in Supply Pile?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Correct number in Supply Pile?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player choice2 is greater than valid                      ////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 2 - Test if player's choice 2 is invalid\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 2, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    
    testAmbassadorEffect = ambassadorEffect(&G, 0, 0, 1, 3);
    
    if(testAmbassadorEffect == -1){
        printf ("Subtest 2 Result...Invalid choice 2?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Invalid choice 2?: Fail\n");
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player choice1 is the same as handPos is greater than valid   ////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 3 - Test if player's choice1 is the same as handPos\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 3, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    
    testAmbassadorEffect = ambassadorEffect(&G, 0, 0, 0, 1);
    
    if(testAmbassadorEffect == -1){
        printf ("Subtest 3 Result...Invalid choice 1?: Pass\n");
    }
    else{
        printf ("Subtest 3 Result...Invalid choice 1?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player does not have enough cards in choice2   ///////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("----------------------------------------------------------------------\n");
    printf ("Subtest 4 - Test if insufficient number cards for choice2\n");
    printf ("----------------------------------------------------------------------\n");
    memset(&G, 4, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = gold;
    G.hand[0][3] = gold;
    G.hand[0][4] = gold;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    
    testAmbassadorEffect = ambassadorEffect(&G, 0, 0, 1, 2);
    
    if(testAmbassadorEffect == -1){
        printf ("Subtest 4 Result...Invalid for insufficient cards?: Pass\n");
    }
    else{
        printf ("Subtest 4 Result...Invalid for insufficient cards?: Fail\n");
    }

    printf ("*******************************************\n");
    printf ("UNIT TEST 3 COMPLETE\n");
    printf ("*******************************************\n");

    return 0;

}
