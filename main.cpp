// Jonathan Ford	jwf222
// CS 2024 Assignment 5 Due 10/1/2016
// Deitel and Deitel 9th ed. 9.23 and 9.24
// create a family of classes that simulates a deck of cards and randomly dealt poker hand
// The part of my solution that was probably relatively unique was my
// data structure implementation. I created private fields faceMap and suitMap
// in class hand to map out the value of my hand. Once I figured out how to implement
// these data structures, implementing the methods was very straightforward.
// This assignment taught me about C++ data structures and more about the interaction
// between .h and .cpp files and the linker and compiler.


#include "Hand.h"
#include <iostream>
using std::cout;
using std::cin;


int main() {

	cout << "Welcome to my poker program!";
	cout << "\n";

	cout << "Here is quick demo to show off some of its functionality.";
	cout << "\n";
	cout << "\n";

	cout << "Press enter to see a random hand from the dealer.";
	cin.get();

	char run = 'y';
	while (run == 'y') {
		cout << "\n";
		cout << "Here are the cards in your hand:";
		cout << "\n";

		Hand h = Hand::Hand();
		cout << h.toString();

		cout << "\n";
		cout << "\n";

		cout << "Your hand has " << h.bestHand() << ".";
		cout << "\n";
		cout << "\n";
		
		cout << "Enter 'y' to see another hand. Enter 'n' to exit. ";
		cin >> run;
	}

	// for testing:
	//Hand h = Hand::Hand();
	//cout << h.toString();
	//cout << "\n";
	//cout << h.getHighCard().toString();
	//cin.get();
	/*Card twoOfClubs = Card::Card(0, 0);
	Card twoOfDiamonds = Card::Card(0, 1);
	Card twoOfHearts = Card::Card(0, 2);
	Card twoOfSpades = Card::Card(0, 3);
	Card threeOfClubs = Card::Card(1, 0);
	Card threeOfDiamonds = Card::Card(1, 1);
	Card fourOfDiamonds = Card::Card(2, 1);
	Card fiveOfDiamonds = Card::Card(3, 1);
	Card sixOfDiamonds = Card::Card(4, 1);
	Card sevenOfDiamonds = Card::Card(5, 1);
	Card sevenOfSpades = Card::Card(5, 3);
	Hand noPair = Hand::Hand(twoOfClubs, threeOfClubs, fourOfDiamonds, fiveOfDiamonds, sevenOfSpades);
	Hand onePair = Hand::Hand(twoOfClubs, twoOfDiamonds, threeOfClubs, fiveOfDiamonds, fourOfDiamonds);
	Hand twoPair = Hand::Hand(twoOfClubs, twoOfDiamonds, threeOfClubs, threeOfDiamonds, fourOfDiamonds);
	Hand threeOfAKind = Hand::Hand(twoOfClubs, twoOfDiamonds, twoOfSpades, threeOfDiamonds, fourOfDiamonds);
	Hand fullHouse = Hand::Hand(twoOfClubs, twoOfDiamonds, twoOfSpades, threeOfDiamonds, threeOfClubs);
	Hand fourOfAKind = Hand::Hand(twoOfClubs, twoOfDiamonds, twoOfSpades, twoOfHearts, threeOfClubs);
	Hand straight = Hand::Hand(twoOfClubs, threeOfClubs, fourOfDiamonds, fiveOfDiamonds, sixOfDiamonds);
	Hand flush = Hand::Hand(twoOfDiamonds, threeOfDiamonds, fourOfDiamonds, fiveOfDiamonds, sevenOfDiamonds);
	Hand straightFlush = Hand::Hand(twoOfDiamonds, threeOfDiamonds, fourOfDiamonds, fiveOfDiamonds, sixOfDiamonds);

	cout << "hand noPair.hasPair() = " << std::boolalpha << noPair.hasPair();
	cout << "\n";
	cout << "hand noPair.hasTwoPair() = " << std::boolalpha << noPair.hasTwoPair();
	cout << "\n";
	cout << "hand noPair.hasThreeOfAKind() = " << std::boolalpha << noPair.hasThreeOfAKind();
	cout << "\n";
	cout << "hand noPair.hasFullHouse() = " << std::boolalpha << noPair.hasFullHouse();
	cout << "\n";
	cout << "hand noPair.hasFourOfAKind() = " << std::boolalpha << noPair.hasFourOfAKind();
	cout << "\n";
	cout << "hand noPair.hasStraight() = " << std::boolalpha << noPair.hasStraight();
	cout << "\n";
	cout << "hand noPair.hasFlush() = " << std::boolalpha << noPair.hasFlush();
	cout << "\n";
	cout << "hand noPair.hasStraightFlush() = " << std::boolalpha << noPair.hasStraightFlush();
	cout << "\n";


	cout << "\n";
	cout << "hand onePair.hasPair() = " << std::boolalpha << onePair.hasPair();
	cout << "\n";
	cout << "hand onePair.hasTwoPair() = " << std::boolalpha << onePair.hasTwoPair();
	cout << "\n";
	cout << "hand onePair.hasThreeOfAKind() = " << std::boolalpha << onePair.hasThreeOfAKind();
	cout << "\n";
	cout << "hand onePair.hasFullHouse() = " << std::boolalpha << onePair.hasFullHouse();
	cout << "\n";
	cout << "hand onePair.hasFourOfAKind() = " << std::boolalpha << onePair.hasFourOfAKind();
	cout << "\n";
	cout << "hand onePair.hasStraight() = " << std::boolalpha << onePair.hasStraight();
	cout << "\n";
	cout << "hand onePair.hasFlush() = " << std::boolalpha << onePair.hasFlush();
	cout << "\n";
	cout << "hand onePair.hasStraightFlush() = " << std::boolalpha << onePair.hasStraightFlush();
	cout << "\n";


	cout << "\n";
	cout << "hand twoPair.hasPair() = " << std::boolalpha << twoPair.hasPair();
	cout << "\n";
	cout << "hand twoPair.hasTwoPair() = " << std::boolalpha << twoPair.hasTwoPair();
	cout << "\n";
	cout << "hand twoPair.hasThreeOfAKind() = " << std::boolalpha << twoPair.hasThreeOfAKind();
	cout << "\n";
	cout << "hand twoPair.hasFullHouse() = " << std::boolalpha << twoPair.hasFullHouse();
	cout << "\n";
	cout << "hand twoPair.hasFourOfAKind() = " << std::boolalpha << twoPair.hasFourOfAKind();
	cout << "\n";


	cout << "\n";
	cout << "hand threeOfAKind.hasPair() = " << std::boolalpha << threeOfAKind.hasPair();
	cout << "\n";
	cout << "hand threeOfAKind.hasTwoPair() = " << std::boolalpha << threeOfAKind.hasTwoPair();
	cout << "\n";
	cout << "hand threeOfAKind.hasThreeOfAKind() = " << std::boolalpha << threeOfAKind.hasThreeOfAKind();
	cout << "\n";
	cout << "hand threeOfAKind.hasFullHouse() = " << std::boolalpha << threeOfAKind.hasFullHouse();
	cout << "\n";
	cout << "hand threeOfAKind.hasFourOfAKind() = " << std::boolalpha << threeOfAKind.hasFourOfAKind();
	cout << "\n";


	cout << "\n";
	cout << "hand fullHouse.hasPair() = " << std::boolalpha << fullHouse.hasPair();
	cout << "\n";
	cout << "hand fullHouse.hasTwoPair() = " << std::boolalpha << fullHouse.hasTwoPair();
	cout << "\n";
	cout << "hand fullHouse.hasThreeOfAKind() = " << std::boolalpha << fullHouse.hasThreeOfAKind();
	cout << "\n";
	cout << "hand fullHouse.hasFullHouse() = " << std::boolalpha << fullHouse.hasFullHouse();
	cout << "\n";
	cout << "hand fullHouse.hasFourOfAKind() = " << std::boolalpha << fullHouse.hasFourOfAKind();
	cout << "\n";


	cout << "\n";
	cout << "hand fourOfAKind.hasPair() = " << std::boolalpha << fourOfAKind.hasPair();
	cout << "\n";
	cout << "hand fourOfAKind.hasTwoPair() = " << std::boolalpha << fourOfAKind.hasTwoPair();
	cout << "\n";
	cout << "hand fourOfAKind.hasThreeOfAKind() = " << std::boolalpha << fourOfAKind.hasThreeOfAKind();
	cout << "\n";
	cout << "hand fourOfAKind.hasFullHouse() = " << std::boolalpha << fourOfAKind.hasFullHouse();
	cout << "\n";
	cout << "hand fourOfAKind.hasFourOfAKind() = " << std::boolalpha << fourOfAKind.hasFourOfAKind();
	cout << "\n";


	cout << "\n";
	cout << "hand flush.hasPair() = " << std::boolalpha << flush.hasPair();
	cout << "\n";
	cout << "hand flush.hasFlush() = " << std::boolalpha << flush.hasFlush();
	cout << "\n";
	cout << "hand flush.hasStraight() = " << std::boolalpha << flush.hasStraight();
	cout << "\n";
	cout << "hand flush.hasStraightFlush() = " << std::boolalpha << flush.hasStraightFlush();
	cout << "\n";



	cout << "\n";
	cout << "hand straight.hasTwoPair() = " << std::boolalpha << straight.hasTwoPair();
	cout << "\n";
	cout << "hand straight.hasFlush() = " << std::boolalpha << straight.hasFlush();
	cout << "\n";
	cout << "hand straight.hasStraight() = " << std::boolalpha << straight.hasStraight();
	cout << "\n";
	cout << "hand straight.hasStraightFlush() = " << std::boolalpha << straight.hasStraightFlush();
	cout << "\n";
	

	cout << "\n";
	cout << "hand straightFlush.hasFullHouse() = " << std::boolalpha << straightFlush.hasFullHouse();
	cout << "\n";
	cout << "hand straightFlush.hasFlush() = " << std::boolalpha << straightFlush.hasFlush();
	cout << "\n";
	cout << "hand straightFlush.hasStraight() = " << std::boolalpha << straightFlush.hasStraight();
	cout << "\n";
	cout << "hand straightFlush.hasStraightFlush() = " << std::boolalpha << straightFlush.hasStraightFlush();
	cout << "\n";

	cin.get();*/
}