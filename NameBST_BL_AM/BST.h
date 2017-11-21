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

//******************************************************
// TreeNode class       
//******************************************************

template <class T, class N>
class TreeNode
{
private:
	N* value;
	TreeNode<T, N>* left;
	TreeNode<T, N>* right;
public:
	TreeNode (N* val);
	TreeNode (N* val, TreeNode<T, N> left, TreeNode<T,N> right);
	N* getValue ();
	TreeNode<T,N>* getLeft ();
	TreeNode<T,N>* getRight ();
	void addLeft (TreeNode<T,N>* node);
	void addRight (TreeNode<T, N>* node);
	void addValue (N*);
};

//******************************************************
// BST class       
//******************************************************

template <class T, class N>
class BST
{

private:
	TreeNode<T,N> *root;
	void addHelper (TreeNode<T,N> *root, NodeMain* val, T (*access)(N*));
	// customizable visit an log
	void visitLogPostorderHelper (TreeNode<T,N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogInorderHelper (TreeNode<T,N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogPreorderHelper (TreeNode<T,N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogLevelHelper (TreeNode<T,N> *root, int level, std::string (*visit)(N*), std::string &log);
	int nodesCountHelper (TreeNode<T,N> *root);
	int heightHelper (TreeNode<T,N> *root);
	void printMaxPathHelper (TreeNode<T,N> *root);
	bool deleteValueHelper (TreeNode<T,N>* parent, TreeNode<T,N>* current, T value);

public:
	void add (N* val, T (*access)(N*));
	void visitLogPostorder (std::string (*visit)(N*), std::string &log);
	void visitLogInorder (std::string (*visit)(N*), std::string &log);
	void visitLogPreorder (std::string (*visit)(N*), std::string &log);
	void visitLogBreadthFirst (std::string (*visit)(N*), std::string &log);
	int nodesCount ();
	int height ();
	void printMaxPath ();
	bool deleteValue (T value);
	bool insert (List<N*>* list, T (*access)(N* node));
};

//******************************************************
// TreeNode class implementation    
//******************************************************

template <class T, class N>
TreeNode<T,N>::TreeNode (N* val)
{
	value = val;
}

template <class T, class N>
TreeNode<T,N>::TreeNode (N* val, TreeNode<T,N> leftNode, TreeNode<T,N> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T, class N>
N* TreeNode<T,N>::getValue ()
{
	return value;
}

template <class T, class N>
TreeNode<T,N>* TreeNode<T,N>::getLeft ()
{
	return left;
}

template <class T, class N>
TreeNode<T,N>* TreeNode<T,N>::getRight ()
{
	return right;
}
template <class T, class N>
void TreeNode<T,N>::addLeft (TreeNode<T,N>* node)
{
	left = node;
}
template <class T, class N>
void TreeNode<T,N>::addRight (TreeNode<T,N>* node)
{
	right = node;
}

template <class T, class N>
void TreeNode<T,N>::addValue (N* val)
{
	value = val;
}

//******************************************************
// BST class implementation    
//******************************************************

template <class T, class N>
void BST<T,N>::addHelper (TreeNode<T,N> *root, NodeMain* val, T (*access)(N*))
{
	if ((*access)(root->getValue ()) > (*access)(val))
	{
		if (!root->getLeft ())
		{
			root->addLeft (new TreeNode<T,N> (val));
		}
		else
		{
			addHelper (root->getLeft (), val, access);
		}
	}
	else
	{
		if (!root->getRight ())
		{
			root->addRight (new TreeNode<T,N> (val));
		}
		else
		{
			addHelper (root->getRight (), val, access);
		}
	}
}
template <class T, class N>
void BST<T,N>::visitLogPostorderHelper (TreeNode<T,N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	visitLogPostorderHelper (root->getLeft (), visit, log);
	visitLogPostorderHelper (root->getRight (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root->getValue());
}

template <class T, class N>
void BST<T,N>::visitLogInorderHelper (TreeNode<T,N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	visitLogInorderHelper (root->getLeft (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
	visitLogInorderHelper (root->getRight (), visit, log);
}

template <class T, class N>
void BST<T,N>::visitLogPreorderHelper (TreeNode<T,N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
	visitLogPreorderHelper (root->getLeft (), visit, log);
	visitLogPreorderHelper (root->getRight (), visit, log);
}

template <class T, class N>
void BST<T,N>::visitLogLevelHelper (TreeNode<T,N> *root, int level, std::string (*visit)(N*), std::string &log)
{
	if (!root)
		return;
	if (level == 1)
		log += (*visit)(root->getValue ());
	else if (level > 1)
	{
		visitLogLevelHelper (root->getLeft (), level - 1, visit, log);
		visitLogLevelHelper (root->getRight (), level - 1, visit, log);
	}
}

template <class T, class N>
int BST<T,N>::nodesCountHelper (TreeNode<T,N> *root)
{
	if (!root) return 0;
	else return 1 + nodesCountHelper (root->getLeft ()) + nodesCountHelper (root->getRight ());
}
template <class T, class N>
int BST<T,N>::heightHelper (TreeNode<T,N> *root)
{
	if (!root) return 0;
	else return 1 + max (heightHelper (root->getLeft ()), heightHelper (root->getRight ()));
}
template <class T, class N>
void BST<T,N>::printMaxPathHelper (TreeNode<T,N> *root)
{
	if (!root) return;
	cout << root->getValue () << ' ';
	if (heightHelper (root->getLeft ()) > heightHelper (root->getRight ()))
	{
		printMaxPathHelper (root->getLeft ());
	}
	else
	{
		printMaxPathHelper (root->getRight ());
	}
}
template <class T, class N>
bool BST<T,N>::deleteValueHelper (TreeNode<T,N>* parent, TreeNode<T,N>* current, T value)
{
	if (!current) return false;
	if (current->getValue () == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			TreeNode<T,N>* temp = current->getLeft ();
			if (current->getRight ()) temp = current->getRight ();
			if (parent)
			{
				if (parent->getLeft () == current)
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
			TreeNode<T,N>* validSubs = current->getRight ();
			while (validSubs->getLeft ())
			{
				validSubs = validSubs->getLeft ();
			}
			T temp = current->getValue ();
			current->addValue (validSubs->getValue ());
			validSubs->addValue (temp);
			return deleteValueHelper (current, current->getRight (), temp);
		}
		delete current;
		return true;
	}
	return deleteValueHelper (current, current->getLeft (), value) ||
		deleteValueHelper (current, current->getRight (), value);
}
template <class T, class N>
void BST<T,N>::add (N* val, T (*access)(N*))
{
	if (root)
	{
		this->addHelper (root, val, access);
	}
	else
	{
		root = new TreeNode<T,N> (val);
	}
}

template <class T, class N>
void BST<T,N>::visitLogPostorder (std::string (*visit)(N*), std::string &log)
{
	visitLogPostorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T,N>::visitLogInorder (std::string (*visit)(N*), std::string &log)
{
	visitLogInorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T,N>::visitLogPreorder (std::string (*visit)(N*), std::string &log)
{
	visitLogPreorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T,N>::visitLogBreadthFirst (std::string (*visit)(N*), std::string &log)
{
	int h = heightHelper (this->root);
	int i;
	for (i = 1; i <= h; i++)
		visitLogLevelHelper (this->root, i, visit, log);
}

template <class T, class N>
int BST<T,N>::nodesCount ()
{
	return nodesCountHelper (root);
}
template <class T, class N>
int BST<T,N>::height ()
{
	return heightHelper (this->root);
}
template <class T, class N>
void BST<T,N>::printMaxPath ()
{
	printMaxPathHelper (this->root);
}
template <class T, class N>
bool BST<T,N>::deleteValue (T value)
{
	return this->deleteValueHelper (NULL, this->root, value);
}

template <class T, class N>
bool BST<T,N>::insert (List<N*>* list, T (*access)(N* node))
{
	bool flag = false;
	int n = list->size ();
	for (int i = 0; i < n; i++)
	{
		add ((*list)[i], access);
	}
	return flag;
}
#endif