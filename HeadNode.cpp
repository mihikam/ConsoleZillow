
//
//  HeadNode.cpp
//  HashTable
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created by test on 12/1/18.
//  Copyright © 2018 s. All rights reserved.
//

//#include "pch.h"
#include <iostream>
#include <string>
#include "HeadNode.h"

/*
Default constructor of HeadNode. Dynamically allocates HashTable, priceTree, squareFtTree, and houseArray.

*/
HeadNode::HeadNode()
{
	count = 0;
	successfulSearch = false;
	successfulDeletion = false;
	hashTable = new HashTable();
	priceTree = new BinarySearchTree<House>();
	squareFtTree = new BinarySearchTree<House>();
	houseArray = new Array<House>(100);
}

HeadNode::~HeadNode()
{
	delete hashTable;
	delete priceTree;
	delete houseArray;
	delete squareFtTree;
}

/*
 This function gets the value of the successfulSearch boolean, used for calculating hash table efficiencies.
 Return: The value of the successfulSearch boolean

*/
bool HeadNode::getSuccessfulSearch() const
{
	return successfulSearch;
}

/*
  This function gets the value of the successfulDeletion boolean, used for calculating hash table efficiencies.
  Return: The value of the successfulDeletion boolean
*/
bool HeadNode::getSuccessfulDeletion() const
{
	return successfulDeletion;
}

/*

this function sets the successfulSearch boolean to the value in the parameter, used for calculating hash table efficiencies.
Parameters: search - a boolean describing whether a search operation resulted in an existing entry or not.
Return: none.

*/
void HeadNode::setSuccessfulSearch(bool search)
{
	successfulSearch = search;
}

/*

this function sets the successfulDeletion boolean to the value in the parameter, used for calculating hash table efficiencies.
Parameters: search - a boolean describing whether a deletion operation was successful or not.
Return: none.

*/
void HeadNode::setSuccessfulDeletion(bool deletion)
{
	successfulDeletion = deletion;
}

/*
This function calls priceTree's inorder traversal to print the house entries whose price is between the min and max parameters.
Parameters: min - minimum price to search
		   max - maximum price to search
Post: House entries matching the price range given are printed to the console.
Return: None.

*/

void HeadNode::priceFilter(int min, int max)
{
	priceTree->inorder(priceTree->getRoot(), min, max, 1);

}

/*
This function calls squareFtTree's inorder traversal to print the house entries whose square feet is between the min and max parameters.
Parameters: min - minimum sq ft to search
max - maximum sq ft to search
Post: House entries matching the sq ft range given are printed to the console.
Return: None.

*/

void  HeadNode::squareFtFilter(int min, int max)
{
	squareFtTree->inorder(squareFtTree->getRoot(), min, max, 2);
}

/*
This function prints the priceTree as a tree on the console by calling priceTree's printIndentedTree function.
Pre: none
Post: the console is printed with a graphical representation of the tree's root, parent, and child node relationships.
Return: none.
*/
void  HeadNode::printPriceTree()
{
	priceTree->printIndentedTreeHorizontally(priceTree->getRoot(), 1, 0);

}

/*
This function prints the sqFtTree as a tree on the console by calling sqFtTree's printIndentedTree function.
Pre: none
Post: the console is printed with a graphical representation of the tree's root, parent, and child node relationships.
Return: none.


*/
void HeadNode::printSqFtTree()
{
	squareFtTree->printIndentedTreeHorizontally(squareFtTree->getRoot(), 2, 0);
}


/*
 This function adds a house entry from the original text file database to each respective data structure.
 Parameters: newHouse- the house object being added from the database text file.
 Return: None.
 Pre: The data structures are empty.
 Post: The new house object is added to each data structure by the appropriate attribute of the object.


*/
void HeadNode::addHouseFromDatabase(House &newHouse)
{
	count++;
	hashTable->add(newHouse.getHouseNo(), newHouse);
	priceTree->add(newHouse, 1);
	squareFtTree->add(newHouse, 2);
	houseArray->insertInOrder(newHouse);

}


/*
This function adds a house entry from user input to each respective data structure.
Parameters: newHouse- the house object being added from user input.
Return: None.
Pre: The original state of each data structure.
Post: The new house object is added to each data structure by the appropriate attribute of the object.


*/
void HeadNode::addNewHouseEntry(House &newHouse)
{
	resetTreeEfficiencies();
	count++;
	hashTable->add(newHouse.getHouseNo(), newHouse);
	priceTree->add(newHouse, 1);
	squareFtTree->add(newHouse, 2);
	houseArray->insertInOrder(newHouse);


}

/*
This function displays all house entries in descending sorted house number order.
Parameters: None
Return: None
Post: The house entries are displayed to the console in sorted house number order.

*/
void HeadNode::displayArray()
{
	houseArray->displayArray();
}

/*
This function displays all house entries in the order they are stored in the hash table.
Parameters: None
Return: None
Post: The house entries are displayed to the console in hash sequence.

*/
void HeadNode::listbyHash()
{
	hashTable->displayAllEntries();
}

