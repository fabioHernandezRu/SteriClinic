/*
 * HashTable.h
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */
//reference http://pumpkinprogrammer.com/2014/06/21/c-tutorial-intro-to-hash-tables/
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "LinkedList.h"

//*****************************************************************
// Hash Table objects store a fixed number of Linked Lists.
//*****************************************************************
class HashTable {
private:

	// Array is a reference to an array of Linked Lists.
	LinkedList * array;

	// Length is the size of the Hash Table array.
	int length;

	// Returns an array location for a given item key.
	int hash(string itemKey);

public:

	// Constructs the empty Hash Table object.
	// Array length is set to 13 by default.
	HashTable(int tableLength = 13);

	// Adds an item to the Hash Table.
	void insertItem(Item * newItem);

	// Deletes an Item by key from the Hash Table.
	// Returns true if the operation is successful.
	bool removeItem(string itemKey);

	// Returns an item from the Hash Table by key.
	// If the item isn't found, a null pointer is returned.
	Item * getItemByKey(string itemKey);

	// Display the contents of the Hash Table to console window.
	void printTable();

	// Prints a histogram illustrating the Item distribution.
	void printHistogram();

	// Returns the number of locations in the Hash Table.
	int getLength();

	// Returns the number of Items in the Hash Table.
	int getNumberOfItems();

	// De-allocates all memory used for the Hash Table.
	~HashTable();
};

//*****************************************************************
// End of File
//*****************************************************************

#endif /* HASHTABLE_H_ */
