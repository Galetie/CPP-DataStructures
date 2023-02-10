/*****************************************************************//**
 * \file   LinkedList.h
 * \brief  
 * 
 * \author Jarryd Hassall
 * \date   9 February 2023
 *********************************************************************/

#pragma once

template <class T>
class LinkedList {
private:
	class Node;

	Node head;
	Node tail;

	unsigned int size;

public:
	LinkedList();
	~LinkedList();

	void insertStart(const T& data);
	void insertEnd(const T& data);
	void remove(const T& data);
	bool contains(const T& data);
	void sort();
};

template <class T>
class LinkedList<T>::Node {
public:
	T data;
	Node* next;
	Node(T data);
};

template <class T>
LinkedList<T>::Node::Node(T data) {
	this->data = data;
	this->next = nullptr;
}

template <class T>
LinkedList<T>::LinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
	// Store the node to delete
	Node temp;

	// For each node in the list, delete
	while (this->head != nullptr) {
		// Store the node to be deleted
		temp = this->head;

		// Move the head down the list
		this->head = this->head->next;

		// Delete the node
		delete temp;
	}
}

template <class T>
void LinkedList<T>::insertStart(const T& data) {
	// Create the node to insert
	Node newNode = new Node(data);

	// The new node will become the new head
	newNode.next = this->head;

	// If the head is not set, the tail also needs to be set
	if (this->head == nullptr) {
		this->tail = newNode;
	}
	this->head = newNode;
}

template <class T>
void LinkedList<T>::insertEnd(const T& data) {
	// Create the node to insert
	Node newNode = new Node(data);

	// If the tail already exists, update it
	if (this->tail != nullptr) {
		this->tail->next = newNode;
	}
	else {
		// This implies the head does not exist, as the tail does not
		this->head = newNode;
	}
	this->tail = newNode;

}
