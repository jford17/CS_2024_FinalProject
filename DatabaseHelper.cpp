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
	char* sql = "CREATE TABLE IF NOT EXISTS contacts (rowid INTEGER PRIMARY KEY ASC, name TEXT, address TEXT, phone_number TEXT);";
//	char* sql = "DROP TABLE contacts";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
}

void DatabaseHelper::addContact(Contact c)
{
	sqlite3_stmt * stmt;
	char *err_msg = 0;
	string tempSql = "INSERT INTO contacts (name, phone_number) VALUES(?,?);";
	const char* sql = tempSql.c_str();
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK) {
		sqlite3_prepare( db, sql, -1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, c.name.c_str(), int(c.name.length()), SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 2, c.phoneNumber.c_str(), int(c.phoneNumber.length()), SQLITE_TRANSIENT);
		sqlite3_step( stmt );
		sqlite3_finalize(stmt);
	}
	else
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
	}

	sqlite3_close(db);
}

vector<Contact*> DatabaseHelper::getAllContacts(){
	string tempSql = "SELECT * FROM contacts";
	vector<Contact*> contacts = DBCall(tempSql);
	return contacts;
}

vector<Contact*> DatabaseHelper::getContactByName(string name) {
	string tempSql = "SELECT * FROM contacts WHERE name='" + name + "';";
	vector<Contact*> contacts = DBCall(tempSql);
	return contacts;
}

/* Helper Function to make DB calls
 	Returns: All contacts full info (i.e. name, address, number, etc...)

 	Private to prevent sql injections of any sort
 */
vector<Contact*> DatabaseHelper::DBCall(string tempSql){
	char *err_msg = 0;
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_open("address_book.db", &db);
	if (rc == SQLITE_OK)
	{
		sqlite3_prepare(db, sql, -1, &stmt, 0);
		rc = sqlite3_step(stmt);
		int ncols = sqlite3_column_count(stmt);

		vector<Contact*> contacts = vector<Contact*>();
		while (rc == SQLITE_ROW)
		{
			string name = string((char*)sqlite3_column_text(stmt, 1));
			string phoneNumber = string((char*)sqlite3_column_text(stmt, 3));
			int id = sqlite3_column_int64(stmt,0);

			contacts.push_back(new Contact(name, phoneNumber, id));

			rc = sqlite3_step(stmt);
		}

		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return contacts;
	} else {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	sqlite3_close(db);
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
}

int DatabaseHelper::callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
