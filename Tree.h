#pragma once
#include <iostream>
#include "TreeNode.h"
using namespace std;


//standard binary tree using composition
template <typename T>
class Tree
{
private:
	TreeNode<T> *root;
	void insertNodeHelper(TreeNode<T> **, const T &);
	void postOrderHelper(TreeNode<T> *);
	void preOrderHelper(TreeNode<T> *);
	void inOrderHelper(TreeNode<T> *);
	int getHeightHelper(TreeNode<T> *);
	int getMax(const int &, const int &) const;
public:
	Tree();
	void insert(const T &);
	void postOrder();
	void preOrder();
	void inOrder();
	int getHeight();
	friend ostream &operator<< (ostream &strm, const Tree<T> &obj);
};


template <typename T>
Tree<T>::Tree()
{
	root = NULL;
}

template <typename T>
void Tree<T>::insert(const T &value)
{
	insertNodeHelper(&root, value);
}

template <typename T>
void Tree<T>::insertNodeHelper(TreeNode<T> **ptr, const T &value)
{
	if (*ptr == NULL)
	{
		*ptr = new TreeNode<T>(value);
	}
	else
	{
		if (value < (*ptr)->data)
			insertNodeHelper(&(*ptr)->left, value);
		else
			insertNodeHelper(&(*ptr)->right, value);
	}
}

template <typename T>
void Tree<T>::postOrder()
{
	postOrderHelper(root);
	cout << endl;
}

template <typename T>
void Tree<T>::preOrder()
{
	preOrderHelper(root);
	cout << endl;
}

template <typename T>
void Tree<T>::inOrder()
{
	inOrderHelper(root);
	cout << endl;
}

template <typename T>
void Tree<T>::postOrderHelper(TreeNode<T> *ptr)
{
	if (ptr != NULL)
	{
		postOrderHelper(ptr->left);
		postOrderHelper(ptr->right);
		cout << ptr->data << " ";
	}
}

template <typename T>
void Tree<T>::preOrderHelper(TreeNode<T> *ptr)
{
	if (ptr != NULL)
	{
		cout << ptr->data << " ";
		preOrderHelper(ptr->left);
		preOrderHelper(ptr->right);
	}
}

template <typename T>
void Tree<T>::inOrderHelper(TreeNode<T> *ptr)
{
	if (ptr != NULL)
	{
		inOrderHelper(ptr->left);
		cout << ptr->data << " ";
		inOrderHelper(ptr->right);
	}
}

template <typename T>
int Tree<T>::getHeight()
{
	return getHeightHelper(root);
}

template <typename T>
int Tree<T>::getHeightHelper(TreeNode<T> *ptr)
{
	if (ptr == NULL)
		return 0;
	else
	{
		return 1 + getMax(getHeightHelper(ptr->left), getHeightHelper(ptr->right));
	}
}

template <typename T>
int Tree<T>::getMax(const int &a, const int &b) const
{
	return (a > b) ? a : b;
}


template <typename T>
ostream &operator<< (ostream &strm, const Tree<T> &obj)
{
	return strm;
}