#include "Contact.h"
#include <iostream>

Contact::Contact(string name, string phoneNumber)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
}

void Contact::printDetails()
{
	std::cout << name << " " << phoneNumber << "\n";
}
