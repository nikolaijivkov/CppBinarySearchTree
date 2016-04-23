// CppBinarySearchTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <queue>
#include <limits>

using namespace std;

template<class T>
struct BSTNode {
	T data;
	BSTNode<T>* left = nullptr;
	BSTNode<T>* right = nullptr;

	BSTNode(T data) : data(data) {}
	BSTNode(T data, BSTNode<T>* left, BSTNode<T>* right) : data(data), left(left), right(right) {};
};

template<class T>
class BSTree {
	BSTNode<T>* root = nullptr;

	void _Insert(BSTNode<T>* &nodePtr, const T data) {
		if (!nodePtr)  // empty node or empty tree
			nodePtr = new BSTNode<T>(data);
		else if (data <= nodePtr->data)
			_Insert(nodePtr->left, data);
		else
			_Insert(nodePtr->right, data);
	}

	BSTNode<T>* _Delete(BSTNode<T>* nodePtr, const T data) {
		if (!nodePtr)
			return nullptr;
		else if (data < nodePtr->data)
			nodePtr->left = _Delete(nodePtr->left, data);
		else if (data > nodePtr->data)
			nodePtr->right = _Delete(nodePtr->right, data);
		else {  // node found
				// case 1: node with no children
			if (!nodePtr->left && !nodePtr->right) {
				delete nodePtr;
				nodePtr = nullptr;
			}
			// case 2: node with one child - left
			else if (nodePtr->left && !nodePtr->right) {
				BSTNode<T>* temp = nodePtr;
				nodePtr = nodePtr->left;
				delete temp;
			}
			// case 2: node with one child - right
			else if (!nodePtr->left && nodePtr->right) {
				BSTNode<T>* temp = nodePtr;
				nodePtr = nodePtr->right;
				delete temp;
			}
			// case 3: node with two children
			else {
				BSTNode<T>* temp = _FindMin(nodePtr->right);
				nodePtr->data = temp->data;
				nodePtr->right = _Delete(nodePtr->right, temp->data);
			}
		}
		return nodePtr;
	}

	bool _Search(BSTNode<T>* nodePtr, const T data) const {
		if (!nodePtr) return false;
		else if (nodePtr->data == data) return true;
		else if (data <= nodePtr->data) return _Search(nodePtr->left, data);
		else return _Search(nodePtr->right, data);
	}

	BSTNode<T>* _FindMin(BSTNode<T>* nodePtr) const {
		if (!nodePtr) {  // empty tree !!!
			cout << "Error: Tree is Empty!" << endl;
			return 0;
			//throw exception("Error: Tree is Empty!");
		}
		while (nodePtr->left)
			nodePtr = nodePtr->left;
		return nodePtr;
	}

	BSTNode<T>* _FindMax(BSTNode<T>* nodePtr) const {
		if (!nodePtr) {  // empty tree !!!
			cout << "Error: Tree is Empty!" << endl;
			return 0;
			//throw exception("Error: Tree is Empty!");
		}
		while (nodePtr->right)
			nodePtr = nodePtr->right;
		return nodePtr;
	}

	int _Height(BSTNode<T>* nodePtr) {
		if (!nodePtr)
			return -1;  // will count number of edges
						//return 0; // will count number of nodes

		int leftHeight = _Height(nodePtr->left);
		int rightHeight = _Height(nodePtr->right);

		return 1 + max(leftHeight, rightHeight);
	}

	bool _IsBSTree(BSTNode<T> *nodePtr, T minValue, T maxValue) const {
		// Check if Binary Tree is Binary Search Tree, 
		// assuming that if Binary Tree can hold duplicating data, all duplicates will be in left subtree
		if (!nodePtr) return true;

		if (nodePtr->data >= minValue && nodePtr->data <= maxValue
			&& _IsBSTree(nodePtr->left, minValue, nodePtr->data)
			&& _IsBSTree(nodePtr->right, nodePtr->data, maxValue))
			return true;
		else
			return false;
	}

