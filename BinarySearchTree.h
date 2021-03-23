#pragma once
//
//  BinarySearchTree.hpp
//  CIS22C Project
//
//  Created by Mihika Marathe on 11/19/18.
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright © 2018 Mihika Marathe. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "TreeNode.h"
#include <cmath>
#include "BinaryNodeTree.h"


using namespace std;

template<typename T>
class BinarySearchTree : public BinaryNodeTree<T>
{
private:
	TreeNode<T>* root;
public:
	BinarySearchTree();
	BinarySearchTree(T& data);
	BinarySearchTree(BinarySearchTree<T>& tree);

	virtual ~BinarySearchTree();

	TreeNode<T>* insertInorder(TreeNode<T> *pSRoot, TreeNode<T>* pNode, bool& success, int type);

	virtual TreeNode<T>* removeValue(TreeNode<T> *pSRoot, T target, bool &success, int type);

	TreeNode<T>* removeNode(TreeNode<T> *pNode);
	TreeNode<T>* removeLeftMostNode(TreeNode<T> * pSRoot, T& data);
	void setLeftMostParent(TreeNode<T> * parent, TreeNode<T> * child, T& data);

	virtual TreeNode<T>* findNode(TreeNode<T>* tree, T& target, int type, int& level);

	int getDepth(TreeNode<T> *pRoot, T target, int type);

	TreeNode<T>* getRoot();

	void setRootData(T& data);

	int compareValues(T one, T two, int type);

	virtual bool add(T& data, int type);
	virtual bool remove(T& data, int type);

	void printIndentedTree(TreeNode<T>* node, int type);
	void printByWidth(T data, int level, int pos, int& prevpos);

	void printIndentedTreeHorizontally(TreeNode<T> *node, int type, int depth);
	void printHorizontalData(T data, int level, int type);
};

/*
Description: This method is the default constructor for Binary Search Tree.
Pre:
Post: It creates a binary search tree with default settings.
Return:
*/
template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
}

/*
Description: This method returns the data the node contains.
Pre:
Post:
Return: Data the node contains of type T.
*/
template<typename T>
BinarySearchTree<T>::BinarySearchTree(T& data)
{
	root = new TreeNode<T>(data, nullptr, nullptr);
}

/*
Description: This is the copy constructor for the tree.
Pre:
Post: A tree indentical to the one sent as a parameter is created.
Return:
*/
template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>& tree)
{

}

/*
Description: This adds nodes in the correct order to the binary tree. Since different attributes of the object are used, it takes in a type and uses compareValues() to compare the objects.
Pre: The root of the tree/subtree to which the node needs to be added.
Post: The tree pointer to the tree containing the new node is sent back.
Return: A tree node containint
*/
template<typename T>
TreeNode<T>* BinarySearchTree<T>::insertInorder(TreeNode<T> *pSRoot, TreeNode<T>* pNode, bool& success, int type)
{
	BinaryNodeTree<T>::incrementEfficiency();
	TreeNode<T>* temp;
	if (pSRoot == nullptr)
	{
		return pNode;
	}
	else if (compareValues(pSRoot->getData(), pNode->getData(), type) == 1)
	{
		temp = insertInorder(pSRoot->getLeft(), pNode, success, type);
		pSRoot->setLeft(temp);
	}
	else
	{
		temp = insertInorder(pSRoot->getRight(), pNode, success, type);
		pSRoot->setRight(temp);
	}
	return pSRoot;
}

/*
Description: This is the copy constructor for the tree.
Pre:
Post: A tree indentical to the one sent as a parameter is created.
Return:
*/
template<typename T>
TreeNode<T>* BinarySearchTree<T>::getRoot()
{
	return root;
}

/*
Description: This method sets the root data.
Pre:
Post:
Return:
*/
template<typename T>
void BinarySearchTree<T>::setRootData(T& data)
{
	root->setData(data);
}

