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

testResult ties_marked_correctly(struct gameState gameState)
{
  noisyprint("Ties marked correctly:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Ties marked correctly.", 255);

  int players[2] = {0};
  for(int i = 0; i < 2; i++)
    noisyprint("\tplayer[%d] = %d\n", i, players[i]);

  getWinners(players, &testState);

  for(int i = 0; i < 2; i++)
    noisyprint("\tplayer[%d] = %d\n", i, players[i]);

  if(players[0] == players[1])
    return success;
  else
    return failure;
}

testResult winner_marked_correctly(struct gameState gameState)
{
  noisyprint("Winner marked correctly:\n");
  struct gameState testState;
  memcpy(&testState, &gameState, sizeof(struct gameState));
  memset(testTitle, '\0', 256);

  testState.deck[1][0] = province;
  if(!NOISY_TEST) strncpy(testTitle, "Winner marked correctly.", 255);

  int players[2] = {0};
  for(int i = 0; i < 2; i++)
    noisyprint("\tplayer[%d] = %d\n", i, players[i]);

  getWinners(players, &testState);

  for(int i = 0; i < 2; i++)
    noisyprint("\tplayer[%d] = %d\n", i, players[i]);

  if(players[1] == 1 && players[0] == 0)
    return success;
  else
    return failure;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR FUNCTION: GETWINNERS===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);

  assert_true( first_test_returns_success(gameState) );
  assert_true( ties_marked_correctly(gameState) );
  assert_true( winner_marked_correctly(gameState) );

  printf("====END TEST SUITE FOR FUNCTION: GETWINNERS====\n\n");
  return 0;
}
