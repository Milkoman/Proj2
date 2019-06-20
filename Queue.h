#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"
#include "Node.h"

template <typename T>
class Queue : protected List<T>
{
  public:
  /*
  checks if empty
  pre: none
  post: bool (true = empty; false = not empty)
  */
    bool isEmpty()
	{
		return this->getCount() == 0 ? true : false;
	};

  /*
  inserts node containing data of type T to rear of queue
  pre: value
  post: value inserted at rear of queue
  */
    void enqueue(T *value)
	{
		this->insertRear(value);
	};

  /*
  overloaded enqueue -> takes in dummy bool as well
  inserts node containing data of type T to rear of queue
  pre: value
  post: value inserted at rear of queue
  */
    void enqueue(T &value, bool a)
	{
		this->insertRear(&value);
	};

  /*
  removes node from front of queue
  pre: none
  post: node @ front of queue removed
  */
    void dequeue()
	{
		this->removeFront();
	};

  /*
  returns pointer to data at front of queue
  pre: none
  post: pointer to data (of type T) at front of queue
  */
   T* front()
	{
    if(!isEmpty())
        return (this->getHead())->getData();
    else
      return NULL;
	};

  /*
  returns pointer to data at rear of queue
  pre: none
  post: pointer to data (of type T) at rear of queue
  */
  T* rear()
 {
   if(!isEmpty())
       return (this->getRear())->getData();
   else
     return NULL;
 };

 /*
 empties queue
 pre: none
 post: queue emptied
 */
 void emptyQueue()
 {
   this->empty();
 }

 /*
 overloaded assignment operator
 pre: queue
 post: this queue constains the values from argument
 */
 Queue<T>& operator=(Queue<T> &obj)
 {
   List<T>::operator=(obj);
   return *this;
 }

 /*
 destructor
 */
  ~Queue()
  {
    emptyQueue();
  };
};

#endif