/*
Description: This method adds values to the binary tree of the type specified by calling the insert in order method. It first creates a new node, assigns it the passed data, and sents it to insertinorder().
Pre: Data to be added and the type it is to be compared by.
Post: The tree now contains a new node containing the data passed.
Return:
*/
template<typename T>
bool BinarySearchTree<T>::add(T& data, int type)
{
	bool success = false;
	TreeNode<T> * pNewNode = new TreeNode<T>();
	pNewNode->setData(data);
	root = insertInorder(root, pNewNode, success, type);
	return true;
}

/*
Description: This method is used to compare values since it is a template class and the type of the object is unspecified. It passes a type the  methods to access the needed methods are called based on that. It returns 1 for greater than, 2 for equal to, and 3 for less than or if the value is duplicated since it will still be in the left tree.
Pre: The two objects of type T to be compared.
Post:
Return: Integer based on comparison.
*/
template<typename T>
int BinarySearchTree<T>::compareValues(T one, T two, int type)
{
	switch (type)
	{
	case 1:
		if (one.getPrice() > two.getPrice())
			return 1;
		else if (one.getPrice() == two.getPrice() && (one.getHouseNo() == two.getHouseNo()))
			return 2;
		else
			return 3;
	case 2:
		if (one.getSquareFootage() > two.getSquareFootage())
			return 1;
		else if (one.getSquareFootage() == two.getSquareFootage() && ((one.getHouseNo() == two.getHouseNo())))
			return 2;
		else
			return 3;
	}
	return 0;
}

/*
Description: This method removes a node from the tree by calling remoove value for the passed data.
Pre: Data to be deleted, type of tree.
Post: The node is deleted from the tree.
Return: Boolean based on whether the operation was succesful.
*/
template<typename T>
bool BinarySearchTree<T>::remove(T& data, int type)
{
	bool success = false;
	root = removeValue(root, data, success, type);
	return success;

}

/*
Description: This method works with the other removal methods to remove a node from the tree. It searches the tree and calls methods accordingly. If it is a nullptr, it returns nullptr. If the data matches, it calls remove node and passes the matching node. The resulting subtree is set to psRoot and it is returned. If the target is less than, the method calls itself and sends it a pointer to the left tree. It does the same with the right subtree if it is greater than.
Pre: Root or subtee root to search from, data to remove, success, and type of tree.
Post: The node is deleted from the tree.
Return: Pointer containing modified tree.
*/
template<typename T>
TreeNode<T>* BinarySearchTree<T>::removeValue(TreeNode<T> *pSRoot, T target, bool &success, int type)
{
	BinaryNodeTree<T>::incrementEfficiency();
	TreeNode<T>* pTemp;
	if (pSRoot == nullptr)
	{
		success = false;
		return nullptr;
	}
	else if (compareValues(pSRoot->getData(), target, type) == 2)
	{
		pSRoot = removeNode(pSRoot);
		success = true;
		return pSRoot;
	}
	else if (compareValues(pSRoot->getData(), target, type) == 1)
	{
		pTemp = removeValue(pSRoot->getLeft(), target, success, type);
		pSRoot->setLeft(pTemp);
		return pSRoot;
	}
	else
	{
		pTemp = removeValue(pSRoot->getRight(), target, success, type);
		pSRoot->setRight(pTemp);
		return pSRoot;
	}
}

