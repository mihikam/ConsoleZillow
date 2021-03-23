//
//  HashTable.cpp
//  HashTable
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created by Brian Huynh on 12/1/18.
//  Copyright © 2018 AG_BH_MM. All rights reserved.
//

//#include "pch.h"
#include "HashTable.h"




/*
Default constructor for HashTable. Dynamically allocates a table of LinkedEntry pointers and sets all pointers to null. Establishes a threshold and max size of table for which to resize the table.



*/
HashTable::HashTable()
{
	numItems = 0;
	numChains = 0;
	numCollisions = 0;
	tableSize = TABLE_SIZE;
	threshold = 0.80f;
	maxSize = (int)(threshold*tableSize);

	table = new LinkedEntry*[tableSize];
	for (int i = 0; i < tableSize; i++)
	{
		table[i] = nullptr;
	}
}
/*
The copy constructor for the HashTable. It copies all attributes and all LinkedEntries are reshashed to the table.

Parameters: newHashTable- the HashTable to copy
Post: a table populated with hashed entries and having all the attributes of the parameter hashtable.


*/

HashTable::HashTable(const HashTable& newHashTable)
{
	LinkedEntry **prevTable = newHashTable.getTable();
	tableSize = newHashTable.getTableSize();
	maxSize = newHashTable.getMaxSize();
	table = new LinkedEntry*[tableSize];
	numItems = 0;
	numChains = 0;
	numCollisions = 0;
	for (int i = 0; i < tableSize; i++)
	{
		table[i] = nullptr;
	}
	for (int i = 0; i < tableSize; i++)
	{

		if (table[i] != nullptr)
		{
			LinkedEntry* prev = nullptr;
			LinkedEntry* current = prevTable[i];

			while (current != nullptr)
			{
				add(current->getKey(), current->getItem());
				prev = current;
				current = current->getNextLinkedEntry();
				delete prev;
			}
		}
	}


}

/*
The resize function finds the number firstdouble the size of the previous table and then finds the next prime number from this new value. It creates a new table of this prime size. It then rehashes all objects in the previous hash table into the new one and resets the attributes numItems and numChains

Pre: table has reached the threshold limit of entries.
Post: a new table of larger size with all previous entries rehashed into new positions
Return: None


*/
void HashTable::resize()
{

	int prevTableSize = tableSize;
	tableSize *= 2;
	tableSize = nextPrime(tableSize);
	maxSize = (int)(tableSize * threshold);
	LinkedEntry **prevTable = table;

	table = new LinkedEntry*[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		table[i] = nullptr;
	}

	numItems = 0;
	numChains = 0;

	for (int i = 0; i < prevTableSize; i++)
	{

		if (prevTable[i] != nullptr)
		{
			LinkedEntry* prev = nullptr;
			LinkedEntry* current = prevTable[i];

			while (current != nullptr)
			{
				add(current->getKey(), current->getItem());
				prev = current;
				current = current->getNextLinkedEntry();
				delete prev;
			}
		}
	}
	delete[] prevTable;

}

/*
This function checks if a given number is prime. It automatically rules out any even numbers and numbers divisible by 3. It then uses the fact that all prime numbers are in the form of 6*k +/- 1. The loop terminates when the square root of size is reached.
Parameters:
size - the integer to check if prime
Return: true if prime
false if not prime.




*/
bool HashTable::isPrime(int size)
{

	if (size == 2 || size == 3)
	{
		return true;
	}

	if (size % 2 == 0 || size % 3 == 0)
	{
		return false;
	}

	int divisor = 6;
	while (divisor * divisor - 2 * divisor + 1 <= size)
	{

		if (size % (divisor - 1) == 0)
		{
			return false;
		}

		if (size % (divisor + 1) == 0)
		{
			return false;
		}

		divisor += 6;

	}

	return true;

}

/*
This function finds the next prime number after a given integer.
Parameters:
size - the base number. the function finds the first prime number larger than this number.
Return: the next prime number after size.

*/

int HashTable::nextPrime(int size)
{
	while (!isPrime(++size))
	{
	}
	return size;

}

