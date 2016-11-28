#include "Contact.h"
#include <string.h>

#ifndef  FRIEND_H
#define FRIEND_H

class Friend : public Contact {
public:
	Friend(string name, string phoneNumber, string address);
	void printDetails();
	string address;
};

#endif