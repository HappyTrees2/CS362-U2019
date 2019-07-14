#include "dominion_helpers.h"   // "dominion.h" is included within this header.
#include <stdio.h>              // printf
#include <string.h>             // memcpy

#define testResult int
#define success 1
#define failure 0

#define NOISY_TEST 1
#define noisyprint if(NOISY_TEST) printf

char testTitle[256];

void assert_true(testResult result)
{
  if (result == success)
    printf("+ PASS\t%s\n", testTitle);
  else
    printf("- FAIL\t%s\n", testTitle);
}

testResult playing_baron_removes_it_from_players_hand(struct gameState gameState)
{
  noisyprint("Playing Baron removes it from player's hand:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Baron removes it from player's hand.", 255);

  int baronsInHandBefore = 0;
  int baronsInHandAfter  = 0;

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == baron) ++baronsInHandBefore;
  noisyprint("\tbaronsInHandBefore = %d\n", baronsInHandBefore);

  playCard(0, 0, 0, 0, &testState);

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == baron) ++baronsInHandAfter;
  noisyprint("\tbaronsInHandAfter  = %d\n", baronsInHandAfter);

  if(baronsInHandAfter == baronsInHandBefore - 1)
    return success;
  else
    return failure;
}

testResult playing_baron_adds_one_buy(struct gameState gameState)
{
  noisyprint("Playing Baron adds +1 buy:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Playing Baron adds +1 buy.", 255);

  int buysBefore = 0;
  int buysAfter  = 0;

  buysBefore = testState.numBuys;
  noisyprint("\tBuys before = %d\n", buysBefore);

  playCard(0, 0, 0, 0, &testState);

  buysAfter = testState.numBuys;
  noisyprint("\tBuys after  = %d\n", buysAfter);

  if(buysAfter == buysBefore + 1)
    return success;
  else
    return failure;
}

testResult discarding_a_valid_estate_removes_one_from_hand(struct gameState gameState)
{
  noisyprint("Discarding a valid estate removes one from hand:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Discarding a valid estate removes one from hand.", 255);

  int estatesBefore = 0;
  int estatesAfter  = 0;

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == estate) ++estatesBefore;
  noisyprint("\testatesBefore = %d\n", estatesBefore);

  playCard(0, 1, 0, 0, &testState);

  for(int i = 0; i < testState.handCount[0]; i++)
    if(testState.hand[0][i] == estate) ++estatesAfter;
  noisyprint("\testatesAfter  = %d\n", estatesAfter);

  if(estatesAfter == estatesBefore - 1)
    return success;
  else
    return failure;
}

int main(){
  printf("\n===BEGIN TEST SUITE FOR CARD: BARON===\n");

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);
  gameState.hand[0][0] = baron;

  assert_true( playing_baron_removes_it_from_players_hand(gameState) );
  assert_true( playing_baron_adds_one_buy(gameState) );
  assert_true( discarding_a_valid_estate_removes_one_from_hand(gameState) );
  // Discarding an Estate (with one in hand) gives +4 coins.
  // Discarding an Estate (without one in hand) gains an Estate.
  // Choosing not to discard an Estate gains an Estate.
  // Gaining an Estate reduces supply by 1.
  // Returning an Estate increases supply by 1.

  printf("====END TEST SUITE FOR CARD: BARON====\n\n");
  return 0;
}
