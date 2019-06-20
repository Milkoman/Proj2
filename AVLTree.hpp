#ifndef AVLTREE_H
#define AVLTREE_H
#include <algorithm>
#include <string>
#include "BinaryNode.hpp"
#include "BinaryTree.hpp"

template<class T>
class AVLTree : public BinaryTree<T>
{
protected:
	void rotateLeft(BinaryNode<T> *treePtr);
	void rotateRight(BinaryNode<T> *treePtr);

public:
	AVLTree(T data) : BinaryTree<T>(data) {}
	void rotateL(const T& target);
};


#endif // !AVLTREE_H

template<class T>
inline void AVLTree<T>::rotateLeft(BinaryNode<T> *treePtr)
{
	if (treePtr->getRightPtr() == nullptr) {
	}
	else {
		T tempData = treePtr->getData();
		treePtr->setData(treePtr->getRightPtr()->getData());
		treePtr->getRightPtr()->setData(tempData);

		treePtr->getRightPtr()->swap();
		treePtr->swap();

		BinaryNode<T>* temp = treePtr->getRightPtr();

		treePtr->setRightPtr(treePtr->getLeftPtr()->getLeftPtr());
		treePtr->getLeftPtr()->setLeftPtr(temp);
	}
	
}

template<class T>
inline void AVLTree<T>::rotateRight(BinaryNode<T>* treePtr)
{
	if (treePtr->getRightPtr() == nullptr) {
	}
	else {
		T tempData = treePtr->getData();
		treePtr->setData(treePtr->getLeftPtr()->getData());
		treePtr->getLeftPtr()->setData(tempData);

		treePtr->getLeftPtr()->swap();
		treePtr->swap();

		BinaryNode<T>* temp = treePtr->getLeftPtr();

		treePtr->setLeftPtr(treePtr->getRightPtr()->getRightPtr());
		treePtr->getRightPtr()->setRightPtr(temp);
	}
}

template<class T>
inline void AVLTree<T>::rotateL(const T& target)
{
	rotateLeft(this->findNode(this->root, target));
}
