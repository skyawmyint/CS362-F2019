#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Unit test portions reused from my (Stuart Kyawmyint's) assignment #3.

int main () {
    
    int testAmbassadorEffect;
    int r;
    int numSupplySilverOriginal;
    int bonus_coins;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, ambassador, great_hall
    };
    
    struct gameState G;
    
    printf ("*************************************************************\n");
    printf ("UNIT TEST 10: Testing ambassador card on cardEffect function.\n");
    printf ("*************************************************************\n");
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player does not have enough cards in choice2   ///////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("-------------------------------------------------------------------------\n");
    printf ("Subtest 1 - Test if insufficient number cards for choice2. choice1 in hand \n");
    printf ("-------------------------------------------------------------------------\n");
    memset(&G, 4, sizeof(struct gameState));
    r = initializeGame(3, k, 323, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = gold;
    G.hand[0][3] = gold;
    G.hand[0][4] = gold;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    bonus_coins = 0;
    
    testAmbassadorEffect = cardEffect(ambassador, 1, 2, 0, &G, 0, &bonus_coins);
    
    if(testAmbassadorEffect == -1){
        printf ("Subtest 1 Result...Invalid for insufficient cards?: Pass\n");
    }
    else{
        printf ("Subtest 1 Result...Invalid for insufficient cards?: Fail\n");
    }
    
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if player does not have enough cards in choice2   ///////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("-------------------------------------------------------------------------------\n");
    printf ("Subtest 2 - Test if insufficient number cards for choice2. choice1 not in hand \n");
    printf ("-------------------------------------------------------------------------------\n");
    memset(&G, 5, sizeof(struct gameState));
    r = initializeGame(3, k, 321, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = gold;
    G.hand[0][3] = gold;
    G.hand[0][4] = gold;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    bonus_coins = 0;
    
    testAmbassadorEffect = cardEffect(ambassador, estate, 1, 0, &G, 0, &bonus_coins);
    
    if(testAmbassadorEffect == -1){
        printf ("Subtest 2 Result...Invalid for insufficient cards?: Pass\n");
    }
    else{
        printf ("Subtest 2 Result...Invalid for insufficient cards?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if revealed card from player is trashed and gained by others ////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("---------------------------------------------------------------------------------------------------\n");
    printf ("Subtest 3 - Test if player's card is trashed and gained by others. Return valid with choice2 as 2.:\n");
    printf ("---------------------------------------------------------------------------------------------------\n");
    memset(&G, 6, sizeof(struct gameState));
    r = initializeGame(3, k, 320, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    
    testAmbassadorEffect = cardEffect(ambassador, 1, 2, 0, &G, 0, &bonus_coins);
    
    if(testAmbassadorEffect == 0){
        printf ("Subtest 3 Result...Valid?: Pass\n");
    }
    else{
        printf ("Subtest 3 Result...Valid?: Fail\n");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    // Test to see if revealed card from player is trashed and gained by others ////////
    ////////////////////////////////////////////////////////////////////////////////////
    printf ("---------------------------------------------------------------------------------------------------\n");
    printf ("Subtest 4 - Test if player's card is trashed and gained by others. Return valid with choice2 as 0.:\n");
    printf ("---------------------------------------------------------------------------------------------------\n");
    memset(&G, 7, sizeof(struct gameState));
    r = initializeGame(3, k, 311, &G);
    G.hand[0][0] = ambassador;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.handCount[0] = 5;
    numSupplySilverOriginal = G.supplyCount[silver];
    
    testAmbassadorEffect = cardEffect(ambassador, 1, 0, 0, &G, 0, &bonus_coins);
    
    if(testAmbassadorEffect == 0){
        printf ("Subtest 4 Result...Valid?: Pass\n");
    }
    else{
        printf ("Subtest 4 Result...Valid?: Fail\n");
    }
    
    printf ("*******************************************\n");
    printf ("UNIT TEST 10 COMPLETE\n");
    printf ("*******************************************\n");
    
    return 0;
    
}