/*
 This function deletes a house entry from all data structures, if it exists.
 Parameters: h_no - the house number of the house entry to delete. Used as a key for retrieval from the hash table. The object retrieved is subsequently passed to the data structures for removal.
 Return: true - if the deletion was successful from all data structures.
		false - if the deletion was unsuccessful.

Pre: the state of each respective data structures
Post: The data structures have removed the object corresponding to the h_no from themselves.

*/
bool HeadNode::deleteHouse(int h_no)
{
	try {
		resetTreeEfficiencies();
		House& deletedHouse = hashTable->remove(h_no);
		setSuccessfulDeletion(true);
		priceTree->remove(deletedHouse, 1);

		squareFtTree->remove(deletedHouse, 2);
		houseArray->deleteValue(deletedHouse);
		return true;

	}
	catch (int e)
	{
		setSuccessfulDeletion(false);
		return false;
	}

}

/*
	This function searches the hashTable for a house entry by house number. If successful, it returns the house object.
	Parameters: h_no - the house number of the house entry being searched for.
	Return: The house object found by the search in the hash table.
	Pre: The hash table in its original state.
	Post: The hash table is unchanged.


*/

House& HeadNode::findHouse(int h_no)
{
	try {
		House& foundHouse = hashTable->get(h_no);
		setSuccessfulSearch(true);
		return foundHouse;
	}
	catch (int e)
	{
		setSuccessfulSearch(false);
		throw(0);
	}
}

/*

This function returns the efficiency of the last performed operation for the priceTree
Return: the efficiency of the tree operation.

*/

int HeadNode::priceTreeEfficiency()
{
	return priceTree->getEfficiency(priceTree->getRoot());
}

/*

This function returns the efficiency of the last performed operation for the squareFtTree
Return: the efficiency of the tree operation.

*/
int HeadNode::sqFtTreeEfficiency()
{
	return squareFtTree->getEfficiency(squareFtTree->getRoot());
}

/*
 This function resets the priceTree and squareFtTree efficiencies before a new operation is performed.

*/
void HeadNode::resetTreeEfficiencies()
{
	priceTree->resetEfficiency();
	squareFtTree->resetEfficiency();
}


/*
This function returns the length of the hash table's longest chain.
Return: the length of the longest chain in the hash table

*/

int HeadNode::getHashLongestChain() const
{
	return hashTable->getLongestChain();
}



/*
This function returns the number of collisions in the hash table
Return: the number of collisions in the hash table.

*/
int HeadNode::getHashCollisions() const
{
	return hashTable->getNumCollisions();
}

/*
This function resets the number of collisions in the hash table to 0.
Pre: the hash table has a number of collisions greater than 0.
Post: the hash table's collisions attribute is reset to 0.

*/

void HeadNode::resetHashCollisions()
{
	hashTable->resetCollisions();
}


/*

This function prints the efficiency of the hash table according to the operation just performed by the user.
Parameters: choice - (1) corresponds to an add operation. (2) Deletion. (3) Search.
Return: None

*/
void HeadNode::hashEfficiency(int choice)
{
	
	if (choice == 1) // adding an entry (corresponds to average number of entries / chain)
	{
		if (hashTable->getNumCollisions() == 0)
		{
			cout << 1 << endl;
		}
		else {
			float alpha = (float)(hashTable->getNumItems() / hashTable->getNumChains());
			cout << (float)(alpha / 2) << endl;

			//hashTable->loadFactor(false);
		}
		
	}
	else if (choice == 2) // deleting an entry (dependent on whether the deletion was successful)
	{
		hashTable->loadFactor(getSuccessfulDeletion());
	}
	else if (choice == 3) // finding an entry (dependent on search success)
	{
		hashTable->loadFactor(getSuccessfulSearch());
	}
	

}

/*
 This function compares the price between two house objects.
 Parameters: house1 - the first house 
			house2 - the second house
Return: 1 - if house1 is more expensive, 2 - if house2 is more expensive, 0 - if they are the same price.
*/

int HeadNode::comparePrice(House& house1, House& house2)
{
	if(house1.getPrice() > house2.getPrice())
	{
		return 1;
	}else if(house1.getPrice() < house2.getPrice())
	{
		return 2;
	}

		return 0;

}

/*
  This function reports to the user the relative price values of two houses by house number.
  Parameters: key1 - the first house number, key2- the second house key
  Return: none
  Post: Print which house is more expensive.

*/
void HeadNode::priceComparison(int key1, int key2)
{
	

		try {
			House& house1 = hashTable->get(key1);
			House& house2 = hashTable->get(key2);
			if (comparePrice(house1, house2) == 1)
			{
				cout << house2.getHouseNo() << " " << house2.getAddress() << " is cheaper. \n you would save " << house1.getPrice() - house2.getPrice() << " dollars" << endl;
			}
			else if (comparePrice(house1, house2) == 2)
			{
				cout << house1.getHouseNo() << " " << house1.getAddress() << " is cheaper. \n you would save " << house2.getPrice() - house1.getPrice() << " dollars" << endl;
			}
			else
			{
				cout << house1.getHouseNo() << " " << house1.getAddress() << " and " << house2.getHouseNo() << " " << house2.getAddress() << " have the same price." << endl;
			}

		}
		catch (int e)
		{
			cout << "We don't have a record of this house: " << e << ". Please try again." << endl;
			throw(0);
			
			
		}
	
}








