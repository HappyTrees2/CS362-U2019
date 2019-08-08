// Create alias 'bool' for primitive type 'int' to improve code clarity:
#define bool  int
#define true  1
#define false 0

#define NUM_TEST_ITERATIONS 500

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
    // Test results
    if(pre.numBuys + 1 != post.numBuys) printf("FAIL numBuys not incremented\n");
    if(pre.coins + 4 != post.coins && choice == 1) printf("FAIL coins not incremented\n");

    if(NOISY_TEST) print_gameState(&pre, &post);
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
  printf("numPlayers = %d", pre->numPlayers);
  if(pre->numPlayers != post->numPlayers) printf(" || %d", post->numPlayers);
  printf("\n");

  printf("outpostPlayed = %d", pre->outpostPlayed);
  if(pre->outpostPlayed != post->outpostPlayed) printf("|| %d", post->outpostPlayed);
  printf("\n");

  printf("outpostTurn = %d", pre->outpostTurn);
  if(pre->outpostTurn != post->outpostTurn) printf(" || %d", post->outpostTurn);
  printf("\n");

  printf("whoseTurn = %d", pre->whoseTurn);
  if(pre->whoseTurn != post->whoseTurn) printf(" || %d", post->whoseTurn);
  printf("\n");

  printf("phase = %d", pre->phase);
  if(pre->phase != post->phase) printf(" || %d", post->phase);
  printf("\n");
  
  printf("numActions = %d", pre->numActions);
  if(pre->numActions != post->numActions) printf(" || %d", post->numActions);
  printf("\n");

  printf("coins = %d", pre->coins);
  if(pre->coins != post->coins) printf(" || %d", post->coins);
  printf("\n");

  printf("numBuys = %d", pre->numBuys);
  if(pre->numBuys != post->numBuys) printf(" || %d\n", post->numBuys);
  printf("\n");

  int currentPlayer = 1;
  for (currentPlayer = 1; currentPlayer < pre->numPlayers + 1; currentPlayer++)
  {
    printf("handCount[%d] = %d", currentPlayer, pre->handCount[currentPlayer]);
    if(pre->handCount[currentPlayer] != post->handCount[currentPlayer]) printf(" || %d", post->handCount[currentPlayer]);
    printf("\n");

    printf("deckCount[%d] = %d", currentPlayer, pre->deckCount[currentPlayer]);
    if(pre->deckCount[currentPlayer] != post->deckCount[currentPlayer]) printf(" || %d", post->deckCount[currentPlayer]);
    printf("\n");

    printf("discardCount[%d] = %d", currentPlayer, pre->discardCount[currentPlayer]);
    if(pre->discardCount[currentPlayer] != post->discardCount[currentPlayer]) printf(" || %d", post->discardCount[currentPlayer]);
    printf("\n");

    printf("playedCards[%d] = %d", currentPlayer, pre->playedCards[currentPlayer]);
    if(pre->playedCards[currentPlayer] != post->playedCards[currentPlayer]) printf(" || %d", post->playedCards[currentPlayer]);
    printf("\n");
  }

  printf("playedCardCount = %d", pre->playedCardCount);
  if(pre->playedCardCount != post->playedCardCount) printf(" || %d\n", post->playedCardCount);
  printf("\n");
}
