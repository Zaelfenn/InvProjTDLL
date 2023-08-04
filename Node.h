#pragma once
#ifndef String
#include "String.h"
#endif 



template<typename DATA>
class List;

template<typename DATA>

class Node {
	friend class List<DATA>;
private:
	Node();
	Node(DATA data);
	~Node();
	Node(const Node& original);
	Node& operator = (const Node& rhs);

	DATA m_data;
	Node* m_next;
	Node* m_prev;
};

template<typename DATA>
Node<DATA>::Node() : m_data(DATA()), m_next(nullptr), m_prev(nullptr)
{} //default constructor

template<typename DATA>
Node<DATA>::Node(DATA data) : m_data(data), m_next(nullptr), m_prev(nullptr)
{} //silly constructor

template<typename DATA>
Node<DATA>::~Node() //destructor
{
	m_data = DATA();
	m_next = nullptr;
}

template<typename DATA>
Node<DATA>::Node(const Node<DATA>& original) : m_data(original.m_data), m_next(original.m_next)
{} //copy constructor

template<typename DATA>
Node<DATA>& Node<DATA>::operator = (const Node<DATA>& rhs) { //copy assignment operator
	if (this != &rhs) { //if they aren't the same
		m_data = rhs.m_data; //replace data
		m_next = rhs.m_next; //replace next
	}
	return *this; //return "new" object
}
