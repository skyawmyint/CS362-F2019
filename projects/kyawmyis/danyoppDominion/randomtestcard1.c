#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"



int main () {
    
    int numPlayer = 2; // set the number of players
    int testBaronEffect; // return of testBaronEffect function
    int currentPlayer = 0; // set who the current player is
    
    int choice1; // tracker for which choice1 player chose **Randomized**
    
    int maxHandSize = 5; // maximum number of cards in current player's hand
    
    int r;
    int numBuysBefore; // number of buys a player has before Baron card played. **Randomized**
    int numCoinsBefore; // number of coins a player has before Baron card is played **Randomized**
    int numEstateBefore; // counter of the number of Estate cards in hand before Baron card is played
    int numEstateAfter; // counter of the number of Estate cards in hand after Baron card is played
    int numSupplyBefore; // counter of the number of Estate cards in supply before Baron card **Randomized**
    
    // Flags to check if test passes
    int buysCheck = 1; // check if the number of buys is ok after Baron card is played. 1 = ok. 0 = not ok.
    int coinsCheck = 1; // check if the number of coins is ok after the Baron card is played
    int estateCheck = 1; // check if estate correctly gained in hand.
    int supplyCheck = 1; // check if the supply was reduced by ok.
    int discardCheck = 1; // check if the Estate was added to discard pile
    
    // Helper variables
    int randomCard; // random card to put in hand of player
    int isSupplyEmpty; // check to see if Estate supply is empty initially
    
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall
    };
    
    struct gameState G; // set a gameState
    srand(time(NULL)); //seed the random generator
    
    printf ("*****************************************************\n");
    printf ("RANDOM TEST 1: Random Testing baronEffect function.\n");
    printf ("*****************************************************\n");
    
    memset(&G, 1, sizeof(struct gameState));
    
    for(int i = 0; i<1000000; i++){
    
        r = initializeGame(numPlayer, k, (int)(rand()%1000+1), &G);
        G.handCount[0] = maxHandSize;
        numBuysBefore = (int)(rand()%10+1); // Randomize number of buys initially from 1-10
        G.numBuys = numBuysBefore;
        numCoinsBefore = (int)(rand()%10+1); // Randomize number of coins initially from 1-10
        G.coins = numCoinsBefore;
        numSupplyBefore = (int)(rand()%9); // Randomize number of Estate cards in supply initially from 0-8
        G.supplyCount[estate] = numSupplyBefore;
        isSupplyEmpty = 0;
        if(numSupplyBefore == 0){
            isSupplyEmpty = 1;
        }
        
        // Make the player have an empty discard
        G.discard[0][0] = -1;
        
        choice1 = (int)(rand()%2); // choice1 random. Either 0 or 1.
        
        // Randomize what is in the hand of the player
        // 0-10 are corresponding k array. 11 is the Estate card.
        for(int j=0; j<maxHandSize; j++){
            randomCard = (int)(rand()%12);
            if(randomCard == 11){
                G.hand[0][j] = estate;
            }
            else{
                G.hand[0][j] = k[randomCard];
            }
        }
        
        // Count the number of Estate card in the hand of player
        numEstateBefore = 0;
        for(int j=0; j<maxHandSize; j++){
            if(G.hand[0][j] == estate){
                numEstateBefore++;
            }
        }
        
        // Run the Baron card effect function
        testBaronEffect = baronEffect(choice1, &G, currentPlayer);
        
        // Check if the number of Buys are ok
        if(numBuysBefore != G.numBuys-1){
            buysCheck = 0;
        }
    
        // Checks for if the player chose choice1 = 0. To Gain an Estate card.
        if(choice1 == 0){
            // Check for the condition that the Estate supply was not empty before
            if(isSupplyEmpty == 0){
                if(G.discard[0][0] != estate){
                    discardCheck = 0;
                }
                if(numSupplyBefore != G.supplyCount[estate]+1){
                    supplyCheck = 0;
                }
            }
            // Check for the condition that the Estate supply was empty
            else if(isSupplyEmpty == 1){
                if(G.discard[0][0] != -1){
                    discardCheck = 0;
                }
                if(numSupplyBefore != supplyCount(estate, &G)){
                    supplyCheck = 0;
                }
            }
            
            // Check that the number of coins stayed the same
            if(numCoinsBefore != G.coins){
                coinsCheck = 0;
            }
        }
        
        // Checks for if the player chose choice1 = 1. To discard an Estate to gain 4 coins.
        else if(choice1 == 1){
            // If there was an estate in the hand of the player
            if(numEstateBefore > 0){
                // Check that the number of coins is gained by 4.
                if(numCoinsBefore != G.coins-4){
                    coinsCheck = 0;
                }
                
                // Check that an Estate card was removed to discard in player hand
                numEstateAfter = 0;
                for(int j=0; j<G.handCount[0]; j++){
                    if(G.hand[0][j] == estate){
                        numEstateAfter++;
                    }
                }
                if(numEstateBefore != numEstateAfter+1){
                    estateCheck = 0;
                }
                // Check that an Estate card was put into the discard pile
                if(G.discard[0][0] != estate){
                    discardCheck = 0;
                }
               
            }
            // Else the player should have just gained an estate card if the supply was not empty.
            else if(isSupplyEmpty == 0){
                // Check if supply was not empty
                if(G.discard[0][0] != estate){
                    discardCheck = 0;
                }
                if(numSupplyBefore != G.supplyCount[estate]+1){
                    supplyCheck = 0;
                }
                if(numCoinsBefore != G.coins){
                    coinsCheck = 0;
                }
            }
            // Else check if the supply was empty
            else if(isSupplyEmpty == 1){
                if(G.discard[0][0] != -1){
                    discardCheck = 0;
                }
                if(numSupplyBefore != supplyCount(estate, &G)){
                    supplyCheck = 0;
                }
                if(numCoinsBefore != G.coins){
                    coinsCheck = 0;
                }
            }
        }
    }
    // Pass or Fail checks at the end of the tests.
    if(buysCheck == 1){
        printf ("Subtest 1: Number of buys ok?: Pass\n");
    }
    else{
        printf ("Subtest 1: Number of buys ok?: Fail\n");
    }
    
    if(estateCheck == 1){
        printf ("Subtest 2: Number of Estate in hand ok?: Pass\n");
    }
    else{
        printf ("Subtest 2: Number of Estate in hand ok?: Fail\n");
    }
    
    if(coinsCheck == 1){
        printf ("Subtest 3: Number of coins ok?: Pass\n");
    }
    else{
        printf ("Subtest 3: Number of coins ok?: Fail\n");
    }
    
    if(supplyCheck == 1){
        printf ("Subtest 4: Number of Estate in supply ok?: Pass\n");
    }
    else{
        printf ("Subtest 4: Number of Estate in supply ok?: Fail\n");
    }
    
    if(discardCheck == 1){
        printf ("Subtest 5: Number of Estate in discard ok?: Pass\n");
    }
    else{
        printf ("Subtest 5: Number of Estate in discard ok?: Fail\n");
    }
    
    printf ("****************************************************************\n");
    printf ("RANDOM TEST 1 COMPLETE\n");
    printf ("****************************************************************\n");
    
    return 0;
    
}
