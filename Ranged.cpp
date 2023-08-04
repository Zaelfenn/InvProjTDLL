#include "Ranged.h"
#ifndef iostream
#include <iostream>
using std::cout;
#endif

Ranged::Ranged() : m_type(""), m_damage(""), m_quantity(1) //default constructor
{}

Ranged::Ranged(const Ranged& original) : m_type(original.m_type), m_damage(original.m_damage), m_quantity(original.m_quantity) //copy constructor
{}

Ranged::~Ranged() { //destructor
	m_type = "";
	m_damage = "";
	m_quantity = 0; //sets the member variables to default value
}

Ranged::Ranged(Ranged&& original)noexcept : m_type(original.m_type), m_damage(original.m_damage), m_quantity(original.m_quantity) //copy constructor
{}

Ranged& Ranged::operator = (const Ranged& rhs) { //copy assignment operator
	if (this != &rhs) {
		m_type = rhs.m_type;
		m_damage = rhs.m_damage;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}

Ranged& Ranged::operator = (Ranged&& rhs) noexcept{ //copy assignment operator
	if (this != &rhs) {
		m_type = rhs.m_type;
		m_damage = rhs.m_damage;
		m_quantity = rhs.m_quantity;
	}

	return *this;
}



void Ranged::setType(String type) { //setter for string "type"
	m_type = type;
}

String Ranged::getType() { //getter for string "type"
	return m_type;
}

void Ranged::setDmg(String dmg) { //setter for string "damage"
	m_damage = dmg;
}

String Ranged::getDmg() { //getter for string "damage"
	return m_damage;
}

void Ranged::setQuant(int quant) { //setter for int "quantity"
	m_quantity = quant;
}

int Ranged::getQuant() { //getter for int "quantity"
	return m_quantity;
}


bool Ranged::Compare(Ranged original, Ranged comp) { //comparison function
	bool same = false; //assume they are not the same

	if (original.m_type == comp.m_type && original.m_damage == comp.m_damage)  //if the damage and types are equal
		same = true; //they are the same

	return same; //return "true" for the same and "false" for not the same
}

bool Ranged::operator == (const Ranged& rhs) { //comparison operator
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}
bool Ranged::operator == (Ranged&& rhs) {
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}


void Ranged::Display() { //display function
	cout << "- " << m_type << " x" << m_quantity << " dmg: " << m_damage <<  std::endl;
}


