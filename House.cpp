//
//  House.cpp
//  CIS22C Project
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created on 11/16/18.
//  Copyright © 2018. All rights reserved.
//

//#include "pch.h"
#include <iostream>
#include <stdio.h>
#include "House.h"
#include <string>

/*
This function returns the house number of the house object.

*/
int House::getHouseNo()
{
	return house_no;
}

/*
This function returns the address of the house object.

*/

string House::getAddress()
{
	return address;
}

/*
This function returns the number of bedrooms of the house object.

*/
int House::getBedrooms()
{
	return bedrooms;
}

/*
This function returns the number of bathrooms of the house object.

*/
float House::getBathrooms()
{
	return bathrooms;
}

/*
This function returns the price of the house object.

*/
int House::getPrice()
{
	return price;
}

/*
This function returns the square footage of the house object.

*/
int House::getSquareFootage()
{
	return square_footage;
}


/*
This function sets the house number to a new value.
Parameters: h_no - the new house number.

*/
void House::setHouseNo(int h_no)
{
	house_no = h_no;
}

/*
This function sets the address to a new value.
Parameters: add - the new address.

*/
void House::setAddress(string add)
{
	address = add;
}

/*
This function sets the bedrooms to a new value.
Parameters: bed - the new number of bedrooms.
*/
void House::setBedrooms(int bed)
{
	bedrooms = bed;
}

/*
This function sets the bathrooms to a new value.
Parameters: bath - the new number of bathrooms.

*/
void House::setBathrooms(float bath)
{
	bathrooms = bath;
}

/*
This function sets the price to a new value.
Parameters: pr - the new price.

*/
void House::setPrice(int pr)
{
	price = pr;
}

/*
This function sets the square_footage to a new value.
Parameters: sq_ft - the new square footage.

*/
void House::setSquareFootage(int sq_ft)
{
	square_footage = sq_ft;
}

/*
This function prints out the house number, address, price, and square footage of the house to the console.
*/
void House::printHouse()
{
	cout << house_no << " " << address << " " << price << " " << " " << square_footage << endl;
}

/*
An overloaded input operator that sets the houses attributes to that of the istream object.
Parameters: ip - the istream object
			val - the house object being read.
Return: The istream object. 
*/
istream& operator >>(istream& ip, House &val)
{
	ip >> val.house_no;
	ip >> val.address;
	ip >> val.bedrooms;
	ip >> val.bathrooms;
	ip >> val.price;
	ip >> val.square_footage;
	return ip;
}

/*
An overloaded output operator that outputs the house number, address, price, and square footage of the house object
Parameters: op - the ostream object
			val - the house object to the output
Return: the ostream object.

*/
ostream& operator <<(ostream& op, House &val)
{
	op << val.house_no << " " << val.address << " " << val.price << " " << " " << val.square_footage << endl;
	return op;
}



/*
 An overloaded equals-to operator that returns whether the houses have the same house number.
 Parameters: valone - the first house object.
			valtwo - the second house object to compare.
Return: true - the objects have the same house number.
		false - the objects do not have the same house number.

*/
bool operator== (const House &valone, const House &valtwo)
{
	if (valone.house_no == valtwo.house_no)
	{
		return true;
	}
	else
		return false;
}


