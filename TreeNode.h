//
//  TreeNode.hpp
//  CIS22C Project
////  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Created by Mihika Marathe on 11/19/18.
//  Copyright © 2018 Mihika Marathe. All rights reserved.
//
#pragma once
#ifndef TreeNode_hpp
#define TreeNode_hpp

#include <stdio.h>
#include "Node.h"
#include <string>

template<typename T>
class TreeNode : public Node<T>
{
private:
	TreeNode<T>* left;
	TreeNode<T>* right;
public:
	TreeNode() : Node<T>()
	{
		left = nullptr;
		right = nullptr;
	}
	void setLeft(TreeNode<T> * node);
	void setRight(TreeNode<T> * node);
	TreeNode<T>* getRight();
	TreeNode<T>* getLeft();
	bool isLeaf();

};

/*
Description: This method sets the right pointer of the node to the node that is passed.
Pre: Node of type T.
Post:
Return: The right pointer of the node that called the function now points to the passed node.
*/
template<typename T>
void TreeNode<T>::setRight(TreeNode<T>* node)
{
	right = node;
}

/*
Description: This method sets the right pointer of the node to the node that is passed.
Pre: Node of type T.
Post:
Return: The right pointer of the node that called the function now points to the passed node.
*/
template<typename T>
void TreeNode<T>::setLeft(TreeNode<T>* node)
{
	left = node;
}

/*
Description: This method returns the Node the right pointer points to.
Pre:
Post:
Return: A node that the node that called the method points to.
*/
template<typename T>
TreeNode<T>* TreeNode<T>::getRight()
{
	return right;
}

/*
Description: This method returns the Node the right pointer points to.
Pre:
Post:
Return: A node that the node that called the method points to.
*/
template<typename T>
TreeNode<T>* TreeNode<T>::getLeft()
{
	return left;
}

/*
Description: This returns whether or not the Node is a leaf by checking if the right/left pointers are null.
Pre:
Post:
Return: True or false depending on whether the node is a leaf.
*/
template<typename T>
bool TreeNode<T>::isLeaf()
{
	if (right == nullptr && left == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif /* TreeNode_hpp */

