	#pragma once

//standard binary tree node
	template <typename T> class Tree;

	template <typename T>
	class TreeNode
	{
		friend class Tree<T>;
	public:
		TreeNode(const T & value) : data(value), left(NULL), right(NULL) {};
	private:
		TreeNode<T> *left;
		TreeNode<T> *right;
		T data;
	};