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

testResult first_test_returns_success()
{
  noisyprint("First test returns success:\n");
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "First test returns success.", 255);

  struct gameState gameState;

  const int NUM_PLAYERS = 2;
  const int RNG_SEED    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(NUM_PLAYERS, kingdom, RNG_SEED, &gameState);

  return success;
}

testResult game_initializes_to_two_players()
{
  noisyprint("game initializes to two players:\n");
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "game initializes to two players.", 255);

  struct gameState gameState;

  const int num_players = 2;
  const int rng_seed    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(num_players, kingdom, rng_seed, &gameState);

  if(gameState.numPlayers == 2)
    return success;
  else
    return failure;
}

testResult supply_counts_at_10()
{
  noisyprint("Supply counts start at 10:\n");
  memset(testTitle, '\0', 256);
  if(!NOISY_TEST) strncpy(testTitle, "Supply counts start at 10.", 255);

  struct gameState gameState;

  const int num_players = 2;
  const int rng_seed    = 1000;

  int kingdom[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

  initializeGame(num_players, kingdom, rng_seed, &gameState);

  if(gameState.supplyCount[adventurer]   != 10) return failure;
  if(gameState.supplyCount[embargo]      != 10) return failure;
  if(gameState.supplyCount[village]      != 10) return failure;
  if(gameState.supplyCount[minion]       != 10) return failure;
  if(gameState.supplyCount[mine]         != 10) return failure;
  if(gameState.supplyCount[cutpurse]     != 10) return failure;
  if(gameState.supplyCount[sea_hag]      != 10) return failure;
  if(gameState.supplyCount[tribute]      != 10) return failure;
  if(gameState.supplyCount[smithy]       != 10) return failure;
  if(gameState.supplyCount[council_room] != 10) return failure;

  return success;
}

int main(int argc, char *argv[]){
  if (argc > 1 && strcmp(argv[1], "-n") == 0) NOISY_TEST = true;

  printf("\n===BEGIN TEST SUITE FOR CARD: INITIALIZEGAME===\n");
  if(!NOISY_TEST) printf("For noisy test: %s -n\n\n", argv[0]);

  assert_true( first_test_returns_success() );
  assert_true( game_initializes_to_two_players() );
  assert_true( supply_counts_at_10() );

  printf("====END TEST SUITE FOR CARD: INITIALIZEGAME====\n\n");
  return 0;
}
