#include <iostream>
#include "sqlite3.h"
#include "DatabaseHelper.h"
#include <vector>

using namespace std;

int main(){
    DatabaseHelper db = DatabaseHelper();
	db.addContact(Contact("John", "123-456-7890"));
//	if (db.deleteRow(4)){
//		cout <<  "Deleted row with rowid 4" << endl;
//	}
	vector<Contact*> johns = db.getAllContacts();
	for (int i = 0; i < johns.size(); i++) {
		johns[i]->printDetails();
	}
//    cin.get();
    return 0;
}