	void _PreOrderTraversal(BSTNode<T>* nodePtr) const {  // Data, Left, Right
		if (!nodePtr) return;

		cout << nodePtr->data << ' ';
		_PreOrderTraversal(nodePtr->left);
		_PreOrderTraversal(nodePtr->right);
	}

	void _InOrderTraversal(BSTNode<T>* nodePtr) const {  // Left, Data, Right
		if (!nodePtr) return;

		_InOrderTraversal(nodePtr->left);
		cout << nodePtr->data << ' ';
		_InOrderTraversal(nodePtr->right);
	}

	void _PostOrderTraversal(BSTNode<T>* nodePtr) const {  // Left, Right, Data
		if (!nodePtr) return;

		_PostOrderTraversal(nodePtr->left);
		_PostOrderTraversal(nodePtr->right);
		cout << nodePtr->data << ' ';
	}

	void _LevelOrderTraversal(BSTNode<T>* nodePtr) const {
		if (!nodePtr) return;

		queue<BSTNode<T>*> que;
		que.push(nodePtr);

		while (!que.empty()) {
			BSTNode<T> *nodePtr = que.front(); que.pop();
			cout << nodePtr->data << ' ';
			if (nodePtr->left)
				que.push(nodePtr->left);
			if (nodePtr->right)
				que.push(nodePtr->right);
		}
	}

	void _DestroyTree(BSTNode<T>* nodePtr) {
		if (nodePtr) {
			_DestroyTree(nodePtr->left);
			_DestroyTree(nodePtr->right);
			delete nodePtr;
		}
	}

public:
	BSTree() { };
	BSTree(const T data) : root(new BSTNode<T>(data)) { };

	void Insert(const T data) { _Insert(root, data); }
	void Delete(const T data) { root = _Delete(root, data); }
	bool Search(const T data) const { return _Search(root, data); }

	T FindMin() const { return _FindMin(root)->data; }
	T FindMax() const { return _FindMax(root)->data; }
	int Height() const { return _Height(root); }
	bool IsBSTree() const { return _IsBSTree(root, numeric_limits<T>::min(), numeric_limits<T>::max()); }

	// https://en.wikipedia.org/wiki/Tree_traversal
	void PreOrderTraversal() const { _PreOrderTraversal(root); cout << endl << endl; }
	void InOrderTraversal() const { _InOrderTraversal(root); cout << endl << endl; }
	void PostOrderTraversal() const { _PostOrderTraversal(root); cout << endl << endl; }
	void LevelOrderTraversal() const { _LevelOrderTraversal(root); cout << endl << endl; }

	~BSTree() { _DestroyTree(root); }
};


int main()
{
	BSTree<char> bstree;
	bstree.Insert('F');
	bstree.Insert('B');
	bstree.Insert('G');
	bstree.Insert('A');
	bstree.Insert('D');
	bstree.Insert('C');
	bstree.Insert('E');
	bstree.Insert('I');
	bstree.Insert('H');

	cout << "PreOrder Traversal :" << endl;
	bstree.PreOrderTraversal();

	cout << "InOrder Traversal: " << endl;
	bstree.InOrderTraversal();

	cout << "PostOrder Traversal: " << endl;
	bstree.PostOrderTraversal();

	cout << "LevelOrder Traversal: " << endl;
	bstree.LevelOrderTraversal();

	cout << "Min data in tree: " << bstree.FindMin() << endl << endl;

	cout << "Max data in tree: " << bstree.FindMax() << endl << endl;

	cout << "Is this Tree a valid Binary Search Tree: " << std::boolalpha << bstree.IsBSTree() << endl << endl;

	bstree.Delete('F');
	cout << "InOrder Traversal after 'F' is deleted: " << endl;
	bstree.InOrderTraversal();

	cin.get();
	return 0;
}

