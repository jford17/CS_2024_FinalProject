#include "Contact.h"
#include <iostream>

Contact::Contact(string name, string phoneNumber, string address, string email, int id)
{
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->address = address;
	this->email = email;
	this->id = id;
}


void Contact::printDetails()
{
	std::cout << "Database id: " << id << ", Name: " << name;
	if (phoneNumber != "")
		std::cout << ", Phone Number: " << phoneNumber;
	if (address != "")
		std::cout << ", Address: " << address;
	if (email != "")
		std::cout << ", Email: " << email;
	std::cout << std::endl;

}
