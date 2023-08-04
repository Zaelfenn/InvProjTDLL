#include "Blade.h"
#ifndef iostream
#include <iostream>
using std::cout;
#endif

Blade::Blade() : m_type(""), m_material(""), m_damage(""), m_quantity(1)
{} //default constructor

Blade::Blade(const Blade& original) : m_type(original.m_type), m_material(original.m_material), m_damage(original.m_damage), m_quantity(original.m_quantity)
{} //copy constructor

Blade::~Blade() { //destructor
	m_type = "";
	m_material = "";
	m_damage = "";
	m_quantity = 0; //set member variables to default values
}

Blade::Blade(Blade&& original)noexcept : m_type(original.m_type), m_material(original.m_material), m_damage(original.m_damage), m_quantity(original.m_quantity)
{} //copy constructor

Blade& Blade::operator = (const Blade& rhs) { //copy assignment operator
	if (this != &rhs) {
		m_type = rhs.m_type;
		m_material = rhs.m_material;
		m_damage = rhs.m_damage;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}

Blade& Blade::operator = (Blade&& rhs)noexcept { //copy assignment operator
	if (this != &rhs) {
		m_type = rhs.m_type;
		m_material = rhs.m_material;
		m_damage = rhs.m_damage;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}



void Blade::setType(String type) { //setter for string "type"
	m_type = type;
}

String Blade::getType() { //getter for string "type"
	return m_type;
}

void Blade::setMat(String material) { //setter for string "material"
	m_material = material;
}

String Blade::getMat() { //getter for string "material"
	return m_material;
}

void Blade::setDmg(String dmg) { //setter for string "damage"
	m_damage = dmg;
}

String Blade::getDmg() { //getter for string "damage"
	return m_damage;
}

void Blade::setQuant(int quant) { //setter for int "quantity"
	m_quantity = quant;
}

int Blade::getQuant() {//getter for int "quantity"
	return m_quantity;
}



bool Blade::Compare(Blade original, Blade comp) { //compare 2 instances of blades
	bool same = false; //assume they are not the same

	if (original.m_type == comp.m_type && original.m_material == comp.m_material && original.m_damage == comp.m_damage) //if the damage, materials, and type match
		same = true; //they are the same

	return same; //return true for same and false for not the same
}

bool Blade::operator == (const Blade& rhs) { //comparison operator
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}
bool Blade::operator == (Blade&& rhs) {
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}

void Blade::Display() { //display function
	cout << "- " << m_type << " of " << m_material << " x" << m_quantity << " dmg: " << m_damage << std::endl;
}
