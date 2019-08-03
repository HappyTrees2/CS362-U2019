#include "dominion_helpers.h"   // "dominion.h" is included within this header.
#include <stdio.h>              // printf
#include <string.h>             // memcpy

#define testResult int
#define success 1
#define failure 0

#define bool  int
#define true  1
#define false 0

bool NOISY_TEST = false;
#define noisyprint if(NOISY_TEST) printf

char testTitle[256];

void assert_true(testResult result)
{
  if (result == success)
    printf("+ PASS\t%s\n", testTitle);
  else
    printf("- FAIL\t%s\n", testTitle);
}

testResult first_test_returns_success(struct gameState gameState)
{
  noisyprint("First test returns success:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "First test returns success.", 255);

  return success;
}

testResult shuffled_deck_stays_same_size(struct gameState gameState)
{
  noisyprint("Shuffling a deck does not change its size:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Shuffling a deck does not change its size.", 255);

  int deckSizeBefore = 0;
  int deckSizeAfter  = 0;

  deckSizeBefore = testState.deckCount[0];

  shuffle(0, &testState);

  deckSizeAfter = testState.deckCount[0];

  if(deckSizeAfter == deckSizeBefore)
    return success;
  else
    return failure;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR FUNCTION: SHUFFLE===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);

  assert_true( first_test_returns_success(gameState) );
  assert_true( shuffled_deck_stays_same_size(gameState) );

  printf("====END TEST SUITE FOR FUNCTION: SHUFFLE====\n\n");
  return 0;
}
