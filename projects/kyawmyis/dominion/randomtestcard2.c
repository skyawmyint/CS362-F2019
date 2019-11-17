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
    int testminionEffect; // return of testMinionEffect function
    int currentPlayer = 0; // set who the current player is
    
    int choice1; // tracker for which choice1 player chose **Randomized**
    int choice2; // tracker for which choice2 player chose **Randomized**
    
    int handSizeBefore; // number of cards in current player's hand **Randomized**
    int opponentHandSizeBefore; // number of cards in opponent's hand **Randomized**
    int numActionsBefore; // number of actions a player has before Baron card played. **Randomized**
    int numCoinsBefore; // number of coins a player has before Baron card is played **Randomized**
    int numMinionBefore; // number of Minion cards in hand before
    
    // Counters for After function Call
    int numMinionAfter;
    int minionDiscard;
    
    // Flags to check if test passes
    int actionsCheck = 1; // check if the number of actionss is ok after Minion card is played. 1 = ok. 0 = not ok.
    int coinsCheck = 1; // check if the number of coins is ok after the Baron card is played
    int playerGainedFour = 1; // check if player gained 4 new cards.
    int playerHandCheck = 1; // check if the player's hand was properly discarded
    int playerDiscardCheck = 1; // check if the player's discard was properly added to
    int opponentHandCheck = 1; // check if the opponent's hand was properly discarded
    int opponentDiscardCheck = 1; // check if the opponent's discard was properly added to
    int opponentGainedFour = 1; // check if opponent gained 4 new cards.
    
    
    // Helper variables
    int randomCard; // random card to put in hand of player
    int minionIndex; // index of the Minion card
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, minion, great_hall};
    
    struct gameState G; // set a gameState
    srand(time(NULL)); //seed the random generator
    
    printf ("*****************************************************\n");
    printf ("RANDOM TEST 2: Random Testing minionEffect function.\n");
    printf ("*****************************************************\n");
    
    memset(&G, 2, sizeof(struct gameState));
    
    for(int i = 0; i<1000000; i++){
    
        r = initializeGame(numPlayer, k, (int)(rand()%1000+1), &G);
        
        // Randomize handCount of both players. From 1 to 10.
        handSizeBefore = (int)(rand()%10+1);
        G.handCount[0] = handSizeBefore;
        opponentHandSizeBefore = (int)(rand()%10+1);
        G.handCount[1] = handSizeBefore;
        
        // Initialize deck of both players with 20 counts of Coppers.
        G.deckCount[0] = 20;
        G.deckCount[1] = 20;
        for(int j = 0; j<20; j++){
            G.deck[0][j] = copper;
            G.deck[1][j] = copper;
        }
        
        // Set initial discardCount of both players to 0.
        G.discardCount[0] = 0;
        G.discardCount[1] = 0;
        
        numActionsBefore = (int)(rand()%10+1); // Randomize number of actions initially from 1-10
        G.numActions = numActionsBefore;
        numCoinsBefore = (int)(rand()%10+1); // Randomize number of coins initially from 1-10
        G.coins = numCoinsBefore;
        
        // Randomize the choice1 and choice2
        choice1 = (int)(rand()%2); // choice1 random. Either 0 or 1.
        if(choice1 == 1){
            choice2 = 0;
        }
        else{
            choice2 = 1;
        }
        
        // Randomize what is in the hand of the player and opponent
        // 0-10 are corresponding k array. 11 is a Silver card.
        // Player1
        for(int j=0; j<handSizeBefore; j++){
            randomCard = (int)(rand()%12);
            if(randomCard == 11){
                G.hand[0][j] = silver;
            }
            else{
                G.hand[0][j] = k[randomCard];
            }
        }
        // Player2
        for(int j=0; j<opponentHandSizeBefore; j++){
            randomCard = (int)(rand()%12);
            if(randomCard == 11){
                G.hand[0][j] = silver;
            }
            else{
                G.hand[0][j] = k[randomCard];
            }
        }
        
        // Find and count Minion card in player's hand.
        numMinionBefore = 0;
        minionIndex = 0;
        for(int j=0; j<handSizeBefore; j++){
            if(G.hand[0][j] == minion){
                minionIndex = j;
                numMinionBefore++;
            }
        }
        
        // If Minion card was found, run the testMinionEffect function.
        if(numMinionBefore > 0){
            
            testminionEffect = minionEffect(&G, minionIndex, currentPlayer, choice1, choice2);
            
            // Check if the number of actions is increased by 1
            if(numActionsBefore != G.numActions-1){
                actionsCheck = 0;
            }
        
            // Check for if choice1 was chosen
            if(choice1 == 1){
                
                // Check if Minion card was discarded from hand
                numMinionAfter = 0;
                for(int j=0; j<G.handCount[0]; j++){
                    if(G.hand[0][j] == minion){
                        numMinionAfter++;
                    }
                }
                if(numMinionBefore != numMinionAfter+1){
                    playerHandCheck = 0;
                }
                for(int j=0; j<G.discardCount[0]; j++){
                    if(G.discard[0][j] == minion){
                        minionDiscard = 1;
                    }
                }
                if(numMinionBefore != 1){
                    playerDiscardCheck = 0;
                }
              
                // Check if current player gains 2 coins
                if(numCoinsBefore != G.coins - 2){
                    coinsCheck = 0;
                }
            }
            
            // Else check for if choice2 was chosen
            else if(choice2 == 1){
                
                // Check if player 1 has 4 cards
                if(G.handCount[0] != 4 ){
                    playerGainedFour = 0;
                }
                for(int j = 0; j < G.handCount[0]; j++){
                    if(G.hand[0][j] != copper){
                        playerHandCheck = 0;
                    }
                }
                
                // Check if player 1's discard pile has what was in hand before
                if(handSizeBefore != G.discardCount[0]){
                    playerDiscardCheck = 0;
                }
                
                // Checks if player 2 had 4 or less cards //
                if(opponentHandSizeBefore<=4) {
                    // Check if player 2 had same hand size as before
                    if(opponentHandSizeBefore != G.handCount[1]){
                        opponentHandCheck = 0;
                    }
                    // Check if player 2 has same discard size as before
                    if(G.discardCount[1] != 0){
                        opponentDiscardCheck = 0;
                    }
                }
                // Checks if player 2 had 5 or more cards
                else if(opponentHandSizeBefore>4){
                    // Check handCount of player 2
                    if(G.handCount[1] != 4){
                        opponentGainedFour = 0;
                    }
                    
                    // Check hand of player 2 is from deck
                    for(int j=0; j<G.handCount[1]; j++){
                        if(G.hand[1][j]!=copper){
                            opponentHandCheck = 0;
                        }
                    }
                    
                    // Check if discard has number of cards from previously
                    if(G.discardCount[1] != opponentHandSizeBefore){
                        opponentDiscardCheck = 0;
                    }
                }
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
    if(playerHandCheck == 1){
        printf ("Subtest 3: Type of Cards in player 1's hand ok?: Pass\n");
    }
    else{
        printf ("Subtest 3: Type of Cards in player 1's hand ok?: Fail\n");
    }
    if(playerDiscardCheck == 1){
        printf ("Subtest 4: Cards in player 1's discard ok?: Pass\n");
    }
    else{
        printf ("Subtest 4: Cards in player 1's discard ok?: Fail\n");
    }
    if(playerGainedFour == 1){
        printf ("Subtest 5: Number of cards in player 1's hand ok?: Pass\n");
    }
    else{
        printf ("Subtest 5: Number of cards in player 1's hand ok?: Fail\n");
    }
    if(opponentHandCheck == 1){
        printf ("Subtest 6: Type of Cards in player 2's hand ok?: Pass\n");
    }
    else{
        printf ("Subtest 6: Type of Cards in player 2's hand ok?: Fail\n");
    }
    if(opponentDiscardCheck == 1){
        printf ("Subtest 7: Cards in player 2's discard ok?: Pass\n");
    }
    else{
        printf ("Subtest 7: Cards in player 2's discard ok?: Fail\n");
    }
    if(opponentGainedFour == 1){
        printf ("Subtest 8: Number of cards in player 2's hand ok?: Pass\n");
    }
    else{
        printf ("Subtest 8: Number of cards in player 2's hand ok?: Fail\n");
    }
    
    printf ("****************************************************************\n");
    printf ("RANDOM TEST 2 COMPLETE\n");
    printf ("****************************************************************\n");
    
    return 0;
    
}
