#pragma once
//
//  HeadNode.h
//  HashTable
//
//  Created by test on 12/1/18.
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright © 2018 s. All rights reserved.
//

#ifndef HeadNode_h
#define HeadNode_h

#include <iostream>
#include <string>
#include "HashTable.h"
#include "BinarySearchTree.h"
#include "House.h"
#include "Array.h"


class HeadNode
{
private:
	int count;
	HashTable* hashTable;
	BinarySearchTree<House>* priceTree;
	BinarySearchTree<House>* squareFtTree;
	Array<House>* houseArray;
	bool successfulSearch;
	bool successfulDeletion;

public:
	HeadNode();
	~HeadNode();

	bool getSuccessfulSearch() const;
	bool getSuccessfulDeletion() const;
	void setSuccessfulSearch(bool search);
	void setSuccessfulDeletion(bool deletion);
	void priceFilter(int min, int max);
	void squareFtFilter(int min, int max);
	int getHashLongestChain() const;
	int getHashCollisions() const;
	void resetHashCollisions();
	void printPriceTree();
	void printSqFtTree();
	void addHouseFromDatabase(House &newHouse);
	void addNewHouseEntry(House &newHouse);
	void listbyHash();
	void displayArray();
	bool deleteHouse(int h_no);
	House& findHouse(int h_no);
	void hashEfficiency(int choice);
	int priceTreeEfficiency();
	int sqFtTreeEfficiency();
	void resetTreeEfficiencies();

	//void treeEfficiency(int tree);


	void priceComparison(int key1, int key2);
	int comparePrice(House& house1, House& house2);





};

#endif /* HeadNode_h */
