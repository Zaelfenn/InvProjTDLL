#pragma once
#ifndef String
#include "String.h"
#endif 

class Mushroom
{
public:
	Mushroom();
	Mushroom(const Mushroom& original);
	~Mushroom();
	Mushroom(Mushroom&& original)noexcept;
	Mushroom& operator = (const Mushroom& rhs);
	Mushroom& operator = (Mushroom&& rhs)noexcept;


	bool Compare(Mushroom original, Mushroom comp);
	
	bool operator == (const Mushroom& rhs);
	bool operator == (Mushroom&& rhs);

	void setSpecies(String species);
	String getSpecies();
	void setEffects(String effects);
	String getEffects();
	void setQuant(int quant);
	int getQuant();

	void Display();

private:
	String m_species;
	String m_effects;
	int m_quantity;

};

