#define MAX_TEST_ITERATIONS 500

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main()
{
  printf("===BEGIN random tests for card: MINION===\n");
  int currentTest = 0;
  for(currentTest = 0; currentTest < MAX_TEST_ITERATIONS; currentTest++)
  {
    printf("ITERATION %d\n", currentTest);
    struct gameState pre, post;
    int currentByte = 0;
    for(currentByte = 0; currentByte < sizeof(struct gameState); currentByte++)
      ((char*)&post)[currentByte] = floor(Random() * 256);

    post.numPlayers = floor(Random() * 3) + 2;
    int player = floor(Random() * post.numPlayers) + 1;
    post.numActions = floor(Random() * 999);
    post.whoseTurn  = player;
    post.numActions = floor(Random() * 999);
    post.coins = floor(Random() * 999);
    post.numBuys = floor(Random() * 999);

    int currentPlayer = 1;
    for(currentPlayer = 1; currentPlayer < post.numPlayers + 1; currentPlayer++)
    {
      int currentHandCard = 0;
      post.handCount[player] = 0;
      for (currentHandCard = 0; currentHandCard < MAX_HAND; currentHandCard++)
      {
        post.hand[currentPlayer][currentHandCard] = floor(Random() * treasure_map);
        ++post.handCount[currentPlayer];
        if(floor(Random() * 4) == 1) break;
      }
      post.hand[currentPlayer][0] = minion;
    }

    for(currentPlayer = 1; currentPlayer < post.numPlayers + 1; currentPlayer++)
    {
      int currentDeckCard = 0;
      post.deckCount[currentPlayer] = 0;
      for (currentDeckCard = 0; currentDeckCard < MAX_DECK; currentDeckCard++)
      {
        post.deck[currentPlayer][currentDeckCard] = floor(Random() * treasure_map);
        ++post.deckCount[currentPlayer];
        if(floor(Random() * 4) == 1) break;
      }
    }

    for(currentPlayer = 1; currentPlayer < post.numPlayers + 1; currentPlayer++)
    {
      int currentDiscardCard = 0;
      post.discardCount[currentPlayer] = 0;
      for (currentDiscardCard = 0; currentDiscardCard < MAX_DECK; currentDiscardCard++)
      {
        post.discard[currentPlayer][currentDiscardCard] = floor(Random() * treasure_map);
        ++post.discardCount[currentPlayer];
        if(floor(Random() * 4) == 1) break;
      }
    }
    int choice = floor(Random() * 2);
    post.playedCardCount = 0;

    memcpy(&pre, &post, sizeof(struct gameState));
    execute_minion(&pre, choice, 0, 0, player);
  }
  printf("===  END random tests for card: MINION===\n");
  return 0;
}
