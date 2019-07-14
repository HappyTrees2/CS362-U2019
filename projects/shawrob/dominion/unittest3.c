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

testResult ambassador_mode_1_removes_1_card_from_hand(struct gameState gameState)
{
  noisyprint("Playing Ambassador returning 1 card removes 1 from player's hand:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Ambassador returning 1 card removes 1 from player's hand.", 255);

  int copperBefore = 0;
  int copperAfter  = 0;

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == copper) ++copperBefore;
  noisyprint("\tcopperBefore = %d\n", copperBefore);

  playCard(0, 1, 0, 1, &testState);

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == copper) ++copperAfter;
  noisyprint("\tcopperAfter = %d\n", copperAfter);

  if(copperAfter == copperBefore - 1)
    return success;
  else
    return failure;
}

testResult ambassador_mode_2_removes_2_cards_from_hand(struct gameState gameState)
{
  noisyprint("Playing Ambassador returning 2 cards removes 2 cards from player's hand:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Ambassador returning 2 cards removes 2 cards from player's hand.", 255);

  int copperBefore = 0;
  int copperAfter  = 0;

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == copper) ++copperBefore;
  noisyprint("\tcopperBefore = %d\n", copperBefore);

  playCard(0, 2, 0, 1, &testState);

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == copper) ++copperAfter;
  noisyprint("\tcopperAfter = %d\n", copperAfter);

  if(copperAfter == copperBefore - 1)
    return success;
  else
    return failure;
}

testResult ambassador_mode_1_adds_1_card_to_supply(struct gameState gameState)
{
  noisyprint("Playing Ambassador returning 1 card adds 1 to supply:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Ambassador returning 1 card adds 1 to supply.", 255);

  int supplyBefore = 0;
  int supplyAfter  = 0;

  supplyBefore = testState.supplyCount[copper];
  noisyprint("\tsupplyBefore = %d\n", supplyBefore);

  playCard(0, 1, 0, 1, &testState);

  supplyAfter = testState.supplyCount[copper];
  noisyprint("\tsupplyAfter = %d\n", supplyAfter);

  if(supplyAfter == supplyBefore)
    return success;
  else
    return failure;
}

testResult ambassador_mode_2_adds_2_cards_to_supply(struct gameState gameState)
{
  noisyprint("Playing Ambassador returning 2 cards adds 2 to supply:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Ambassador returning 2 cards adds 2 to supply.", 255);

  int supplyBefore = 0;
  int supplyAfter  = 0;

  supplyBefore = testState.supplyCount[copper];
  noisyprint("\tsupplyBefore = %d\n", supplyBefore);

  playCard(0, 2, 0, 1, &testState);

  supplyAfter = testState.supplyCount[copper];
  noisyprint("\tsupplyAfter = %d\n", supplyAfter);

  if(supplyAfter == supplyBefore + 1)
    return success;
  else
    return failure;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR CARD: AMBASSADOR===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);
  gameState.hand[0][0] = ambassador;

  assert_true( first_test_returns_success(gameState) );
  assert_true( ambassador_mode_1_removes_1_card_from_hand(gameState) );
  assert_true( ambassador_mode_2_removes_2_cards_from_hand(gameState) );
  assert_true( ambassador_mode_1_adds_1_card_to_supply(gameState) );
  assert_true( ambassador_mode_2_adds_2_cards_to_supply(gameState) );

  printf("====END TEST SUITE FOR CARD: AMBASSADOR====\n\n");
  return 0;
}
