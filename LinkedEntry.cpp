
//
//  LinkedEntry.cpp
//  HashTable
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created by test on 12/1/18.
//  Copyright © 2018 s. All rights reserved.
//

//#include "pch.h"
#include "LinkedEntry.h"
#include <iostream>


/*
Default constructor of LinkedEntry. All LinkedEntries contain an attribute for the number of items in the chain, however only the first LinkedEntry in a chain will have a value > 0.

*/
LinkedEntry::LinkedEntry()
{
	key = -1;
	house = nullptr;
	nextLinkedEntry = nullptr;
	numItemsinChain = 0;


}

/*
Constructor for LinkedEntry.
Parameters: searchkey - the house number primary key
			newHouse - the house object of which its address will be stored in the hash table.

*/
LinkedEntry::LinkedEntry(int searchKey, House& newHouse)
{
	key = searchKey;
	house = &newHouse;

	nextLinkedEntry = nullptr;
	numItemsinChain = 0;

}

/*
  Constructor for Linked Entry.
  Parameters: searchkey - the house number primary key
			newHouse - the house object of which its address will be stored in the hash table.
			newLinkedEntry - pointer to the nextLinkedEntry in the chain.
*/
LinkedEntry::LinkedEntry(int searchKey, House& newHouse, LinkedEntry* newLinkedEntry)
{
	key = searchKey;
	house = &newHouse;
	nextLinkedEntry = newLinkedEntry;
	numItemsinChain = 0;
}

/*
 This function returns the house object pointed to by the house pointer.
*/

House& LinkedEntry::getItem() const
{
	return *house;
}

/*
This function returns the key(house number) of the LinkedEntry.
*/
int LinkedEntry::getKey() const
{
	return key;
}

/*
This function returns the nextLinkedEntry of the current LinkedEntry.
*/

LinkedEntry* LinkedEntry::getNextLinkedEntry() const
{
	return nextLinkedEntry;
}

/*
This function returns the number of items in the chain attribute of the LinkedEntry.
*/

int LinkedEntry::getNumItemsinChain() const
{
	return numItemsinChain;
}

/*
This function sets the number of items in the chain.
Parameters: newNumItems - the number of items to set the numItemsinChain attribute to.
*/
void LinkedEntry::setNumItemsinChain(int newNumItems)
{
	numItemsinChain = newNumItems;
}

/*
This function sets the key of the linked entry. It is protected and shouldn't be accessed easily.
Parameters: searchKey - the key to set the key attribute to.
*/

void LinkedEntry::setKey(const int& searchKey)
{
	key = searchKey;
}

/*
This function sets the house pointer to the address of a new house object.
Parameters: newHouse - the new House object the house pointer will point to.

*/

void LinkedEntry::setItem(House& newHouse)
{
	house = &newHouse;
}

/*
This function sets the nextLinkedEntry to a LinkedEntry pointer.
Parameters: newLinkedEntry - the LinkedEntry that the current LinkedEntry should point to.

*/
void LinkedEntry::setNextLinkedEntry(LinkedEntry* newLinkedEntry)
{
	nextLinkedEntry = newLinkedEntry;
}

/*
 This function increases the numItemsinChain attribute by 1.
*/
void LinkedEntry::incrementNumItemsinChain()
{
	numItemsinChain++;
}

/*
This function decreases the numItemsinChain attribute by 1.
*/
void LinkedEntry::decrementNumItemsinChain()
{
	numItemsinChain--;
}



