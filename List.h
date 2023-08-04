#pragma once
#include <iostream>
using std::cout;
using std::cerr;
#include "Node.h"

#include <exception>
using std::exception;
using std::invalid_argument;

#include "Armor.h"
#include "Blade.h"
#include "Mushroom.h"
#include "Potion.h"
#include "Ranged.h"

template <typename DATA>

class List {
public:
	List();
	List(Node<DATA>* head);
	~List();
	List(const List<DATA>& original);
	List(List&& original)noexcept;
	List& operator = (List<DATA>&& rhs)noexcept;
	List& operator = (const List<DATA>& rhs);
	void prependList(DATA data);
	void appendList(DATA data);
	void deleteNode(DATA data);
	void purgeList();
	void insertList(DATA data);
	
	void insertArmor(Armor data);
	void insertBlade(Blade data);
	void insertMushroom(Mushroom data);
	void insertPotion(Potion data);
	void insertRanged(Ranged data);

	void deleteArmor(Armor data);
	void deleteBlade(Blade data);
	void deleteMushroom(Mushroom data);
	void deletePotion(Potion data);
	void deleteRanged(Ranged data);

	void displayListFrwd();
	void displayListBckwd();
private:
	Node<DATA>* m_head;
	Node<DATA>* m_tail;
};

template<typename DATA>
List<DATA>::List() : m_head(nullptr), m_tail(nullptr) //default ctor
{}

template<typename DATA>
List<DATA>::List(Node<DATA>* node) : m_head(node), m_tail(node)
{}

template<typename DATA>
List<DATA>::List(const List<DATA>& original) : m_head(nullptr), m_tail(nullptr) //copy constructor
{
	if (original.m_head != nullptr) { //if data can be copied
		purgeList(); //clear the old list
		Node<DATA>* travel = original.m_head; //make a traveling pointer through old list
		Node<DATA>* nn = new Node<DATA>; //new node for new list
		nn->m_data = travel->m_data; //set data
		m_head = nn; //make head of new list new node
		if (travel->m_next == nullptr) { //if this is the end of the list
			m_tail = nn; //new node is also the tail
		}
		else {
			nn->m_next = new Node<DATA>(travel->m_next->m_data); //set the next node to a new node that has the data of old lists next node
			nn->m_next->m_prev = nn; //set the next node's previous to the "original" new node
			travel = travel->m_next; //traverse the list
			while (travel != nullptr) { //while the list still has data
				nn = nn->m_next; //go to the next item
				if (travel->m_next == nullptr) { //if this is the last item in the list
					m_tail = nn; //make this node the tail
				}
				else
				{
					nn->m_next = new Node<DATA>(travel->m_next->m_data); //set the next node to a new node with the next data
					nn->m_next->m_prev = nn; //set the previous node of the next node to this node
				}
				travel = travel->m_next; //traverse the list
			}

		}
	}
}

template<typename DATA>
List<DATA>::List(List<DATA>&& original) noexcept : m_head(original.m_head), m_tail(original.m_tail) //move semantics, set beginnning and end of list
{
	original.m_head = nullptr; //old list will no longer have a head pointer
	original.m_tail = nullptr; //old list will no longer have a tail pointer (both were moved to the new list)
}

template<typename DATA>
List<DATA>::~List() //destructor
{
	purgeList();
}

template<typename DATA>
List<DATA>& List<DATA>::operator = (const List<DATA>& rhs) //copy assignment operator
{
	if (this != &rhs) { //if these are not the same list
		purgeList(); //clear the old list
		Node<DATA>* travel = rhs.m_head; //make a traveling pointer through old list
		Node<DATA>* nn = new Node<DATA>; //new node for new list
		nn->m_data = travel->m_data; //set data
		m_head = nn; //make head of new list new node
		if (travel->m_next == nullptr) { //if this is the end of the list
			m_tail = nn; //new node is also the tail
		}
		else {
			nn->m_next = new Node<DATA>(travel->m_next->m_data); //set the next node to a new node that has the data of old lists next node
			nn->m_next->m_prev = nn; //set the next node's previous to the "original" new node
			travel = travel->m_next; //traverse the list
			while (travel != nullptr) { //while the list still has data
				nn = nn->m_next; //go to the next item
				if (travel->m_next == nullptr) { //if this is the last item in the list
					m_tail = nn; //make this node the tail
				}
				else
				{
					nn->m_next = new Node<DATA>(travel->m_next->m_data); //set the next node to a new node with the next data
					nn->m_next->m_prev = nn; //set the previous node of the next node to this node
				}
				travel = travel->m_next; //traverse the list
			}

		}
	}
	return *this; //return the new list
}

