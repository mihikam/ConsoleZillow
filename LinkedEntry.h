//
//  LinkedEntry.h
//  HashTable
//
//  //  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright © 2018 s. All rights reserved.
//
#pragma once
#ifndef LinkedEntry_h
#define LinkedEntry_h

#include <iostream>
#include <string>
#include "House.h"
//#include "pch.h"

class LinkedEntry
{
private:
	int key;
	House* house;
	LinkedEntry* nextLinkedEntry;
	int numItemsinChain;

protected:
	void setKey(const int& searchKey);

public:
	LinkedEntry();
	LinkedEntry(int searchKey, House& newHouse);
	LinkedEntry(int searchKey, House& newHouse, LinkedEntry* newLinkedEntry);
	House& getItem() const;
	int getKey() const;
	LinkedEntry* getNextLinkedEntry() const;
	int getNumItemsinChain() const;
	void setNumItemsinChain(int newNumItems);
	void incrementNumItemsinChain();
	void decrementNumItemsinChain();

	void setItem(House& newHouse);
	void setNextLinkedEntry(LinkedEntry* newLinkedEntry);

};





#endif /* LinkedEntry_h */

