#ifndef POKER_GAMESYSTEM_H_
#define POKER_GAMESYSTEM_H_

#include "cardgen.h"
#include "chipsystem.h"

#include <stdlib.h>
#include <vector>

namespace game_system {
	enum GameState { kDealing, kPreflop, kFlop, kTurn, kRiver, kShowdown };
	
	class PlayerObject {
	private:
		bool is_winner;
	public:
		int hand[2];
		PlayerObject() { this->is_winner = false; }
	};


	class Game {
	private:
		cardgen::Deck game_deck;

		GameState current_round;
		bool override;
		bool round_end; //Used as a flag to call round_end chipsystem: hand rankings, etc.
	public:
		int number_of_players;
		std::vector<PlayerObject*> players;
		int community_cards[5];

		Game() { 
			this->override = false;
			this->round_end = false;
			this->players.reserve(globals::kMaxPlayers); 
		}
		~Game() {
			for (size_t i = 0; i < this->players.size(); i++) {
				if (this->players[i] != nullptr) {
					delete this->players[i];
				}
			}
		}
		//Initialise (or change) game settings through data members
		//Settings include: players, TODO: bet size, buy-in size
		void set_game(int playercount);

		//Initialise, game_deck, players, current_round; then call Round(). TODO: Chip amounts initialised.
		//Called manually by user. TODO: actual interface
		void NewGame();

		//Deals (i.e. displays) cards. TODO: Manage turns mechanism, alter PlayerObject vals on win/loss - NOT RANKING
		//Will be loop through GameStates unless override = true
		void Round();

	};

} //namespace game_system


#endif //POKER_GAMESYSTEM_H_
