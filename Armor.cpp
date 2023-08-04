#include "Armor.h"
#ifndef iostream
#include <iostream>
using std::cout;
#endif

Armor::Armor() : m_type(""), m_class(0), m_quantity(1) //default constructor
{}

Armor::Armor(const Armor& original) : m_class(original.m_class), m_type(original.m_type), m_quantity(original.m_quantity) //copy constructor
{}

Armor::~Armor() { //destructor
	m_type = "";
	m_class = 0;
	m_quantity = 0; //set member variables to default values
}

Armor::Armor(Armor&& original) noexcept : m_class(original.m_class), m_type(original.m_type), m_quantity(original.m_quantity) //copy constructor
{}

Armor& Armor::operator = (const Armor& rhs) { //copy assignment operator
	if (this != &rhs) {
		m_class = rhs.m_class;
		m_type = rhs.m_type;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}

Armor& Armor::operator = (Armor&& rhs) noexcept { //copy assignment operator
	if (this != &rhs) {
		m_class = rhs.m_class;
		m_type = rhs.m_type;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}



void Armor::setType(String name) {//setter for string "name"
	m_type = name;
}

String Armor::getType() { //getter for string "name"
	return m_type;
}

void Armor::setClass(int _class) { //setter for int "class"
	m_class = _class;
}

int Armor::getClass() { //getter for int "class"
	return m_class;
}

void Armor::setQuant(int quant) { //setter for int "quantity"
	m_quantity = quant;
}

int Armor::getQuant() { //getter for int "quantity"
	return m_quantity;
}



bool Armor::Compare(Armor original, Armor comp) { //compares 2 armors
	bool same = false; //assuming they are not the same
	if (original.m_class == comp.m_class && original.m_type == comp.m_type) { //if the classes and types match
		same = true; //the armor is the same
	}
	return same; //return true for same and false for not the same
}

bool Armor::operator == (const Armor& rhs) { //comparison operator
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}
bool Armor::operator == (Armor&& rhs) {
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}


void Armor::Display() { //display function
	cout << "- " << m_type << " armor of class: " << m_class << "   x" << m_quantity << std::endl;

}