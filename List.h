#pragma once
#include <string>

using namespace std;

template <typename T>
class List
{
	void add_first(T new_element);
	void reset();
	class Node
	{
	public:
		Node(T data, Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		};
		~Node() {};
		T data;
		Node* next;
	};
	Node* head;
	Node* tail;
	size_t size;
public:
	List();
	~List();
	size_t get_size() const;
	void push_back(T new_element);
	void push_front(T new_element);
	T at(size_t index);
	void clear();
	bool isEmpty();
	int get_index(T sublist);
	void print_to_console();
	void remove(size_t index);
};

#include "List.inl";