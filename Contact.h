#include <string>

#ifndef  CONTACT_H
#define CONTACT_H

using std::string;

class Contact {
public:
	Contact(string name, string phoneNumber);
	Contact(string name, string phoneNumber, int id);
	virtual void printDetails();
	string name;
	string phoneNumber;
	int id;
};

#endif
