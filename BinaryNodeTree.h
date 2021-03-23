#pragma once
////
//  BinaryTree.hpp
//  CIS22C Project
//
//  Created by Mihika Marathe on 11/19/18.
//  Created by Rasya, Arjun, Brian, Jason, Mihika on 12/4/18.
//  Copyright � 2018 Mihika Marathe. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include "TreeNode.h"
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include "minmax.h"


template<typename T>
class BinaryNodeTree
{
private:
	TreeNode<T>* root;
	int efficiency;
public:
	BinaryNodeTree();
	BinaryNodeTree(T& data, TreeNode<T>* left, TreeNode<T>* right);
	BinaryNodeTree(BinaryNodeTree<T>* tree);
	~BinaryNodeTree();

	TreeNode<T>* getRoot();
	void setRoot(TreeNode<T>* ptr);

	void resetEfficiency();
	int getEfficiency(TreeNode<T>* pRoot);
	void incrementEfficiency();

	int getHeightHelper(TreeNode<T>* node);
	int getHeight();

	int getNumNodesHelper(TreeNode<T>* node);
	int getNumNodes();

	bool isEmpty();

	TreeNode<T>* balancedAdd(TreeNode<T> * r, TreeNode<T>*  newNode, bool& success);
	bool add(T& data);

	bool removeValue(TreeNode<T>* node, T data, bool& success);
	TreeNode<T>* moveValuesUpTree(TreeNode<T>* node);
	bool remove(T& data);

	TreeNode<T>* findNode(TreeNode<T>* node, T& data, bool& success);
	T getEntry(T data);
	bool contains(T data);

	TreeNode<T>* copyTree(TreeNode<T>* node);

	void destroyTree(TreeNode<T>* node);

	void preorder(TreeNode<T>* node);
	void inorder(TreeNode<T>* node, int min, int max, int type);
	void postorder(TreeNode<T>* node);
	void breadthFirst(TreeNode<T>* node);
	void visitone(T data, int min, int max);
	void visittwo(T data, int min, int max);

	
};

/*
Description: This is the default constructor of the Binary Tree.
Pre:
Post: The class variable, root is set to a default pointer.
Return:
*/
template<typename T>
BinaryNodeTree<T>::BinaryNodeTree()
{
	root = nullptr;
	efficiency = 0;
}

/*
Description: This method sets the data componenet of root to the data passed and the pointers to left and right.
Pre: The parameters include the data that is to be set, and the pointers the node should point to.
Post: Root is now equivalent to a node containing the data passed and pointing to the nodes passed.
Return:
*/

template<typename T>
BinaryNodeTree<T>::BinaryNodeTree(T& data, TreeNode<T>* left, TreeNode<T>* right)
{
	root = new TreeNode<T>(data, left, right);
	efficiency = 0;
}


/*
Description: This is a copy constructor for binary tree. It calls copytree and passes the root to it.
Pre: It takes in a tree to make a copy of.
Post: A tree that is a copy of the passed tree is created.
Return: Node that the Node that calls it points to of type T.
*/

template<typename T>
BinaryNodeTree<T>::BinaryNodeTree(BinaryNodeTree<T>* tree)
{
	root = copyTree(tree->getRoot());
	efficiency = 0;
}

/*
Description: This method returns root pointer contains.
Pre:
Post:
Return: Node that the Node that calls it points to of type T.
*/

template<typename T>
TreeNode<T>* BinaryNodeTree<T>::getRoot()
{
	return root;
}

/*
Description: This method sets the data of the root.
Pre: The data to set the root to.
Post: The root now contains the data passed.
Return:
*/

template<typename T>
void BinaryNodeTree<T>::setRoot(TreeNode<T>* ptr)
{
	root = ptr;
}


/*
Description: This method resets the efficiency of the tree.
Pre: the previous efficiency calculated.
Post: the efficiency is set to 0.
Return: None.
*/
template<typename T>
void BinaryNodeTree<T>::resetEfficiency()
{
	efficiency = 0;
}

