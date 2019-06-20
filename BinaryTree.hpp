#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <string>
#include "BinaryNode.hpp"
#include "Queue.h"

//Exception class
class EmptyTree {};
class NotFound {};

using std::ostream;
template<class T>
class BinaryTree;
template<class T>
ostream &operator<< (ostream &, const BinaryTree<T> &);


template<class T>
class BinaryTree
{
private:


protected:
	BinaryNode<T> *root;
	void destroyTree(BinaryNode<T> *);
	BinaryNode<T> * copyTree(const BinaryNode<T> *);
	int getHeightHelper(BinaryNode<T> *) const;
	int getNumNodesHelper(BinaryNode<T> *) const;
	BinaryNode<T> * placeNode(BinaryNode<T> *, BinaryNode<T> *);
	BinaryNode<T> * placeNode(BinaryNode<T> *, BinaryNode<T> *, bool leftGreaterThanRight(const T &,const  T &));
	BinaryNode<T> * removeNode(BinaryNode<T> *);
	BinaryNode<T> * removeLeftmostNode(BinaryNode<T> *, T **);
	BinaryNode<T> * removeValue(BinaryNode<T> *, const T &, bool &);
	BinaryNode<T> * removeValue(BinaryNode<T> *, const T &, bool &, bool LER(const T &, const  T &), bool LGR(const T &, const  T &));
	BinaryNode<T> * findNode(BinaryNode<T> *, const T &) const;
	BinaryNode<T> * findNode(BinaryNode<T> *, const T &, bool LER(const T &, const  T &), bool LGR(const T &, const  T &)) const;
	void ostreamHelper(BinaryNode<T> *) const;

	void breadthFirst(void visit(T &), BinaryNode<T> *treePtr) const;
	void preorder(void visit(T &), BinaryNode<T> *treePtr) const;
	void inorder(void visit(T &), BinaryNode<T> *treePtr) const;
	void postorder(void visit(T &), BinaryNode<T> *treePtr) const;

	void breadthFirst(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream &) const;
	void preorder(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream &) const;
	void inorder(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream &) const;
	void postorder(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream &) const;

	void breadthFirst(void visit(T &, int), BinaryNode<T> *treePtr) const;
	void preorder(void visit(T &, int), BinaryNode<T> *treePtr) const;
	void inorder(void visit(T &, int), BinaryNode<T> *treePtr) const;
	void postorder(void visit(T &, int), BinaryNode<T> *treePtr) const;

	void breadthFirst(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream&) const;
	void preorder(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream&) const;
	void inorder(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream&) const;
	void postorder(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream&) const;

	template<template<class V> class U>
	void breadthFirst(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>&) const;
	template<template<class V> class U>
	void preorder(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>&) const;
	template<template<class V> class U>
	void inorder(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>&) const;
	template<template<class V> class U>
	void postorder(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>&) const;

