/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

Node
A Node ADT which will have two attributes - 
a data attribute and a pointer attribute.  Remember the Node has to be an ADT, 
so that it can hold any kind of data.
You can choose to use this node as both a data and a head-pointing node 
or as a simple data node in which case you will need a new head pointing node.
*/

#ifndef NODE_H
#define NODE_H
template <class T>
class Node
{
public:
	T value;
	Node<T> *next;

	Node (T nodeValue);
	~Node ();
};

//******************************************************
// Default Constructor        
//******************************************************
template <class T>
Node<T>::Node (T nodeValue)
{
	value = nodeValue;
	next = nullptr;
}

//******************************************************
// Destructor          
//******************************************************
template <class T>
Node<T>::~Node ()
{
	next = nullptr;
}
#endif