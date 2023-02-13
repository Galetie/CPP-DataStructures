/*****************************************************************//**
 * \file   LinkedList.h
 * \brief  
 * 
 * \author Jarryd Hassall
 * \date   9 February 2023
 *********************************************************************/

#pragma once
#include <string>
#include <sstream>

template <class T>
class LinkedList {
private:
	class Node;

	Node* head;
	Node* tail;

	unsigned int size;

public:
	LinkedList();
	~LinkedList();

	void insertStart(const T& data);
	void insertEnd(const T& data);
	void remove(const T& data);
	bool contains(const T& data);
	std::string toString();
};

template <class T>
class LinkedList<T>::Node {
public:
	T data;
	Node* next;
	Node();
	Node(T data);
};

template <class T>
LinkedList<T>::Node::Node() {
	this->next = nullptr;
}

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
	Node* temp;

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
	Node* newNode = new Node(data);

	// The new node will become the new head
	newNode->next = this->head;

	// If the head is not set, the tail also needs to be set
	if (this->head == nullptr) {
		this->tail = newNode;
	}
	this->head = newNode;
}

template <class T>
void LinkedList<T>::insertEnd(const T& data) {
	// Create the node to insert
	Node* newNode = new Node(data);

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

template <class T>
void LinkedList<T>::remove(const T& data) {
	Node* current = this->head;

	// Check if current is the target
	if (current->data == data) {
		this->head = this->head->next;
		delete current;
		return;
	}

	// Traverse until the next node is the target value
	while (current->next != nullptr) {
		// Delete the next node if it contains the target value
		if (current->next->data == data) {
			Node* toDelete = current->next;
			current->next = current->next->next;
			delete toDelete;

			// Check if current is now the tail
			if (current->next == nullptr) {
				this->tail = current;
			}
			return;
		}

		current = current->next;
	}
}

template <class T>
bool LinkedList<T>::contains(const T& data) {
	Node current = this->head;

	while (current != nullptr) {
		if (current.data == data) {
			return true;
		}

		// Travel to the next node
		current = current.next;
	}

	return false;
}

template <class T>
std::string LinkedList<T>::toString() {
	std::stringstream output;

	Node* current = this->head;

	while (current != nullptr) {
		output << current->data;
		if (current->next != nullptr) {
			output << " -> ";
		}

		current = current->next;
	}

	return output.str();
}