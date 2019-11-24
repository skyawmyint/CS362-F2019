#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int main () {
    
    int r;
    int numPlayer = 2; // set the number of players
    int testTributeEffect; // return of testMinionEffect function
    int currentPlayer = 0; // set who the current player is
    
    // Counters before the function call
    int numActionsBefore; // **Randomized**
    int numCoinsBefore; // **Randomized**
    int numPlayerCardsBefore; // **Randomized**
    int numOpponentDeckBefore; // **Randomized**
    int numOpponentDiscardBefore; // **Randomized**
    
    // Counters for after function Call
    int revealedTemp[2] = {-1,-1};
    int actionsIncrease;
    int coinsIncrease;
    int cardsIncrease;
    
    // Flags to check if test passes
    int actionsCheck = 1; // check number of actions after call. 0 = not ok. 1 = ok.
    int coinsCheck = 1; // check number of coins after call
    int cardsCheck = 1; // check number of cards after call
    
    // Helper variables
    int randomCard; // random card to put in hand of player
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, tribute, great_hall};
    
    struct gameState G; // set a gameState
    srand(time(NULL)); //seed the random generator
    
    printf ("*****************************************************\n");
    printf ("RANDOM TEST 3: Random Testing tributeEffect function.\n");
    printf ("*****************************************************\n");
    
    memset(&G, 2, sizeof(struct gameState));
    
    for(int i = 0; i<1000000; i++){
    
        r = initializeGame(numPlayer, k, (int)(rand()%1000+1), &G);
        
        // Set the current player's number of Actions and Coins before
        numActionsBefore = (int)(rand()%10+1); // Random from 1 to 10
        G.numActions = numActionsBefore;
        numCoinsBefore = (int)(rand()%10+1); // Random from 1 to 10
        G.coins = numCoinsBefore;
        
        // Set the current player's hand with random number of cards -- use copper
        numPlayerCardsBefore = (int)(rand()%10+1); // Random from 1 to 10
        G.handCount[0] = numPlayerCardsBefore;
        for(int j=0; j<numPlayerCardsBefore; j++){
            G.hand[0][j] = copper;
        }
        
        // Set the opponent's deck pile
        numOpponentDeckBefore = (int)(rand()%4); // Random from 0 to 3
        G.deckCount[1] = numOpponentDeckBefore;
        
        // Randomize what is in the opponent's deck. 0-9: Corresponding to Action cards in k. 10-12 are copper, silver, gold. 13-17 are estate, duchy, province, gardens, and great_hall
        for(int j=0; j<numOpponentDeckBefore; j++){
            randomCard = (int)(rand()%18);
            if(randomCard <= 9){
                G.deck[1][j] = k[randomCard];
            }
            else if(randomCard==10){
                G.deck[1][j] = copper;
            }
            else if(randomCard==11){
                G.deck[1][j] = silver;
            }
            else if(randomCard==12){
                G.deck[1][j] = gold;
            }
            else if(randomCard==13){
                G.deck[1][j] = estate;
            }
            else if(randomCard==14){
                G.deck[1][j] = duchy;
            }
            else if(randomCard==15){
                G.deck[1][j] = province;
            }
            else if(randomCard==16){
                G.deck[1][j] = gardens;
            }
            else if(randomCard==17){
                G.deck[1][j] = great_hall;
            }
        }
        
        // Set the opponent's discard pile. Randomize what is in opponent's deck
        numOpponentDiscardBefore = (int)(rand()%4); // Random from 0 to 3
        G.discardCount[1] = numOpponentDiscardBefore;
        for(int j=0; j<numOpponentDiscardBefore; j++){
            randomCard = (int)(rand()%18);
            if(randomCard <= 9){
                G.discard[1][j] = k[randomCard];
            }
            else if(randomCard==10){
                G.discard[1][j] = copper;
            }
            else if(randomCard==11){
                G.discard[1][j] = silver;
            }
            else if(randomCard==12){
                G.discard[1][j] = gold;
            }
            else if(randomCard==13){
                G.discard[1][j] = estate;
            }
            else if(randomCard==14){
                G.discard[1][j] = duchy;
            }
            else if(randomCard==15){
                G.discard[1][j] = province;
            }
            else if(randomCard==16){
                G.discard[1][j] = gardens;
            }
            else if(randomCard==17){
                G.discard[1][j] = great_hall;
            }
        }
        
        // Keep track of what was revealed from deck. We will be checking for when the Deck has enough cards to not warrant shuffle of discard
        if(numOpponentDeckBefore>=2){
            revealedTemp[0] = G.deck[1][numOpponentDeckBefore-1];
            revealedTemp[1] = G.deck[1][numOpponentDeckBefore-2];
        }

        // If the revealed card was a duplicate
        if(revealedTemp[0] == revealedTemp[1]){
            revealedTemp[1] = -1;
        }
        
        // Call the card effect function
        testTributeEffect = tributeEffect(&G, currentPlayer+1, currentPlayer);
        
        // Add conditions based on rule of card
        actionsIncrease = 0;
        coinsIncrease = 0;
        cardsIncrease = 0;
        if(numOpponentDeckBefore>=2){
            for(int j=0; j<2; j++){
                
                if(revealedTemp[j] == copper || revealedTemp[j] == silver || revealedTemp[j] == gold){
                    coinsIncrease = coinsIncrease+2;
                }
                else if(revealedTemp[j] == estate || revealedTemp[j] == duchy || revealedTemp[j] == province || revealedTemp[j] == gardens || revealedTemp[j] == great_hall){
                    cardsIncrease = cardsIncrease+2;
                }
                else if(revealedTemp[j] == k[0] || revealedTemp[j] == k[1] || revealedTemp[j] == k[2] || revealedTemp[j] == k[3] || revealedTemp[j] == k[4] || revealedTemp[j] == k[5] || revealedTemp[j] == k[6] || revealedTemp[j] == k[7] || revealedTemp[j] == k[8] || revealedTemp[j] == k[9]){
                    actionsIncrease = actionsIncrease+2;
                }
            }
            
            // Checks to see if increases are correct
            if(numActionsBefore != G.numActions - actionsIncrease){
                actionsCheck = 0;
            }
            if(numCoinsBefore != G.coins - coinsIncrease){
                coinsCheck = 0;
            }
            if(numPlayerCardsBefore != G.handCount[0] - cardsIncrease){
                cardsCheck = 0;
            }
        }
    }
    // End of the for loop
    // Pass or Fail checks at the end of the tests.
    if(actionsCheck == 1){
        printf ("Subtest 1: Number of actions ok?: Pass\n");
    }
    else{
        printf ("Subtest 1: Number of actions ok?: Fail\n");
    }
    if(coinsCheck == 1){
        printf ("Subtest 2: Number of coins ok?: Pass\n");
    }
    else{
        printf ("Subtest 2: Number of coins ok?: Fail\n");
    }
    if(cardsCheck == 1){
        printf ("Subtest 3: Number of cards ok?: Pass\n");
    }
    else{
        printf ("Subtest 3: Number of cards ok?: Fail\n");
    }
    
    printf ("****************************************************************\n");
    printf ("RANDOM TEST 3 COMPLETE\n");
    printf ("****************************************************************\n");
    
    return 0;
    
}