/*
Description: This method returns the efficiency of the tree.
Pre: pRoot- the root of the tree
Post: 
Return: the efficiency of the tree.
*/
template<typename T>
int BinaryNodeTree<T>::getEfficiency(TreeNode<T>* pRoot)
{
	return efficiency;

}

/*
Description: This method increments the efficiency of the tree.
Pre: the efficiency of the tree
Post: the efficiency is incremented.
Return: none
*/

template<typename T>
void BinaryNodeTree<T>::incrementEfficiency()
{
	efficiency++;
}
/*
Description: This method recursively finds the height of the tree. It checks whether the left or right side of the tree gives a greater height and returns the greater one. One is added at each step to keep a tally.
Pre: The root pointer of the tree or subtree whose height is being calculated is passed.
Post:
Return: The height of the tree.
*/
template<typename T>
int BinaryNodeTree<T>::getHeightHelper(TreeNode<T> *node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + max(getHeightHelper(node->getLeft()), getHeightHelper(node->getRight()));
	}
}

/*
Description: This method calls the method that recursively calculates the height.
Pre:
Post:
Return: Integer representing the height.
*/
template<typename T>
int BinaryNodeTree<T>::getHeight()
{
	return getHeightHelper(root);
}

/*
Description: This method recursively checks the number of nodes in the tree.
Pre: The root pointer is passed to it.
Post:
Return: An integer representing the number of nodes.
*/
template<typename T>
int BinaryNodeTree<T>::getNumNodesHelper(TreeNode<T>* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else if (node->getLeft() != nullptr && node->getRight() != nullptr)
	{
		return 1 + getNumNodesHelper(node->getLeft()) + getNumNodesHelper(node->getRight());
	}
	else if (node->getLeft() != nullptr)
	{
		return 1 + getNumNodesHelper(node->getLeft());
	}
	else
	{
		return 1 + getNumNodesHelper(node->getRight());
	}
}

/*
Description: This method calls the recursive method that finds the number of nodes.
Pre:
Post:
Return: An integer representing the number of nodes.
*/
template<typename T>
int BinaryNodeTree<T>::getNumNodes()
{
	return getNumNodesHelper(root);
}

/*
Description: This method checks whether the tree is empty by checking if the roots left/right pointers are null or not.
Pre:
Post:
Return: True if it's empty, false if not.
*/
template<typename T>
bool BinaryNodeTree<T>::isEmpty()
{
	if (root == nullptr)
		return true;
	else
		return false;
}

/*
Description: This method adds nodes to the binary tree in a balanced fashion recursively. It checks the height on each side and moves toward the side with a smaller height.
Pre: It takes the root node and the new node as a parameter.
Post: It adds the new node to the correct position.
Return:
*/
template<typename T>
TreeNode<T>* BinaryNodeTree<T>::balancedAdd(TreeNode<T>* r, TreeNode<T>* newNode, bool& success)
{
	if (r == nullptr)
	{
		return newNode;
	}
	else
	{
		TreeNode<T>* left = r->getLeft();
		TreeNode<T>* right = r->getRight();

		if (getHeightHelper(left) > getHeightHelper(right))
		{
			right = balancedAdd(right, newNode, success);
			r->setRight(right);
		}
		else
		{
			left = balancedAdd(left, newNode, success);
			r->setLeft(left);
		}
	}
	success = true;
	return r;
}

/*
Description: This method adds a node to the tree. It dynamically allocates a new treenode pointer and calls balancedAdd to recursively add it.
Pre: It takes in the data the new node is supposed to contain.
Post:
Return: Boolean, whether or not the data was succesfully added.
*/
template<typename T>
bool BinaryNodeTree<T>::add(T& data)
{
	bool success = false;
	TreeNode<T>* newNode = new TreeNode<T>();
	newNode->setData(data);
	root = balancedAdd(root, newNode, success);
	return success;
}

