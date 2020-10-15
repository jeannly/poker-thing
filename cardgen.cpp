#include "cardgen.h"

#include <stdlib.h>
#include <time.h>

namespace cardgen{
Deck::Deck() {
	for (int i = 0; i < globals::kDeckSize; i++) {
		this->cards[i] = i;
	}
}

void Deck::Shuffle() {
	srand((unsigned int)time(NULL));

	int temp = 0;
	for (int i = 0; i < globals::kDeckSize; i++) {
		//random number between current and final index
		int rand_index = ((rand() + i) % (globals::kDeckSize - 1));

		//swap cards[i] with random card cards[randIndex]
		temp = this->cards[i];
		this->cards[i] = this->cards[rand_index];
		this->cards[rand_index] = temp;
	}
}
} //namespace cardgen
