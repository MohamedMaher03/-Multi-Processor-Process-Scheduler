
#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private :
	T item; // A data item
	int priority;
	Node<T>* next; // Pointer to next node
public :
	Node();
	Node( const T & r_Item);	
	Node(const T& item, int priority, Node<T>* next)
		: item(item), priority(priority), next(next) {}
	Node( const T & r_Item, Node<T>* nextNodePtr);
	void setItem( const T & r_Item);
	void setNext(Node<T>* nextNodePtr);
	void setpriority(int p);
	int getpriority();
	T getItem() const ;
	Node<T>* getNext() const ;
}; // end Node


template < typename T>
Node<T>::Node() 
{
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}
template<typename T>
inline void Node<T>::setpriority(int p)
{
	priority = p;
}

template<typename T>
inline int Node<T>::getpriority()
{
	return priority;
}


template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}
#endif