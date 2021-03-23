
//
//  FileOperations.cpp
//  CIS22C Project
//
//  Created on 11/16/18.
//  Copyright © 2018. All rights reserved.
//
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FileOperations.h"


using namespace std;

/*
Description: This is the default constructor for file operations and sets path to an empty string.
Pre:
Post:
Return:
*/
FileOperations::FileOperations()
{
	path = "";
}

/*
Description: This is the overloaded constructor that sets the path to the value passed.
Pre:
Post:
Return:
*/
FileOperations::FileOperations(string p)
{
	path = p;
}

/*
Description: Setter for the path.
Pre: String to set path to.
Post:
Return:
*/
void FileOperations::setPath(string p)
{
	path = p;
}

/*
Description: Getter for path
Pre:
Post:
Return: string path
*/
string FileOperations::getPath()
{
	return path;
}

/*
Description: This method reads information in from the file, and adds the data into dynamically allocated objects.
Pre: hash table/bst by reference?
Post: ?
Return: ?
*/
void FileOperations::readFromFile(HeadNode* headNode)
{
	//BinarySearchTree<House>* pricetree = new BinarySearchTree<House>;
	// BinarySearchTree<House>* sftree = new BinarySearchTree<House>;
	ifstream myfile;
	string line;
	myfile.open(path);
	if (myfile)
	{
		while (getline(myfile, line))
		{
			stringstream stream;
			bool firstEntry = true;
			stream << line;
			string var;
			int count = 0;
			House * pHouse = new House();
			//cin >> *pHouse;
			while (getline(stream, var, ','))
			{
				istringstream iss(var);
				switch (count)
				{
					if (count == 0 && firstEntry)
					{
						var = var.substr(3, var.length());
						firstEntry = false;
					}
				case 0:
					pHouse->setHouseNo(stoi(var));
					break;
				case 1:
					pHouse->setAddress(var);
					break;
				case 2:
					pHouse->setBedrooms(stoi(var));
					break;
				case 3:
					pHouse->setBathrooms(stol(var));
					break;
				case 4:
					pHouse->setPrice(stoi(var));
					break;
				case 5:
					pHouse->setSquareFootage(stoi(var));
					break;
				}
				count++;
			}

			headNode->addHouseFromDatabase(*pHouse);
		}
		

		myfile.close();
	}
	else
	{
		cout << "Invalid file" << endl;
	}
	

}

/*
Description: This method adds objects of type house to the file. It converts the attributes of house into a string that matches the general form in the file.
Pre: Object of type house.
Post:
Return:
*/
void FileOperations::addToFile(House& data)
{
	fstream f;
	f.open(path, fstream::app);
	f << data.getHouseNo() << "," << data.getAddress() << "," << data.getBedrooms() << "," << data.getBathrooms() << "," << data.getPrice() << "," << data.getSquareFootage() << endl;
	f.close();
}


/*
Description: This method deletes values from the file. It searches the file based on the information passed to it as a parameter and deletes accordingly.
Pre: Key of data to be deleted.
Post:
Return:
*/
void FileOperations::deleteFromFile(int key)
{
	ifstream myfile;
	string line;
	ofstream temp;
	temp.open("temp.txt");
	myfile.open(path);
	if (myfile)
	{
		while (getline(myfile, line))
		{
			stringstream stream;
			string var;
			stream << line;
			getline(stream, var, ',');
			if (stoi(var) != key)
				temp << line << endl;
		}
	}
	else
	{
		cout << "Invalid file" << endl;
	}

	temp.close();
	myfile.close();
	remove(path.c_str());
	rename("temp.txt", "housedata.txt");
}
