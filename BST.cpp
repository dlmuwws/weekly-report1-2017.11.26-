#include"BST.h"


TreeNode::TreeNode()
{
	key = 0;
	left = right = p = NULL;
}
TreeNode::TreeNode(int val)
{
	key = val;
	left = right = p = NULL;
}
void inorder_tree_walk(TreeNode* x)           
{
	if (x != NULL)
	{
		inorder_tree_walk(x->left);
		cout << x->key << " ";
		inorder_tree_walk(x->right);
	}
	else
		return;
}
void preorder_tree_walk(TreeNode*x)        //前序遍历
{
	if (x)
	{
		cout << x->key << " ";
		preorder_tree_walk(x->left);
		preorder_tree_walk(x->right);
	}
}

TreeNode* tree_search(TreeNode* x, int k)   
{
	if (x == NULL || k == x->key)
	return x;
if (k<x->key)
	return tree_search(x->left,k);
else return tree_search(x->right,k);
}
TreeNode* tree_minmum(TreeNode* x)   
{
	while (x->left != NULL)
		x = x->left;
	return x;
}
TreeNode* tree_maxmum(TreeNode* x)
{
	while (x->right != NULL)
		x = x->right;
	return x;
}
TreeNode* tree_successor(TreeNode* x)   
{
	if (x->right)
		return tree_minmum(x->right);
	TreeNode* y = x->p;
	while (y&& x == y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}
TreeNode* tree_predecessor(TreeNode* x)   //小于x.key的最大关键字的节点为前驱   
{
	if (x->left)
		return tree_maxmum(x->left);
	TreeNode* y = x->p;
	while (y&& x == y->left)
	{
		x = y;
		y = y->p;
	}
	return y;
}
//c插入  
void tree_insert(TreeNode* T, TreeNode* z)    //T是现在的BST的树根  
{
	TreeNode * y = T; TreeNode *x = T;
	while (x)
	{
		y = x;
		if (z->key<x->key)
			x = x->left;
		else x = x->right;
	}
	z->p = y;
	if (!y)
		T = z;//T是颗空树  
	else if (z->key<y->key)
		y->left = z;
	else y->right = z;
	//   return T;   
}
//删除树节点  
void transplant(TreeNode* T, TreeNode* u, TreeNode* v)//用一颗子树代v替另一个子树u   
{
	if (u->p == NULL)
		T = v;
	else if (u == u->p->left)
		u->p->left = v;
	else u->p->right = v;
	if (v)
		v->p = u->p;
}
void tree_delete(TreeNode* T, TreeNode* z)
{
	if (!z->left)
		transplant(T, z, z->right);
	else if (!z->right)
		transplant(T, z, z->left);
	else {
		TreeNode* y = tree_minmum(z->right);
		if (y->p != z)
		{
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		y->left->p = y;
	}
}

	int main()
	{
	TreeNode* T = new TreeNode(15);
	int a[10] = { 2,4,7,9,10,12,6,8,1,15 };
	for (int i = 0; i<10; i++)
	{
		TreeNode* z = new TreeNode(a[i]);
		tree_insert(T, z);
	}
	inorder_tree_walk(T); cout << endl;
	preorder_tree_walk(T);
	TreeNode* min = tree_minmum(T);
	TreeNode* max = tree_maxmum(T); cout << endl;
	cout << "最大值：" << max->key << "  最小值：" << min->key << endl;
	cout << "查找z=9的节点：";
	TreeNode* z = tree_search(T, 13); cout << z->key << endl;
	TreeNode* prez = tree_predecessor(z);
	TreeNode* sucz = tree_successor(z);
	cout << "z的前驱：" << prez->key << " " << "z的后继：" << sucz->key << endl;
	tree_delete(T, z);
	cout << "删除z之后：";
	inorder_tree_walk(T); cout << endl;
	system("pause");
	return 0;
}
