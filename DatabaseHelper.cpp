/* Lots of help from code found here: https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
 * 	as well as here: https://www.sqlite.org/cintro.html*/
#include "DatabaseHelper.h"
#include "sqlite3.h"
#include <iostream>
#include <string.h>
#include <vector>
#include "Friend.h"

using namespace std;

DatabaseHelper::DatabaseHelper()
{
	int rc;

	rc = sqlite3_open("address_book.db", &db);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}

	char *err_msg = 0;
	// create table if it doesn't already exist
	char* sql = "CREATE TABLE IF NOT EXISTS contacts "
			"(rowid INTEGER PRIMARY KEY ASC,"
			"name TEXT NOT NULL, "
			"phone_number TEXT, "
			"address TEXT, "
			"email TEXT,"
			"CONSTRAINT row_unique UNIQUE(name, phone_number, address, email));";
//	char* sql = "DROP TABLE contacts";

	// create table
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) { // if creation failed, send error

		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
}

/* Function Used to add contact with whatever fields are filled out.
 * MUST HAVE NAME. EVERYTHING ELSE IS OPTIONAL.
 * Whole row is unique, so items like this:
 * 		Database id: 1, Name: John, Phone Number: 123-456-7890
 * 		Database id: 2, Name: John, Phone Number: 123-456-7890, Address: John@John.com
 * is allowed, but this:
 * 		Database id: 1, Name: John, Phone Number: 123-456-7890
 * 		Database id: 2, Name: John, Phone Number: 123-456-7890
 * is not. Up to the user to decide if they want to add a contact or update an existing one
 * */
void DatabaseHelper::addContact(Contact c)
{
	sqlite3_stmt * stmt;
	char *err_msg = 0;
	// initial sql string with ? instead of values for binding (to prevent sql injections)
	string tempSql = "INSERT INTO contacts (name, phone_number, address, email) VALUES(?,?,?,?);";
	const char* sql = tempSql.c_str();
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		// make a prepared statement and do all bindings
		sqlite3_prepare( db, sql, -1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, c.name.c_str(), int(c.name.length()), SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 2, c.phoneNumber.c_str(), int(c.phoneNumber.length()), SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 3, c.address.c_str(), int(c.address.length()), SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 4, c.email.c_str(), int(c.email.length()), SQLITE_TRANSIENT);
		sqlite3_step( stmt ); // add to database
		rc = sqlite3_finalize(stmt); // clear statment

		if (rc == SQLITE_CONSTRAINT)
			cerr << "Row not unique, not added to database" << endl;

	}
	else
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
	}

	sqlite3_close(db);
}

/* Used to retrieve contacts by name */
vector<Contact*> DatabaseHelper::getContactByName(string name) {
	string tempSql = "SELECT * FROM contacts WHERE name=?;";
	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	int rc = sqlite3_open("address_book.db", &db);
	sqlite3_stmt *stmt;
	if (rc == SQLITE_OK) {
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (name != "")
			rc = sqlite3_bind_text(stmt, 1, name.c_str(), int(name.length()), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);
		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	}
	vector<Contact*> contacts;
	sqlite3_close(db);
	return contacts;
}

/* Used to retrieve contacts by phoneNumber */
vector<Contact*> DatabaseHelper::getContactByPhoneNumber(string phoneNumber) {
	string tempSql = "SELECT * FROM contacts WHERE phone_number = ?;";

	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (phoneNumber != "")
			rc = sqlite3_bind_text(stmt, 1, phoneNumber.c_str(), int(phoneNumber.length()), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);
		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	}
	vector<Contact*> contacts;
	sqlite3_close(db);
	return contacts;
}

/* Used to retrieve contacts by address */
vector<Contact*> DatabaseHelper::getContactByAddress(string address) {
	string tempSql = "SELECT * FROM contacts WHERE address=?;";
	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (address != "")
			rc = sqlite3_bind_text(stmt, 1, address.c_str(), int(address.length()), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);
		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	}
	vector<Contact*> contacts;
	sqlite3_close(db);
	return contacts;
}

/* Used to retrieve contacts by email */
vector<Contact*> DatabaseHelper::getContactByEmail(string email) {
	string tempSql = "SELECT * FROM contacts WHERE email=?;";
	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (email != "")
			rc = sqlite3_bind_text(stmt, 1, email.c_str(), int(email.length()), SQLITE_TRANSIENT);
		rc = sqlite3_step(stmt);
		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	}
	vector<Contact*> contacts;
	sqlite3_close(db);
	return contacts;
}