/*
Description: This method removes the node containing the data passed.
Pre: It takes in the root, data, and a boolean variable to success to check whether or not the node was deleted.
Post: The node is deleted from the tree if it points go a subtree, it is moved up. It calls moveVsluesUpTree() to do this.
Return: Node that the Node that calls it points to of type T.
*/
template<typename T>
bool BinaryNodeTree<T>::removeValue(TreeNode<T>* node, T data, bool& success)
{
	bool s;
	node = findNode(node, data, s);
	if (node == nullptr)
	{
		success = false;
	}
	else
	{
		node = moveValuesUpTree(node);
		success = true;
	}
	return success;

}


/*
Description: This method replaces the node that is to be deleted. It copies values upwards as it moves down and deletes the leaf. It checks first for a left node, then a right node. If a node exists, it copies it to the current node and sets the pointer to the next call of the function which returns what the node that was moved up points to.
Pre: It takes in the node that is to be deleted as the root of the subtree to move up.
Post:
Return: Node pointer containing subtree.
*/

template<typename T>
TreeNode<T>* BinaryNodeTree<T>::moveValuesUpTree(TreeNode<T> *node)
{
	TreeNode<T> * temp = node;
	if (node->isLeaf())
	{
		delete node;
		temp = nullptr;
	}
	else if (node->getLeft() != nullptr)
	{

		temp->setData((node->getLeft())->getData());
		temp->setLeft(moveValuesUpTree(node->getLeft()));
		//node = temp;
	}
	else if (node->getRight() != nullptr)
	{
		temp->setData((node->getRight())->getData());
		temp->setLeft(moveValuesUpTree(node->getRight()));
		//node = temp;
	}
	return temp;
}


/*
Description: This method calls the remove value function passing it the data to be deleted.
Pre: This method takes in the data to be deleted.
Post: The node is deleted from the tree and a subtree is moved up.
Return: True/false depending on whether or not the deletion was completed.
*/

template<typename T>
bool BinaryNodeTree<T>::remove(T& data)
{
	bool success = false;
	removeValue(root, data, success);
	return success;

}


/*
Description: This method finds the node whose data is passed to the function. It recursively checks the left and right side as at moves down the tree.
Pre: It takes in the root node, the data to be found, and success to determine whether or not it was found.
Post:
Return: Node that contains the data.
*/

template<typename T>
TreeNode<T>* BinaryNodeTree<T>::findNode(TreeNode<T>* node, T& data, bool& success)
{
	if (node != nullptr || node->isLeaf())
	{
		if (node->getData() == data)
		{
			success = true;
		}
		else if (node->getLeft() != nullptr)
		{
			node = findNode(node->getLeft(), data, success);
		}
		else if (node->getRight() != nullptr)
		{
			node = findNode(node->getRight(), data, success);
		}
		return node;
	}
	else
	{
		success = false;
		return nullptr;
	}
}



/*
Description: This method creates a new node containing the data passed and calls balancedAdd to add it in it's proper place in the tree.
Pre: It takes in the data the new node is supposed to contain.
Post:
Return: Node that the Node that calls it points to of type T.
*/
template<typename T>
T BinaryNodeTree<T>::getEntry(T data)
{
	bool success = false;
	TreeNode<T> temp = findNode(root, data, success);
	return temp;

}


/*
Description: This method calls findNode to determine whether the tree contains the data passed.
Pre: It takes in the data that is to be searched for.
Post:
Return: True or false, whether or not it was found.
*/

template<typename T>
bool BinaryNodeTree<T>::contains(T data)
{
	bool success = false;
	findNode(root, data, success);
	return success;
}


/*
Description: This method copies the tree using the treenode pointer passed to it which points to the tree or subtree. It calls itself to move down the tee ,accessing all the left and right pointers.
Pre: t takes in the root of the tree to be copied.
Post:
Return: Tree node pointer that contains the copied tree.
*/
template<typename T>
TreeNode<T>* BinaryNodeTree<T>::copyTree(TreeNode<T> * oldTree)
{
	TreeNode<T>* newTree = nullptr;
	if (oldTree != nullptr)
	{
		newTree = new TreeNode<T>(oldTree->getData(), nullptr, nullptr);
		newTree->setLeft(copyTree(oldTree->getLeft()));
		newTree->setRight(copyTree(oldTree->getRight()));
	}
	return newTree;
}