	template<template<class V> class U>
	void breadthFirst(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const;
	template<template<class V> class U>
	void preorder(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const;
	template<template<class V> class U>
	void inorder(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const;
	template<template<class V> class U>
	void postorder(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const;


	void breadthFirstBounded(void visit(T&), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const;
	void preorderBounded(void visit(T&), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const;
	void inorderBounded(void visit(T &), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const;
	void postorderBounded(void visit(T &), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const;

	template<template<class V> class U>
	void breadthFirstBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const;
	template<template<class V> class U>
	void preorderBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const;
	template<template<class V> class U>
	void inorderBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const;
	template<template<class V> class U>
	void postorderBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const;

	template<template<class V> class U>
	void breadthFirstBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const;
	template<template<class V> class U>
	void preorderBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const;
	template<template<class V> class U>
	void inorderBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const;
	template<template<class V> class U>
	void postorderBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const;
public:
	//Constructors & Destructor
	BinaryTree();
	BinaryTree(T &);



	//BinaryTree(const BinaryNode<T> *&tree) { root = copyTree(tree.root); }  !!!DOES NOT GET CALLED !!!

	virtual ~BinaryTree() { destroyTree(root); }

	//Methods
	bool isEmpty() const { return root == nullptr; }
	int getHeight() const { return getHeightHelper(root); }
	int getNumNodes() const { return getNumNodesHelper(root); }
	void setRootData(T &newData);
	T& getRootData() const;
	virtual bool add(T &);
	virtual bool add(T &, bool leftGreaterThanRight(const T &, const T &));
	bool remove(const T& target);
	bool remove(T & target, bool LER(const T &, const T &), bool LGR(const T &, const T &));
	T& search(const T & datain);
	void clear();
	bool replace(T & data, T &);
	bool replace(T & data, T &, bool LER(const T &, const T &), bool LGR(const T &, const T &));

	//Traversals ***Requires client defined function(s) - pass said function as argument***
	void preorderTraverse(void visit(T &)) const { preorder(visit, root); }
	void inorderTraverse(void visit(T &)) const { inorder(visit, root); }
	void postorderTraverse(void visit(T &)) const { postorder(visit, root); }
	void breadthFirstTraverse(void visit(T &)) const { breadthFirst(visit, root); }

	void preorderTraverse(void visit(T &, int)) const { preorder(visit, root); }
	void inorderTraverse(void visit(T &, int)) const { inorder(visit, root); }
	void postorderTraverse(void visit(T &, int)) const { postorder(visit, root); }
	void breadthFirstTraverse(void visit(T &, int)) const { breadthFirst(visit, root); }

	void preorderTraverse(void visit(T &, ostream &), ostream & strm) const { preorder(visit, root, strm); }
	void inorderTraverse(void visit(T &, std::ostream &), std::ostream & strm) const { inorder(visit, root, strm); }
	void postorderTraverse(void visit(T &, ostream &), ostream & strm) const { postorder(visit, root, strm); }
	void breadthFirstTraverse(void visit(T &, ostream &), ostream & strm) const { breadthFirst(visit, root, strm); }

	void preorderTraverse(void visit(T &, int, ostream &), ostream & strm) const { preorder(visit, root, strm); }
	void inorderTraverse(void visit(T &, int, ostream &), ostream & strm) const { inorder(visit, root, strm); }
	void postorderTraverse(void visit(T &, int, ostream &), ostream & strm) const { postorder(visit, root, strm); }
	void breadthFirstTraverse(void visit(T &, int, ostream &), ostream & strm) const { breadthFirst(visit, root, strm); }

	void inorderBoundedTraverse(void visit(T&), bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const { inorderBounded(visit, root, leftGreaterThanRight, min, max); }
	void breadthFirstBoundedTraverse(void visit(T&), bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const { breadthFirstBounded(visit, root, leftGreaterThanRight, min, max); }
	void preorderBoundedTraverse(void visit(T&), bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const { preorderBounded(visit, root, leftGreaterThanRight, min, max); }
	void postorderBoundedTraverse(void visit(T&), bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const { postorderBounded(visit, root, leftGreaterThanRight, min, max); }

	template<template<class V> class U>
	void breadthFirstTraverse(void visit(U<T>&, T&), U<T>& obj) const { breadthFirst(visit, root, obj); }
	template<template<class V> class U>
	void preorderTraverse(void visit(U<T>&, T&), U<T>& obj) const { preorder(visit, root, obj); }
	template<template<class V> class U>
	void inorderTraverse(void visit(U<T>&, T&), U<T>& obj) const { inorder(visit, root, obj); }
	template<template<class V> class U>
	void postorderTraverse(void visit(U<T>&, T&), U<T>& obj) const { postorder(visit, root, obj); }

	template<template<class V> class U>
	void breadthFirstTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterR(const T &, const T &)) const { breadthFirst(visit, root, obj, LGreaterR); }
	template<template<class V> class U>
	void preorderTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterR(const T &, const T &)) const { preorder(visit, root, obj, LGreaterR); }
	template<template<class V> class U>
	void inorderTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterR(const T &, const T &)) const { inorder(visit, root, obj, LGreaterR); }
	template<template<class V> class U>
	void postorderTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterR(const T &, const T &)) const { postorder(visit, root, obj, LGreaterR); }


	template<template<class V> class U>
	void breadthFirstBoundedTraverse(void visit(U<T>&, T&), U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const { breadthFirstBounded(visit, root, obj, LGreaterR, min, max); }
	template<template<class V> class U>
	void preorderBoundedTraverse(void visit(U<T>&, T&), U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const { preorderBounded(visit, root, obj, LGreaterR, min, max); }
	template<template<class V> class U>
	void inorderBoundedTraverse(void visit(U<T>&, T&), U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const { inorderBounded(visit, root, obj, LGreaterR, min, max); }
	template<template<class V> class U>
	void postorderBoundedTraverse(void visit(U<T>&, T&), U<T>& obj, bool LGreaterR(const T &, const T &), const T & min, const T & max) const { postorderBounded(visit, root, obj, LGreaterR, min, max); }

	template<template<class V> class U>
	void breadthFirstBoundedTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const { breadthFirstBounded(visit, root, obj, LGreaterRT, LGreaterRP, min, max); }
	template<template<class V> class U>
	void preorderBoundedTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const { preorderBounded(visit, root, obj, LGreaterRT, LGreaterRP, min, max); }
	template<template<class V> class U>
	void inorderBoundedTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const { inorderBounded(visit, root, obj, LGreaterRT, LGreaterRP, min, max); }
	template<template<class V> class U>
	void postorderBoundedTraverse(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), U<T>& obj, bool LGreaterRT(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const { postorderBounded(visit, root, obj, LGreaterRT, LGreaterRP, min, max); }

	template <class U>
	friend ostream &operator<< (ostream &, const BinaryTree<T> &);

};



/*
	Pre:
	Perameters: Pointer to root of tree to be destroyed
	Post: All of the nodes from the root down are deleted
*/
template<class T>
inline void BinaryTree<T>::destroyTree(BinaryNode<T> *nodePtr)
{
	if (nodePtr)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}
// !! NOT TESTED !! PUBLIC METHOD (COPY CONSTRUCTOR) NOT CALLING THIS
template<class T>
inline BinaryNode<T>* BinaryTree<T>::copyTree(const BinaryNode<T> *oldroot)
{
	BinaryNode<T> *newRoot;
	if (oldroot)
	{
		newRoot = new BinaryNode<T>(oldroot->getData(), nullptr, nullptr);
		newRoot->setLeftPtr(copyTree(oldroot->getLeftPtr()));
		newRoot->setRightPtr(copyTree(oldroot->getRightPtr()));
	}
	return newRoot;
}
/*
	Pre:
	Perameters: Pointer of root of tree
	Post: Returns the height of the tree from the root down
*/
template<class T>
inline int BinaryTree<T>::getHeightHelper(BinaryNode<T> *subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return  1 + std::max(getHeightHelper(subTreePtr->getLeftPtr()), getHeightHelper(subTreePtr->getRightPtr()));

}
/*
	Pre:
	Perameters: Pointer to root of tree
	Post: Returns the number of binary nodes in the tree
*/
template<class T>
inline int BinaryTree<T>::getNumNodesHelper(BinaryNode<T> *nodePtr) const
{
	if (nodePtr == nullptr)
		return 0;
	else
		return 1 + getNumNodesHelper(nodePtr->getLeftPtr()) + getNumNodesHelper(nodePtr->getRightPtr());

}
/*
	Pre:
	Perameters: Pointer to root of subtree, Pointer to node to be added
	Post: Places the node in the subtree according to BST rules
*/
template<class T>
inline BinaryNode<T>* BinaryTree<T>::placeNode(BinaryNode<T> *subTreePtr, BinaryNode<T> *newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else if (subTreePtr->getData() > newNodePtr->getData())
	{
		BinaryNode<T> *tempPtr = placeNode(subTreePtr->getLeftPtr(), newNodePtr);
		subTreePtr->setLeftPtr(tempPtr);
	}
	else
	{
		BinaryNode<T> *tempPtr = placeNode(subTreePtr->getRightPtr(), newNodePtr);
		subTreePtr->setRightPtr(tempPtr);
	}
	return subTreePtr;
}
/*
	Pre:
	Perameters: Pointer to root of subtree, Pointer to node to be added, Left>Right function that takes compare two objects of types T
	Post: Places the node in the subtree according to BST rules with the comparisons according to Left>Right function
*/
template<class T>
inline BinaryNode<T>* BinaryTree<T>::placeNode(BinaryNode<T> *subTreePtr, BinaryNode<T> *newNodePtr, bool leftGreaterThanRight(const T &, const T &))
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else if (leftGreaterThanRight(subTreePtr->getData(), newNodePtr->getData()))
	{
		BinaryNode<T> *tempPtr = placeNode(subTreePtr->getLeftPtr(), newNodePtr, leftGreaterThanRight);
		subTreePtr->setLeftPtr(tempPtr);
	}
	else
	{
		BinaryNode<T> *tempPtr = placeNode(subTreePtr->getRightPtr(), newNodePtr, leftGreaterThanRight);
		subTreePtr->setRightPtr(tempPtr);
	}
	return subTreePtr;
}
/*
	Pre:
	Perameters: Pointer to node to be removed
	Post: removes the node from the BST according to BST guidelines
*/
template<class T>
inline BinaryNode<T>* BinaryTree<T>::removeNode(BinaryNode<T> *nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == nullptr || nodePtr->getRightPtr() == nullptr)
	{
		if (nodePtr->getLeftPtr() != nullptr)
		{
			BinaryNode<T> *nodeToConnect = nodePtr->getLeftPtr();
			delete nodePtr;
			return nodeToConnect;
		}
		else
		{
			BinaryNode<T> *nodeToConnect = nodePtr->getRightPtr();
			delete nodePtr;
			return nodeToConnect;
		}
	}
	else
	{
		BinaryNode<T> *pNext = nodePtr->getRightPtr();
		T **newNodeValue = new T*;
		while (pNext->getLeftPtr())
		{
			*newNodeValue = &(pNext->getData());
			pNext = pNext->getLeftPtr();
		}


		BinaryNode<T> *tempPtr = removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue);
		nodePtr->setRightPtr(tempPtr);
		nodePtr->setData(**newNodeValue);
		delete newNodeValue;
		return nodePtr;
	}
}
/*
	Pre:
	Perameters: Pointer to node to be removed, reference T inorderSuccessor
	Post: Recursively finds the left-most node, sets its value to inorderSuccessor and deletes the node to be deleted
*/
template<class T>
inline BinaryNode<T>* BinaryTree<T>::removeLeftmostNode(BinaryNode<T> *nodePtr, T **inorderSuccessor)
{
	if (nodePtr->getLeftPtr() == nullptr)
	{
		*inorderSuccessor = &(nodePtr->getData());
		return removeNode(nodePtr);
	}
	else
	{
		BinaryNode<T> *tempPtr = removeLeftmostNode(nodePtr->getLeftPtr(), inorderSuccessor);
		nodePtr->setLeftPtr(tempPtr);
		return nodePtr;
	}

}
/*
	Pre:
	Perameters: Pointer to root of subtree, T target data, reference bool if succesful
	Post: Removes first node found with target data Returns new subtree to recurse with, sets isSuccessful to whether deletion was successful
*/
template<class T>
inline BinaryNode<T>* BinaryTree<T>::removeValue(BinaryNode<T> *subTreePtr, const T & target, bool &isSuccessful)
{
	if (subTreePtr == nullptr)
		isSuccessful = false;
	else if (subTreePtr->getData() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		isSuccessful = true;
	}
	else if (subTreePtr->getData() > target)
	{
		BinaryNode<T> *tempPtr = removeValue(subTreePtr->getLeftPtr(), target, isSuccessful);
		subTreePtr->setLeftPtr(tempPtr);
	}
	else
	{
		BinaryNode<T> *tempPtr = removeValue(subTreePtr->getRightPtr(), target, isSuccessful);
		subTreePtr->setRightPtr(tempPtr);
	}
	return subTreePtr;
}
template<class T>
inline BinaryNode<T>* BinaryTree<T>::removeValue(BinaryNode<T>* subTreePtr, const T & target, bool &isSuccessful, bool LER(const T &, const  T &), bool LGR(const T &, const  T &))
{
	if (subTreePtr == nullptr)
		isSuccessful = false;
	else if (LER(subTreePtr->getData(), target))
	{
		subTreePtr = removeNode(subTreePtr);
		isSuccessful = true;
	}
	else if (LGR(subTreePtr->getData(), target))
	{
		BinaryNode<T> *tempPtr = removeValue(subTreePtr->getLeftPtr(), target, isSuccessful, LER, LGR);
		subTreePtr->setLeftPtr(tempPtr);
	}
	else
	{
		BinaryNode<T> *tempPtr = removeValue(subTreePtr->getRightPtr(), target, isSuccessful, LER, LGR);
		subTreePtr->setRightPtr(tempPtr);
	}
	return subTreePtr;
}
/*
	Pre:
	Perameters: pointer to node to be used for recursion, T target data
	Post: nullptr if the data wasnt found, pointer to node if it was
*/
template<class T>
inline BinaryNode<T>* BinaryTree<T>::findNode(BinaryNode<T> *nodePtr, const T & target) const
{
	if (nodePtr == nullptr)
		return nullptr;
	else if (nodePtr->getData() == target)
		return nodePtr;
	else if (nodePtr->getData() > target)
		return findNode(nodePtr->getLeftPtr(), target);
	else
		return findNode(nodePtr->getRightPtr(), target);
}
template<class T>
inline BinaryNode<T>* BinaryTree<T>::findNode(BinaryNode<T>* nodePtr, const T & target, bool LER(const T &, const  T &), bool LGR(const T &, const  T &)) const
{


	if (nodePtr == nullptr)
		return nullptr;
	else if (LER(nodePtr->getData(), target))
		return nodePtr;
	else if (LGR(nodePtr->getData(), target))
		return findNode(nodePtr->getLeftPtr(), target, LER, LGR);
	else
		return findNode(nodePtr->getRightPtr(), target, LER, LGR);
}
/*
	Pre:
	Perameters: ostream reference, node ptr
	Post: out-streams to strm inOrder
*/
template<class T>
inline void BinaryTree<T>::ostreamHelper(BinaryNode<T>* ptr) const
{
	if (ptr)
	{
		ostreamHelper(ptr->getLeftPtr());
		std::cout << ptr->getData() << "  ";
		ostreamHelper(ptr->getRightPtr());
	}


}
/*
	Pre:
	Perameters: A processing function, root node pointer
	Post: Processess nodes according to visit breadth first
*/
template<class T>
inline void BinaryTree<T>::breadthFirst(void visit(T &), BinaryNode<T>* treePtr) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T> *> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();

		visit(active->getData());
		if (active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }

	}
}
/*
	Pre:
	Perameters: A processing function, root node pointer
	Post: Processess nodes according to visit preorder
*/
template<class T>
inline void BinaryTree<T>::preorder(void visit(T &), BinaryNode<T>* treePtr) const
{
	if (treePtr)
	{
		visit(treePtr->getData());
		preorder(visit, treePtr->getLeftPtr());
		preorder(visit, treePtr->getRightPtr());
	}
}
/*
	Pre:
	Perameters: A processing function, root node pointer
	Post: Processess nodes according to visit inorder
*/
template<class T>
inline void BinaryTree<T>::inorder(void visit(T &), BinaryNode<T>* treePtr) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr());
		visit(treePtr->getData());
		inorder(visit, treePtr->getRightPtr());
	}
}
/*
	Pre:
	Perameters: A processing function, root node pointer
	Post: Processess nodes according to visit postorder
*/
template<class T>
inline void BinaryTree<T>::postorder(void visit(T &), BinaryNode<T>* treePtr) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftPtr());
		postorder(visit, treePtr->getRightPtr());
		visit(treePtr->getData());

	}
}

/*
	Pre:
	Perameters: A processing function with ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit breadth first
*/
template<class T>
inline void BinaryTree<T>::breadthFirst(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream & strm) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T>*> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();
		visit(active->getData(), strm);
		if (active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }

	}
}
/*
	Pre:
	Perameters: A processing function with ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit preorder
*/
template<class T>
inline void BinaryTree<T>::preorder(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (treePtr)
	{
		visit(treePtr->getData(), strm);
		preorder(visit, treePtr->getLeftPtr(), strm);
		preorder(visit, treePtr->getRightPtr(), strm);
	}
}
/*
	Pre:
	Perameters: A processing function with ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit inorder
*/

