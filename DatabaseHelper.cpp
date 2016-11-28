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
	char* sql = "CREATE TABLE IF NOT EXISTS contacts (name TEXT, address TEXT, phone_number TEXT);";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
		return;
	}
}

void DatabaseHelper::addContact(Contact c)
{
	char *err_msg = 0;
	string tempSql = "INSERT INTO contacts VALUES('" + c.name + "', '', '" + c.phoneNumber + "');";
	const char* sql = tempSql.c_str();
	int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);
	}
}

vector<Contact*> DatabaseHelper::getContactByName(string name) {
	char *err_msg = 0;
	string tempSql = "SELECT * FROM contacts WHERE name='" + name + "';";
	const char* sql = tempSql.c_str();

	sqlite3_stmt *stmt;
	int rc = sqlite3_prepare(db, sql, -1, &stmt, 0);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	rc = sqlite3_step(stmt);
	int ncols = sqlite3_column_count(stmt);

	vector<Contact*> contacts = vector<Contact*>();
	while (rc == SQLITE_ROW)
	{
		string name = string((char*)sqlite3_column_text(stmt, 0));
		string phoneNumber = string((char*)sqlite3_column_text(stmt, 2));
		string address = string((char*)sqlite3_column_text(stmt, 1));
		if (address != "")
			contacts.push_back(new Friend(name, phoneNumber, address));
		else
			contacts.push_back(new Contact(name, phoneNumber));

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);

	return contacts;
}
