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

testResult tribute_action_treasure_draw_adds_2_actions_and_2_coins(struct gameState gameState)
{
  noisyprint("Tribute adds 2 actions and 2 coins when appropriate:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Tribute adds 2 actions and 2 coins when appropriate.", 255);

  int actionsBefore = 0;
  int coinsBefore   = 0;
  int actionsAfter  = 0;
  int coinsAfter    = 0;

  actionsBefore = testState.numActions;
  coinsBefore   = testState.coins;
  noisyprint("\tactionsBefore = %d\n", actionsBefore);
  noisyprint("\tcoinsBefore   = %d\n", coinsBefore);

  playCard(0, 0, 0, 0, &testState);

  actionsAfter = testState.numActions;
  coinsAfter   = testState.coins;
  noisyprint("\tactionsAfter = %d\n", actionsAfter);
  noisyprint("\tcoinsAfter   = %d\n", coinsAfter);

  if(actionsAfter == actionsBefore + 1 && coinsAfter == coinsBefore + 2)
    return success;
  else
    return failure;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR CARD: TRIBUTE===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);
  gameState.hand[0][0] = tribute;

  assert_true( first_test_returns_success(gameState) );

  gameState.deck[1][0] = estate;
  gameState.deck[1][1] = copper;
  assert_true( tribute_action_treasure_draw_adds_2_actions_and_2_coins(gameState) );

  printf("====END TEST SUITE FOR CARD: TRIBUTE====\n\n");
  return 0;
}
