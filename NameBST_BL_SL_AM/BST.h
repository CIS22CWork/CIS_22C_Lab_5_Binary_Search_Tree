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
class Node
{
private:
	T value;
	Node *left;
	Node *right;
public:
	Node (T val);
	Node (T val, Node<T> left, Node<T> right);
	T getValue ();
	Node<T>* getLeft ();
	Node<T>* getRight ();
	void addLeft (Node<T>* node);
	void addRight (Node<T>* node);
	void addValue (T val);
};

template <class T>
class BST
{

private:
	Node<T> *root;
	void addHelper (Node<T> *root, T val);
	void printHelper (Node<T> *root);
	int nodesCountHelper (Node<T> *root);
	int heightHelper (Node<T> *root);
	void printMaxPathHelper (Node<T> *root);
	bool deleteValueHelper (Node<T>* parent, Node<T>* current, T value);

public:
	void add (T val);
	void print ();
	int nodesCount ();
	int height ();
	void printMaxPath ();
	bool deleteValue (T value);
};

template <class T>
Node<T>::Node (T val)
{
	value = val;
}

template <class T>
Node<T>::Node (T val, Node<T> leftNode, Node<T> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T>
T Node<T>::getValue ()
{
	return value;
}

template <class T>
Node<T>* Node<T>::getLeft ()
{
	return left;
}

template <class T>
Node<T>* Node<T>::getRight ()
{
	return right;
}
template <class T>
void Node<T>::addLeft (Node<T>* node)
{
	left = node;
}
template <class T>
void Node<T>::addRight (Node<T>* node)
{
	right = node;
}

template <class T>
void Node<T>::addValue (T val)
{
	value = val;
}

template <class T>
void BST<T>::addHelper (Node<T> *root, T val)
{
	if (root->getValue() > val)
	{
		if (!root->getLeft ())
		{
			root->addLeft (new Node<T> (val));
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
			root->addRight (new Node<T> (val));
		}
		else
		{
			addHelper (root->getRight (), val);
		}
	}
}
template <class T>
void BST<T>::printHelper (Node<T> *root)
{
	if (!root) return;
	printHelper (root->getLeft());
	cout << root->getValue () << ' ';
	printHelper (root->getRight ());
}
template <class T>
int BST<T>::nodesCountHelper (Node<T> *root)
{
	if (!root) return 0;
	else return 1 + nodesCountHelper (root->getLeft ()) + nodesCountHelper (root->getRight ());
}
template <class T>
int BST<T>::heightHelper (Node<T> *root)
{
	if (!root) return 0;
	else return 1 + max (heightHelper (root->getLeft ()), heightHelper (root->getRight ()));
}
template <class T>
void BST<T>::printMaxPathHelper (Node<T> *root)
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
bool BST<T>::deleteValueHelper (Node<T>* parent, Node<T>* current, T value)
{
	if (!current) return false;
	if (current->getValue () == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			Node<T>* temp = current->getLeft ();
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
			Node<T>* validSubs = current->getRight();
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
		root = new Node<T> (val);
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