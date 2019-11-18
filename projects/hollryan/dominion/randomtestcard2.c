#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"



// source:https://cboard.cprogramming.com/c-programming/154145-random-number-interval-[0-1].html
int randInRange(int min, int max) // inclusive
{
	int num;
	num = rand() % (max - min + 1) + min;
	return num;
}


int test() {
	// This function first calls initializeGame() with random valid args. (The code provided by the assignment just gave it the same args every time.)
	// initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)

	// ARG 1 needs 2 to 4 players
	int numPlayers = randInRange(2, 4);

	// ARG 2 needs an array of 10 unique cards (nonestate, nontreasure)
	char cards[20][16] = { // 20 total possibilities, 16 chars each
		"adventurer",
		"council_room",
		"feast",
		"gardens",
		"mine",
		"remodel",
		"smithy",
		"village",
		"baron",
		"great_hall",
		"minion",
		"steward",
		"tribute",
		"ambassador",
		"cutpurse",
		"embargo",
		"outpost",
		"salvager",
		"sea_hag",
		"treasure_map"
	};

	// We will get 10 uniques by shuffling the cards using this algorithm: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#Modern_method
	int kingdomCards[10];
	int a = 19;
	int b;
	char holder[16];
	while (a > -1) {
		b = randInRange(0, 19);
		strcpy(holder, cards[a]);
		strcpy(cards[a], cards[b]);
		strcpy(cards[b], holder);
		a--;
	}
	a = 0;
	while (a < 10) {
		kingdomCards[a] = cards[a];
		a++;
	}

	// arg3 needs a random seed number
	int randomSeed = randInRange(1, 100);

	// arg4 needs a game state.
	struct gameState* state = newGame();

	// call the function to initialize the game
	int setup = initializeGame(numPlayers, kingdomCards, randomSeed, state);
	if (setup < 0) {
		// error
		printf("error with initializeGame() in randomtestcard2.c!\n\n");
	}
	else {
		printf("initializeGame() in randomtestcard2.c succeeded.\n\n");
	}
	// Generate random values for the state
	state->numPlayers = numPlayers;
	state->numBuys = randInRange(0, 10);
	int i;
	for (i = 0; i < treasure_map + 1; i++) {
		state->supplyCount[i] = randInRange(0, 20);
		state->embargoTokens[i] = randInRange(0, 20);
	}
	state->numActions = randInRange(0, 10);
	state->coins = randInRange(0, 10);
	state->discard[state->numPlayers][MAX_DECK];
	state->handCount[MAX_PLAYERS] = randInRange(0, MAX_DECK);
	state->discardCount[state->numPlayers] = randInRange(0, MAX_DECK);
	state->playedCardCount = randInRange(0, MAX_DECK);
	state->whoseTurn = randInRange(0, state->numPlayers - 1);
	state->deckCount[state->numPlayers] = MAX_DECK - *state->discardCount;
	/* State variables which we aren't changing
	state->outpostPlayed;
	state->outpostTurn;
	state->phase;
	state->hand[MAX_PLAYERS][MAX_HAND];
	state->deck[MAX_PLAYERS][MAX_DECK];
	state->playedCards[MAX_DECK];
	*/
	// fill up hand with random cards
	int estatesBefore = 0;
	for (i = 0; i < *state->handCount; i++) {
		*state->hand[state->whoseTurn] = randInRange(0, 19);
		if (state->hand[state->whoseTurn] == estate) {
			estatesBefore++;
		}
	}


	// generate the last 2 things it wants: a binary choice, and its position in the hand
	int choice1 = randInRange(0, 1);
	int choice2 = randInRange(0, 1);
	int choice3 = randInRange(0, 1);
//	printf("choice1: %d (draw=0, discard=1)\n", choice1);

	int handPos = randInRange(0, *state->handCount);
	//printf("handPos: %d\n", handPos);

	int numBuysBefore = state->numBuys;

	// now we will call the main function we are testing:
	// int minionCardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
	// run the test
	int test = minionCardEffect(0, choice1, 0, 0, state, handPos, 0);
	/*
	// check the results
	if (test == -1) {
		printf("\nTest returned -1 \n");
	}
	if (test == -2) {
		printf("\nEndless loop detected \n");
	}

	printf("numBuysBefore: %d\n", numBuysBefore);

	printf("buys after: %d\n", state->numBuys);

	if (state->numBuys != numBuysBefore + 1) {
		printf("error: did not increase buys by 1!\n");
	}

	int coinsBefore = state->coins;

	printf("estatesBefore: %d\n", estatesBefore);
	// we have to check if our hand contains an estate
	int estatesAfter = 0;
	for (i = 0; i < *state->handCount; i++) {
		if (state->hand[state->whoseTurn][i] == estate) {
			estatesAfter++;
		}
	}
	printf("estatesBefore: %d\n", estatesBefore);
	printf("estatesAfter: %d\n", estatesAfter);


	if (choice1 == 0 && estatesBefore != estatesAfter - 1) { // if they chose to draw but didnt gain one
		printf("error: chose to draw but didnt gain one! \n");
	}
	if (choice1 == 1 && estatesBefore != estatesAfter + 1) { // if they chose to discard but didnt lose one
		if (estatesBefore > 0) {
			printf("error: chose to discard, and had one, but didnt lose one! \n");
		}
		else {
			printf("chose to discard, but didn't have an estate to discard. \n");
		}
	}

	printf("coinsBefore: %d\n", coinsBefore);
	int coinsAfter = state->coins;
	printf("coinsAfter: %d\n", coinsAfter);
	if (choice1 == 1 && coinsAfter != coinsBefore + 4) { // chose to discard but didn get 4 cards
		printf("error: didnt get 4 coins for discarding! \n");
	}
	else if (coinsAfter != coinsBefore) {
		printf("error: coins changed value but shouldnt have!");
	}
	*/
}

int main(int argc, char* argv[]) {

	/* Intializes random number generator */
	time_t t;
	srand((unsigned)time(&t));

	int x;
	for (x = 0; x < 100; x++) {
		test();
	}
	return 0;
}
