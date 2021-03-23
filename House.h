#pragma once
//
//  House.h
//  Zillow_Final_Project
//
//  Created by test on 11/16/18.
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright © 2018 s. All rights reserved.
//

#ifndef House_h
#define House_h


#include <iostream>
#include <string.h>

using namespace std;

class House
{
private:
	int house_no;
	string address;
	int bedrooms;
	float bathrooms;
	int price;
	int square_footage;


public:
	House()
	{
		house_no = 0;
		address = "";
		bedrooms = 0;
		bathrooms = 0;
		price = 0;
		square_footage = 0;
	}
	House(int house_no, string address, int bedrooms, float bathrooms, int price, int square_footage)
	{
		house_no = house_no;
		address = address;
		bedrooms = bedrooms;
		bathrooms = bathrooms;
		price = price;
		square_footage = square_footage;

	}

	int getHouseNo();
	string getAddress();
	int getBedrooms();
	float getBathrooms();
	int getPrice();
	int getSquareFootage();

	void setHouseNo(int h_no);
	void setAddress(string add);
	void setBedrooms(int bed);
	void setBathrooms(float bath);
	void setPrice(int pr);
	void setSquareFootage(int sq_ft);
	void printHouse();

	friend istream& operator >>(istream& ip, House &val);
	friend ostream& operator <<(ostream& op, House &val);
	friend bool operator== (const House &valone, const House &valtwo);
};

#endif /* House_h */
