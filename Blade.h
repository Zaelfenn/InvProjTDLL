#pragma once
#ifndef String
#include "String.h"
#endif 
class Blade
{
public:
	Blade();
	Blade(const Blade& original);
	~Blade();
	Blade(Blade&& original)noexcept;
	Blade& operator = (const Blade& rhs);
	Blade& operator = (Blade&& rhs)noexcept;


	bool Compare(Blade original, Blade comp);

	bool operator == (const Blade& rhs);
	bool operator == (Blade&& rhs);
	
	void setType(String type);
	String getType();
	void setMat(String material);
	String getMat();
	void setDmg(String dmg);
	String getDmg();
	void setQuant(int quant);
	int getQuant();

	void Display();
private:
	String m_type;
	String m_material;
	String m_damage;
	int m_quantity;

};