template<class T>
inline void BinaryTree<T>::inorder(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr(), strm);
		visit(treePtr->getData(), strm);
		inorder(visit, treePtr->getRightPtr(), strm);
	}
}

/*
	Pre:
	Perameters: A processing function with ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit postorder
*/
template<class T>
inline void BinaryTree<T>::postorder(void visit(T &, ostream &), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftPtr(), strm);
		postorder(visit, treePtr->getRightPtr(), strm);
		visit(treePtr->getData(), strm);

	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node, root node pointer
	Post: Processess nodes according to visit breadth first
*/
template<class T>
inline void BinaryTree<T>::breadthFirst(void visit(T &, int), BinaryNode<T>* treePtr) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T> *> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();
		visit(active->getData(), getHeightHelper(active));
		if (active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }

	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node, root node pointer
	Post: Processess nodes according to visit preorder
*/
template<class T>
inline void BinaryTree<T>::preorder(void visit(T &, int), BinaryNode<T>* treePtr) const
{
	if (treePtr)
	{
		visit(treePtr->getData(), getHeightHelper(treePtr));
		preorder(visit, treePtr->getLeftPtr());
		preorder(visit, treePtr->getRightPtr());
	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node, root node pointer
	Post: Processess nodes according to visit inorder
*/
template<class T>
inline void BinaryTree<T>::inorder(void visit(T &, int), BinaryNode<T>* treePtr) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr());
		visit(treePtr->getData(), getHeightHelper(treePtr));
		inorder(visit, treePtr->getRightPtr());
	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node, root node pointer
	Post: Processess nodes according to visit postorder
*/
template<class T>
inline void BinaryTree<T>::postorder(void visit(T &, int), BinaryNode<T>* treePtr) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftPtr());
		postorder(visit, treePtr->getRightPtr());
		visit(treePtr->getData(), getHeightHelper(treePtr));

	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node and ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit breadth first
