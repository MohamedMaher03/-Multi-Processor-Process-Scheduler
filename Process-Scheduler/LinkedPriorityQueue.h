
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

The Node: item of type T and a "next" pointer
-------------
| item| next | --->
-------------
General Queue case:

frontPtr																backPtr
\											   						/
\											  					   /
------------- 	  ------------- 	  ------------- 	  -------------
| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

frontptr	 backptr
\	 /
\	/
---- NULL ------


Single Node Case:
frontPtr	 backPtr
\		/
\	   /
-----------
|item| next| -->NULL
-----------

*/
#pragma once
#ifndef LINKED_PRIORITY_QUEUE_
#define LINKED_PRIORITY_QUEUE_

#include "Node.h"
#include "QueueADT.h"
#include <vector>
#include"PROCESS.h"
using namespace std;
template <typename T>
class LinkedPriorityQueue 
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int length;
public:
	LinkedPriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& data, int priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	void printContents();
	int getlength();
	~LinkedPriorityQueue();

	//copy constructor
	LinkedPriorityQueue(const LinkedPriorityQueue<T>& LQ);
};
#endif
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedPriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedPriorityQueue<T>::enqueue(const T& data, int priority) {
	Node<T>* newNode = new Node<T>{ data, priority, nullptr};
	if (isEmpty()) {
		frontPtr = newNode;
		return true;
	}
	if (priority < frontPtr->getpriority()) {
			newNode->setNext(frontPtr);
			frontPtr = newNode;
			return true;
	}

	Node<T>* current = frontPtr;

	while (current->getNext() != nullptr && current->getNext()->getpriority() <= priority) {
		current=current->getNext();
	}

	newNode->setNext(current->getNext());
	current->setNext(newNode);

	return true;
}



  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*Function: dequeue
  Removes the front of this queue. That is, removes the item that was added
  earliest.

  Input: None.
  Output: True if the operation is successful; otherwise false.
  */

template <typename T>
bool LinkedPriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	length--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool LinkedPriorityQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template<>
inline void LinkedPriorityQueue<PROCESS*>::printContents()
{

	Node<PROCESS*>* curr = frontPtr;

	while (curr)
	{
		if (!curr->getNext())
		{
			cout << curr->getItem()->get_PID();
			return;
		}
		cout << curr->getItem()->get_PID() << ",  ";
		curr = curr->getNext();
	}
}

///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedPriorityQueue<T>::~LinkedPriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/
template<typename T>
int LinkedPriorityQueue<T>::getlength()
{
	return length;
}

template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue(const LinkedPriorityQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

