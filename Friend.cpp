#include "Friend.h"
#include <iostream>

Friend::Friend(string name, string phoneNumber, string address) : Contact(name, phoneNumber)
{
	this->address = address;
}

void Friend::printDetails()
{
	std::cout << name << " " << phoneNumber << " " << address << "\n";
}
