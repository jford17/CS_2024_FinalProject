// class represents a 5-card poker hand dealt from a standard 52-card deck

#include <iostream>
#include "Hand.h"
using std::pair;
using std::map;
using std::string;


// constructor: Returns a vector of 5 Card objects representing a poker hand
Hand::Hand() {
	// allocate memory in field hand for 5 Cards
	hand.reserve(5);
	// create a DeckOfCards and shuffle it
	DeckOfCards deck = DeckOfCards::DeckOfCards();
	deck.shuffle();
	// deal 5 cards
	for (int i = 0; i < 5; i++) {
		hand.emplace(hand.begin() + i, deck.dealCard());
	}
	// initialze faceMap and suitMap
	for (int i = 0; i < 5; i++) {	// iterate through hand
		Card c = hand.at(i);
		// update faceMap value
		faceMap[c.getFaceValue()]++;
		// updateSuitMap
		suitMap[c.getSuit()]++;
	}
}


// constructor for testing
//Hand::Hand(Card one, Card two, Card three, Card four, Card five) {
//	// allocate memory in field hand for 5 Cards
//	hand.reserve(5);
//	// insert Cards into hand
//	hand.emplace(hand.begin(), one);
//	hand.emplace(hand.begin() + 1, two);
//	hand.emplace(hand.begin() + 2, three);
//	hand.emplace(hand.begin() + 3, four);
//	hand.emplace(hand.begin() + 4, five);
//	// initialze faceMap and suitMap
//	for (int i = 0; i < 5; i++) {	// iterate through hand
//		Card c = hand.at(i);
//		// update faceMap value
//		faceMap[c.getFaceValue()]++;
//		// updateSuitMap
//		suitMap[c.getSuit()]++;
//	}
//}


// Returns the best hand or high card if no pair, straight, or flush
string Hand::bestHand() {
	if (this->hasStraightFlush() == true) {
		return "straight flush";
	}
	else if (this->hasFourOfAKind() == true) {
		return "four of a kind";
	}
	else if (this->hasFullHouse() == true) {
		return "full house";
	}
	else if (this->hasFlush() == true) {
		return "flush";
	}
	else if (this->hasStraight() == true) {
		return "straight";
	}
	else if (this->hasThreeOfAKind() == true) {
		return "three of a kind";
	}
	else if (this->hasTwoPair() == true) {
		return "two pair";
	}
	else if (this->hasPair() == true) {
		return "one pair";
	}
	else {
		string highCard = this->getHighCard().toString();
		return "nothing. High card: " + highCard;
	}
}


// Return true if hand contains a pair, else false.
// hasPair() will return true even if pair is part of any better hand
// (e.g. two pair, three of a kind, four of a kind, full house)
bool Hand::hasPair() {
	// if faceMap has any values > 1, return true
	for (unsigned int i = 0; i < faces.size(); i++) {
		if (faceMap.at(faces[i]) > 1) {
			return true;
		}
	}
	return false;
}


// Return true if hand contains two pair, else false.
// hasTwoPair() will return true even if two pair is part of any better hand
// (e.g. three of a kind, four of a kind, full house)
bool Hand::hasTwoPair() {
	int pairs = 0;	// counter for number of pairs in hand
	for (unsigned int i = 0; i < faces.size(); i++) {
		if (faceMap.at(faces[i]) > 1) {
			pairs = pairs + 1;
		}
	}
	if (pairs > 1) {
		return true;
	}
	else {
		return false;
	}
}


// Return true if hand contains three of a kind, else false.
// hasThreeOfAKind() will return true if three of a kind is part of any better hand
// (e.g. four of a kind, full house)
bool Hand::hasThreeOfAKind() {
	// if faceMap has any values > 2, return true
	for (unsigned int i = 0; i < faces.size(); i++) {
		if (faceMap.at(faces[i]) > 2) {
			return true;
		}
	}
	return false;
}


// Return true if hand contains Full House, else false.
bool Hand::hasFullHouse() {
	// if faceMap has any values > 2, check if any other face locations have value > 1
	for (unsigned int i = 0; i < faces.size(); i++) {
		if (faceMap.at(faces[i]) > 2) {		// hasThreeOfAKind == True
			for (unsigned int j = 0; j < faces.size(); j++) {
				// check if (hasPair == True) at any location other than the threeOfAKind
				if ((faceMap.at(faces[j]) > 1) && (i != j)) {
					return true;
				}
			}
		}
	}
	return false;
}


// Return true if hand contains four of a kind
// hasFourOfAKind() will return true if four of a kind is part of any better hand
// (e.g. full house)
bool Hand::hasFourOfAKind() {
	// if faceMap has any values > 3, return true
	for (unsigned int i = 0; i < faces.size(); i++) {
		if (faceMap.at(faces[i]) > 3) {
			return true;
		}
	}
	return false;
}


// Return true if hand contains a flush
// hasFlush() will return true if flush is part of any better hand
// (e.g. straight flush)
bool Hand::hasFlush() {
	// if suitMap has any values > 4, return true
	for (unsigned int i = 0; i < suits.size(); i++) {
		if (suitMap.at(suits[i]) > 4) {
			return true;
		}
	}
	return false;
}


// Return true if hand contains a straight
// hasSraight() will return true if straight is part of any better hand
// (e.g. straight flush)
bool Hand::hasStraight() {
	// return true if faceMap has 5 consecutive elements with values
	int consecutiveFaces = 0;
	for (unsigned int i = 0; i < faces.size(); i++) {
		if (faceMap.at(faces[i]) > 0) {
			consecutiveFaces = consecutiveFaces + 1;
			if (consecutiveFaces > 4) {
				return true;
			}
		}
		else {
			consecutiveFaces = 0;
		}
	}
	return false;
}


// Return true if hand contains a straight flush
bool Hand::hasStraightFlush() {
	bool straight = this->hasStraight();
	bool flush = this->hasFlush();
	if ((straight == true) && (flush== true)) {
		return true;
	}
	else {
		return false;
	}
}


// Return the high Card in the hand (arbitrarily picks suit if two cards have same face value)
Card Hand::getHighCard() {
	// iterate backwards through faces and facemap to find high Card
	int i = faces.size() - 1;
	while (i >= 0) {
		if (faceMap.at(faces[i]) > 0) {
			string highFace = faces[i];
			for (unsigned int j = 0; j < hand.size(); j++) {
				if (hand[j].getFaceValue() == highFace) {
					return hand[j];
				}
			}
		}
		i = i - 1;
	}
	std::cout << "hand is empty. returning default card, two of clubs";
	return Card::Card(0, 0);
}


// return a string representation of the poker Hand instance
string Hand::toString() {
	string pokerHand;
	for (unsigned int i = 0; i < hand.size(); i++) {
		pokerHand = pokerHand + "\n" + "\t" + hand[i].toString();
	}
	return pokerHand;
}