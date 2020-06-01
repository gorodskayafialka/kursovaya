#include <string>
#include <stdexcept>
#include <iostream>
#include "List.h"

using namespace std;

template <typename T>
void List<T>::reset()//resets the list 
{
	head = nullptr;
	tail = nullptr;
};


template <typename T>
List<T>::List() //Constructor
{
	reset();
	size = 0;
};


template <typename T>
List<T>::~List()
{
	List::clear();
};

template <typename T>
void List<T>::add_first(T new_element)//adds the first element to an empty list
{
	head = new Node(new_element);
	tail = head;
};

template <typename T>
size_t List<T>::get_size() const
{
	return size;
};

template <typename T>
void List<T>::push_back(T new_element) // adds an element to the list's end
{
	if (size == 0) { add_first(new_element); }
	else
	{
		tail->next = new Node(new_element);
		tail = tail->next;
	}
	size++;
};

template <typename T>
void List<T>::push_front(T new_element) // adds an element to the list's end
{
	if (size == 0) { add_first(new_element); }
	else
	{
		head = new Node(new_element, head);
	}
	size++;
};

template <typename T>
T List<T>::at(size_t index) // returns the value of the element based on its index
{
	if ((index >= size) || (index < 0)) { throw out_of_range("Impossible index"); }
	else
	{
		size_t counter = 0;
		Node* current = head;
		while (counter != index)
		{
			current = current->next;
			counter++;
		}
		return current->data;
	}
};

template <typename T>
void List<T>::clear()//delets the list
{
	Node* current = head;
	while (current != tail)
	{
		Node* Next = current->next;
		delete current;
		current = Next;
		size--;
	}
	delete current;
	size--;
	reset();
};

template <typename T>
bool List<T>::isEmpty() // checks if the list is empty
{
	if (size == 0) { return true; }
	else { return false; }
};

template <typename T>
int List<T>::get_index(T sublist)
{
	int counter = 0;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == sublist)
			return(counter);
		current = current->next;
		counter++;
	}
	return (-1);
}

template <typename T>
void List<T>::print_to_console()// prints the list to console
{
	Node* current = head;
	while (current != nullptr)
	{
		cout << current->data << " ";
		current = current->next;
	}
};

template <typename T>
void List<T>::remove(size_t index)// prints the list to console
{
	if ((index >= size) || (index < 0)) { throw out_of_range("Impossible index"); }
	else
	{
		size_t counter = 0;
		Node* current = head;
		Node* last = head;
		while (counter != index)
		{
			last = current;
			current = current->next;
			counter++;
		}
		last->next = current->next;
		delete current;
		size--;
	}
};