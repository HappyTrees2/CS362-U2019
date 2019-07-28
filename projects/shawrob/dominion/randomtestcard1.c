#define bool  int
#define true  1
#define false 0

#include <stdio.h>
#include <string.h>

bool NOISY_TEST = false;

bool check_switch_noisyTest(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  NOISY_TEST = check_switch_noisyTest(argc, argv);
  printf("===BEGIN random tests for card: BARON===\n");
  printf("===END   random tests for card: BARON===\n");
  return 0;
}

bool check_switch_noisyTest(int argc, char *argv[])
{
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
