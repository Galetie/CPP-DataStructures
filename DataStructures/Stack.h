#pragma once
#include <exception>

template <class T>
class Stack {
private:
	class Node;

	Node* top;
public:
	Stack();
	~Stack();

	void push(const T& data);
	T& pop();

	bool isEmpty();
};

template <class T>
class Stack<T>::Node {
public:
	T data;
	Node* next;

	Node();
	Node(const T& data);
};

template <class T>
Stack<T>::Node::Node() {
	this->next = nullptr;
}

template <class T>
Stack<T>::Node::Node(const T& data) {
	this->data = data;
	this->next = nullptr;
}

template <class T>
Stack<T>::Stack() {
	this->top = nullptr;
}

template <class T>
Stack<T>::~Stack() {
	Node* current = this->top;

	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template <class T>
void Stack<T>::push(const T& data) {
	Node* newNode = new Node(data);
	newNode->next = this->top;
	this->top = newNode;
}

template <class T>
T& Stack<T>::pop() {
	// Check if the stack is empty
	if (isEmpty()) {
		throw std::exception("Stack is empty");
	}

	T toReturn = this->top->data;
	Node* newTop = this->top->next;
	delete this->top;
	this->top = newTop;

	return toReturn;
}

template <class T>
bool Stack<T>::isEmpty() {
	return this->top == nullptr;
}