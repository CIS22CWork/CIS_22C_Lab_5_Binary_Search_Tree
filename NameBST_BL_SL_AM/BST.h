/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

BST class
Implement your BST as a link-based ADT - you may be able to reuse your Node classes from Labs 2 and 2b.
*/
#ifndef BST_H
#define BST_H

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

template <class T>
class NodeBST
{
private:
	T value;
	NodeBST *left;
	NodeBST *right;
public:
	NodeBST (T val);
	NodeBST (T val, NodeBST<T> left, NodeBST<T> right);
	T getValue ();
	NodeBST<T>* getLeft ();
	NodeBST<T>* getRight ();
	void addLeft (NodeBST<T>* node);
	void addRight (NodeBST<T>* node);
	void addValue (T val);
};

template <class T>
class BST
{

private:
	NodeBST<T> *root;
	void addHelper (NodeBST<T> *root, T val);
	void printHelper (NodeBST<T> *root);
	int nodesCountHelper (NodeBST<T> *root);
	int heightHelper (NodeBST<T> *root);
	void printMaxPathHelper (NodeBST<T> *root);
	bool deleteValueHelper (NodeBST<T>* parent, NodeBST<T>* current, T value);

public:
	void add (T val);
	void print ();
	int nodesCount ();
	int height ();
	void printMaxPath ();
	bool deleteValue (T value);
};

template <class T>
NodeBST<T>::NodeBST (T val)
{
	value = val;
}

template <class T>
NodeBST<T>::NodeBST (T val, NodeBST<T> leftNode, NodeBST<T> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T>
T NodeBST<T>::getValue ()
{
	return value;
}

template <class T>
NodeBST<T>* NodeBST<T>::getLeft ()
{
	return left;
}

template <class T>
NodeBST<T>* NodeBST<T>::getRight ()
{
	return right;
}
template <class T>
void NodeBST<T>::addLeft (NodeBST<T>* node)
{
	left = node;
}
template <class T>
void NodeBST<T>::addRight (NodeBST<T>* node)
{
	right = node;
}

template <class T>
void NodeBST<T>::addValue (T val)
{
	value = val;
}

template <class T>
void BST<T>::addHelper (NodeBST<T> *root, T val)
{
	if (root->getValue() > val)
	{
		if (!root->getLeft ())
		{
			root->addLeft (new NodeBST<T> (val));
		}
		else
		{
			addHelper (root->getLeft (), val);
		}
	}
	else
	{
		if (!root->getRight ())
		{
			root->addRight (new NodeBST<T> (val));
		}
		else
		{
			addHelper (root->getRight (), val);
		}
	}
}
template <class T>
void BST<T>::printHelper (NodeBST<T> *root)
{
	if (!root) return;
	printHelper (root->getLeft());
	cout << root->getValue () << ' ';
	printHelper (root->getRight ());
}
template <class T>
int BST<T>::nodesCountHelper (NodeBST<T> *root)
{
	if (!root) return 0;
	else return 1 + nodesCountHelper (root->getLeft ()) + nodesCountHelper (root->getRight ());
}
template <class T>
int BST<T>::heightHelper (NodeBST<T> *root)
{
	if (!root) return 0;
	else return 1 + max (heightHelper (root->getLeft ()), heightHelper (root->getRight ()));
}
template <class T>
void BST<T>::printMaxPathHelper (NodeBST<T> *root)
{
	if (!root) return;
	cout << root->getValue() << ' ';
	if (heightHelper (root->getLeft ()) > heightHelper (root->getRight ()))
	{
		printMaxPathHelper (root->getLeft ());
	}
	else
	{
		printMaxPathHelper (root->getRight ());
	}
}
template <class T>
bool BST<T>::deleteValueHelper (NodeBST<T>* parent, NodeBST<T>* current, T value)
{
	if (!current) return false;
	if (current->getValue () == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			NodeBST<T>* temp = current->getLeft ();
			if (current->getRight()) temp = current->getRight ();
			if (parent)
			{
				if (parent->getLeft() == current)
				{
					parent->addLeft (temp);
				}
				else
				{
					parent->addRight (temp);
				}
			}
			else
			{
				this->root = temp;
			}
		}
		else
		{
			NodeBST<T>* validSubs = current->getRight();
			while (validSubs->getLeft())
			{
				validSubs = validSubs->getLeft();
			}
			T temp = current->getValue();
			current->addValue (validSubs->getValue ());
			validSubs->addValue (temp);
			return deleteValueHelper (current, current->getRight(), temp);
		}
		delete current;
		return true;
	}
	return deleteValueHelper (current, current->getLeft(), value) ||
		deleteValueHelper (current, current->getRight(), value);
}
template <class T>
void BST<T>::add (T val)
{
	if (root)
	{
		this->addHelper (root, val);
	}
	else
	{
		root = new NodeBST<T> (val);
	}
}
template <class T>
void BST<T>::print ()
{
	printHelper (this->root);
}
template <class T>
int BST<T>::nodesCount ()
{
	return nodesCountHelper (root);
}
template <class T>
int BST<T>::height ()
{
	return heightHelper (this->root);
}
template <class T>
void BST<T>::printMaxPath ()
{
	printMaxPathHelper (this->root);
}
template <class T>
bool BST<T>::deleteValue (T value)
{
	return this->deleteValueHelper (NULL, this->root, value);
}

#endif