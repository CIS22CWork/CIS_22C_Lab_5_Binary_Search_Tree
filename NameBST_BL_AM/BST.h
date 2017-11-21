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

template <class T>
class TreeNode
{
private:
	NodeMain* value;
	TreeNode *left;
	TreeNode *right;
public:
	TreeNode (NodeMain* val);
	TreeNode (NodeMain* val, TreeNode<T> left, TreeNode<T> right);
	NodeMain* getValue ();
	TreeNode<T>* getLeft ();
	TreeNode<T>* getRight ();
	void addLeft (TreeNode<T>* node);
	void addRight (TreeNode<T>* node);
	void addValue (NodeMain*);
};

//******************************************************
// BST class       
//******************************************************

template <class T>
class BST
{

private:
	TreeNode<T> *root;
	void addHelper (TreeNode<T> *root, NodeMain* val, T (*access)(TreeNode<T>*));
	// customizable visit an log
	void visitLogPostorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogInorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogPreorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogLevelHelper (TreeNode<T> *root, int level, std::string (*visit)(TreeNode<T>*), std::string &log);
	int nodesCountHelper (TreeNode<T> *root);
	int heightHelper (TreeNode<T> *root);
	void printMaxPathHelper (TreeNode<T> *root);
	bool deleteValueHelper (TreeNode<T>* parent, TreeNode<T>* current, T value);

public:
	void add (NodeMain* val, T (*access)(TreeNode<T>*));
	void visitLogPostorder (std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogInorder (std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogPreorder (std::string (*visit)(TreeNode<T>*), std::string &log);
	void visitLogBreadthFirst (std::string (*visit)(TreeNode<T>*), std::string &log);
	int nodesCount ();
	int height ();
	void printMaxPath ();
	bool deleteValue (T value);
	bool insert (List<NodeMain*>* list, T (*access)(TreeNode<T>* node));
};

//******************************************************
// TreeNode class implementation    
//******************************************************

template <class T>
TreeNode<T>::TreeNode (NodeMain* val)
{
	value = val;
}

template <class T>
TreeNode<T>::TreeNode (NodeMain* val, TreeNode<T> leftNode, TreeNode<T> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T>
NodeMain* TreeNode<T>::getValue ()
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
void TreeNode<T>::addValue (NodeMain* val)
{
	value = val;
}

//******************************************************
// BST class implementation    
//******************************************************

template <class T>
void BST<T>::addHelper (TreeNode<T> *root, NodeMain* val, T (*access)(TreeNode<T>*))
{
	if ((*access)(root->getValue ()) > (*access)(val))
	{
		if (!root->getLeft ())
		{
			root->addLeft (new TreeNode<T> (val));
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
			root->addRight (new TreeNode<T> (val));
		}
		else
		{
			addHelper (root->getRight (), val, access);
		}
	}
}
template <class T>
void BST<T>::visitLogPostorderHelper (TreeNode<T> *root, std::string (*visit)(TreeNode<T>*), std::string &log)
{
	if (!root) return;
	visitLogPostorderHelper (root->getLeft (), visit, log);
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
void BST<T>::visitLogLevelHelper (TreeNode<T> *root, int level, std::string (*visit)(TreeNode<T>*), std::string &log)
{
	if (!root)
		return;
	if (level == 1)
		log += (*visit)(root);
	else if (level > 1)
	{
		visitLogLevelHelper (root->getLeft (), level - 1, visit, log);
		visitLogLevelHelper (root->getRight (), level - 1, visit, log);
	}
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
template <class T>
bool BST<T>::deleteValueHelper (TreeNode<T>* parent, TreeNode<T>* current, T value)
{
	if (!current) return false;
	if (current->getValue () == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			TreeNode<T>* temp = current->getLeft ();
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
			TreeNode<T>* validSubs = current->getRight ();
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
template <class T>
void BST<T>::add (NodeMain* val, T (*access)(TreeNode<T>*))
{
	if (root)
	{
		this->addHelper (root, val, access);
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
void BST<T>::visitLogBreadthFirst (std::string (*visit)(TreeNode<T>*), std::string &log)
{
	int h = heightHelper (this->root);
	int i;
	for (i = 1; i <= h; i++)
		visitLogLevelHelper (this->root, i, visit, log);
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
bool BST<T>::insert (List<NodeMain*>* list, T (*access)(TreeNode<T>* node))
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