/* Used to retrieve contacts by id */
vector<Contact*> DatabaseHelper::getContactById(int id) {
	string tempSql = "SELECT * FROM contacts WHERE rowid=?;";
	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (id != -1)
			rc = sqlite3_bind_int(stmt, 1, id);
		rc = sqlite3_step(stmt);
		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	}
	vector<Contact*> contacts;
	sqlite3_close(db);
	return contacts;
}

/* Returns all rows in the table*/
vector<Contact*> DatabaseHelper::getAllContacts(){
	string tempSql = "SELECT * FROM contacts;";
	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		rc = sqlite3_step(stmt);
		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	}
	vector<Contact*> contacts;
	sqlite3_close(db);
	return contacts;
}

/* For more costomized select queries. Parameters must include empty strings if using something like address but
 * not phone number... like so:
 * 		buildSelectQuery("John", "123-456-1234") 			--> OK, all remaining fields default to ""
 * 		buildSelectQuery("John", "John@John.com") 			--> Not OK. Will be looking for a phone number "John@John.com"
 * 		buildSelectQuery("John", "", "", "John@John.com")	--> This is it!
 **/
vector<Contact*> DatabaseHelper::buildSelectQuery(string name, string phoneNumber,
												  string address, string email, int id){
	// initialize sql strings to build off of
	string tempSql = "SELECT * FROM contacts ";
	string tempSqlAfter = "WHERE ";
	int count = 0; // count is to keep track of sentence building and ? index
	int n, p, a, e, i;
	n = p = a = e = i= 0;

	// only add name, phoneNumber, etc if they are set in parameters
	if (name != "") {
		tempSqlAfter += "name = ? "; // set to ? for binding
		count++;
		n = count;
	}
	if (phoneNumber != "") {
		if (count > 0)
			tempSqlAfter += "AND phone_number = ? "; // only want and if there is something before it
		else
			tempSqlAfter += "phone_number = ? ";
		count++;
		p = count;
	}
	if (address != "") {
		if (count > 0)
			tempSqlAfter += "AND address = ? ";
		else
			tempSqlAfter += "address = ? ";
		count++;
		a = count;
	}
	if (email != "") {
		if (count > 0)
			tempSqlAfter += "AND email = ? ";
		else
			tempSqlAfter += "email = ? ";
		count++;
		e = count;
	}
	if (id != -1) {
		if (count > 0)
			tempSqlAfter += "AND id = ? ";
		else
			tempSqlAfter += "id = ? ";
		count++;
		i = count;
	}

	if (count > 0)
		tempSql += tempSqlAfter;

	tempSql += ";";

	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK)
	{
		// only bind if the value is set (duh)
		rc = sqlite3_prepare_v2( db, sql, -1, &stmt, NULL);
		if (name != "")
			rc = sqlite3_bind_text(stmt, n, name.c_str(), int(name.length()), SQLITE_TRANSIENT);
		if (phoneNumber != "")
			rc = sqlite3_bind_text(stmt, p, phoneNumber.c_str(), int(phoneNumber.length()), SQLITE_TRANSIENT);
		if (address != "")
			rc = sqlite3_bind_text(stmt, a, address.c_str(), int(address.length()), SQLITE_TRANSIENT);
		if (email != "")
			rc = sqlite3_bind_text(stmt, e, email.c_str(), int(email.length()), SQLITE_TRANSIENT);
		if (id != -1)
			rc = sqlite3_bind_int(stmt, i, id);

		rc = sqlite3_step(stmt);

		vector<Contact*> contacts = getContactsFromDB(rc,stmt);
		sqlite3_close(db);
		return contacts;
	} else {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	sqlite3_close(db);
	vector<Contact*> contacts;
	return contacts;
}

// deletes a row based on rowid.
// Returns True if successful, False if not
bool DatabaseHelper::deleteRow(int id) {
	char *err_msg = 0;
	const char* data = "Callback function called";

	// get row first to ensure we only delete if there is a row with the specified id
	string tempSql = "SELECT * FROM contacts WHERE rowid=" + std::to_string(id);
	const char* sql = tempSql.c_str();


	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		sqlite3_prepare(db, sql, -1, &stmt, 0);
		rc = sqlite3_step(stmt);

		while (rc == SQLITE_ROW){
			string delSql = "DELETE from contacts WHERE rowid=" + std::to_string(id);
			sql = delSql.c_str();
			rc = sqlite3_exec(db, sql, callback, (void*)data, &err_msg);
			sqlite3_close(db);
			return (rc == SQLITE_OK);
		}
	}
	else{
		sqlite3_close(db);
		return false;
	}
	return false;
}

