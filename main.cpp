#include <iostream>
#include "sqlite3.h"
#include "DatabaseHelper.h"
#include <vector>
#include <string>

using namespace std;

int main(){
    DatabaseHelper db = DatabaseHelper();
//	db.addContact(Contact("John", "123-456-7890", "John@John.com"));
//	if (db.deleteRow(4)){
//		cout <<  "Deleted row with rowid 4" << endl;
//	}
	vector<Contact*> johns = db.getContactByPhoneNumber("123-456-7890");
	for (int i = 0; i < johns.size(); i++) {
		johns[i]->printDetails();
	}
//    cin.get();
//	db.updateRow(1, "John Smith", "", "", "JohnWork2@John.com");

    return 0;
}