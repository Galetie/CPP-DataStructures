/*****************************************************************//**
 * \file   Queue.h
 * \brief
 * A basic Queue utilizing the first in -> first out paradime.
 * 
 * \author Jarryd Hassall
 * \date   13 February 2023
 *********************************************************************/

#pragma once
#include <exception>


template <class T>
class Queue {
private:
	class Node;

	Node* head;
	Node* tail;

public:
	Queue();
	~Queue();

	void enqueue(const T& data);
	T& dequeue();

	bool isEmpty();
};

template <class T>
class Queue<T>::Node {
public:
	T data;
	Node* next;
	Node* previous;

	Node();
	Node(const T& data);
};

template <class T>
Queue<T>::Node::Node() {
	this->next = nullptr;
	this->previous = nullptr;
}

template <class T>
Queue<T>::Node::Node(const T& data) {
	this->data = data;
	this->next = nullptr;
	this->previous = nullptr;
}

template <class T>
Queue<T>::Queue() {
	this->head = nullptr;
	this->tail = nullptr;
}

template <class T>
Queue<T>::~Queue() {
	Node* current = this->head;

	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template <class T>
bool Queue<T>::isEmpty() {
	return this->head == nullptr;
}

template <class T>
void Queue<T>::enqueue(const T& data) {
	// Check if the tail is null (implies head is null)
	if (this->tail == nullptr) {
		this->tail = new Node(data);
		this->head = this->tail;
		return;
	}

	// Tail is defined, add to head
	Node* newHead = new Node(data);
	this->head->previous = newHead;
	this->head = newHead;
}

template <class T>
T& Queue<T>::dequeue() {
	// Check that there is data to dequeue
	if (isEmpty()) {
		throw std::exception("Queue is empty");
	}

	T toReturn = this->tail->data;
	Node* newTail = this->tail->previous;

	// If newTail ( the previous tothe tail) is null, do not set next value
	if (newTail != nullptr) {
		newTail->next = nullptr;
	}
	else {
		this->head = nullptr;
	}
	delete this->tail;
	this->tail = newTail;

	return toReturn;
}