// updates a row based on rowid.
// Returns True if successful, False if not
bool DatabaseHelper::updateRow(int id, string name, string phoneNumber,
							   string address, string email) {
	char *err_msg = 0;
	const char* data = "Callback function called";

	// get row first to ensure we only delete if there is a row with the specified id
	string tempSql = "SELECT * FROM contacts WHERE rowid=" + std::to_string(id);
	const char* sql = tempSql.c_str();


	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		sqlite3_prepare(db, sql, -1, &stmt, 0);
		rc = sqlite3_step(stmt);

		while (rc == SQLITE_ROW){

			int row_id = (int) sqlite3_column_int64(stmt,0);
			string row_name = string((char*)sqlite3_column_text(stmt, 1));
			string row_phoneNumber = string((char*)sqlite3_column_text(stmt, 2));
			string row_address = string((char*)sqlite3_column_text(stmt, 3));
			string row_email = string((char*)sqlite3_column_text(stmt, 4));

			// This part works basically the same as in the buildSelectQuery function
			string setString = "";
			int count = 0;
			int n, p, a, e;
			n = p = a = e = 0;
			if (name != "" && name != row_name) {
				setString += " name = ? ";
				count++;
				n = count;
			}
			if (phoneNumber != "" && phoneNumber != row_phoneNumber) {
				if (count > 0)
					setString += ", phone_number = ? ";
				else
					setString += " phone_number = ? ";
				count++;
				p = count;
			}
			if (address != "" && address != row_address) {
				if (count > 0)
					setString += ", address = ? ";
				else
					setString += " address = ? ";
				count++;
				a = count;
			}
			if (email != "" && email != row_email) {
				if (count > 0)
					setString += ", email = ? ";
				else
					setString += " email = ? ";
				count++;
				e = count;
			}

			string delSql = "UPDATE contacts "
									"SET" + setString +
									" WHERE rowid=" + std::to_string(id) + ";";
			sql = delSql.c_str();
			rc = sqlite3_prepare_v2( db, sql, -1, &stmt, NULL);
			if (name != "" && name != row_name)
				rc = sqlite3_bind_text(stmt, n, name.c_str(), int(name.length()), SQLITE_TRANSIENT);
			if (phoneNumber != "" && phoneNumber != row_phoneNumber)
				rc = sqlite3_bind_text(stmt, p, phoneNumber.c_str(), int(phoneNumber.length()), SQLITE_TRANSIENT);
			if (address != "" && address != row_address)
				rc = sqlite3_bind_text(stmt, a, address.c_str(), int(address.length()), SQLITE_TRANSIENT);
			if (email != "" && email != row_email)
				rc = sqlite3_bind_text(stmt, e, email.c_str(), int(email.length()), SQLITE_TRANSIENT);

			rc = sqlite3_step(stmt);

			sqlite3_close(db);
			return (rc == SQLITE_DONE);
		}
	}
	else{
		sqlite3_close(db);
		return false;
	}
	return false;
}

// Callback function for when sqlite3_exec is called.
// Found here: https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
int DatabaseHelper::callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

/* Helper Function to make DB calls. It's just here to simplify some code... probably don't need it
 	Returns: All contacts full info (name, number, address, email, id)
 */
vector<Contact*> DatabaseHelper::getContactsFromDB(int rc, sqlite3_stmt *stmt){
	vector<Contact*> contacts = vector<Contact*>();
	while (rc == SQLITE_ROW)
	{
		int row_id = (int) sqlite3_column_int64(stmt, 0);
		string row_name = string((char*)sqlite3_column_text(stmt, 1));
		string row_phoneNumber = string((char*)sqlite3_column_text(stmt, 2));
		string row_address = string((char*)sqlite3_column_text(stmt, 3));
		string row_email = string((char*)sqlite3_column_text(stmt, 4));

		contacts.push_back(new Contact(row_name, row_phoneNumber,row_address, row_email, row_id));

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return contacts;
}
