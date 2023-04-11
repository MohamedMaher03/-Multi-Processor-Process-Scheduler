#pragma once

#include "Node.h"
#include"PROCESS.h"

#include<iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;

	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList();
	

	///////////////////////////////////////////////////////////////////////
	/*
	*function: IsEmpty.
	* that checks if the list is empty or not.
	*/
	bool IsEmpty() {
		if (Head == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	/////function that returns the head
	Node* get_Head() 
	{
		return Head;
	}


	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		Node<T>* N = new Node<T>(data);
		Node<T>* tmpPtr = Head;
		if (Head == nullptr) {
			Head = N;
		}
		else {
			while (tmpPtr->getNext() != nullptr)
				tmpPtr = tmpPtr->getNext();
			tmpPtr->setNext(N);
			N->setNext(nullptr);
		}
	}

	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key) {
		Node<T>* ptr = Head;
		//This is how to iterate over a linked list using for loop, NO i++ here (ptr = ptr->next)
		for (ptr; ptr; ptr = ptr->getNext()) //the second ptr means while ptr!= NULL
		{
			if (ptr->getItem() == Key)
				return true;
		}
		return false;
	}


	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value) {
		int count = 0;
		Node<T>* tmpPtr = Head;
		while (tmpPtr != NULL) {
			if (tmpPtr->getItem() == value) {
				count++;
			}
			tmpPtr = tmpPtr->getNext();
		}
		return count;
	}


	//Deletes the first node in the list
	void DeleteFirst() {
		Node<T>* tmpPtr = Head;
		Head = Head->getNext();
		delete tmpPtr;
	}



	//Deletes the last node in the list
	void DeleteLast() {
		Node<T>* tmpPtr = Head;
		if (!Head)
			return;
		if (!Head->getNext()) {
			DeleteFirst();
			return;
		}

		while (tmpPtr->getNext()->getNext())
			tmpPtr = tmpPtr->getNext();

		delete tmpPtr->getNext();
		tmpPtr->setNext(NULL);
	}


	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value) {

		Node<T>* current = Head;

		if (!Head) //list is empty
			return false;

		if (!Head->getNext()) {
			DeleteFirst();
			return true;
		}
		//puts the value of the head in the node we want to delete
		//then delets the head and the second node becomes the head
		while (current != NULL)
		{
			if (current->getItem() == value)
			{
				current->setItem(Head->getItem());
				DeleteFirst();
				return true;
			}
			current = current->getNext();
		}
		return false;
	}


	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L) {
		Node<T>* tmpPtr = Head;
		while (tmpPtr->getNext())
			tmpPtr = tmpPtr->getNext();
		tmpPtr->setNext(L.Head);
		Head = this->Head;

	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		Node<T>* previous = NULL, * following = NULL;
		Node<T>* current = Head;

		while (current != NULL) {
			//the following pointer points at the next of the current pointer
			following = current->getNext();
			//reverse the next pointer of the current node to point at the previous one
			current->setNext(previous);
			//shifts the previous pointer to point at the same node as the current pointer
			previous = current;
			//shifts the current pointer to the next one
			current = following;
		}
		Head = previous;
	}
	void Dequeue(T* temp) {
		Node<T>* tmpPtr = Head;
		T value = Head->getItem();
		temp = &value;
		Head = Head->getNext();
		delete tmpPtr;
	}


};
template<>
void LinkedList<PROCESS*>::PrintList()
{
	Node<PROCESS*>* p = Head;

	if (!p->getNext())
	{
		cout << p->getItem()->get_PID();
		return;
	}
	while (p)
	{
		cout << p->getItem()->get_PID() << ",  ";
		p = p->getNext();
	}
	
	}