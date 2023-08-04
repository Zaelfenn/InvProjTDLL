#pragma once
#ifndef String
#include "String.h"
#endif 

class Ranged
{
public:
	Ranged(); //default constructor
	Ranged(const Ranged& original); //copy constructor
	~Ranged(); //destructor
	Ranged(Ranged&& original)noexcept; //copy constructor
	Ranged& operator = (const Ranged& rhs); //copy assignment operator
	Ranged& operator = (Ranged&& rhs)noexcept; //copy assignment operator


	bool Compare(Ranged original, Ranged comp); //comparison function

	bool operator == (const Ranged& rhs);
	bool operator == (Ranged&& rhs);

	void setType(String type); //setter
	String getType(); //getter
	void setDmg(String dmg); //setter
	String getDmg(); //getter
	void setQuant(int quant); //setter
	int getQuant(); //getter

	void Display(); //display function
private:
	String m_type; //the type of ranged weapon should be a string (i.e. Heavy Crossbow)
	String m_damage; //the damage type should be a string (i.e. 1d8)
	int m_quantity; //the quantity should be an int (i.e. 4)

};

