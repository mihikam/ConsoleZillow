#pragma once
//
//  HashTable.h
//  HashTable
//
//  Created by test on 11/28/18.
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright © 2018 s. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include "LinkedEntry.h"
#include <iostream>
#include <string.h>
#include "House.h"


const int TABLE_SIZE = 13;

class HashTable
{
private:
	LinkedEntry** table;
	float threshold;
	int numItems;
	int numChains;
	int maxSize;
	int tableSize;
	void resize();
	int numCollisions;



public:
	HashTable();

	HashTable(const HashTable& newHashTable);

	~HashTable();

	int getNumItems() const;
	int getNumChains() const;
	int getTableSize() const;
	float getThreshold() const;
	int getMaxSize() const;
	LinkedEntry** getTable() const;
	LinkedEntry* operator[](int index) const;
	LinkedEntry* operator[](int index);
	House& get(int key);
	void addFirst(int key, House& newHouse);
	void addLast(int key, House& newHouse);
	void add(int key, House& newHouse);
	void loadFactor(bool successful);
	int getNumCollisions() const;
	void resetCollisions();


	House& removeFirst(int key);
	House& removeLast(int key);
	House& remove(int key);

	int hash(int key);
	void displayTable();
	void displayAllEntries();
	int getLongestChain();

	bool isPrime(int size);
	int nextPrime(int size);





};



#endif /* HashTable_h */
