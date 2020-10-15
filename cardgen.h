#ifndef POKER_CARDGEN_H_
#define POKER_CARDGEN_H_

#include <stdlib.h>

//Defined only in cardgen.cpp
namespace globals {
	constexpr int kDeckSize = 52;
	constexpr int kMaxPlayers = 6;
}

namespace cardgen {
class Deck {
public:
	int cards[globals::kDeckSize];

	//Initialise 'cards' array, sequential 1 to 52
	Deck();
	//Use Knuth Fisher-Yates algorithm to shuffle 'cards' array
	void Shuffle();
};
} //namespace cardgen
#endif //POKER_CARDGEN_H_