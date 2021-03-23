#pragma once
//
//  FileOperations.h
//  CIS22C Project
//
//  Created  on 11/26/18.
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright © 2018. All rights reserved.
//

#ifndef FileOperations_h
#define FileOperations_h
#include "House.h"
#include <string>
#include "Array.h"
#include "HeadNode.h"


class FileOperations
{
private:
	string path;


public:
	FileOperations();
	FileOperations(string p);
	void setPath(string p);
	string getPath();
	void readFromFile(HeadNode* headNode);
	void addToFile(House& data);
	void deleteFromFile(int key);
	
};


#endif /* FileOperations_h */

