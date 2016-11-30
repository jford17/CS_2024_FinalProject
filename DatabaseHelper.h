#include "sqlite3.h"
#include "Contact.h"
#include <vector>

class DatabaseHelper {
public:
	DatabaseHelper();
	void addContact(Contact c);
	std::vector<Contact*> getContactByName(string name);
	std::vector<Contact*> getContactByPhoneNumber(string phoneNumber);
	std::vector<Contact*> getContactByAddress(string address);
	std::vector<Contact*> getContactByEmail(string email);
	std::vector<Contact*> getContactById(int id);
	std::vector<Contact*>buildSelectQuery(string name="", string phoneNumber="",
										  string address="", string email="", int id=-1);
	std::vector<Contact*> getAllContacts();
	bool deleteRow(int id);
	bool updateRow(int id, string name = "", string phoneNumber = "", string address = "", string email = "");
	static int callback(void *data, int argc, char **argv, char **azColName);

private:
	sqlite3 *db;

	//Helper Functions that should only be called by the class
	std::vector<Contact*> getContactsFromDB(int rc, sqlite3_stmt *stmt);
};