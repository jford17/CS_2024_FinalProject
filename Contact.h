#include <string>

#ifndef  CONTACT_H
#define CONTACT_H

using std::string;

class Contact {
public:
	Contact(string name, string phoneNumber = "",string address = "", string email = "", int id = 0);
	virtual void printDetails();
	string name;
	string phoneNumber;
	string address;
	string email;
	int id;
};

#endif
