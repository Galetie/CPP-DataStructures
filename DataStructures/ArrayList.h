/*****************************************************************//**
 * \file   ArrayList.h
 * \brief  
 * A dynamic array implementation. Scales through use 
 * and can be trimmed to fit current data.

 * 
 * \author Jarryd Hassall
 * \date   8 February 2023
 *********************************************************************/

#pragma once
#include <stdlib.h> 
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

#define DEFAULT_SIZE 8
#define INCREMENT_SIZE 8

template <class T>
class ArrayList {
private:
	unsigned int size;
	unsigned int used;

	T* start;

	void expand();
	T* copyToNewArray(unsigned int newSize);

public:
	ArrayList();
	ArrayList(const ArrayList<T>& other);
	~ArrayList();

	void add(const T& item);
	void insert(unsigned int index, const T& item);
	void remove(unsigned int index);
	void clear();

	unsigned int getSize();
	bool isEmpty();
	void trim();
	std::string toString();

	T& operator [] (const unsigned int index);
	T* toArray();
};

/**
 * Constructs an ArrayList with no initialized data.
 * 
 */
template <class T>
ArrayList<T>::ArrayList() {
	// Initialize size and used to their default values
	this->size = DEFAULT_SIZE;
	this->used = 0;

	// Initialize an array
	this->start = new T[this->size];
}

/**
 * Constructs an ArrayList and populates the array with the data from the other array.
 * 
 * \param other The other ArrayList to copy
 */
template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
	// Initialize size and used to the same values as other
	this->size = other.size;
	this->used = other.used;

	// Initialize an array
	this->start = new T[other.size];

	// Copy data from other array to this array
	for (int i = 0; i < this->used; i++) {
		this->start[i] = other.start[i];
	}
}

/**
 * Destroys the underlying array structure, frees memory.
 * 
 */
template <class T>
ArrayList<T>::~ArrayList() {
	// Delete (free) the allocated memory
	delete[] this->start;
}

/**
 * Adds (appends) a given item to the end of the array.
 * 
 * \param item The item to insert
 */
template <class T>
void ArrayList<T>::add(const T& item) {
	// Assign the current used index to the provided item
	// Increments used at the same time
	this->start[used++] = item;

	// expand the underlying structure (if necessary)
	expand();
}

/**
 * Inserts a given element to the given index.
 * Results in the existing element and all those to the right of the given element 
 * being shifted right.
 * 
 * \param index The index to insert into
 * \param item The item to insert
 * \throws std::out_of_range If the given index is outside the working range
 */
template <class T>
void ArrayList<T>::insert(unsigned int index, const T& item) {
	// Ensure the provided index is accessible
	if (index > this->used) {
		throw std::out_of_range("Provided index " + std::to_string(index) + " is out of bounds for array of size " + std::to_string(this->used));
	}

	// Shift everything from index -> used right
	for (int i = this->used; i > index; i--) {
		this->start[i] = this->start[i - 1];
	}

	// Insert at index
	this->start[index] = item;
	
	// Increment the used count and attempt to expand
	used++;
	expand();
}

/**
 * Removes the provided index and shuffles the elements to the left.
 * 
 * \param index The index to remove
 * \throws std::out_of_range If the provided index is outside the working range
 */
template <class T>
void ArrayList<T>::remove(unsigned int index) {
	// Ensure the provided index is accessible
	if (index >= this->used) {
		throw std::out_of_range("Provided index " + std::to_string(index) + " is out of bounds for array of size " + std::to_string(this->used));
	}

	// Shift everything to the right of index, left
	for (int i = index; i < used; i++) {
		this->start[i] = this->start[i + 1];
	}

	// Removing an item reduces the used space
	used--;
}

/**
 * Clears and resets the array to the default size.
 * 
 */
template <class T>
void ArrayList<T>::clear() {
	// Delete the array
	delete[] this->start;

	// Initialize size and used to their defaults
	this->used = 0;
	this->size = DEFAULT_SIZE;

	// Initialize a new array
	this->start = new T[this->size];
}

/**
 * Returns if the array is currently empty.
 * 
 * \return is the array empty?
 */
template <class T>
bool ArrayList<T>::isEmpty() {
	// The array is empty if there are no used slots
	return this->used == 0;
}

/**
 * Compacts the underlying array structure to fit to the given data.
 * 
 */
template <class T>
void ArrayList<T>::trim() {
	// Create a new array of the trimmed size
	T* newArray = copyToNewArray(this->used + 1);

	// Delete the old array, reassign
	delete[] this->start;
	this->start = newArray;

	// Update the size property
	this->size = this->used + 1;
}

/**
 * Returns the current working size of the array.
 * 
 * \return The size of the array
 */
template <class T>
unsigned int ArrayList<T>::getSize() {
	return this->used;
}

/**
 * Creates a c++ string representation of the array.
 * Follows the form "[ a b c ]" where a b and c are elements.
 * 
 * \return A string representation of the array
 */
template <class T>
std::string ArrayList<T>::toString() {
	// Use a string stream for simplicity
	std::stringstream output;

	// Append the "[", write each value and then "]"
	output << "[ ";
	for (unsigned int i = 0; i < this->used; i++) {
		output << this->start[i] << ' ';
	}
	output << "]";

	return output.str();
}

/**
 * Expands the internal array structure to fit additional data.
 * 
 */
template <class T>
void ArrayList<T>::expand() {
	// Copy existing data in to a larger array
	T* newArray = copyToNewArray(this->size + INCREMENT_SIZE);

	// Delete and reassign the array
	delete[] this->start;
	this->start = newArray;
	this->size += INCREMENT_SIZE;
}

/**
 * Overloads the [] operator and allows the underlying array structure
 * to be accessed like a typical array.
 * 0 <= index < size
 * 
 * \param index The index to access
 * \return a reference tot the item at the given index
 * \throws std::out_of_range If the provided index exceeds the required limit.
 */
template <class T>
T& ArrayList<T>::operator [] (const unsigned int index) {
	// Ensure the provided index is within the working range
	if (index >= this->used) {
		throw std::out_of_range;
	}

	// Return the item at the provided index
	return this->start[index];
}

/**
 * Creates a new Array of size newSize and copies existing data into it.
 * newSize cannot be less than the current size of the array.
 * 
 * \param newSize The size of the array to create
 * \return The new expanded array
 * \throws std::invalid_argument If the provided size is smaller than the minimum
 */
template <class T>
T* ArrayList<T>::copyToNewArray(unsigned int newSize) {
	// Ensure the new size is at least the same size as the current array
	if (newSize < this->used) {
		throw std::invalid_argument("newSize (" + std::to_string(newSize) + ") cannot be less than the current size of the array");
	}

	// Create the new array
	T* newArray = new T[newSize];

	// Copy existing data in to the new array
	for (unsigned int i = 0; i < newSize; i++) {
		newArray[i] = this->start[i];
	}

	return newArray;
}

/**
 * Reduces the ArrayList to a single primitive array.
 * 
 * \return An array of type T
 */
template <class T>
T* ArrayList<T>::toArray() {
	return copyToNewArray(this->used);
}
