#include "sqlite3.h"
#include "Contact.h"
#include <vector>

class DatabaseHelper {
public:
	DatabaseHelper();
	void addContact(Contact c);
	std::vector<Contact*> getContactByName(string name);
	std::vector<Contact*> getAllContacts();
	bool deleteRow(int id);
	static int callback(void *data, int argc, char **argv, char **azColName);

private:
	sqlite3 *db;

	//Helper Functions that should only be called by the class
	std::vector<Contact*> DBCall(string tempSql);
};