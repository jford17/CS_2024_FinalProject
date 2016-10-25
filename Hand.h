// class represents a 5-card poker hand dealt from a standard 52-card deck


#include "DeckOfCards.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <array>
using namespace std;
using std::pair;
using std::map;
using std::string;


class Hand {

public:
	
	// constructor: Returns a vector of 5 Card objects representing a poker hand
	Hand();

	// constructor for testing
	// Hand(Card, Card, Card, Card, Card);

	// Returns the best hand or high card if no pair, straight, or flush
	string bestHand();

	// Return true if hand contains a pair, else false.
	// hasPair() will return true even if one pair is part of any better hand
	// (e.g. two pair, three of a kind, four of a kind, full house)
	bool hasPair();

	// Return true if hand contains two pair, else false.
	// hasTwoPair() will return true even if two pair is part of any better hand
	// (e.g. three of a kind, four of a kind, full house)
	bool hasTwoPair();

	// Return true if hand contains three of a kind, else false.
	// hasThreeOfAKind() will return true if three of a kind is part of any better hand
	// (e.g. four of a kind, full house)
	bool hasThreeOfAKind();

	// Return true if hand contains Full House, else false.
	bool hasFullHouse();

	// Return true if hand contains four of a kind
	// hasFourOfAKind() will return true if four of a kind is part of any better hand
	// (e.g. full house)
	bool hasFourOfAKind();

	// Return true if hand contains a flush
	// hasFlush() will return true if flush is part of any better hand
	// (e.g. straight flush)
	bool hasFlush();

	// Return true if hand contains a straight
	// hasSraight() will return true if straight is part of any better hand
	// (e.g. straight flush)
	bool hasStraight();

	// Return true if hand contains a straight flush
	bool hasStraightFlush();

	// Return high Card in hand (arbitrarily picks suit if two cards have same face value)
	Card getHighCard();

	// return a string representation of the poker Hand instance
	string toString();

//private:

	// field. stores the 5-card poker hand
	std::vector<Card> hand;

	// field. key value pair representing face values of Cards in hand
	map<string, int> faceMap = { {"two", 0}, { "three", 0 }, { "four", 0 }, 
		{ "five", 0 }, { "six", 0 }, { "seven", 0 }, { "eight", 0 }, 
		{ "nine", 0 }, { "ten", 0 }, { "jack", 0 }, { "queen", 0 }, 
		{ "king", 0 }, { "ace", 0 } };
	
	// field. key value pair representing suits of Cards in hand
	map<string, int> suitMap = { { "clubs", 0 }, { "diamonds", 0 },
		{ "hearts", 0 }, { "spades", 0} };

	// field. array containing the 13 possible face values of a playing card in a standard 52-card deck
	array<string, 13> faces { "two", "three", "four", "five", "six", "seven", 
		"eight", "nine", "ten", "jack", "queen", "king", "ace" };

	// field. array containing the 4 possible suits of a playing card in a standard 52-card deck
	array<string, 4> suits { "clubs", "diamonds", "hearts", "spades" };

};