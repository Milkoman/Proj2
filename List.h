#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>

#include "Node.h"

template <typename T>
class List
{
	private:
		Node<T> *head;
		Node<T> *rear;
		int count;
    bool ordered;

  protected:

    /*
    returns head pointer
    Pre: none
    Post: returns head pointer
    */
    Node<T>* getHead()
    {
      return head;
    };

    /*
    returns rear pointer
    Pre: none
    Post: returns rear pointer
    */
    Node<T>* getRear()
    {
      return rear;
    };

		/*
		returns pointer to node ptr at a certain position
		Pre: none
		Post: returns pointer to node
		*/
		Node<T>* getNodePTR(int pos);

	public:
		List(bool order = false)
		{
			count = 0;
			head = NULL;
			rear = NULL;
      ordered = order;
		};

		/*
		Inserts Node containing T into LL (linked list) at pos'th node of LL
		(pos starts at 1)
		Pre: value of type T and position (count+1> pos > 0)
		Post: node is inserted into LL
		*/
		void insert(T *value, int pos);

		/*
		Inserts Node into an ordered LL (from least to greatest)
		Important Note: if T1 and T2 are two data of type T => T1 > T2 must be valid operation
		Pre: value of type T
		Post: node is inserted into LL
	    */
		void insert(T *value);

		/*
		Inserts node with value at front of LL
		Pre: value of type T
		Post: node is inserted into front of LL
		*/
		void insertFront(T *value)
		{
			insert(value, 1);
		};

		/*
		Inserts node value T at end of LL
		Pre: value of type T
		Post: node is inserted into end of LL
		*/
		void insertRear(T *value)
		{
			insert(value, count + 1);
		};

		/*
		Removes first node at position pos
		Pre: int containing position
		Post: node is removed from LL
		*/
		void remove(int pos);

		/*
		Removes first node with data that has value of type T
		Pre: value of type T, reference variable found of type bool
		Post: node with data of type T is removed from LL;
		Post [cont]: if the node is in linked list, found = true; else, found = false
		*/
		void remove(T *value, bool &found);

    /*
    Removes first node
    Pre: none
    Post: first node removed
    */
		void removeFront()
		{
			remove(1);
		};

    /*
    Removes last node
    Pre: none
    Post: last node removed
    */
		void removeRear()
		{
			remove(count);
		};

    /*
    returns count
    Pre: none
    Post: count returned
    */
		int getCount() const
		{
			return count;
		};

    /*
    gets postion of value of type T
    Pre: value of type T
    Post: position (int)
    */
		int find(T *value);

    /*
    empties list
    Pre: none
    Post: list empty
    */
		void empty();

    /*
    displays LL
    Pre: none
    Post: outputs (via cout) LL
    */
		void display(bool numbered = false);

		/*
		iterator
		pre: the address of some function
		post: does function on data in list
		*/
		template <typename U>
		U iterator(U funct(T *a, U b), U starting_value);

		/*
		copies nodes into another Linked List
		pre: pointer to linked list
		post: changed linked list
		Note: needs to have same ordered value
		*/
		bool copier(List<T> *receiving) const;

		/*
		returns ordered
		pre: none
		post: ordered
		*/
		bool isOrdered() const
		{
			return ordered;
		}
		/*
returns data in first node
pre: none
post: data
*/
T* getFirst()
{
	if(getCount() != 0)
		return head->getData();
	else
		return NULL;
}

/*
returns data in last node
pre: none
post: data
*/
T* getLast()
{
	if(getCount() != 0)
		return rear->getData();
	else
		return NULL;
}
		/*
		overloaded assignment operator
		pre: LL object
		post: LL now equals the argument
		*/
		List<T>& operator=(List &obj)
		{
			empty();
			ordered = obj.isOrdered();
			obj.copier(this);
			return *this;
		}

		virtual ~List()
		{
			empty();
		};
};

template <typename T>
Node<T>* List<T>::getNodePTR(int pos)
{
	if(pos > count || pos < 1)
	{
		return NULL;
	}
	Node<T> *ptr = head;
	for(int i = 1; i < pos; i++)
	{
		ptr = ptr->getNext();
	}
	return ptr;
};

