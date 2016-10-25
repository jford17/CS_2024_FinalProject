// enables easy random number generation for poker game

#include "RandomInt.h"
#include <random>


// constructor implementation
RandomInt::RandomInt(int low, int high) {
	// adapted from Walter's post at http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::random_device rd;							// init seed engine
	std::mt19937 rng(rd());							// Mersenne-Twister random-number engine
	std::uniform_int_distribution<int> uni(low, high);
	randInt = uni(rng);

}

// getter implementation
int RandomInt::getRandomInt() {
	return randInt;
}