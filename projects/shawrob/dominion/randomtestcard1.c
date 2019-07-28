// Create alias 'bool' for primitive type 'int' to improve code clarity:
#define bool  int
#define true  1
#define false 0

#define NUM_TEST_ITERATIONS 1000

#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include "rngs.h"
#include <stdio.h>
#include <string.h>

bool NOISY_TEST = false; // If true, display extra information during execution (normally used for debugging).
#define noisyprint if(NOISY_TEST) printf

bool check_switch_noisyTest(int argc, char *argv[]); // Return true if flag '-n' set.
void print_gameState(struct gameState *pre, struct gameState *post);

int main(int argc, char *argv[])
{
  NOISY_TEST = check_switch_noisyTest(argc, argv);
  printf("===BEGIN random tests for card: BARON===\n");

  int currentTest, currentByte; // Iterators.

  for (currentTest = 0; currentTest < NUM_TEST_ITERATIONS; currentTest++)
  {
    noisyprint("===ITERATION %d===\n", currentTest);
    struct gameState pre, post;   // For comparing game state before and after test execution.
    
    for (currentByte = 0; currentByte < sizeof(struct gameState); currentByte++)
      ((char*)&post)[currentByte] = floor(Random() * 256);

    post.numPlayers = floor(Random() * 3) + 2; // Valid player count: 2-4.
    int player = floor(Random() * post.numPlayers) + 1; // Choose one of the players.
    int choice = floor(Random() * 2);

    noisyprint("Number of players = %d\t", post.numPlayers);
    noisyprint("Chosen player = %d\t", player);
    noisyprint("Choice = %d\n", choice);

    // Ensure sane values for relevant game state values.
    post.supplyCount[estate] = floor(Random() * 24);
    post.discardCount[player] = floor(Random() * MAX_DECK);
    int currentCard = 0;
    post.handCount[player] = 0;
    for (currentCard = 0; currentCard < MAX_HAND; currentCard++)
    {
      post.hand[player][currentCard] = floor(Random() * 28);
      ++post.handCount[player];
      if(floor(Random() * 4) == 1) break;
    }
    
    memcpy(&pre, &post, sizeof(struct gameState));
    execute_baron(&post, choice, player);
    print_gameState(&pre, &post);
  }
  printf("===END   random tests for card: BARON===\n");
  return 0;
}

bool check_switch_noisyTest(int argc, char *argv[])
{
  // Currently, will only return true if EXACTLY argv[1] is set to '-n'.
  // TODO: Update this to function like UNIX builtin flags (set anywhere and in any combination).
  if (argc > 1 && strcmp(argv[1], "-n") == 0)
  {
    printf("NOISY TEST\n");
    return true;
  }
  else
  {
    printf("For noisy test: %s -n\n", argv[0]);
    return false;
  }
}

void print_gameState(struct gameState *pre, struct gameState *post)
{
  printf("numPlayers = %d || %d\n", pre->numPlayers, post->numPlayers);
  //int i = 0;
  //for(i = 0; i < 27; i++)
  //  printf("\tsupplyCount[%d] = %d\n", i, pre->supplyCount[i]);
  //for(i = 0; i < 27; i++)
  //  printf("\tembargoTokens[%d] = %d\n", i, pre->embargoTokens[i]);
  printf("outpostPlayed = %d || %d\n", pre->outpostPlayed, post->outpostPlayed);
  printf("outpostTurn = %d || %d\n", pre->outpostTurn, post->outpostTurn);
  printf("whoseTurn = %d || %d\n", pre->whoseTurn, post->whoseTurn);
  printf("phase = %d || %d\n", pre->phase, post->phase);
  printf("numActions = %d || %d\n", pre->numActions, post->numActions);
  printf("coins = %d || %d\n", pre->coins, post->coins);
  printf("numBuys = %d || %d\n", pre->numBuys, post->numBuys);
  printf("handCount[1] = %d || %d\n", pre->handCount[1], post->handCount[1]);
  printf("handCount[2] = %d || %d\n", pre->handCount[2], post->handCount[2]);
  printf("handCount[3] = %d || %d\n", pre->handCount[3], post->handCount[3]);
  printf("handCount[4] = %d || %d\n", pre->handCount[4], post->handCount[4]);
  printf("deckCount[1] = %d || %d\n", pre->deckCount[1], post->deckCount[1]);
  printf("deckCount[2] = %d || %d\n", pre->deckCount[2], post->deckCount[2]);
  printf("deckCount[3] = %d || %d\n", pre->deckCount[3], post->deckCount[3]);
  printf("deckCount[4] = %d || %d\n", pre->deckCount[4], post->deckCount[4]);
  printf("discardCount[1] = %d || %d\n", pre->discardCount[1], post->discardCount[1]);
  printf("discardCount[2] = %d || %d\n", pre->discardCount[2], post->discardCount[2]);
  printf("discardCount[3] = %d || %d\n", pre->discardCount[3], post->discardCount[3]);
  printf("discardCount[4] = %d || %d\n", pre->discardCount[4], post->discardCount[4]);
  printf("playedCards[1] = %d || %d\n", pre->playedCards[1], post->playedCards[1]);
  printf("playedCards[2] = %d || %d\n", pre->playedCards[2], post->playedCards[2]);
  printf("playedCards[3] = %d || %d\n", pre->playedCards[3], post->playedCards[3]);
  printf("playedCards[4] = %d || %d\n", pre->playedCards[4], post->playedCards[4]);
  printf("playedCardCount = %d || %d\n", pre->playedCardCount, post->playedCardCount);
}
