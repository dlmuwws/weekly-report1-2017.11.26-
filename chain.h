#pragma once
#include<iostream>
using namespace std;
#include"chainNode.h"

template <class T>
class chain {
public:
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	bool empty() const { return listsize == 0; }
	int size() const { return listsize; }
	T & get(int theIndex)const;
	int IndexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int thIndex, const T & theElement);
	void output(ostream & out) const;

protected:
	void checkIndex(int Index) const;
	chainNode<T> *firstNode;
	int listsize;
};

template <class T>
chain<T>::chain(int initialCapacity) {
	if (initialCapacity < 1)
		cout << "init capacity must >0";
	firstNode = NULL;
	listsize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList) {
	listsize = theList.listsize;
	if (listsize == 0) {
		firstNode = NULL;
		return;
	}
	chainNode<T> *sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);

	sourceNode = sourceNode->next;
	chainNode<T>*targetNode = firstNode;
	while (sourceNode != NULL) {
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}

template <class T>
chain<T>::~chain() {
	while (firstNode != NULL) {
		chainNode<T>*nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template <class T>
void chain<T>::checkIndex(int theIndex)const {
	if (theIndex<0 || theIndex>listsize)
		cout << "illegal index"<<endl;
}

template <class T>
T& chain<T>::get(int theIndex) const {
	checkIndex(theIndex);
	chainNode<T>*currentNode = firstNode;
	for (int i = 0; i < theIndex; i++) {
		currentNode = currentNode->next;
	}
	return currentNode->element;
}

template<class T>
int chain<T>::IndexOf(const T& theElement) const {
	chainNode<T> *currentNode = firstNode;
	int index = 0;
	while (currentNode != NULL && currentNode->element != theElement  )
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
		return -1;
	else
		return index;
}

template<class T>
void chain<T>:: erase(int theIndex) {
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	if (theIndex ==0) {
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else 
	{
		chainNode<T>*pointer = firstNode;
		for (int i = 0; i < theIndex-1; i++) {
			pointer = pointer->next;
		}
		deleteNode = pointer->next;
		pointer->next = pointer->next->next;
	}
	listsize--;
	delete deleteNode;
	
}

template<class T>
void chain<T>::insert(int theIndex, const T &theElement) {
	checkIndex(theIndex);
	if (theIndex == 0) {

		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		chainNode<T>*p=firstNode;
		for (int i = 0; i < theIndex - 1; i++) {
			p = p->next;
		}
		chainNode<T>*insertNode = new chainNode<T>(theElement,p->next);
		p->next = insertNode;
	}
	listsize++;
}

template<class T>
void chain<T>::output(ostream & out) const {
	for (chainNode<T>*currentNode = firstNode; currentNode->next != NULL; currentNode = currentNode->next) {
		out << currentNode->element << " ";
	}
}

template<class T>
ostream& operator<<(ostream &out, const chain<T> & x) {
	x.output(out);
	return out;
}