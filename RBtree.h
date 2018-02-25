#pragma once
#include<iostream>  
using namespace std;



class RBtree;
class RBtreeNode
{
private:
	friend class RBtree;    //RBtree类可以访问该类里面的private成员
	int key;          
	bool color;    //0,1
	RBtreeNode* left;
	RBtreeNode* right;
	RBtreeNode* parent;
public:
	RBtreeNode() :key(-1), color(0), left(NULL), right(NULL), parent(NULL) {}
	RBtreeNode(int num, bool flag) :key(num), color(flag), left(NULL), right(NULL), parent(NULL) {}
	~RBtreeNode(){}
};


class RBtree
{
private:
	RBtreeNode* root; 
	RBtreeNode* nil;  //一个空节点
public:
	RBtree() :nil(new RBtreeNode())
	{
		root = nil;
	}
	int Getkey(RBtreeNode* node){return node->key;}
	bool Getcolor(RBtreeNode* node){return node->color;}
	RBtreeNode* Getroot(){return root;}
	RBtreeNode* GetParent(RBtreeNode*node){return node->parent;}
	int GetHeight(RBtreeNode* node)
	{
		int L, R;
		if (node == nil)
			return 0;
		L = GetHeight(node->left);
		R = GetHeight(node->right);
		return 1 + (L>R ? L : R);
	}
	int GetBlackHeight(RBtreeNode* node)
	{
		int L, R;
		if (node == nil) return 0;
		L = GetHeight(node->left);
		R = GetHeight(node->right);
		if (node->color) return(L>R ? L : R);
		else return 1 + (L>R ? L : R);
	}
	void Inorder(RBtreeNode*node)
	{
		if (node != nil)
		{
			Inorder(node->left);
			cout << node->key << " ";
			Inorder(node->right);
		}
	}
	void Preorder(RBtreeNode*node)
	{
		if (node != nil)
		{
			cout << node->key << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}
	void Posetorder(RBtreeNode*node)
	{
		if (node != nil)
		{
			Posetorder(node->left);
			Posetorder(node->right);
			cout << node->key << " ";
		}
	}

	//左旋节点node：node 的右孩子成为node的parent, node 成为其左孩子,node 的右孩子的左孩子成为node的右孩子
	bool LeftRotate(RBtreeNode* node)
	{
		RBtreeNode*y;
		if (node->right == nil)
		{
			cout << "can't left rotate!" << endl;
			return 0;
		}
		y = node->right;
		node->right = y->left;
		if (y->left != nil)
		{
			y->left->parent = node;
		}
		y->parent = node->parent;
		if (node->parent == nil)
		{
			root = y;
		}
		else if (node->parent->left == node)
		{
			node->parent->left = y;
		}
		else
		{
			node->parent->right = y;
		}
		y->left = node;   //左旋完毕
		node->parent = y;
		return 1;
	}
	//右旋节点 ，与左旋相反
	bool RightRotate(RBtreeNode* node)
	{
		if (node->left == nil)
		{
			cout << "can't right rotate!" << endl;
			return 0;
		}
		RBtreeNode* x;
		x = node->left;
		node->left = x->right;
		if (x->right != nil)
		{
			x->right->parent = node;
		}
		x->parent = node->parent;
		if (node->parent == nil)
		{
			root = x;
		}
		else if (node->parent->left == node)
		{
			node->parent->left = x;
		}
		else
		{
			node->parent->right = x;
		}
		node->parent = x;
		x->right = node;
		return 1;
	}
	void Insert(int num)   //插入健值为num的新节点
	{
		RBtreeNode* node = new RBtreeNode(num, 1);
		node->left = nil;
		node->right = nil;
		node->parent = nil;
		RBtreeNode* p = root, *q = nil;
		if (root == nil)
		{
			node->color = 0;
			root = node;
			root->left = root->right = root->parent = nil;
			return;
		}
		while (p != nil)
		{
			if (p->key == num)
			{
				cout << num << "  has exist!" << endl;
				return;
			}
			else if (p->key>num)
			{
				q = p;   //q纪录插入位置
				p = p->left;
			}
			else
			{
				q = p;
				p = p->right;
			}
		}
		if (q->key>num)   //找到插入点，决定插到左孩子还是右孩子
		{
			q->left = node;
			node->parent = q;
		}
		else
		{
			q->right = node;
			node->parent = q;
		}
		RBInsertAdjust(node);   
	}
	void RBInsertAdjust(RBtreeNode* node)    //修正红黑树的平衡性，变色，左旋，右旋
	{
		RBtreeNode* y;
		while (node->parent->color == 1)
		{
			if (node->parent == node->parent->parent->left)
			{
				y = node->parent->parent->right;   
				if (y->color == 1)//叔叔节点和父亲节点均为红色，进行变色操作
				{
					node->parent->color = 0;
					y->color = 0;
					y->parent->color = 1;
					node = node->parent->parent;    //node指向祖父节点，为了情况2的左旋
				}
				//此时y的颜色是黑色    
				else
				{
					//第二种情况    
					if (node == node->parent->right)  //父亲节点是右孩子
					{
						node = node->parent;
						LeftRotate(node);
					}
					//第三种情况    父亲节点是左孩子
					node->parent->color = 0;
					node->parent->parent->color = 1;
					RightRotate(node->parent->parent);
				}
			}
			else   //父亲节点是右孩子，和上面一样调整
			{
				y = node->parent->parent->left;
				if (y->color == 1)
				{
					node->parent->color = 0;
					y->color = 0;
					y->parent->color = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						RightRotate(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					LeftRotate(node->parent->parent);
				}
			}
		}
		root->color = 0;
	}
	RBtreeNode* Search(int num)    //和BST查找一样
	{
		RBtreeNode* p = root;
		while (p != nil)
		{
			if (p->key == num)
			{
				return p;
			}
			else if (p->key>num)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		cout << "there is no " << num << " in this tree!" << endl;
		return nil;
	}
	//获取以node节点为根节点的树的最小元素，并返回该节点    
	RBtreeNode* MinNum(RBtreeNode*node)
	{
		RBtreeNode*p = node;
		while (p->left != nil)
		{
			p = p->left;
		}
		return p;
	}
	//获取以node节点为根节点的树的最大元素    
	RBtreeNode* MaxNum(RBtreeNode*node)
	{
		RBtreeNode*p = node;
		while (p->right != nil)
		{
			p = p->right;
		}
		return p;
	}
	RBtreeNode*InorderSuccessor(RBtreeNode*node)   //后继
	{
		if (node->right != nil)
		{
			return MinNum(node->right);
		}
		else
		{
			RBtreeNode*p = GetParent(node);
			while (p&&node == p->right)
			{
				node = p;
				p = GetParent(node);
			}
			return p;
		}
	}
	//中序遍历的前趋    
	RBtreeNode*InordePredecessor(RBtreeNode*node)
	{
		if (node->left != nil)
		{
			return MaxNum(node->left);
		}
		else
		{
			RBtreeNode*p = GetParent(node);
			while (p&&node == p->left)
			{
				node = p;
				p = GetParent(node);
			}
			return p;
		}
	}
	//删除操作
	bool Delete(int num)
	{
		RBtreeNode*z, *y, *x;
		//寻找key值为num的节点p    
		z = Search(num);
		//如果没有该节点则返回0    
		if (z == nil){return 0;}
		if (z->left == nil || z->right == nil)   //只有一个孩子，删除后直接让孩子代替自己的位置
		{
			y = z;
		}
		else
			y = InorderSuccessor(z);     //找后继
		if (y->left != nil)
			x = y->left;
		else
			x = y->right;
		x->parent = y->parent;
		if (x->parent == nil)
			root = x;
		else if (y = y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		if (y != z)
		{
			z->key = y->key;
		}
		if (y->color == 0)
		{
			RBTreeFixup(x);
		}
		return 1;
	}
	void RBTreeFixup(RBtreeNode* x)       //删除后的树平衡修复，4种情况
	{
		RBtreeNode*w;
		while (x != root&&x->color == 0)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					LeftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == 0 && w->right->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else
				{
					if (w->right->color == 0)
					{
						w->color = 1;
						RightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->right->color = 0;
					LeftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					RightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == 0 && w->left->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else
				{
					if (w->left->color == 0)
					{
						w->color = 1;
						LeftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->left->color = 0;
					RightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}
};

