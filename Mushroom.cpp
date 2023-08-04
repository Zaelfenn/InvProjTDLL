#include "Mushroom.h"
#ifndef iostream
#include <iostream>
using std::cout;
#endif

Mushroom::Mushroom() : m_species(""), m_effects(""), m_quantity(1)
{} //default constructor

Mushroom::Mushroom(const Mushroom& original) : m_species(original.m_species), m_effects(original.m_effects), m_quantity(original.m_quantity)
{} //copy constructor

Mushroom::~Mushroom(){ //destructor
	m_species = "";
	m_effects = "";
	m_quantity = 0; //sets all member variables to default values
}

Mushroom::Mushroom(Mushroom&& original) noexcept : m_species(original.m_species), m_effects(original.m_effects), m_quantity(original.m_quantity)
{} //copy constructor

Mushroom& Mushroom::operator = (const Mushroom& rhs) { //copy assignment operator
	if (this != &rhs) {
		m_species = rhs.m_species;
		m_effects = rhs.m_effects;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}

Mushroom& Mushroom::operator = (Mushroom&& rhs)noexcept { //copy assignment operator
	if (this != &rhs) {
		m_species = rhs.m_species;
		m_effects = rhs.m_effects;
		m_quantity = rhs.m_quantity;
	}
	return *this;
}



void Mushroom::setSpecies(String species) { //setter for string "species"
	m_species = species;
}

String Mushroom::getSpecies() { //getter for string "species"
	return m_species;
}

void Mushroom::setEffects(String effects) { //setter for string "effects"
	m_effects = effects;
}

String Mushroom::getEffects() { //getter for string "effects"
	return m_effects;
}

void Mushroom::setQuant(int quant) { //setter for int "quantity"
	m_quantity = quant;
}

int Mushroom::getQuant() { //getter for int "quantity"
	return m_quantity;
}



bool Mushroom::Compare(Mushroom original, Mushroom comp) { //compare function
	bool same = false; //assume they aren't the same

	if (original.m_species == comp.m_species && original.m_effects == comp.m_effects) //if the species and effects are the same
		same = true; //they are the same

	return same; //return true for same and false for not the same
}

bool Mushroom::operator == (const Mushroom& rhs) { //comparison operator
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}
bool Mushroom::operator == (Mushroom&& rhs) {
	bool retVal = Compare(*this, rhs); //calls compare function to detect if they are the same
	return retVal; //return result
}


void Mushroom::Display() { //display function
	cout << "- " << m_species << "; " << m_effects << " x" << m_quantity << std::endl;
}
