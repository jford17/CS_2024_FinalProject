#include "sqlite3.h"
#include "Contact.h"
#include <vector>
using std::vector;

class DatabaseHelper {
public:
	DatabaseHelper();
	void addContact(Contact c);
	bool deleteRow(int id);
	vector<Contact*> getContactByName(string name);
	vector<Contact*> getAllContacts();
	static int callback(void *data, int argc, char **argv, char **azColName);
private:
	sqlite3 *db;
	// Helper Functions that should only be called by the class
	vector<Contact*> DBCall(string tempSql);
};