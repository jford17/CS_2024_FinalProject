#include <iostream>
#include "sqlite3.h"
#include "DatabaseHelper.h"
#include <vector>

using namespace std;

int main(){
    DatabaseHelper db = DatabaseHelper();
	db.addContact(Contact("John", "123-456-7890"));
	vector<Contact*> johns = db.getContactByName("John");
	for (int i = 0; i < johns.size(); i++) {
		johns[i]->printDetails();
	}
    cin.get();
    return 0;
}