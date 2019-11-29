#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int assert(int expected, int testval , char* string)
{
	if(expected==testval)
	{return 0;}
	else if(expected > testval)
	{printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);} 
	else if(expected < testval)
	{printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);} 
	return 1;
}

int falseAssert(int NotExpected, int testval , char* string)
{
	if(NotExpected!=testval)
	{return 0;}
	else 	{printf("FALSE-ASSERT FAILED: (%d-NotAllowed ) and (%d-value present) for %s\n", NotExpected, testval, string);} 
	return 1;
}


int printGameState(struct gameState G)
{
	printf("numPlayers: %d\n", G.numPlayers);
	printf("Whose turn: %d\n", G.whoseTurn);
	printf("Number of buys: %d\n", G.numBuys);
	printf("Number of coins: %d\n", G.coins);
	printf("Number of actions: %d\n", G.numActions);
	printf("Current player Handcount: %d\n", G.handCount[G.whoseTurn]);
	printf("Current player DeckCount: %d\n", G.deckCount[G.whoseTurn]);
	printf("Current player Discard Count: %d\n", G.discardCount[G.whoseTurn]);
	printf("Current player Played cards: %d\n", G.playedCardCount);
	
	printf("Current player Cards in hand: ");
	int a = 0;
	for(a=0; a < G.handCount[G.whoseTurn]; a++)
		{
		printf("%d ", G.hand[G.whoseTurn][a]);
		}
	printf("\n");
	printf("Current player Cards in deck: ");
	for(a=0; a < G.deckCount[G.whoseTurn]; a++)
		{
		printf("%d ", G.deck[G.whoseTurn][a]);
		}
	printf("\n");
	printf("Current player Cards in discard ");
	for(a=0; a < G.discardCount[G.whoseTurn]; a++)
		{
		printf("%d ", G.discard[G.whoseTurn][a]);
		}
	printf("\n");
	printf("Current player Cards in Played Cards " );
	for(a=0; a < G.playedCardCount; a++)
		{
		printf("%d ", G.playedCards[a]);
		}
	printf("\n");
	
	printf("Card numbers in supply ");
	
	for(a=0; a < 26; a++)
		{
		printf("%d ", G.supplyCount[a]);
		}
	printf("\n");

	return 0;
}




//Declare Gamestate
int main()
{
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	struct gameState G;
	struct gameState preG;
	
	unsigned seed;
	seed = time(0);
	srand(seed);

//////////////////////////////////////////////////
//Begin test 1
// Try to upgrade a estate to gold
//////////////////////////////////////////////////
	memset(&G, 23, sizeof(struct gameState)); 
	memset(&preG, 23, sizeof(struct gameState)); 
	int r = initializeGame(3, k, seed, &G);
	assert(0,r,"initialize Game");

	//make testing changes to gamestate
	G.hand[G.whoseTurn][0] = mine; //mine added to deck 
	G.hand[G.whoseTurn][1] = silver; // add estate to deck 
	G.hand[G.whoseTurn][2] = estate; 
	G.hand[G.whoseTurn][3] = estate;
	G.hand[G.whoseTurn][4] = estate;

	//copy inital gamestate
	memcpy(&preG, &G, sizeof(G));
	int returnVal;
	int *placeholder = NULL;
	
	//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
	returnVal = cardEffect( mine, 1, gold,  -1, &G, 0, placeholder); 
	
//	printGameState(preG);
//	printGameState(G);

	//Test results for expected outcome
	printf("TEST Bug 2 RESULTS: upgrade a silver to a gold\n");
	assert( 0, returnVal, "Return Value should be zero" );
	assert( mine, G.playedCards[0], "mine missing from played cards");
	assert( 1, G.playedCardCount, "expected only one card in played cards array");
	assert( G.handCount[0], 4, "Handcount not 4 cards");
	int a = 0;
	int estatecount = 0;
	int goldcount = 0;
	for(a=0; a < G.handCount[G.whoseTurn]; a++)
		{
			if(G.hand[G.whoseTurn][a] == estate) {estatecount++;}
			if(G.hand[G.whoseTurn][a] == gold) {goldcount++;}
		}
	assert( 3, estatecount, "Number of estates in hand should be 3");
	assert( 1, goldcount, "Number of golds in hand should be 1"); 

	return 0;
}
