#pragma once
#include <iostream>

using namespace std;

template<class T>
class Array {
private:
	int size;
	T** myArray;
	int currentSize;

public:
	// constructor with user pre-defined size
	Array(int size) {
		this->size = size;
		this->myArray = new T*[size];
		currentSize = 0;
	}

	int getCurrentSize() { return currentSize; }

	// copy constructor
	Array(const Array &origin) {
		this->size = origin.size;
		// copy every element to new array
		this->myArray = new T[size];
		for (int i = 0; i < this->size; i++) {
			set(i, origin.get(i));
		}
	}

	// destructor
	// delete myArray to prevent memory leak
	~Array() {
		delete[] this->myArray;
	}

	int getSize() { return size; }

	//set element value at a position
	void set(T& val) {
		myArray[currentSize] = val;
		currentSize++;
	}

	//get the element value from a position
	T* get(int i) const {
		return myArray[i];
	}

	// operator overloads
	T &operator [] (int index) {
		return this->myArray[index];
	}

	// This method returns whether or not two houses are equal.
	bool isEqual(House* house1, House* house2)
	{
		if (house1 == house2)
			return true;
		return false;
	}

	bool compareValues(House* house1, House* house2)
	{
		if (house1->getHouseNo() >= house2->getHouseNo())
			return true;
		return false;
	}

	/*
	Description: Takes an address and inserts its data into it's correct place in the array
	Pre: an ordered array from greatest to least
	Post: an ordered array from greatest to least
	Return: Success of function
	*/
	bool insertInOrder(House &value)
	{
		bool flag = false;
		House* current = &value;

		if (currentSize == 0)
		{
			myArray[currentSize] = current;
			flag = true;
		}

		for (int i = 0; i < currentSize; i++)
		{
			//if value is not the smallest value
			if (compareValues(current, myArray[i]))
			{
				T *temp = myArray[i];
				myArray[i] = current;
				for (int j = i + 1; j < currentSize + 1; j++)
				{
					current = temp;
					temp = myArray[j];
					myArray[j] = current;
				}
				flag = true;
				break;
			}
			//if it's the smallest value in the array
			else if (i == currentSize - 1)
			{
				myArray[currentSize] = &value;
				flag = true;
			}
		}



		currentSize++;

		return flag;
	}

	/*
	Description: Remove an entry from the array
	@pre An ordered array
	@post an ordered array with a value removed
	*/
	bool deleteValue(House &value)
	{
		bool flag = false;
		for (int i = 0; i < currentSize; i++)
		{
			if (isEqual(&value, myArray[i]))
			{
				flag = true;
				for (int j = i; j < currentSize; j++)
				{
					myArray[j] = myArray[j + 1];
				}
				currentSize--;
				return flag;
			}
		}
		return false;
	}




	template <class U>
	friend istream &operator >> (istream&, Array<U>&);

	template <class U>
	friend ostream &operator << (ostream&, const Array<U>&);
	/*
	Description: This method parses and prints the contents of the array.
 
	*/
	void displayArray()
	{
		for (int i = 0; i < currentSize; i++)
		{
			cout << *get(i) << endl;
		}
	}
};

/*
Description: This method overloads the input operator for array objects. When it is called, data is read in, 
validated, and added to the array.
Parameters: Input stream and the array of type U.
Pre:
Post: Values are added to the array.
*/
template <class U>
istream &operator >> (istream &io, Array<U> &arr) {
	U data;
	for (int i = 0; i < arr.size; i++) {
		cout << "Please input item " << i + 1 << ": ";
		io >> data;

		while (!io.good()) {
			io.clear();
			io.ignore(1024, '\n');

			cout << "Invalid type! Please retry: ";
			io >> data;
		}

		arr.set(i, data);
	}

	return io;
}


/*
Description: This method overloads the output operator for array objects. When it is called, the data is formatted for output,
specifically, commas are added between each value.
Parameters: Output stream and the array of type U.
Pre:
Post: The contents of the array are outputted.
*/
template <class U>
ostream &operator << (ostream &io, const Array<U> &arr) {
	for (int i = 0; i < arr.size; i++) {
		io << arr.myArray[i];

		if (i != arr.size - 1) {
			io << ", ";
		}
	}

	return io;
}










