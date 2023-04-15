#pragma once
#include"Node.h"

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
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	void insert_end(const T& newEntry);
	void insert_front(const T& newEntry);
	int get_length();
	void printContents();
	~LinkedPriorityQueue();

	//copy constructor
	LinkedPriorityQueue(const LinkedPriorityQueue<T>& LQ);
};

template <typename T>
void LinkedPriorityQueue<T>::insert_end(const T& newEntry) {
	Node<T>* item = new Node<T>(newEntry);

	if (!frontPtr)
		frontPtr = backPtr = item;
	else {
		backPtr->setNext(item);
		backPtr = item;
	}
	++length;
}
template <typename T>
inline void LinkedPriorityQueue<T>::insert_front(const T& newEntry) {
	Node<T>* item = new Node<T>(newEntry);
	if (!frontPtr) {
		frontPtr = item;
		backPtr = item;
	}
	else {
		item->setNext(frontPtr);
		frontPtr = item;
	}
	length++;
}
template<typename T>
inline int LinkedPriorityQueue<T>::get_length()
{
	return length;
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
template <typename T>
LinkedPriorityQueue<T>::LinkedPriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	length = 0;
}

template <typename T>
bool LinkedPriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename T>
bool LinkedPriorityQueue<T>::enqueue(const T& newEntry)
{
	if (length == 0)
	{
		insert_front(newEntry);
		length++;
		return true;
	}
	if (!length || newEntry <= frontPtr->getItem()) {
		insert_front(newEntry);
		length++;
		return true;
	}
	else if (newEntry <= backPtr->getItem()) {
		insert_end(newEntry);
		length++;
		return true;
	}
	else {
		Node<T>* curr = frontPtr->getNext();
		for (Node<T>* cur = curr, *prv = frontPtr;cur;prv = cur, cur = cur->getNext()) {
			if ((newEntry <= cur->getItem())) {
				Node<T>* item = new Node<T>(newEntry);
				prv->setNext(item);
				item->setNext(cur);
				length++;
				return true;
			}
		}
	}
	return false;
} // end enqueue
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
template <typename T>
bool LinkedPriorityQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template <typename T>
LinkedPriorityQueue<T>::~LinkedPriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
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

