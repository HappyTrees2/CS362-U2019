// Create alias 'bool' for primitive type 'int' to improve code clarity:
#define bool  int
#define true  1
#define false 0

#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include "rngs.h"
#include <stdio.h>
#include <string.h>

bool NOISY_TEST = false; // If true, display extra information during execution (normally used for debugging).

bool check_switch_noisyTest(int argc, char *argv[]); // Return true if flag '-n' set.
void print_gameState(struct gameState *pre, struct gameState *post);

int main(int argc, char *argv[])
{
  NOISY_TEST = check_switch_noisyTest(argc, argv);
  printf("===BEGIN random tests for card: BARON===\n");
  struct gameState G;
  int n = 0;
  for (n = 0; n < 1; n++)
  {
    int i = 0;
    int p = 0;
    for (i = 0; i < sizeof(struct gameState); i++)
      ((char*)&G)[i] = floor(Random() * 256);
    p = floor(Random() * 2) + 1;
    int c1 = floor(Random() * 2);

    G.numPlayers = 2;
    G.supplyCount[1] = floor(Random() * 24);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    
    struct gameState pre;
    memcpy(&pre, &G, sizeof(struct gameState));
    printf("pregame state: \n");
    execute_baron(&G, c1, p);
    print_gameState(&pre, &G);
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
  printf("deckCount[1] = %d || %d\n", pre->deckCount[1], post->deckCount[1]);
  printf("deckCount[2] = %d || %d\n", pre->deckCount[2], post->deckCount[2]);
  printf("discardCount[1] = %d || %d\n", pre->discardCount[1], post->discardCount[1]);
  printf("discardCount[2] = %d || %d\n", pre->discardCount[2], post->discardCount[2]);
  printf("playedCards[1] = %d || %d\n", pre->playedCards[1], post->playedCards[1]);
  printf("playedCards[2] = %d || %d\n", pre->playedCards[2], post->playedCards[2]);
  printf("playedCardCount = %d || %d\n", pre->playedCardCount, post->playedCardCount);
}
