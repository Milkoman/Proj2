#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
	private:
		T *data;
		Node<T>* next;
	public:
		Node(T *in);

		Node<T>* getNext()
		{
			return next;
		};

		T *getData()
		{
			return data;
		};

		void setNext(Node<T>* in_next)
		{
			next = in_next;
		};

		void setData(T *in_data)
		{
			data = *in_data;
		};
};

template <typename T>
Node<T>::Node(T *in)
{
	next = 0;
	data = in;
}

#endif
