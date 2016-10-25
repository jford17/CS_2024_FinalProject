// Deitel & Deitel 9th ed. 9.24
// class Deck represents a standard 52-card deck of playing cards (will shrink when cards are dealt)


#include "RandomInt.h"
#include "Card.h"
#include <deque>


class DeckOfCards {

public:
	
	// constructor: returns a vector of class type Card objects
	DeckOfCards();

	// shuffles the DeckOfCards
	void shuffle();

	// returns the next class type Card object to be dealt
	Card dealCard();

	// returns a boolean indicating if there a more Cards to be dealt
	bool moreCards();

private:

	// stores the DeckOfCards
	std::deque<Card> deck;

	// the next Card to deal
	int currentCard;

};