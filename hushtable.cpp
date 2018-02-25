
#include "hashtable.h"
#include<iostream>
using namespace std;

//输入一个数，返回比它大的最小素数
int find_prime(int num)
{
	int i;
	if (0 == num % 2)
		++num;
	for (;; num += 2)
	{
		for (i = 3; i*i <= num; i += 2)
		{
			if (0 == num % i)
			{
				num += 2;
				i = 3;
			}
		}
		return num;
	}
}
//构造函数
HashTable::HashTable(int TableSize_)
{
	TableSize = find_prime(TableSize_);   //指定哈希表长度为素数  
	List = new Node*[TableSize];      
	for (int i = 0; i < TableSize; ++i)    //初始化  
		List[i] = NULL;
}

//析构函数
void HashTable::MakeEmpty()
{
	Node *list = NULL;
	for (int i = 0; i < this->TableSize; ++i)
	{
		list = List[i];
		while (list != NULL)
		{
			Node *temp = list;
			list = list->next;
			delete temp;
		}
		List[i] = NULL;
	}
}

 int HashTable::Hash(int data)
{
	return data % TableSize;
}

 //返回指向该值的指针，没有则返回NULL  
 Node* HashTable::Find(int data)
 {
	 int Index = Hash(data);
	 Node *list = List[Index];
	 while (list != NULL && list->data != data)
		 list = list->next;

	 return list;
 }

 //往哈希表插入 数据
 void HashTable::Insert(int data)
 {
	  int Index = Hash(data);
	 Node *Pos = NULL;
	 Pos = Find(data);
	 /*
	 Pos = List[Index];
	 while (Pos != NULL && Pos->data != data)
	 Pos = Pos->next;
	 */
	 if (NULL == Pos)  //表中当前不存在
	 {
		 Node *Newnode= new Node(data);
		 Newnode->next = List[Index];
		 List[Index] = Newnode;
	 }
 }

 //删除数据
 void HashTable::Delete(int data)
 {
	  int Index = Hash(data);
	 Node *list = List[Index];

	 if (list != NULL)
	 {
		 if (list->data == data)  //头节点元素  
		 {
			 List[Index] = list->next;
			 delete list;
		 }
		 else
		 {   //找到数值节点的前一个节点  
			 while (list != NULL && list->next != NULL)
			 {
				 if (list->next->data == data)
				 {
					 Node *temp = list->next;
					 list->next = temp->next;
					 delete temp;
				 }
				 list = list->next;
			 } 
		 } 
	 }    
 }




 int main()
 {
	 cout << "test:" << endl;
	 HashTable *hashtable=new HashTable(9);
	 cout << hashtable->getsize() << endl;
	 hashtable->Insert(11);
	 hashtable->Insert(22);
	 hashtable->Insert(33); 
	 hashtable->Insert(35);
	 hashtable->Insert(23);
	 hashtable->Insert(4);
	 hashtable->Insert(6);
	 hashtable->Insert(8);
	 hashtable->Insert(9);

	 cout << hashtable->Hash(11) << endl;
	 cout << hashtable->Hash(22) << endl;

	 Node *node1 = hashtable->Find(9);
	 cout << node1->get_data() << endl;

	 Node *node2 = hashtable->Find(33);
	 cout << node2->get_data() << endl;

	 hashtable->Delete(35);

	 system("pause");
	 return 0;
}
