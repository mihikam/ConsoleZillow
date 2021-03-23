//
//  Queue.hpp
//  LabTwo
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created by Mihika Marathe on 10/21/18.
//  Copyright © 2018 Mihika Marathe. All rights reserved.
//
#pragma once
#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include "Node.h"

template <typename Q>
class Queue
{
private:
	int count;
	Node<Q>* front;
	Node<Q>* rear;
public:
	Queue()
	{
		front = nullptr;
		rear = nullptr;
		count = 0;
	}
	void enqueue(Q d);
	void dequeue();
	Q getFront();
	Q getRear();
	bool isEmpty();
	~Queue();
};

/*
Description: This method adds a new node to the end queue.
Pre: Data of type d.
Post: Changes the rear of the queue to the new value,.
Return:
*/
template<typename Q>
void Queue<Q>::enqueue(Q d)
{
	Node<Q> * newNode;
	Node<Q> * tempNode;
	newNode = new Node<Q>;
	newNode->setData(d);
	newNode->setNext(nullptr);
	if (count == 0)
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		tempNode = front;
		while (tempNode->getNext() != nullptr)
		{
			tempNode = tempNode->getNext();
		}
		tempNode->setNext(newNode);
		rear = newNode;
	}
	count++;

}

/*
Description: This method adds a removes a node from the queue (the front).
Pre: Data of type d.
Post: Removes the front and assigns the next node to front.
Return:
*/
template <typename Q>
void Queue<Q>::dequeue()
{
	Node<Q> *tempNode;
	if (count == 0)
	{
		cout << "There are no elements in the stack.";
	}
	else if (count == 1)
	{
		delete front;
		count = 0;
	}
	else
	{
		if (count != 0)
		{
			tempNode = front->getNext();
			delete front;
			front = tempNode;
			count--;
		}
	}

}

/*
Description: This method returns the data the front contains.
Pre:
Post:
Return: Data the front node contains of type Q.
*/
template <typename Q>
Q Queue<Q>::getFront()
{
	return front->getData();
}

/*
Description: This method returns the data the rear contains.
Pre:
Post:
Return: Data the rear node contains of type Q.
*/
template <typename Q>
Q Queue<Q>::getRear()
{
	return rear->getData();

}

/*
Description: This method returns whether or not the queue is empty.
Pre:
Post:
Return: True if it is empty, else if not.
*/
template<typename Q>
bool Queue<Q>::isEmpty()
{
	if (count <= 0)
	{
		return true;
	}
	else {
		return false;
	}
}

/*
Description: This method deconstructs the queue. It uses the dequeue method until count id 0.
Pre:
Post: The list is deleted.
Return:
*/
template<typename Q>
Queue<Q>:: ~Queue<Q>()
{
	while (count > 0)
	{
		dequeue();
		count--;
	}
}


#endif /* Queue_hpp */