/*
This function returns the current table size
Return: the tableSize

*/

int HashTable::getTableSize() const
{
	return tableSize;
}

/*
This function returns the max size of the table.
Return: the maxSize

*/

int HashTable::getMaxSize() const
{
	return maxSize;
}


/*
This function returns the threshold of the table size.
Return: the threshold.

*/
float HashTable::getThreshold() const
{
	return threshold;
}

/*
This function returns the number of linked chains in the table.
Return: Number of chains

*/
int HashTable::getNumChains() const
{
	return numChains;
}

/*
This function returns the number of all LinkedEntries in the table
Return: the number of LinkedEntries.

*/

int HashTable::getNumItems() const
{
	return numItems;
}


/*
this function returns the pointer to the table.


*/
LinkedEntry** HashTable::getTable() const
{
	return table;
}

/*

This function returns the number of collisions upon adding entries to the hash table.


*/
int HashTable::getNumCollisions() const
{
	return numCollisions;
}

/*
This function resets the collisions attribute to 0.
Pre: the numCollisions attribute corresponds to the number of collisions that occurred upon adding multiple entries.
Post: the number of collisions is reset to 0;

*/
void HashTable::resetCollisions()
{
	numCollisions = 0;
}


/*

This hash function utilizes the modulo-arithmetic algorithm for hashing. It ensures a more even distribution of objects.

Parameters:
key- the house number of the house object
Return: the hashtable index


*/

int HashTable::hash(int key)
{

	return key % tableSize;
}

/*

Overloaded subscript operator constant.

@param index the index of table to access
@return the LinkedEntry of table at index.


*/

LinkedEntry* HashTable::operator[](int index) const
{
	if (index < 0 || index > TABLE_SIZE)
	{
		cout << "bad index" << endl;
		exit(0);
	}
	else {
		return table[index];
	}


}

/*
Overloaded subscript operator

@param index the index of table to access
@return the LinkedEntry of table at index.

*/


LinkedEntry* HashTable::operator[](int index)
{
	if (index < 0 || index > TABLE_SIZE)
	{
		cout << "bad index" << endl;
		exit(0);
	}
	else {
		return table[index];
	}

}


/*
The get function retrieves a House object from the table, if it exists. It uses linear search if there are multiple linkedentries at the hash index.
Parameters:
key - the house number of the house object to retrieve
Return: nullptr if the House is not stored in the table
the House object if it exists in the table.



*/
House& HashTable::get(int key)
{
	int h = hash(key);
	if (table[h] == nullptr)
	{
		throw(key);
		//return nullptr;
	}
	else
	{
		LinkedEntry* prev = nullptr;
		LinkedEntry* current = table[h];
		while (current != nullptr && current->getKey() != key)
		{
			prev = current;
			current = current->getNextLinkedEntry();
		}

		if (current == nullptr)
		{
			std::cout << "sorry, the list does not have this item" << std::endl;
			throw(key);
			// return nullptr;
		}
		else
		{

			return current->getItem();
		}
	}
}

/*

This function adds a house object to the first position of a linked list at the hash index of the table calculated by the house number.
Parameters:
newHouse- the House object to add to the front of the list.
key- the house number of the house object.
Pre: A table with or without LinkedEntries at the hash index.
Post: the table has a LinkedEntry added to the front of the linkedlist at the hash index.
Return: none.


*/
void HashTable::addFirst(int key, House& newHouse)
{
	int h = hash(key);
	LinkedEntry* entry = new LinkedEntry(key, newHouse);
	entry->setNextLinkedEntry(table[h]);
	table[h] = entry;
	numItems++;
}


/*

This function adds a house object to the last position of a linked list at the hash index of the table calculated by the house number.
Parameters:
newHouse- the House object to add to the end of the list.
key- the house number of the house object.
Pre: A table with or without LinkedEntries at the hash index.
Post: the table has a LinkedEntry added to the end of the linkedlist at the hash index.
Return: none.


*/
void HashTable::addLast(int key, House& newHouse)
{
	LinkedEntry* prev = nullptr;
	LinkedEntry* current = table[hash(key)];
	while (current != nullptr)
	{
		prev = current;
		current = current->getNextLinkedEntry();
	}
	LinkedEntry* entry = new LinkedEntry(key, newHouse);
	prev->setNextLinkedEntry(entry);
	numItems++;

}


