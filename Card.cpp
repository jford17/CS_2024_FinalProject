// Deitel & Detiel 9th ed. 9.23
// class represents a playing card from a standard 52-card deck


#include "DeckOfCards.h"
using std::string;


// Default Constructor: returns Card object representing a single playing card in a standard 52-card deck
// default card is two of clubs
Card::Card() {
	face = 0;
	suit = 0;
}

// constructor: Card(int f, int s)
// returns Card object representing a single playing card in a standard 52-card deck
// f must be an int with range [0,12]
// s must be an int with range [0,3]
Card::Card(int f, int s) {
	face = f;
	suit = s;
}

// returns the string representation of a class type Card object, e.g. "two of clubs"
string Card::toString() {
	return Card::faces[face] + " of " + Card::suits[suit];
}

// returns string representation of Card's face value
string Card::getFaceValue() {
	return Card::faces[face];
}

// returns string representation of Card's suit
string Card::getSuit() {
	return Card::suits[suit];
}