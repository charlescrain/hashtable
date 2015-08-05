#include <cstdlib>
#include <cstring>
#include <iostream>

//#include "HashTable.h"

using namespace std;

class Person {
	public:
		string name; //Name of Person
		int key;     // Last 4-digits of phone number

		Person();
		Person(int, string);
};

class HashTable {
	private:
		int TableSize; 
		int entries;  // number of entries in hashtable
		Person *table;  //Pointer to person Array
		
	public:
		//constructors
		HashTable();	//default constructor
		HashTable(int); //specify table size constructor

		//methods
		void insert(int, string); //insert a Person into the HashTable
		void lookUp(int);
		void deletePerson(int);
		void printTable();

};


int main( int argc, const char* argv[]) {
	HashTable *hashtable = new HashTable();
	
	int key;
	char buffer[256];
	string input, name;
	while(!cin.eof()){
		cin >> input;
		if(input.compare("insert") == 0) {
			cin >> buffer >> name;
			key = atoi(buffer);
			hashtable->insert(key,name); 
		}
		else if(input.compare("lookup") == 0) {
			cin >> buffer;
			key = atoi(buffer);
			hashtable->lookUp(key);
		}
		else if(input.compare("delete") == 0) {
			cin >> buffer;
			key = atoi(buffer);
			hashtable->deletePerson(key);
		}
		else if(input.compare("print") == 0) {
			hashtable->printTable();
		}
		input = "";

	}


}

Person::Person() { //default constructor
	key = -1;
}
Person::Person(int keyr, string namer) {
	key = keyr;
	name = namer;
}

HashTable::HashTable() {  //default constructor

	TableSize = 5;
	entries=0;
	table = new Person[TableSize]; // not sure if can use pointer like this!!
}

HashTable::HashTable(int size){
	TableSize = size;
	entries=0;
	table = new Person[TableSize];
	
}

void HashTable::insert(int keyr, string namer) {
	int index;
	index = (keyr%443) % TableSize;	//Hash Function//

	while(table[index].key  >= 0) { //while loop for linear probing.
		if(table[index].key == keyr) {
			cout << "item already present\n";
			return;
		}
		if(index < TableSize -1)
			index++;
		else
			index = 0;              //case when hit end of table.
	}
	
	table[index].name = namer;  //add person//
	table[index].key = keyr;		//add person//
	entries++;							//increase number of entries//
	cout << "item successfully inserted\n";

	if( (static_cast<float>(entries)/static_cast<float>(TableSize))  >=  0.7 ) {  //if load factor greater than 0.7 resize table//
		Person *tmp = new Person[TableSize*2 +1];							  //make new table//
		for(int i=0;i<TableSize; i++) {   //copy over entries to new, larger table//
			if(table[i].key < 0)   //if bucket is empty skip
				continue;
			int index2 = (table[i].key%443)%(TableSize*2 +1);  //rehash key
			while(tmp[index2].key >=0)							//deal with collisions
				index2++;
			tmp[index2].key = table[i].key;
			
			tmp[index2].name = table[i].name;
			cout << "table doubled\n";
		}
		table = tmp;	
		TableSize = TableSize*2+1;    //set new table size//
		cout << "table resized\n";
	}
}
void HashTable::deletePerson(int keyr) {
	int index = (keyr%443)%TableSize;
	while(table[index].key != -1) {
		if(keyr == table[index].key){
			table[index].key = -2;			//Lazy delete. If the key is -2 then it is an emptied location
			cout << "item sucessfully deleted \n";
			return;
		}
		if(index == (TableSize -1))
			index =0;
		else
			index++;
	}
	cout << "item not present in the table\n";
}
void HashTable::lookUp(int keyr){
	int index = (keyr%443)%TableSize;
	
	while(table[index].key != -1) {
		if(keyr == table[index].key){
			cout << "item found; " << table[index].name << " " << index << "\n";
			return;
		}
		if(index == (TableSize -1))
			index =0;
		else
			index++;
	}
	cout << "item not found\n";
}
void HashTable::printTable() { 
	for(int i=0;i<TableSize;i++){
		if(table[i].key < 0)
			continue;
		cout << "(" << table[i].key << "," << table[i].name << ")";
	}
	cout << "\n";
}










