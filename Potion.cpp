#include "Potion.h"
#ifndef iostream
#include <iostream>
using std::cout;
#endif

Potion::Potion() : m_name(""), m_description(""), m_quantity(1) //default constructor
{}

Potion::Potion(const Potion& original) : m_name(original.m_name), m_description(original.m_description), m_quantity(original.m_quantity) //copy constructor
{}

Potion::~Potion() { //destructor
	m_name = "";
	m_description = "";
	m_quantity = 0; //set member variables to default values
}

Potion::Potion(Potion&& original) noexcept : m_name(original.m_name), m_description(original.m_description), m_quantity(original.m_quantity)
{} //copy constructor

Potion& Potion::operator = (const Potion& rhs) { //copy assignment operator
	if (this != &rhs) {
		m_name = rhs.m_name;
		m_description = rhs.m_description;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}

Potion& Potion::operator = (Potion&& rhs) noexcept{ //copy assignment operator
	if (this != &rhs) {
		m_name = rhs.m_name;
		m_description = rhs.m_description;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}





void Potion::setName(String name) { //setter for string "name"
	m_name = name;
}

String Potion::getName() { //getter for string "name"
	return m_name;
}

void Potion::setDescription(String description) { //setter for string "description
	m_description = description;
}

String Potion::getDescription() { //getter for string "description"
	return m_description;
}

void Potion::setQuant(int quant) { //setter for integer "quantity"
	m_quantity = quant;
}

int Potion::getQuant() { //getter for integer "quantity"
	return m_quantity;
}



bool Potion::Compare(Potion original, Potion comp) { //compares two instances of class "potion"
	bool same = false; //start off with the assumption that they aren't the same
	if (original.m_name == comp.m_name && original.m_description == comp.m_description) //if they have the same name and description
		same = true; //they are the same

	return same; //returns false for not same and true for the same
}

bool Potion::operator == (const Potion& rhs) { //comparison operator
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}
bool Potion::operator == (Potion&& rhs) {
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}

void Potion::Display() { //display function
	cout << "- " << m_name << "; " << m_description << " x" << m_quantity << std::endl;
}