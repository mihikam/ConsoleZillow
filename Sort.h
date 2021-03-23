#pragma once
/*

Written by Jason and Rasya
12/2/2018

*/


#include "iostream"
#include "fstream"
#include "Array.h"

/**
* partition puts all that is smaller than
* the pivot to the right and all that is
* larger to the left
* @param  { &Array } arr
* @param  { Int } low  [the start index]
* @param  { Int } high [the end index]
* @return { Int }      [the index of the item that is in the right place]
*/
template<class T>
int partition(Array<T> &arr, int low, int high) {

	// set the pivot as the last element
	T* pivot = arr[high];

	// Index of the bound of larger elements
	int index = low - 1;

	// group larger element to the left
	for (int j = low; j <= high - 1; j++) {

		// If current element is larger than or equal to pivot
		// swap it to the left
		if (arr.compareValues(arr[j], pivot)) {
			index++;

			T* tmp = arr[index];
			arr[index] = arr[j];
			arr[j] = tmp;
		}
	}

	// swap the pivot to the right position
	// which is right after the bound
	T* tmp = arr[index + 1];
	arr[index + 1] = arr[high];
	arr[high] = tmp;

	return (index + 1);
}

/**
* quick sort
* @param { &Array } arr
* @param { Int } low  [the index of start]
* @param { Int } high [the index of end]
*/
//template<class T>
/*void quickSort(Array<T> &arr, int low, int high, std::ofstream &outFile) {
if (low < high) {
// pi is partitioning index, arr[pi] is now at right place
int pi = partition(arr, low, high);

// Separately sort elements before partition and after partition
quickSort(arr, low, pi - 1, outFile);
quickSort(arr, pi + 1, high, outFile);
}

// print status of every step
std::cout << "Step: " << arr << std::endl;
outFile << "Step: " << arr << std::endl;
}*/

template<class T>
void quickSort(Array<T> &arr, int low, int high) {
	if (low < high) {
		// pi is partitioning index, arr[pi] is now at right place
		int pi = partition(arr, low, high);

		// Separately sort elements before partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}

	// print status of every step
	//std::cout << "Step: " << arr << std::endl;
}