/*

This function adds a house object to the linked list at the hash index of the table calculated by the house number in an ascending sort based on the house number(key). If upon adding the new LinkedEntry, the maxSize threshold is reached, then the table is resized by calling the resize function.
Parameters:
newHouse- the House object to add to the list.
key- the house number of the house object.
Pre: A table with or without LinkedEntries at the hash index.
Post: the table has a LinkedEntry added to the linkedlist at the hash index.
Return: none.


*/
void HashTable::add(int key, House& newHouse)
{
	int h = hash(key);
	if (table[h] == nullptr) // new chain entry
	{
		addFirst(key, newHouse);
		numChains++;
		table[h]->incrementNumItemsinChain();
	}
	else //iterate through linked list
	{
		numCollisions++;
		LinkedEntry* prev = nullptr;
		LinkedEntry* current = table[h];
		if (current->getKey() >= key)
		{
			int numItemsinChain = table[h]->getNumItemsinChain();
			table[h]->setNumItemsinChain(0);
			addFirst(key, newHouse);
			table[h]->setNumItemsinChain(numItemsinChain + 1);

		}
		else
		{
			while ((current != nullptr) && (key > current->getKey()))
			{
				prev = current;
				current = current->getNextLinkedEntry();
			}
			LinkedEntry* entry = new LinkedEntry(key, newHouse);
			entry->setNextLinkedEntry(prev->getNextLinkedEntry());
			prev->setNextLinkedEntry(entry);
			numItems++;
			table[h]->incrementNumItemsinChain();
		}
	}

	if (numItems > maxSize)
	{
		resize();
	}
}


/*

This function removes a house object from the first position of a linked list at the hash index of the table calculated by the house number and returns the removed house object.
Parameters:
key- the house number of the house object to remove.
Pre: A table with or without LinkedEntries at the hash index.
Post: the table has a LinkedEntry removed from the front of the linkedlist at the hash index.
Return: nullptr- if there is no House object with that key in the table.
removedHouse- the house object removed from the front of the linked list at the hash index.


*/

House& HashTable::removeFirst(int key)
{
	int h = hash(key);
	if (table[h] == nullptr)
	{
		std::cout << "This entry does not exist" << std::endl;
		throw(0);
	}
	else
	{

		LinkedEntry* current = table[h];
		table[h] = table[h]->getNextLinkedEntry();
		House& removedHouse = current->getItem();
		current->setNextLinkedEntry(nullptr);
		delete current;
		numItems--;
		return removedHouse;
	}
}

/*

This function removes a house object from the last position of a linked list at the hash index of the table calculated by the house number and returns the removed house object.
Parameters:
key- the house number of the house object to remove.
Pre: A table with or without LinkedEntries at the hash index.
Post: the table has a LinkedEntry removed from the end of the linkedlist at the hash index.
Return: nullptr- if there is no House object with that key in the table.
removedHouse- the house object removed from the end of the linked list at the hash index.


*/

House& HashTable::removeLast(int key)
{
	int h = hash(key);
	if (table[h] == nullptr)
	{
		std::cout << "nothing in your linked list to delete" << std::endl;
		throw(0);
	}
	else if (table[h] != nullptr && numItems == 1)//deleting last with one node is the same as deleting first.
	{

		return removeFirst(key);

	}
	else if ((table[h] != nullptr) && (numItems>1))
	{
		LinkedEntry* prev = nullptr;
		LinkedEntry* current = table[h];
		while (current->getNextLinkedEntry() != nullptr)
		{
			prev = current;
			current = current->getNextLinkedEntry();
		}


		House& removedHouse = current->getItem();

		prev->setNextLinkedEntry(nullptr);
		delete(current);
		numItems--;
		return removedHouse;

	}
	else {
		throw(10);
	}

}


