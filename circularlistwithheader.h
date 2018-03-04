#pragma once
#include<iostream>
using namespace std;
#include<sstream>
#include<string>
#include "chainNode.h"


template<class T>
class circularListWithHeader
{
public:
	circularListWithHeader();
	int size() const { return listSize; }
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

protected:
	void checkIndex(int theIndex) const;
	
	chainNode<T>* headerNode;  
	int listSize;              
};

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{
	headerNode = new chainNode<T>();
	headerNode->next = headerNode;
	listSize = 0;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}

template<class T>
int circularListWithHeader<T>::indexOf(const T& theElement) const
{

 
	headerNode->element = theElement;

	
	chainNode<T>* currentNode = headerNode->next;
	int index = 0;  
	while (currentNode->element != theElement)
	{
		
		currentNode = currentNode->next;
		index++;
	}

	
	if (currentNode == headerNode)
		return -1;
	else
		return index;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	
	chainNode<T>* p = headerNode;
	for (int i = 0; i < theIndex; i++)
		p = p->next;

	
	p->next = new chainNode<T>(theElement, p->next);

	listSize++;
}

template<class T>
void circularListWithHeader<T>::output(ostream& out) const
{
	for (chainNode<T>* currentNode = headerNode->next;
		currentNode != headerNode;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}


template <class T>
ostream& operator<<(ostream& out, const circularListWithHeader<T>& x)
{
	x.output(out); return out;
}
