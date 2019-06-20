#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <algorithm>

using std::ostream;
template<class T>
class BinaryNode;
template<class T>
ostream &operator<< (ostream &, const BinaryNode<T> &);


template<class T>
class BinaryNode
{
	private:
		T *data;
		BinaryNode<T> *left;
		BinaryNode<T> *right;

	public:
		//Constructors
		BinaryNode();
		BinaryNode(T &);
		BinaryNode(T &, BinaryNode<T> *, BinaryNode<T> *);

		//Mutators
		void setData(T & nodeData) { data = &nodeData; }
		void setLeftPtr(BinaryNode<T> *leftPtr) { left = leftPtr; }
		void setRightPtr(BinaryNode<T> *rightPtr) { right = rightPtr; }
		void swap();

		//Accessors
		T & getData() const { return *data; }
		BinaryNode<T> * getLeftPtr() const { return left; }
		BinaryNode<T> * getRightPtr() const { return right; }

		//Methods
		bool isLeaf() const { return left == nullptr && right == nullptr; }

		template <class U>
		friend ostream &operator<< (ostream &, const BinaryNode<T> &);


};

template<class T>
inline BinaryNode<T>::BinaryNode() : left(nullptr), right(nullptr)
{
}

template<class T>
inline BinaryNode<T>::BinaryNode(T & nodedata) : data(&nodedata), left(nullptr), right(nullptr)
{
}

template<class T>
inline BinaryNode<T>::BinaryNode(T & nodedata, BinaryNode<T>* Lptr, BinaryNode<T>* Rptr) : data(&nodedata), left(Lptr), right(Rptr)
{
}

template<class T>
inline void BinaryNode<T>::swap()
{
	BinaryNode<T> *temp = getLeftPtr();
	setLeftPtr(getRightPtr());
	setRightPtr(temp);

}

template<class T>
inline ostream & operator<<(ostream & strm, const BinaryNode<T> &obj)
{
	strm << obj.getData();
	return strm;
}
#endif
