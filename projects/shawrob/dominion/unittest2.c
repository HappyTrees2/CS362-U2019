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

testResult playing_minion_adds_1_action(struct gameState gameState)
{
  noisyprint("Playing Minion adds +1 action:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Minion adds +1 action.", 255);

  int actionsBefore = 0;
  int actionsAfter  = 0;

  actionsBefore = testState.numActions;
  noisyprint("\tactionsBefore = %d\n", actionsBefore);

  playCard(0, 0, 0, 0, &testState);

  actionsAfter = testState.numActions;
  noisyprint("\tactionsAfter  = %d\n", actionsAfter);

  if(actionsAfter == actionsBefore)
    return success;
  else
    return failure;
}

testResult minion_choice_1_adds_2_coins(struct gameState gameState)
{
  noisyprint("Minion choice 1 adds +2 coins:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Minion choice 1 adds +2 coins.", 255);

  int coinsBefore = 0;
  int coinsAfter  = 0;

  coinsBefore = testState.coins;
  noisyprint("\tcoinsBefore = %d\n", coinsBefore);

  playCard(0, 1, 0, 0, &testState);

  coinsAfter = testState.coins;
  noisyprint("\tcoinsAfter  = %d\n", coinsAfter);

  if(coinsAfter == coinsBefore + 2)
    return success;
  else
    return failure;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR CARD: MINION===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);
  gameState.hand[0][0] = minion;

  assert_true( first_test_returns_success(gameState) );
  assert_true( playing_minion_adds_1_action(gameState) );
  assert_true( minion_choice_1_adds_2_coins(gameState) );

  printf("====END TEST SUITE FOR CARD: MINION====\n\n");
  return 0;
}
