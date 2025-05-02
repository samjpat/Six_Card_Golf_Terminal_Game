#include <getopt.h>
#include <sys/types.h>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>



enum Rank {
  TWO     = 0,
  THREE   = 1,
  FOUR    = 2,
  FIVE    = 3,
  SIX     = 4,
  SEVEN   = 5,
  EIGHT   = 6,
  NINE    = 7,
  TEN     = 8,
  JACK    = 9,
  QUEEN   = 10,
  KING    = 11,
  ACE     = 12,
};

enum Suit {
  SPADES   = 0,
  HEARTS   = 1,
  CLUBS    = 2,
  DIAMONDS = 3,
};
