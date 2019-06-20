#ifndef ADTSTATIC_H
#define ADTSTATIC_H
#include "Queue.h"
#include "BinaryTree.hpp"

class ADTStatic
{
public:
	template <class T>
	static void loadQueue(Queue<T> & q, T & data) { q.enqueue(data, true); }

	template <class T>
	static void loadBinaryTree(BinaryTree<T> & tree, T & data) { tree.add(data); }

	template <class T>
	static void loadBinaryTree(BinaryTree<T> & tree, T & data, bool LGR(const T &, const T &)) { tree.add(data, LGR); }

	template <class T>
	static void loadLinkedList(List<T> & l, T & data) { l.insertRear(&data); }
};

#endif // !ADTSTATIC_H
