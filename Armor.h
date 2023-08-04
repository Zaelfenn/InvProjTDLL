#pragma once
#ifndef String
#include "String.h"
#endif 



class Armor
{
public:
	Armor();
	Armor(const Armor& original);
	~Armor();
	Armor(Armor&& original)noexcept;
	Armor& operator = (const Armor& rhs);
	Armor& operator = (Armor&& rhs)noexcept;


	bool Compare(Armor original, Armor comp);

	bool operator == (const Armor& rhs);
	bool operator == (Armor&& rhs);

	void setType(String type);
	String getType();
	void setClass(int _class);
	int getClass();
	void setQuant(int quant);
	int getQuant();

	void Display();


private:
	String m_type;
	int m_class;
	int m_quantity;

};

