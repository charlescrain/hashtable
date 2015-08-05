#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstdlib>
#include <cstring>
#include <iostream>

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

#endif
