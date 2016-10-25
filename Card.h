// Deitel & Detiel 9th ed. 9.23
// class represents a playing card from a standard 52-card deck


#include <string>
#include <array>
using namespace std;
using std::string;


class Card {

public: 
	// default constructor: returns Card object representing a single playing card in a standard 52-card deck
	// default card is two of clubs
	Card();

	// default constructor: returns Card object representing a single playing card in a standard 52-card deck
	// Card(int f, int s)
	// f must be an int with range [0,12]
	// s must be an int with range [0,3]
	Card(int, int);

	// returns the string representation of a class type Card object, e.g. "two of clubs"
	string toString();

	// returns string representation of Card's face value
	string getFaceValue();

	// returns string representation of Card's suit
	string getSuit();

private:
	
	// index of face value of Card
	int face;
	
	// index of suit of Card
	int suit;
	
	// array containing the 13 possible face values of a playing card in a standard 52-card deck
	array<string, 13> faces{ "two", "three", "four", "five", "six", "seven",
		"eight", "nine", "ten", "jack", "queen", "king", "ace" };

	// array containing the 4 possible suits of a playing card in a standard 52-card deck
	array<string, 4> suits{ "clubs", "diamonds", "hearts", "spades" };

};