template <typename T>
void List<T>::insert(T *value)
{
  if(!ordered)
  {
    return;
  }
	//try-catch is to prevent use when there is no overloaded > and == operator for type T
	try
	{
		Node<T> *newNode;
		Node<T> *nodePtr = head;
		newNode = new Node<T>(value);

		if(count == 0)
		{
			head = newNode;
			rear = newNode;
			newNode->setNext(NULL);
		}

		else if(*(nodePtr->getData()) > *value || *(nodePtr->getData()) == *value)
		{
			newNode->setNext(nodePtr);
			head = newNode;
		}

		else
		{
			Node<T> *prevNode = NULL;

			while(*value > *(nodePtr->getData()) && nodePtr->getNext() != NULL)
			{
				prevNode = nodePtr;
				nodePtr = nodePtr->getNext();
			}

			if(*value > *(nodePtr->getData()) && nodePtr == rear)
			{
				nodePtr->setNext(newNode);
				rear = newNode;
			}

			else
			{
				newNode->setNext(nodePtr);
				prevNode->setNext(newNode);
			}
		}
		count++;
	}

	catch(...)
	{
		;
	}
}

template <typename T>
void List<T>::insert(T *value, int pos)
{
  if(ordered)
  {
    return;
  }

	pos--;
	Node<T> *newNode;
	newNode = new Node<T>(value);

	if(pos == 0)
	{
		Node<T> *temp = head;
		head = newNode;
		newNode->setNext(temp);
		if(count == 0)
			rear = newNode;
		count++;
	}

	else if(pos == count)
	{
		Node<T> *temp = rear;
		temp->setNext(newNode);
		newNode->setNext(NULL);
		rear = newNode;
		count++;
	}

	else if(pos > 0 && pos < count)
	{
		Node<T> *prevNode = NULL;
		Node<T> *nodePtr = head;

		for(int i = 0; i < pos; i++)
		{
			prevNode = nodePtr;
			nodePtr = nodePtr->getNext();
		}

		newNode->setNext(nodePtr);
		prevNode->setNext(newNode);
		count++;
	}
}

template <typename T>
void List<T>::remove(T *value, bool &found)
{
	int pos = find(value);
	if(pos == -9)
		found = false;
	else
	{
		found = true;
		remove(pos);
	}
}

template <typename T>
void List<T>::remove(int pos)
{
	pos--;
	Node<T> *curr_ptr = head;
	Node<T> *prev_ptr = NULL;
	Node<T> *temp = NULL;

	if(pos==0 && count > 0)
	{
		temp = head->getNext();
		delete curr_ptr;
		head = temp;
		count--;
	}

	else if(pos > 0 && count > 1 && pos < count)
	{
		for(int i = 0; i < pos; i++)
		{
			prev_ptr = curr_ptr;
			curr_ptr = curr_ptr->getNext();
		}

		prev_ptr->setNext(curr_ptr->getNext());
		if(pos == count - 1)
			rear = prev_ptr;
		delete curr_ptr;
		count--;
	}
}

template <typename T>
int List<T>::find(T *value)
{
	Node<T> *curr_ptr = head;
	int pos = -9;
	bool found = false;
	for(int i = 0; i < count && !found; i++)
	{
		if(*value == *(curr_ptr->getData()))
		{
			pos = i;
			found = true;
		}
		curr_ptr = curr_ptr->getNext();
	}
	return ++pos;
}

template <typename T>
void List<T>::display(bool numbered)
{
	Node<T> *ptr = head;
	int counter = 0;
	while(ptr != NULL)
	{
		if(numbered)
		{
			std::cout << ++counter << ": ";
		}
		std::cout << *(ptr->getData()) << std::endl;
		ptr = ptr->getNext();
	}
}

template <typename T>
template <typename U>
U List<T>::iterator(U funct(T *a, U b), U starting_value)
{
	Node<T> *ptr = head;
	U val = starting_value;
	while(ptr != NULL)
	{
		val = funct(ptr->getData(), val);
		ptr = ptr->getNext();
	}
	return val;
}

template <typename T>
bool List<T>::copier(List<T> *receiving) const
{
	if(receiving->isOrdered() != ordered)
		return false;
	Node<T> *ptr = head;
	while(ptr != NULL)
	{
		if(ordered)
			receiving->insert(ptr->getData());
		else
			receiving->insertRear(ptr->getData());
		ptr = ptr->getNext();
	}
	return true;
}

template <typename T>
void List<T>::empty()
{
	Node<T> *curr_ptr;
	Node<T> *prev_ptr = head;
	for(int i = 0; i < count; i++)
	{
		curr_ptr = prev_ptr->getNext();
		delete prev_ptr;
		prev_ptr = curr_ptr;
	}
	count = 0;
	head = NULL;
}

#endif
