#include <iostream>
using namespace std;

template <typename T>
class LinkedPriorityQueue {
private:
    struct Node 
    {
        T data;
        int priority;
        Node* next;
    };

    Node* head;

public:
    void printContents();
    LinkedPriorityQueue() : head(nullptr) {}

    ~LinkedPriorityQueue() {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const 
    {
        return head == nullptr;
    }

    void enqueue(const T& data, int priority) 
    {
        Node* newNode = new Node{data, priority, nullptr};

        if (isEmpty()) {
            head = newNode;
            return;
        }

        if (priority < head->priority) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;

        while (current->next != nullptr && current->next->priority <= priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    T dequeue(T& frntEntry) {
        if (isEmpty()) 
            return nullptr;

        Node* temp = head;
        frntEntry = temp->data;

        head = head->next;
        delete temp;

        return frntEntry;
    }

    T peek(T& frntEntry) const 
    {
        if (isEmpty()) 
        {
            return nullptr;
        }
        frntEntry = head->data;
        return frntEntry;
    }

    int size() const 
    {
        int count = 0;

        for (Node* current = head; current != nullptr; current = current->next) {
            ++count;
        }

        return count;
    }

    void print() const {
        for (Node* current = head; current != nullptr; current = current->next) {
            std::cout << current->data << " ";
        }

        std::cout << std::endl;
    }
    
};
template<>
inline void LinkedPriorityQueue<PROCESS*>::printContents()
{

    for (Node* current = head; current != nullptr; current = current->next) 
    {
        if (!current->next)
        {
            cout << current->data->get_PID();
            return;
        }
        cout << current->data->get_PID() << ", ";
    }
}