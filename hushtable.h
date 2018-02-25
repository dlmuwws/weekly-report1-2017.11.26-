#pragma once
#include<stdio.h>

class HashTable;
class Node
{
public:
	Node(int data_) :data(data_), next(NULL) {}
	int get_data() { return data; };
private:
	int data;
	Node *next;
	friend class HashTable;
};


class HashTable
{
public:
	HashTable(int tablesize_);
	~HashTable() {
		MakeEmpty();
		delete[] List;
	}
	int getsize() { return TableSize; };
	 int Hash(int);
	void Insert(int);
	void Delete(int);
	Node *Find(int);
	void MakeEmpty();
private:
	int TableSize;  //表的长度
	Node **List;    //哈希表
};