/*
Description: This method determines what the node to be deleted needs to be replaced with, replaces it with the help of other methods, and deletes the extra node.
Pre: The node to be deleted.
Post: The node to be deleted is replaced by it's inorder succesor.
Return: Node replacement.
*/
template<typename T>
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T> *pNode)
{
	BinaryNodeTree<T>::incrementEfficiency();
	TreeNode<T>* pTemp;
	TreeNode<T>* pConnection;
	T newData;
	// node has no children
	if (pNode->isLeaf())
	{
		delete pNode;
		pNode = nullptr;
		return pNode;
	}
	// node only has a left child, replaces node with the left child.
	else if (pNode->getLeft() != nullptr && pNode->getRight() == nullptr)
	{
		pConnection = pNode->getLeft();
		delete pNode;
		pNode = nullptr;
		return pConnection;
	}
	// node only has a right child, replaces node with the right child.
	else if (pNode->getLeft() == nullptr && pNode->getRight() != nullptr)
	{
		pConnection = pNode->getRight();
		delete pNode;
		pNode = nullptr;
		return pConnection;
	}
	// node has two children and the left of the right child is a nullptr
	else if ((pNode->getRight())->getLeft() == nullptr)
	{
		pTemp = removeLeftMostNode(pNode->getRight(), newData);
		pNode->setRight(pTemp);
		pNode->setData(newData);
		return pNode;
	}
	// node has two children so finds leftmost of right child
	else
	{
		TreeNode<T> * l = pNode->getRight();
		T d;
		setLeftMostParent(l, l->getLeft(), d);
		pNode->setData(d);
		return pNode;
	}
}

/*
Description: This method removes the left
Pre: The node to be deleted.
Post: The node to be deleted is replaced by it's inorder succesor.
Return: Node replacement.
*/
template<typename T>
TreeNode<T>* BinarySearchTree<T>::removeLeftMostNode(TreeNode<T> * pSRoot, T& data)
{
	BinaryNodeTree<T>::incrementEfficiency();
	if (pSRoot->getLeft() == nullptr)
	{
		data = pSRoot->getData();
		return removeNode(pSRoot);
	}
	else
		return removeLeftMostNode(pSRoot->getLeft(), data);
}

/*
Description: This sets the parent of the left most child to the right pointer of the left most child and deletes the left most node by calling removenode and sending the child. It also sets the data to that of left most node.
Pre: Parent node and its' left child.
Post: The left pointer of the parent is the same as the right pointer of left most node.
Return:
*/
template<typename T>
void BinarySearchTree<T>::setLeftMostParent(TreeNode<T> * parent, TreeNode<T> * child, T& data)
{
	BinaryNodeTree<T>::incrementEfficiency();
	if (child->getLeft() == nullptr)
	{
		data = child->getData();
		parent->setLeft(removeNode(child));
	}
	else
		setLeftMostParent(child, child->getLeft(), data);
}

/*
Description: This method finds the node containing the data passed and returns it. It searches using compareValues by the type passed.
Pre: Root/subtree pointer, data to be found, type to be compared by.
Post:
Return: The node containing the data.
*/
template<typename T>
TreeNode<T>* BinarySearchTree<T>::findNode(TreeNode<T> *tree, T& target, int type, int& level)
{
	level++;
	if (tree == nullptr)
	{
		return nullptr;
	}
	else if (compareValues(tree->getData(), target, type) == 2)
	{
		return tree;
	}
	else if (compareValues(tree->getData(), target, type) == 1)
	{
		return findNode(tree->getLeft(), target, type, level);
	}
	else
		return findNode(tree->getRight(), target, type, level);
}

/* This method returns the depth of the node passed to it. Findnode keeps a track of the level so it sends findNode the value to be found
and an integer by reference to get the depth. 
Pre: Root/root of subtree, target of type T, type of tree.
Post: 
Return: The depth is returned.
*/
template<typename T>
int BinarySearchTree<T>::getDepth(TreeNode<T> *pRoot, T target, int type)
{
	int temp = 0;
	findNode(pRoot, target, type, temp);
	return temp;
}