template<typename DATA>
List<DATA>& List<DATA>::operator = (List&& rhs) noexcept { //move semantics

	if (this != &rhs) { //if they arent the same list
		purgeList(); //destroy the old list
		m_head = rhs.m_head; //steal the head of the new list
		m_tail = rhs.m_tail; //steal the tail of the new list
		rhs.m_head = nullptr;
		rhs.m_tail = nullptr; //cut the ties of the old list
	}
	return *this; //return new list
}

template<typename DATA>
void List<DATA>::deleteNode(DATA data) //deleting a node
{
	try {
		if (m_head == nullptr) //if the list is nonexistent
			throw invalid_argument("Error: List doesn't exist");
	}
	catch (invalid_argument& e) {
		cerr << e.what() << std::endl;
	}
	if (m_head != nullptr) {
		Node<DATA>* travel = m_head; //traveling pointer to traverse the list
		while (travel->m_data != data && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (travel->m_data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node<DATA>* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else {
			try {
				throw invalid_argument("Error: List doesn't exist");
			}
			catch (invalid_argument& e) {
				cerr << e.what() << std::endl;
			}
		}
	}
}

template<typename DATA> 
void List<DATA>::prependList(DATA data) //prepend the list
{
	Node<DATA>* nn = new Node<DATA>(data); //new node initialized with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else {
		nn->m_next = m_head; //set the new nodes next to the old head
		m_head->m_prev = nn; //set the old heads previous to the new node
		m_head = nn; //set the new head of the list to the new node
	}
}

template<typename DATA>
void List<DATA>::appendList(DATA data) //append the list
{
	Node<DATA>* nn = new Node<DATA>(data); //new node initialized with data
	if (m_tail == nullptr) { //if the list doesn't exist yet
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else {
		nn->m_prev = m_tail; //set the new nodes previous to the old tail
		m_tail->m_next = nn
			; //set the old tails next to the new node
		m_tail = nn; //set the new tail to the new node
	}
}

template<typename DATA>
void List<DATA>::insertList(DATA data) //insert data into the list in order
{
	Node<DATA>* nn = new Node<DATA>(data); //initialize new node with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else
	{
		Node<DATA>* travel = m_head; //traveling pointer from the beginning of the list
		bool loop = true; //keep looping until finished
		while (loop == true) {
			if (travel->m_data >= nn->m_data) { //if the data is the same or comes first alphabetically
				if (travel == m_head) { //if the traveling pointer is the head
					travel->m_prev = nn; //prepend the list
					nn->m_next = travel;
					m_head = nn;
					loop = false; //stop the loop
				}
				else //the data is not the first in the list
				{
					Node<DATA>* trail = travel->m_prev; //find the node right before
					trail->m_next = nn; //set the next to the new node
					nn->m_prev = trail; //set the new nodes previous to the trailing pointer
					nn->m_next = travel; //set the new noedes next to the traveling pointer
					travel->m_prev = nn; //set the traveling pointers previous to the new node
					loop = false; //stop the loop
				}
			}
			else if (travel == m_tail) { //if the pointer has traveled to the end of the list but the data is alphabetically last
				travel->m_next = nn; //append the list
				nn->m_prev = travel;
				m_tail = nn;
				loop = false; //stop the loop
			}
			travel = travel->m_next; //traverse the list
		}


	}
}

template<>
void List<Armor>::insertArmor(Armor data) {
	Node<Armor>* nn = new Node<Armor>(data); //initialize new node with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else
	{
		Node<Armor>* travel = m_head; //create a traveling pointer at the beginning of the list
		bool loop = true; //conditional statement for looping
		while (loop) { //while loop is not false
			if (nn->m_data.Compare(nn->m_data, travel->m_data) == true) { //if they are the same
				travel->m_data.setQuant(travel->m_data.getQuant() + 1); //increase the quantity of the current node
				delete nn; //delete the new node
				loop = false; //stop the loop
			}
			else if (travel == m_tail) { //if at the end of the list and not equal to  
				travel->m_next = nn;
				nn->m_prev = travel;
				m_tail = nn;
				loop = false; //append the list and stop the loop
			}
			travel = travel->m_next; //traverse the list
		}
	}
}

template <> 
void List<Blade>::insertBlade(Blade data) {
	Node<Blade>* nn = new Node<Blade>(data); //initialize new node with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else
	{
		Node<Blade>* travel = m_head; //set a travelling pointer at the beginning of the list
		bool loop = true; //conditional statement
		while (loop) { //while loop is true
			if (nn->m_data.Compare(nn->m_data, travel->m_data) == true) { //if they are the same
				travel->m_data.setQuant(travel->m_data.getQuant() + 1); //increase the quantity of the current node
				delete nn; //delete the new node
				loop = false; //stop the loop
			}
			else if (travel == m_tail) { //if at the end of the list and not equal to
				travel->m_next = nn;
				nn->m_prev = travel;
				m_tail = nn;
				loop = false; //append the list and stop the loop
			}
			travel = travel->m_next; //traverse the list
		}
	}
}


template<>
void List<Mushroom>::insertMushroom(Mushroom data) {
	Node<Mushroom>* nn = new Node<Mushroom>(data); //initialize new node with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else
	{
		Node<Mushroom>* travel = m_head; //travelling pointer at beginning of list
		bool loop = true; //conditional statement
		while (loop) { //while loop is true
			if (nn->m_data.Compare(nn->m_data, travel->m_data) == true) { //if they are the same
				travel->m_data.setQuant(travel->m_data.getQuant() + 1); //increase the quantity of the current node
				delete nn; //delete the new node
				loop = false; //stop the loop
			}
			else if (travel == m_tail) { //if at the end of the list and not equal to
				travel->m_next = nn;
				nn->m_prev = travel;
				m_tail = nn;
				loop = false; //append the list and stop the loop
			}
			travel = travel->m_next; //traverse the list
		}
	}
}



template <>
void List<Potion>::insertPotion(Potion data) {
	Node<Potion>* nn = new Node<Potion>(data); //initialize new node with data
if (m_head == nullptr) { //if the list is nonexistent
	m_head = nn; //set the head to new node
	m_tail = nn; //set the tail to new node
}
else
{
	Node<Potion>* travel = m_head; //traveling pointer from the beginning of the list
	bool loop = true; //keep looping until finished
	while (loop) { //while loop is true
		if (nn->m_data.Compare(nn->m_data, travel->m_data) == true) { //if they are the same
			travel->m_data.setQuant(travel->m_data.getQuant() + 1); //increase the quantity of the current node
			delete nn; //delete the new node
			loop = false; //stop the loop
		}
		else if (travel == m_tail) { //if at the end of the list and not equal to
			travel->m_next = nn;
			nn->m_prev = travel;
			m_tail = nn;
			loop = false; //append the list and stop the loop
		}
		travel = travel->m_next; //traverse the list
		}
	}
}


template<>
void List<Ranged>::insertRanged(Ranged data) {
	Node<Ranged>* nn = new Node<Ranged>(data); //initialize new node with data
	if (m_head == nullptr) { //if the list is nonexistent
		m_head = nn; //set the head to new node
		m_tail = nn; //set the tail to new node
	}
	else
	{
		Node<Ranged>* travel = m_head; //create a traveling pointer starting at list beginning
		bool loop = true; //conditional statement
		while (loop) { //while loop is true
			if (nn->m_data.Compare(nn->m_data, travel->m_data) == true) { //if they are the same
				travel->m_data.setQuant(travel->m_data.getQuant() + 1); //increase the quantity of the current node
				delete nn; //delete the new node
				loop = false; //stop the loop
			}
			else if (travel == m_tail) { //if at the end of the list and not equal to 
				travel->m_next = nn;
				nn->m_prev = travel;
				m_tail = nn;
				loop = false; //append the list and stop the loop
			}
			travel = travel->m_next; //traverse the list
		}
	}
}


template<typename DATA>
void List<DATA>::purgeList()//delete all nodes
{
	Node<DATA>* travel = m_head; //from the head of the list
	while (travel != nullptr) { //while the list still exists
		m_head = travel->m_next;
		delete travel; //delete the nodes
		travel = m_head; //traverse the list
	}
	m_tail = travel;
}

template<typename DATA>
void List<DATA>::displayListFrwd() //display from head to tail
{
	Node<DATA>* travel = m_head; //travel set to start of list
	while (travel != m_tail) { //while it is not at the end 
		travel->m_data.Display(); //output data 
		travel = travel->m_next; //traverse the list
	}
	travel->m_data.Display();
	cout << std::endl;//at the end, output just the data
}

template<typename DATA>
void List<DATA>::displayListBckwd() //display from tail to head
{
	Node<DATA>* travel = m_tail; //travel set to end of list
	while (travel != m_head) { //while it is not at the start
		travel->m_data.Display(); //output data 
		travel = travel->m_prev; //traverse the list
	}
	travel->m_data.Display() << std::endl; //at the start, output only data
}

template<>
void List<Armor>::deleteArmor(Armor data) {
	try {
		if (m_head == nullptr) //if the list is nonexistent
			throw invalid_argument("Error: List doesn't exist");
	}
	catch (invalid_argument& e) {
		cerr << e.what() << std::endl;
	}
	if (m_head != nullptr) {
		Node<Armor>* travel = m_head; //traveling pointer to traverse the list
		while (!(travel->m_data == data) && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel->m_data.getQuant() > 1) {
			travel->m_data.setQuant(travel->m_data.getQuant() - 1);
		}
		else if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node<Armor>* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else {
			try {
				throw invalid_argument("Error: List doesn't exist");
			}
			catch (invalid_argument& e) {
				cerr << e.what() << std::endl;
			}
		}
	}
}

template<>
void List<Blade>::deleteBlade(Blade data) {
	try {
		if (m_head == nullptr) //if the list is nonexistent
			throw invalid_argument("Error: List doesn't exist");
	}
	catch (invalid_argument& e) {
		cerr << e.what() << std::endl;
	}
	if (m_head != nullptr) {
		Node<Blade>* travel = m_head; //traveling pointer to traverse the list
		while (!(travel->m_data == data) && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel->m_data.getQuant() > 1) {
			travel->m_data.setQuant(travel->m_data.getQuant() - 1);
		}
		else if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node<Blade>* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else {
			try {
				throw invalid_argument("Error: List doesn't exist");
			}
			catch (invalid_argument& e) {
				cerr << e.what() << std::endl;
			}
		}
	}
}

template<>
void List<Mushroom>::deleteMushroom(Mushroom data) {
	try {
		if (m_head == nullptr) //if the list is nonexistent
			throw invalid_argument("Error: List doesn't exist");
	}
	catch (invalid_argument& e) {
		cerr << e.what() << std::endl;
	}
	if (m_head != nullptr) {
		Node<Mushroom>* travel = m_head; //traveling pointer to traverse the list
		while (!(travel->m_data == data) && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel->m_data.getQuant() > 1) {
			travel->m_data.setQuant(travel->m_data.getQuant() - 1);
		}
		else if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node<Mushroom>* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else {
			try {
				throw invalid_argument("Error: List doesn't exist");
			}
			catch (invalid_argument& e) {
				cerr << e.what() << std::endl;
			}
		}
	}
}

template<>
void List<Potion>::deletePotion(Potion data) {
	try {
		if (m_head == nullptr) //if the list is nonexistent
			throw invalid_argument("Error: List doesn't exist");
	}
	catch (invalid_argument& e) {
		cerr << e.what() << std::endl;
	}
	if (m_head != nullptr) {
		Node<Potion>* travel = m_head; //traveling pointer to traverse the list
		while (!(travel->m_data == data) && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel->m_data.getQuant() > 1) {
			travel->m_data.setQuant(travel->m_data.getQuant() - 1);
		}
		else if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node<Potion>* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else {
			try {
				throw invalid_argument("Error: List doesn't exist");
			}
			catch (invalid_argument& e) {
				cerr << e.what() << std::endl;
			}
		}
	}
}

template<>
void List<Ranged>::deleteRanged(Ranged data) {
	try {
		if (m_head == nullptr) //if the list is nonexistent
			throw invalid_argument("Error: List doesn't exist");
	}
	catch (invalid_argument& e) {
		cerr << e.what() << std::endl;
	}
	if (m_head != nullptr) {
		Node<Ranged>* travel = m_head; //traveling pointer to traverse the list
		while (!(travel->m_data == data) && travel != m_tail) //while the data isn't found and the traveling pointer hasn't found the end
			travel = travel->m_next; //traverse the list
		if (travel->m_data.getQuant() > 1) {
			travel->m_data.setQuant(travel->m_data.getQuant() - 1);
		}
		else if (travel == m_head) { //if the deleted item is the head of the list
			m_head = travel->m_next; //set the next item in the list to the head of the list
			delete travel; //delete the item 
			m_head->m_prev = nullptr; //set the previous to nothing, since this is the head of the list
		}
		else if (data == m_tail->m_data) { //if the item to be deleted is the last
			m_tail = travel->m_prev; //find the item right before the deleted one
			delete travel; //delete the item
			m_tail->m_next = nullptr; //this is now the end of the list
		}
		else if (travel->m_data == data) { //if the data is found but not the head or the tail
			Node<Ranged>* trail = travel->m_prev; //find the node right before the item
			trail->m_next = travel->m_next; //set the node to point to the next node after the item
			travel->m_next->m_prev = trail; //set that node's previous to the node before the item
			delete travel; //delete the item
		}
		else {
			try {
				throw invalid_argument("Error: List doesn't exist");
			}
			catch (invalid_argument& e) {
				cerr << e.what() << std::endl;
			}
		}
	}
}