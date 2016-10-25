// Deitel & Deitel 9th ed. 9.24
// class Deck represents a standard 52-card deck of playing cards (will shrink when cards are dealt)


#include "DeckOfCards.h"
#include <iostream>


// constructor: returns a class type DeckOfCards object
// initial deck is unshuffled
DeckOfCards::DeckOfCards() {
	for (int suit = 0; suit < 4; suit++) {
		for (int face = 0; face < 13; face++) {
			deck.emplace_back(Card(face, suit));
		}
	}
}

// shuffles the DeckOfCards
void DeckOfCards::shuffle() {
	// iterate through deck
	for (unsigned int i = 0; i < deck.size(); i++) {
		// choose random card to swap positions with
		int randIndex = RandomInt::RandomInt(0, deck.size() - 1).getRandomInt();
		// swap cards
		Card temp = deck.at(randIndex);
		deck[randIndex] = deck[i];
		deck[i] = temp;
	}
}

// returns the next class type Card object to be dealt
Card DeckOfCards::dealCard() {
	Card topOfDeck = deck[0];
	deck.pop_front();
	return topOfDeck;
}

// returns a boolean indicating if there a more Cards to be dealt
bool DeckOfCards::moreCards() {
	if (deck.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}