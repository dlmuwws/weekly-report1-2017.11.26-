#pragma once

enum RBTColor { RED, BLACK };

template <class T>
class RBTNode {
public:
	RBTColor color;    
	T key;            
	RBTNode *left;    
	RBTNode *right;    
	RBTNode *parent; 

	RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		key(value), color(c), parent(), left(l), right(r) {}
};

template <class T>
class RBTree {
private:
	RBTNode<T> *mRoot;    // 根结点

public:
	RBTree();
	

	template <class T>//函数模板
	void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
	{
		
		RBTNode<T> *y = x->right;

		
		x->right = y->left;
		if (y->left != NULL)
			y->left->parent = x;

		
		y->parent = x->parent;

		if (x->parent == NULL)
		{
			root = y;           //y是根节点
		}
		else
		{
			if (x->parent->left == x)
				x->parent->left = y;   
			else
				x->parent->right = y;   
		}

		
		y->left = x;
	
		x->parent = y;
	}

	template <class T>
	void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
	{
		RBTNode<T> *y = NULL;
		RBTNode<T> *x = root;

		//添加一个节点
		while (x != NULL)
		{
			y = x;
			if (node->key < x->key)
				x = x->left;
			else
				x = x->right;
		}

		node->parent = y;
		if (y != NULL)
		{
			if (node->key < y->key)
				y->left = node;
			else
				y->right = node;
		}
		else
			root = node;

		//初始化为红色
		node->color = RED;

		
		insertFixUp(root, node);
	}

	
	template <class T>
	void RBTree<T>::insert(T key)
	{
		RBTNode<T> *z = NULL;

		//建不了节点
		if ((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
			return;

		insert(mRoot, z);
	}


	template <class T>
	void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T> *node)
	{
		RBTNode<T> *child, *parent;
		RBTColor color;

		
		if ((node->left != NULL) && (node->right != NULL))
		{
			
			RBTNode<T> *replace = node;

			//拿到后面的节点
			replace = replace->right;
			while (replace->left != NULL)
				replace = replace->left;

			
			if (rb_parent(node))
			{
				if (rb_parent(node)->left == node)
					rb_parent(node)->left = replace;
				else
					rb_parent(node)->right = replace;
			}
			else
				
				root = replace;

			
			child = replace->right;
			parent = rb_parent(replace);
			
			color = rb_color(replace);

		
			if (parent == node)
			{
				parent = replace;
			}
			else
			{
				
				if (child)
					rb_set_parent(child, parent);
				parent->left = child;

				replace->right = node->right;
				rb_set_parent(node->right, replace);
			}

			replace->parent = node->parent;
			replace->color = node->color;
			replace->left = node->left;
			node->left->parent = replace;

			if (color == BLACK)
				removeFixUp(root, child, parent);

			delete node;
			return;
		}

		if (node->left != NULL)
			child = node->left;
		else
			child = node->right;

		parent = node->parent;
		
		color = node->color;

		if (child)
			child->parent = parent;

		
		if (parent)
		{
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			root = child;

		if (color == BLACK)
			removeFixUp(root, child, parent);
		delete node;
	}

	
	template <class T>
	void RBTree<T>::remove(T key)
	{
		RBTNode<T> *node;

		if ((node = search(mRoot, key)) != NULL)
			remove(mRoot, node);
	}
};
