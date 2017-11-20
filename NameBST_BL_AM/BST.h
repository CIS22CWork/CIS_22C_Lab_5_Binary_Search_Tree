/*
Branden Lee and Alex Morfin
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
class TreeNode
{
private:
	T value;
	TreeNode *left;
	TreeNode *right;
public:
	TreeNode (T val);
	TreeNode (T val, TreeNode<T> left, TreeNode<T> right);
	T getValue ();
	TreeNode<T>* getLeft ();
	TreeNode<T>* getRight ();
	void addLeft (TreeNode<T>* node);
	void addRight (TreeNode<T>* node);
	void addValue (T val);
};

template <class T>
class BST
{

private:
	TreeNode<T> *root;
	void addHelper (TreeNode<T> *root, T val);
	// customizable visit an log
	void visitLogPostorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogInorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogPreorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log);
	int nodesCountHelper (TreeNode<T> *root);
	int heightHelper (TreeNode<T> *root);
	void printMaxPathHelper (TreeNode<T> *root);
	bool deleteValueHelper (TreeNode<T>* parent, TreeNode<T>* current, T value);

public:
	void add (T val);
	void visitLogPostorder (std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogInorder (std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogPreorder (std::string (*visit)(TreeNode<T>*), std::string &log);
	int nodesCount ();
	int height ();
	void printMaxPath ();
	bool deleteValue (T value);
	void printLevelOrder (TreeNode<T>* root);
	void printGivenLevel (TreeNode<T>* root, int level);
};

template <class T>
TreeNode<T>::TreeNode (T val)
{
	value = val;
}

template <class T>
TreeNode<T>::TreeNode (T val, TreeNode<T> leftNode, TreeNode<T> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T>
T TreeNode<T>::getValue ()
{
	return value;
}

template <class T>
TreeNode<T>* TreeNode<T>::getLeft ()
{
	return left;
}

template <class T>
TreeNode<T>* TreeNode<T>::getRight ()
{
	return right;
}
template <class T>
void TreeNode<T>::addLeft (TreeNode<T>* node)
{
	left = node;
}
template <class T>
void TreeNode<T>::addRight (TreeNode<T>* node)
{
	right = node;
}

template <class T>
void TreeNode<T>::addValue (T val)
{
	value = val;
}

template <class T>
void BST<T>::addHelper (TreeNode<T> *root, T val)
{
	if (root->getValue() > val)
	{
		if (!root->getLeft ())
		{
			root->addLeft (new TreeNode<T> (val));
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
			root->addRight (new TreeNode<T> (val));
		}
		else
		{
			addHelper (root->getRight (), val);
		}
	}
}
template <class T>
void BST<T>::visitLogPostorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log)
{
	if (!root) return;
	visitLogPostorderHelper (root->getLeft(), visit, log);
	visitLogPostorderHelper (root->getRight (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root);
}

template <class T>
void BST<T>::visitLogInorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log)
{
	if (!root) return;
	visitLogInorderHelper (root->getLeft (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root);
	visitLogInorderHelper (root->getRight (), visit, log);
}

template <class T>
void BST<T>::visitLogPreorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log)
{
	if (!root) return;
	// call custom visit method and append output to log
	log += (*visit)(root);
	visitLogPreorderHelper (root->getLeft (), visit, log);
	visitLogPreorderHelper (root->getRight (), visit, log);
}
template <class T>
int BST<T>::nodesCountHelper (TreeNode<T> *root)
{
	if (!root) return 0;
	else return 1 + nodesCountHelper (root->getLeft ()) + nodesCountHelper (root->getRight ());
}
template <class T>
int BST<T>::heightHelper (TreeNode<T> *root)
{
	if (!root) return 0;
	else return 1 + max (heightHelper (root->getLeft ()), heightHelper (root->getRight ()));
}
template <class T>
void BST<T>::printMaxPathHelper (TreeNode<T> *root)
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
bool BST<T>::deleteValueHelper (TreeNode<T>* parent, TreeNode<T>* current, T value)
{
	if (!current) return false;
	if (current->getValue () == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			TreeNode<T>* temp = current->getLeft ();
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
			TreeNode<T>* validSubs = current->getRight();
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
		root = new TreeNode<T> (val);
	}
}

template <class T>
void BST<T>::visitLogPostorder (std::string (*visit)(TreeNode<T>*), std::string &log)
{
	visitLogPostorderHelper (this->root, visit, log);
}

template <class T>
void BST<T>::visitLogInorder (std::string (*visit)(TreeNode<T>*), std::string &log)
{
	visitLogInorderHelper (this->root, visit, log);
}

template <class T>
void BST<T>::visitLogPreorder (std::string (*visit)(TreeNode<T>*), std::string &log)
{
	visitLogPreorderHelper (this->root, visit, log);
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

template <class T>
void BST<T>::printLevelOrder (TreeNode<T>* root)
{
	int h = heightHelper (root);
	int i;
	for (i = 1; i <= h; i++)
		printGivenLevel (root, i);
}

template <class T>
void BST<T>::printGivenLevel (TreeNode<T>* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		std::cout << root->value;
	else if (level > 1)
	{
		printGivenLevel (root->left, level - 1);
		printGivenLevel (root->right, level - 1);
	}
}

#endif