/*
Description: This method deletes the tree by calling itself for all left/right pointers and deleting each node.
Pre: It takes in the root of the tree to be deleted.
Return: Node that the Node that calls it points to of type T.
*/
template<typename T>
void BinaryNodeTree<T>::destroyTree(TreeNode<T> *node)
{

	if (node != nullptr)
	{
		destroyTree(node->getLeft());
		destroyTree(node->getRight());
		delete node;
	}

}

/*
Description: This method traverses the tree in the preorder way. It visits the node, then left, and right.
Pre: It takes in the root of the tree to be traversed.
Post:
Return:
*/
template<typename T>
void BinaryNodeTree<T>::preorder(TreeNode<T>* node)
{
	if (node != nullptr)
	{
		T data = node->getData();
		preorder(node->getLeft());
		preorder(node->getRight());
	}
}

/*
Description: This method traverses the tree in the inorder way. It goes left, then visits the node, and then right. It is used to print a range of houses within the min and max 
based on the type sent.
Pre: It takes in the root of the tree to be traversed.
Post:
Return:
*/
template<typename T>
void BinaryNodeTree<T>::inorder(TreeNode<T>* node, int min, int max, int type)
{
	if (node != nullptr)
	{
		inorder(node->getLeft(), min, max, type);
		T data = node->getData();
		//cout << node->getData() << endl;
		if (type == 1)
			visitone(data, min, max);
		else
			visittwo(data, min, max);
		inorder(node->getRight(), min, max, type);
	}
}

/*
Description: This method traverses the tree in the postorder way. It goes left, right, and then visits the node.
Pre: It takes in the root of the tree to be traversed.
Post:
Return:
*/
template<typename T>
void BinaryNodeTree<T>::postorder(TreeNode<T>* node)
{
	if (node != nullptr)
	{
		postorder(node->getLeft());
		postorder(node->getRight());
		T data = node->getData();

	
	}
}


/*
Description: This method traverses the tree breadth first.
Pre: node- the root of the tree
Post: Traverses the tree 

*/
template<typename T>
void BinaryNodeTree<T>::breadthFirst(TreeNode<T>* node)
{
	Queue<TreeNode<T>*> que;
	while (node != nullptr)
	{
		if (node->getLeft() != nullptr)
		{
			que.enqueue(node->getLeft());
		}
		if (node->getRight() != nullptr)
		{
			que.enqueue(node->getRight());
		}
		if (!que.isEmpty())
		{
			node = que.getFront();
			que.dequeue();
		}
		else
			node = nullptr;
	}
	
}


/*
Description: This method contains the process to be done when the tree is traversed. In this case, houses with prices ranging between min and max are printed.
Pre: It takes in the data to be processed.
Post:
Return:
*/
template<typename T>
void BinaryNodeTree<T>::visitone(T data, int min, int max)
{
	if ((data.getPrice() >= min) && (data.getPrice() <= max))
	{
		cout << data << endl;
	}
	
}
/*
Description: This method contains the process to be done when the tree is traversed.In this case, houses with prices ranging between min and max are printed.
	Pre: It takes in the data to be processed.
	Post :
	Return :
	*/
template<typename T>
void BinaryNodeTree<T>::visittwo(T data, int min, int max)
{
	if ((data.getSquareFootage() >= min) && (data.getSquareFootage() <= max))
	{
		cout << data << endl;
	};
}

/*
Description: This is the destructor for the tree. It calls the destroy tree function to delete it.
Pre:
Post: The tree is deleted.
Return:
*/
template<typename T>
BinaryNodeTree<T>::~BinaryNodeTree<T>()
{
	destroyTree(root);
}

#endif

