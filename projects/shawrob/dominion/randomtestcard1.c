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

int main(int argc, char *argv[])
{
  NOISY_TEST = check_switch_noisyTest(argc, argv);
  printf("===BEGIN random tests for card: BARON===\n");
  struct gameState G;
  int n = 0;
  for (n = 0; n < 2000; n++)
  {
    int i = 0;
    int p = 0;
    for (i = 0; i < sizeof(struct gameState); i++)
      ((char*)&G)[i] = floor(Random() * 256);
    p = floor(Random() * 2);
    int c1 = floor(Random() * 2);

    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    execute_baron(&G, c1, p);
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
