// Create alias 'bool' for primitive type 'int' to improve code clarity:
#define bool  int
#define true  1
#define false 0

#include <stdio.h>
#include <string.h>

bool NOISY_TEST = false; // If true, display extra information during execution (normally used for debugging).

bool check_switch_noisyTest(int argc, char *argv[]); // Return true if flag '-n' set.

int main(int argc, char *argv[])
{
  NOISY_TEST = check_switch_noisyTest(argc, argv);
  printf("===BEGIN random tests for card: BARON===\n");
  // INSERT TESTS HERE //
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
