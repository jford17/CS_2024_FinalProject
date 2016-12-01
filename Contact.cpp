#include "Contact.h"
#include <iostream>

Contact::Contact(string name, string phoneNumber)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
}
Contact::Contact(string name, string phoneNumber, int id)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->id = id;
}

void Contact::printDetails()
{
	std::cout << "id: " << id << "\tname: " << name << "\tphone: " << phoneNumber << "\n";
}
