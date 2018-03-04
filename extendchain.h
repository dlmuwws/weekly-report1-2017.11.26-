#pragma once
#include<iostream>
using namespace std;
#include"chainNode.h"

#include <iostream>
#include <sstream>
#include <string>


using namespace std;

template<class T>
class extendedChain 
{
public:
	
	extendedChain(int initialCapacity = 10) :
		chain<T>(initialCapacity) {}
	extendedChain(const extendedChain<T>& c) :
		chain<T>(c) {}

	
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const
	{
		return chain<T>::get(theIndex);
	}
	int indexOf(const T& theElement) const
	{
		return chain<T>::indexOf(theElement);
	}
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void clear()
	{
		while (firstNode != NULL)
		{
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
		listSize = 0;
	}
	void push_back(const T& theElement);
	void output(ostream& out) const
	{
		chain<T>::output(out);
	}

	
	void zero()
	{
		firstNode = NULL; listSize = 0;
	}

protected:
	chainNode<T>* lastNode;  
};


template<class T>
void extendedChain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{ 
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; 
		if (deleteNode == lastNode)
			lastNode = p;
	}
	listSize--;
	delete deleteNode;
}

template<class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
		if (listSize == 0)
			lastNode = firstNode;
	}
	else
	{  
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		
		p->next = new chainNode<T>(theElement, p->next);
		if (listSize == theIndex)
			lastNode = p->next;
	}
	listSize++;
}

template<class T>
void extendedChain<T>::push_back(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
	if (firstNode == NULL)
		
		firstNode = lastNode = newNode;
	else
	{  
		lastNode->next = newNode;
		lastNode = newNode;
	}
	listSize++;
}