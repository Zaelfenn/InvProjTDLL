#pragma once
#ifndef String
#include "String.h"
#endif 

class Potion
{
public:
	Potion();
	Potion(const Potion& original);
	~Potion();
	Potion(Potion&& original)noexcept;
	Potion& operator = (const Potion& rhs);
	Potion& operator = (Potion&& rhs)noexcept;


	bool Compare(Potion original, Potion comp);

	bool operator == (const Potion& rhs);
	bool operator == (Potion&& rhs);

	void setName(String name);
	String getName();
	void setDescription(String description);
	String getDescription();
	void setQuant(int quant);
	int getQuant();

	void Display();

private:
	String m_name;
	String m_description;
	int m_quantity;
};

