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
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, tribute };

	struct gameState G;
	
	unsigned seed;
	seed = time(0);
	srand(seed);

//////////////////////////////////////////////////
//Begin test 1
//////////////////////////////////////////////////
	memset(&G, 23, sizeof(struct gameState)); 
	int r = initializeGame(3, k, seed, &G);
	assert(0,r,"initialize Game");

	//make testing changes to gamestate
	G.supplyCount[province] = 0; 


	int returnVal;
	
	returnVal = isGameOver(&G);

//	printGameState(G);

	//Test results for expected outcome
	printf("TEST Bug 4a RESULTS: Game Over? no providence\n");
	assert( 1, returnVal, "Return Value should be one" );

//////////////////////////////////////////////////
//Begin test 2
//////////////////////////////////////////////////
	memset(&G, 23, sizeof(struct gameState)); 
	r = initializeGame(3, k, seed, &G);
	assert(0,r,"initialize Game");

	//make testing changes to gamestate
	G.supplyCount[sea_hag] = 0; 
	G.supplyCount[treasure_map] = 0; 

	returnVal = isGameOver(&G);

//	printGameState(G);

	//Test results for expected outcome
	printf("TEST Bug 4b RESULTS: Game Over? no sea_hag no treasure_map\n");
	assert( 0, returnVal, "Return Value should be zero" );

//////////////////////////////////////////////////
//Begin test 3
//////////////////////////////////////////////////
	memset(&G, 23, sizeof(struct gameState)); 
	r = initializeGame(3, k, seed, &G);
	assert(0,r,"initialize Game");

	//make testing changes to gamestate
	G.supplyCount[salvager] = 0; 
	G.supplyCount[sea_hag]= 0; 
	G.supplyCount[treasure_map] = 0; 

	returnVal = isGameOver(&G);

//	printGameState(G);

	//Test results for expected outcome
	printf("TEST Bug 4c RESULTS: Game Over? no salvager, no sea_hag, no treasure_map\n");
	assert( 1, returnVal, "Return Value should be one" );




return 0;
}