/* This method prints the binary search tree verticlly using a breadth first traversal. It keeps track of the position and depth to better 
format the print.
Pre: Root of the tree/subtrees, the type of tree.
Post: Indented tree printed to console.
Return:
*/
template<typename T>
void BinarySearchTree<T>::printIndentedTree(TreeNode<T>* node, int type)
{
	Queue<TreeNode<T>*> que;
	Queue<int> position;
	int prevpos = 0;
	int levels = 0;
	if (node != nullptr)
		que.enqueue(node);
	//cout << setw(50) << node->getData().getHouseNo() << endl;
	printByWidth(node->getData(), 0, 1, prevpos);
	position.enqueue(1);
	levels++;
	cout << endl;
	while (node != nullptr)
	{
		if (node->getLeft() != nullptr)
		{
			que.enqueue(node->getLeft());
			position.enqueue(position.getFront() * 2 - 1);
			printByWidth(que.getRear()->getData(), getDepth(root, que.getRear()->getData(), type), position.getRear(), prevpos);
			prevpos = position.getRear();
			//leftfirst = false;
			//cout << que.getRear();
		}
		if (node->getRight() != nullptr)
		{
			T data = node->getRight()->getData();
			findNode(root, data, 1, levels);
			que.enqueue(node->getRight());
			position.enqueue(position.getFront() * 2);
			printByWidth(que.getRear()->getData(), getDepth(root, que.getRear()->getData(), type), position.getRear(), prevpos);
			prevpos = position.getRear();
		}
		que.dequeue();
		if (!que.isEmpty())
		{
			if (getDepth(root, que.getFront()->getData(), type) > getDepth(root, node->getData(), type))
			{
				cout << endl;
				prevpos = 0;
			}
			position.dequeue();
			node = que.getFront();
		}
		else
			node = nullptr;

	}

}


/* This method formats and prints each value based on the depth and position. It also accounts for values the tree does not have and prints
space accordingly.
Pre: The data, the depth, the position, and the previous position.
Post: Formatted value printed to console.
Return:
*/
template<typename T>
void BinarySearchTree<T>::printByWidth(T data, int level, int pos, int& prevpos)

{
	int width = 1024 / pow(2, level);
	if (prevpos == 0 && pos == 1)
	{
		cout << setw(width / 2) << data.getHouseNo();;
		return;
	}

	else if (pos != prevpos + 1)
	{
		if (prevpos == 0)
		{
			cout << setw(width / 2) << " ";
			prevpos++;
		}
		for (int i = prevpos; i < pos - 1; i++)
		{
			cout << setw(width) << " ";
		}
	}
	cout << setw(width) << data.getHouseNo();
	//count++;

}

/* This method prints the binary search tree horizontally traversing it right first, node, and then left. It calls print horizontal data to print
it and formats it using the depth of the node.
Pre: Root of the tree/subtrees, the type of tree, and the depth of the node.
Post: Indented tree printed to console.
Return:
*/
template<typename T>
void BinarySearchTree<T>::printIndentedTreeHorizontally(TreeNode<T> *node, int type, int depth)
{
	const int h = BinaryNodeTree<T>::getHeightHelper(root);
	if (node != nullptr)
	{
		printIndentedTreeHorizontally(node->getRight(), type, getDepth(root, node->getData(), type));
		T data = node->getData();
		int depth = getDepth(root, data, type);
		printHorizontalData(data, depth, type);
		printIndentedTreeHorizontally(node->getLeft(), type, getDepth(root, node->getData(), type));
	}
}

/* This method prints data passed to it based on the depth. 
Pre: data to print and level.
Post: Prints formatted value to console.
Return:
*/
template<typename T>

void BinarySearchTree<T>::printHorizontalData(T data, int level, int type)

{
	if (type == 1)
	{
		cout << setw(level * 10) << data.getPrice() << endl;
		cout << endl;
	}
	else if (type == 2)
	{
		cout << setw(level * 10) << data.getSquareFootage() << endl;
		cout << endl;
	}
}




/*
Description: This is the destructor for binary search tree. It calls the destroy tree method in binary node tree to delete it.
Pre:
Post: The tree is deleted.
Return:
*/
template<typename T>
BinarySearchTree<T>::~BinarySearchTree<T>()
{
	BinaryNodeTree<T>::destroyTree(root);
}

#endif /* BinarySearchTree_hpp */
