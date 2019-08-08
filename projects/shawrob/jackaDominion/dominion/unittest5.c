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

testResult mine_trashes_chosen_treasure(struct gameState gameState)
{
  noisyprint("Mine trashes chosen treasure:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Mine trashes chosen treasure.", 255);

  int copperBefore = 0;
  int copperAfter  = 0;

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == copper) ++copperBefore;
  noisyprint("copperBefore = %d\n", copperBefore);

  playCard(0, 1, 0, 0, &testState);

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == copper) ++copperAfter;
  noisyprint("copperAfter = %d\n", copperAfter);

  if(copperAfter == copperBefore - 1)
    return success;
  else
    return failure;
}

testResult mine_gains_a_silver(struct gameState gameState)
{
  noisyprint("Mine gains a silver:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Mine gains a silver.", 255);

  int silverBefore = 0;
  int silverAfter  = 0;

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == silver) ++silverBefore;
  noisyprint("silverBefore = %d\n", silverBefore);

  playCard(0, 1, 0, 0, &testState);

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == silver) ++silverAfter;
  noisyprint("silverBefore = %d\n", silverAfter);

  if(silverAfter == silverBefore + 1)
    return success;
  else
    return failure;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR CARD: MINE===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);
  gameState.hand[0][0] = mine;

  assert_true( first_test_returns_success(gameState) );
  assert_true( mine_trashes_chosen_treasure(gameState) );
  assert_true( mine_gains_a_silver(gameState) );

  printf("====END TEST SUITE FOR CARD: MINE====\n\n");
  return 0;
}