/*

This function removes a house object from the hash index of the table calculated by the house number and returns the removed house object.
Parameters:
key- the house number of the house object to remove.
Pre: A table with or without LinkedEntries at the hash index.
Post: the table has a LinkedEntry removed from the linkedlist at the hash index.
Return: nullptr- if there is no House object with that key in the table.
removedHouse- the house object removed from the linked list at the hash index.


*/


House& HashTable::remove(int key)
{
	int h = hash(key);

	if (table[h] == nullptr)
	{
		std::cout << "That item is not in the table" << std::endl;
		//return nullptr;
		throw(0);
	}
	else
	{
		LinkedEntry* prev = nullptr;
		LinkedEntry* current = table[h];
		while (current != nullptr && current->getKey() != key)
		{
			prev = current;
			current = current->getNextLinkedEntry();

		}

		if (current == nullptr)
		{
			std::cout << "sorry, the list does not have this item" << std::endl;
			throw(0);
		}
		else
		{
			House& removedHouse = current->getItem();
			if (prev == nullptr)
			{
				if (current->getNextLinkedEntry() == nullptr)
				{
					numChains--;
					removeFirst(key);
				}
				else
				{
					table[h]->getNextLinkedEntry()->setNumItemsinChain(current->getNumItemsinChain() - 1);

				}


			}
			else if (prev->getKey() == key)
			{
				table[h]->decrementNumItemsinChain();
				removeLast(key);
			}
			else
			{
				prev->setNextLinkedEntry(current->getNextLinkedEntry());
				current->setNextLinkedEntry(nullptr);
				delete current;
				table[h]->decrementNumItemsinChain();
			}
			return removedHouse;

		}
	}
}

/*
This function finds the hash index which contains the longest chain of linked entries by comparing the number of items in chain of the first item of all non-nullptr indices.
Return: the length of the longest chain.


*/

int HashTable::getLongestChain()
{
	int longest = -1;
	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] != nullptr)
		{
			if (longest < table[i]->getNumItemsinChain())
			{
				longest = table[i]->getNumItemsinChain();
			}

		}
	}
	return longest;
}




/*
This function calculates the load factor of a retreival / removal operation. First an average number of items per chain, alpha, is calculated by dividing the total number of entries by the total number of chains in the table. If the retrieval/removal operation is successful, then the operation first locates the correct hash index and then traverses the linked list, giving it a load factor of 1 + alpha/2. If the operation is unsuccessful, then it must still, on average, traverse the entire list to determine if the object exists, so its load factor is alpha.

Parameter: successful - a boolean indicating if the operation was successful or not.
Return: a float value of the load factor.

*/
void HashTable::loadFactor(bool successful)
{
	float alpha = (float)(getNumItems() / getNumChains());
	if (successful)
	{
		cout << 1 + (alpha / 2) << endl;
	}
	else {
		cout << alpha << endl;

	}
}

/*

This function displays the table by showing which indices have entries.

*/
void HashTable::displayTable()
{
	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] == nullptr)
		{
			cout << "table[" << i << "] has no entries" << endl;
		}
		if (table[i] != nullptr)
		{
			cout << "table[" << i << "] has " << table[i]->getNumItemsinChain() << " entries." << endl;

		}
	}
}

/*
This function iterates through the hashtable and outputs all House entries.
*/

void HashTable::displayAllEntries()
{
	for (int i = 0; i < tableSize; i++)
	{

		if (table[i] != nullptr)
		{
			LinkedEntry* current = table[i];
			while (current != nullptr)
			{
				current->getItem().printHouse();
				current = current->getNextLinkedEntry();
			}
		}
	}

}

/*
The destructor of the HashTable. It deletes all LinkedEntries and then deletes the table.

*/

HashTable::~HashTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != nullptr)
		{
			LinkedEntry* prev = nullptr;
			LinkedEntry* current = table[i];
			while (current != nullptr)
			{
				prev = current;
				current = current->getNextLinkedEntry();
				delete prev;
			}
		}
	}
	delete[] table;
}



