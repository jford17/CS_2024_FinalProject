#include "sqlite3.h"
#include "DatabaseHelper.h"
#include <iostream>
#include <vector>
#include <string>
using std::string;
using namespace std;
using std::cin;


// display db
void printAll(DatabaseHelper db) {
	vector<Contact*> allContacts = db.getAllContacts();
	for (unsigned int i = 0; i < allContacts.size(); i++) {
		cout << "\t";
		allContacts[i]->printDetails();
	}
}


void userAddContact(DatabaseHelper db) {
	cout << "\tEnter contact name: ";
	string name = "";
	cin >> name;
	cout << "\tEnter contact phone number: ";
	string phone = "";
	cin >> phone;
	db.addContact(Contact(name, phone));
}

void userGetContact(DatabaseHelper db) {
	cout << "\tEnter contact name: ";
	string name = "";
	cin >> name;
	vector<Contact*>  contact = db.getContactByName(name);
	cout << "\n\t";
	contact[0]->printDetails();
}


void userDelete(DatabaseHelper db) {
	cout << "\tEnter contact id#: ";
	int id;
	cin >> id;
	db.deleteRow(id);
	cout << "\n\tcontact " << id << " deleted.\n";
}

void printCommandMenu() {
	cout << "\nUse the following command line keywords to interact with Contacts DB:\n";
	cout << "\t 'get'     to display a single contact\n";
	cout << "\t 'showAll' to display all contacts\n";
	cout << "\t 'add'     to add a new contact\n";
	cout << "\t 'delete'  to delete a contact\n";
	cout << "\t 'x'       to exit the application\n";
}


int main(){
	
	// welcome users
	cout << "Welcome to ContactsDB!\n";
	
	// create object to access DB of Contacts
    DatabaseHelper db = DatabaseHelper();
	
	// display keywords for user
	printCommandMenu();

	// interact with db via command line keywords
	string keyword = "a";
	while (keyword != "x") {
		cout << "\n";
		cin >> keyword;
		if (keyword == "get") { userGetContact(db); }
		else if (keyword == "showAll") { printAll(db); }
		else if (keyword == "add") { userAddContact(db); }
		else if (keyword == "delete") { userDelete(db); }
		else if (keyword == "help") { printCommandMenu(); }
	}

    return 0;
}