*/
template<class T>
inline void BinaryTree<T>::breadthFirst(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T>*> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();

		visit(active->getData(), getHeightHelper(treePtr), strm);
		if (active->getLeftPtr()) { queue.enqueue(active->getLeftPtr(), strm); }
		if (active->getRightPtr()) { queue.enqueue(active->getRightPtr(), strm); }

	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node and ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit preorder
*/
template<class T>
inline void BinaryTree<T>::preorder(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (treePtr)
	{
		visit(treePtr->getData(), getHeightHelper(treePtr), strm);
		preorder(visit, treePtr->getLeftPtr(), strm);
		preorder(visit, treePtr->getRightPtr(), strm);
	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node and ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit inorder
*/
template<class T>
inline void BinaryTree<T>::inorder(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr(), strm);
		visit(treePtr->getData(), getHeightHelper(treePtr), strm);
		inorder(visit, treePtr->getRightPtr(), strm);
	}
}
/*
	Pre:
	Perameters: A processing function that also accepts the height of the node and ostream ref, root node pointer, ostream ref
	Post: Processess nodes according to visit postorder
*/
template<class T>
inline void BinaryTree<T>::postorder(void visit(T &, int, ostream&), BinaryNode<T>* treePtr, ostream& strm) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftPtr(), strm);
		postorder(visit, treePtr->getRightPtr(), strm);
		visit(treePtr->getData(), getHeightHelper(treePtr), strm);

	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::breadthFirst(void visit(U<T> &, T&), BinaryNode<T>* treePtr, U<T>& obj) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T> *> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();

		visit(obj, active->getData());
		if (active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::preorder(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj) const
{
	if (treePtr)
	{
		visit(obj, treePtr->getData());
		preorder(visit, treePtr->getLeftPtr(), obj);
		preorder(visit, treePtr->getRightPtr(), obj);
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::inorder(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr(), obj);
		visit(obj, treePtr->getData());
		inorder(visit, treePtr->getRightPtr(), obj);
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::postorder(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftPtr(), obj);
		postorder(visit, treePtr->getRightPtr(), obj);
		visit(obj, treePtr->getData());

	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::breadthFirst(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T> *> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();

		visit(obj, active->getData(), LGreaterR);
		if (active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::preorder(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const
{
	if (treePtr)
	{

		visit(obj, treePtr->getData(), LGreaterR);
		preorder(visit, treePtr->getLeftPtr(), obj, LGreaterR);
		preorder(visit, treePtr->getRightPtr(), obj, LGreaterR);
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::inorder(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr(), obj, LGreaterR);
		visit(obj, treePtr->getData(), LGreaterR);
		inorder(visit, treePtr->getRightPtr(), obj, LGreaterR);
	}
}
template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::postorder(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool LGreaterR(const T &, const T &)) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftPtr(), obj, LGreaterR);
		postorder(visit, treePtr->getRightPtr(), obj, LGreaterR);
		visit(obj, treePtr->getData(), LGreaterR);
	}
}




template<class T>
inline void BinaryTree<T>::inorderBounded(void visit(T &), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const
{
	if (treePtr)
	{

		if (!leftGreaterThanRight(min, treePtr->getData())) {
			inorderBounded(visit, treePtr->getLeftPtr(), leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(treePtr->getData());
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			inorderBounded(visit, treePtr->getRightPtr(), leftGreaterThanRight, min, max);
		}


	}
}
template<class T>
inline void BinaryTree<T>::postorderBounded(void visit(T&), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T &, const T &), const T& min, const T& max) const
{
	if (treePtr)
	{

		if (!leftGreaterThanRight(min, treePtr->getData())) {
			postorderBounded(visit, treePtr->getLeftPtr(), leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			postorderBounded(visit, treePtr->getRightPtr(), leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(treePtr->getData());
		}
	}
}
template<class T>
inline void BinaryTree<T>::breadthFirstBounded(void visit(T&), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T &, const T &), const T& min, const T& max) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T>*> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();
		if (!leftGreaterThanRight(min, active->getData()) && !leftGreaterThanRight(active->getData(), max)) {
			visit(active->getData());
		}

		if (!leftGreaterThanRight(min, active->getData()) && active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (!leftGreaterThanRight(active->getData(), max) && active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }

	}
}
template<class T>
inline void BinaryTree<T>::preorderBounded(void visit(T&), BinaryNode<T>* treePtr, bool leftGreaterThanRight(const T&, const T&), const T& min, const T& max) const
{
	if (treePtr)
	{
		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(treePtr->getData());
		}
		if (!leftGreaterThanRight(min, treePtr->getData())) {
			preorderBounded(visit, treePtr->getLeftPtr(), leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			preorderBounded(visit, treePtr->getRightPtr(), leftGreaterThanRight, min, max);
		}
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::breadthFirstBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T>*> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();
		if (!leftGreaterThanRight(min, active->getData()) && !leftGreaterThanRight(active->getData(), max)) {
			visit(obj, active->getData());
		}

		if (!leftGreaterThanRight(min, active->getData()) && active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (!leftGreaterThanRight(active->getData(), max) && active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }

	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::preorderBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const
{
	if (treePtr)
	{
		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(obj, treePtr->getData());
		}
		if (!leftGreaterThanRight(min, treePtr->getData())) {
			preorderBounded(visit, treePtr->getLeftPtr(), obj, leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			preorderBounded(visit, treePtr->getRightPtr(), obj, leftGreaterThanRight, min, max);
		}
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::inorderBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const
{
	if (treePtr)
	{

		if (!leftGreaterThanRight(min, treePtr->getData())) {
			inorderBounded(visit, treePtr->getLeftPtr(), obj, leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(obj, treePtr->getData());
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			inorderBounded(visit, treePtr->getRightPtr(), obj, leftGreaterThanRight, min, max);
		}
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::postorderBounded(void visit(U<T>&, T&), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), const T & min, const T & max) const
{
	if (treePtr)
	{

		if (!leftGreaterThanRight(min, treePtr->getData())) {
			postorderBounded(visit, treePtr->getLeftPtr(), obj, leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			postorderBounded(visit, treePtr->getRightPtr(), obj, leftGreaterThanRight, min, max);
		}

		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(obj, treePtr->getData());
		}
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::breadthFirstBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const
{
	if (!treePtr) { return; }
	Queue<BinaryNode<T>*> queue;
	queue.enqueue(treePtr);

	while (!queue.isEmpty()) {
		BinaryNode<T>* active = queue.dequeue();
		if (!leftGreaterThanRight(min, active->getData()) && !leftGreaterThanRight(active->getData(), max)) {
			visit(obj, active->getData(), LGreaterRP);
		}

		if (!leftGreaterThanRight(min, active->getData()) && active->getLeftPtr()) { queue.enqueue(active->getLeftPtr()); }
		if (!leftGreaterThanRight(active->getData(), max) && active->getRightPtr()) { queue.enqueue(active->getRightPtr()); }

	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::preorderBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const
{
	if(treePtr)
	{
		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(obj, treePtr->getData(), LGreaterRP);
		}
		if (!leftGreaterThanRight(min, treePtr->getData())) {
			preorderBounded(visit, treePtr->getLeftPtr(), obj, leftGreaterThanRight, LGreaterRP, min, max);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			preorderBounded(visit, treePtr->getRightPtr(), obj, leftGreaterThanRight, LGreaterRP, min, max);
		}
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::inorderBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const
{
	if (treePtr)
	{

		if (!leftGreaterThanRight(min, treePtr->getData())) {
			inorderBounded(visit, treePtr->getLeftPtr(), obj, leftGreaterThanRight, LGreaterRP, min, max);
		}

		if (!leftGreaterThanRight(min, treePtr->getData()) && !leftGreaterThanRight(treePtr->getData(), max)) {
			visit(obj, treePtr->getData(), LGreaterRP);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			inorderBounded(visit, treePtr->getRightPtr(), obj, leftGreaterThanRight, LGreaterRP, min, max);
		}
	}
}

template<class T>
template<template<class V> class U>
inline void BinaryTree<T>::postorderBounded(void visit(U<T>&, T&, bool LgreaterR(const T &, const T &)), BinaryNode<T>* treePtr, U<T>& obj, bool leftGreaterThanRight(const T &, const T &), bool LGreaterRP(const T &, const T &), const T & min, const T & max) const
{
	if (treePtr)
	{

		if (!leftGreaterThanRight(min, treePtr->getData())) {
			postorderBounded(visit, treePtr->getLeftPtr(), obj, leftGreaterThanRight, LGreaterRP, min, max);
		}

		if (!leftGreaterThanRight(treePtr->getData(), max)) {
			postorderBounded(visit, treePtr->getRightPtr(), obj, leftGreaterThanRight, LGreaterRP, min, max);
		}

		T theItem = treePtr->getData();
		if (!leftGreaterThanRight(min, theItem) && !leftGreaterThanRight(theItem, max)) {
			visit(obj, theItem, LGreaterRP);
		}
	}
}


/*
	Pre:
	Perameters:
	Post: Sets root to nullptr
*/
template<class T>
inline BinaryTree<T>::BinaryTree() : root(nullptr)
{
}
/*
	Pre:
	Perameters: T root data
	Post: Creates new node with root data, and sets root to it
*/
template<class T>
inline BinaryTree<T>::BinaryTree(T &rootData)
{
	BinaryNode<T> *newnode = new BinaryNode<T>(rootData);
	root = newnode;

}

/*
	Pre:
	Perameters: T root data
	Post: Sets root data
*/
template<class T>
inline void BinaryTree<T>::setRootData(T & newData)
{
	if (isEmpty())
	{
		BinaryNode<T> *newnode = new BinaryNode<T>(newData);
		root = newnode;
	}
	else
		root->setData(newData);

}
/*
	Pre:
	Perameters:
	Post: Returns root data
*/
template<class T>
inline T& BinaryTree<T>::getRootData() const
{
	if (isEmpty())
		throw EmptyTree();
	else
		return root->getData();
}
/*
	Pre:
	Perameters: T data to be added
	Post: creates a new node with the datam and places it according to placeNode with root as the subtree
*/
template<class T>
inline bool BinaryTree<T>::add(T &newData)
{
	BinaryNode<T> *newNode = new BinaryNode<T>(newData);
	root = placeNode(root, newNode);
	return true;
}
/*
	Pre:
	Perameters: T data to be added, comparison function
	Post: creates a new node with the datam and places it according to placeNode with root as the subtree and the comparison function
*/
template<class T>
inline bool BinaryTree<T>::add(T & newData, bool leftGreaterThanRight(const T &,const  T &))
{
	BinaryNode<T> *newNode = new BinaryNode<T>(newData);
	root = placeNode(root, newNode, leftGreaterThanRight);
	return true;
}

/*
	Pre:
	Perameters: T data to be removed
	Post: Finds and removes first oucurrence of target data in tree
*/
template<class T>
inline bool BinaryTree<T>::remove(const T & target)
{
	bool isSuccessful = false;
	root = removeValue(root, target, isSuccessful);
	return isSuccessful;
}
template<class T>
inline bool BinaryTree<T>::remove(T & target, bool LER(const T &, const T &), bool LGR(const T &, const T &))
{
	bool isSuccessful = false;
	root = removeValue(root, target, isSuccessful, LER, LGR);
	return isSuccessful;
}
/*
	Pre:
	Perameters: T data to be searched for
	Post: Whether or not the data is in the tree
*/
template<class T>
inline T& BinaryTree<T>::search(const T & dataIn)
{
	if (findNode(root, dataIn))
		return dataIn;
	else
		throw NotFound();
}
/*
	Pre:
	Perameters:
	Post: Destroys tree
*/
template<class T>
inline void BinaryTree<T>::clear()
{
	destroyTree(root);
	root = nullptr;
}

template<class T>
inline bool BinaryTree<T>::replace(T & dataOut, T & dataIn)
{
	bool success;
	if (findNode(root, dataOut)) {
		removeValue(root, dataOut, success);
		if (!success) {
			return false;
		}
		add(dataIn);

		return true;
	}
	return false;
}

template<class T>
inline bool BinaryTree<T>::replace(T & dataOut, T & dataIn, bool LER(const T &, const T &), bool LGR(const T &, const T &))
{
	bool success;
	if (findNode(root, dataOut, LER, LGR)) {
		removeValue(root, dataOut, success, LER, LGR);
		if (!success) {
			return false;
		}
		add(dataIn);

		return true;
	}
	return false;
}


/*
	Pre:
	Perameters: ostream refm BinaryTree ref
	Post: overloaded ostream operator
*/
template<class T>
inline ostream & operator<<(ostream & strm, const BinaryTree<T> &obj)
{
	obj.ostreamHelper(obj.root);
	return strm;
}


template<class U, class T>
inline void inorder(void visit(U&,T&), U & othercls, BinaryNode<T>* treePtr)
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftPtr());
		T theItem = treePtr->getData();
		visit(othercls, theItem);
		inorder(visit, treePtr->getRightPtr());
	}
}




#endif
