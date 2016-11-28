#include "sqlite3.h"
#include "Contact.h"
#include <vector>

class DatabaseHelper {
public:
	DatabaseHelper();
	void addContact(Contact c);
	std::vector<Contact*> getContactByName(string name);
private:
	sqlite3 *db;
};