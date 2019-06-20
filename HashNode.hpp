#ifndef HASHNODE_H
#define HASHNODE_H

template <class K, class T>
class HashNode
{
	private:
		K key;
		T *data;
		HashNode<K,T> *next;
	public:
		HashNode(const K &k, T *d) : key(k), data(d), next(nullptr){}

		K getKey() const { return key; }
		T getData() const { return *data; }
		HashNode<K,T> * getNext() const { return next; }
		void setData( T *d) { data = d; }
		void setNext(HashNode<K,T> *ptr) { next = ptr; }
};
#endif
