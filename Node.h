//
//  Node.hpp
//  LabTwo
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created by Mihika Marathe on 10/16/18.
//  Copyright © 2018 Mihika Marathe. All rights reserved.
//
#pragma once
#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <iostream>

template<class T>
class Node
{
private:
	T data;
	Node<T>* next;
public:
	Node()
	{
		next = nullptr;
	}
	void setData(T d);
	void setNext(Node<T>* node);
	T getData();
	Node<T>* getNext();
};

/*
Description: This method sets the data part of the node to the value of type T passed.
Pre: Data of type d.
Post: Changes the contents of the Node.
Return:
*/
template<typename T>
void Node<T>::setData(T d)
{
	data = d;
}

/*
Description: This method sets the pointer part of the node to the node passed of type T.
Pre: Node of type T.
Post: Changes the pointer of the Node.
Return:
*/
template<typename T>
void Node<T>::setNext(Node<T>* node)
{
	next = node;
}

/*
Description: This method returns the data the node contains.
Pre:
Post:
Return: Data the node contains of type T.
*/
template<typename T>
T Node<T>::getData()
{
	return data;
}

/*
Description: This method returns the Node the pointer of the Node points to.
Pre:
Post:
Return: Node that the Node that calls it points to of type T.
*/
template<typename T>
Node<T>* Node<T>::getNext()
{
	return next;
}

#endif /* Node_hpp */
