/*****************************************************
* 
* Author: Zaelfenn Sandow
* 
* Date Created: 04/25/2023
* 
* 
* Purpose: an Inventory for an RPG-style game. The inventory is sorted into
* 5 distinct parts- armor, blades, ranged weapons, mushrooms, and potions.
* these 5 parts all have their own linked lists. However, given how similar
* the contents are, a templated linked list is all that is necessary. 
* 
****************************************************************/

#include "String.h"
#include "List.h"
#include "Armor.h"
#include "Blade.h"
#include "Mushroom.h"
#include "Potion.h"
#include "Ranged.h"
#include <fstream>
using std::ifstream;
//memory leaks...
#define _CRT_DBG_MAP_ALLOC 




#include<crtdbg.h>

int createClass(const char* word); //used to determine what kind of item is being added to the inventory

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //memory leaks...
	List<Armor> armor;
	List<Blade> blade;
	List<Mushroom> mushroom;
	List<Potion> potion;
	List<Ranged> ranged;

	Armor n_armor;
	Blade n_blade;
	Mushroom n_mushroom;
	Potion n_potion;
	Ranged n_ranged;

	Mushroom test_del;
	test_del.setSpecies("Oyster");
	test_del.setEffects("+10 chance to find treasure for 10 minutes");

	ifstream inv("Assignment 5.txt");
	if (inv.is_open()) {
		char line[75];
		inv.getline(line, 75);
		String word(strtok(line, ","));
		
		switch (createClass(word.getStr())) {
		case 1: //armor
			word = strtok(NULL, ","); //continue the tokenization of the string
			n_armor.setType(word); //sets the type of armor to what was tokenized from the string
			word = strtok(NULL, ","); //continue tokinizing
			n_armor.setClass(word.sToI()); //sets the class given by the string (cast to an integer)
			armor.insertArmor(n_armor); //inserts the new object into the list
		
			break;
		
		case 2: //blade
			
			word = strtok(NULL, ","); //continue the tokenization of the string
			n_blade.setType(word); //set the type of blade
			word = strtok(NULL, ","); //keep tokenizing
			n_blade.setMat(word); //set the material of the blade
			word = strtok(NULL, ","); //last tokenization...
			n_blade.setDmg(word); //set the damage of the blade
			blade.insertBlade(n_blade); //insert the blade into the list
		
			break;
		
		case 3: //mushroom
			word = strtok(NULL, ","); 
			n_mushroom.setSpecies(word); //set the species of mushroom
			word = strtok(NULL, ",");
			n_mushroom.setEffects(word); //set the effects of mushroom
			mushroom.insertMushroom(n_mushroom); //insert the mushroom into the list
		
			break;
		
		case 4: //potion
			word = strtok(NULL, ",");
			n_potion.setName(word); //set the name of the potion
			word = strtok(NULL, ",");
			n_potion.setDescription(word); //set the description of the potion
			potion.insertPotion(n_potion); //insert the potion into the list
		
			break;
	
		case 5: //ranged
			word = strtok(NULL, ",");
			n_ranged.setType(word); //set the type of ranged weapon
			word = strtok(NULL, ","); 
			n_ranged.setDmg(word); //set the damage of the ranged weapon
			ranged.insertRanged(n_ranged); //insert the ranged weapon into the list
			
			break;
		
		default:
			cout << "Error: no type given" << std::endl;

		}
		
		while (!inv.eof()) {
			inv.getline(line, 75);
			String word = strtok(line, ",");
			
			switch (createClass(word.getStr())) {
			case 1: //armor
				word = strtok(NULL, ","); //continue the tokenization of the string
				n_armor.setType(word); //sets the type of armor to what was tokenized from the string
				word = strtok(NULL, ","); //continue tokinizing
				n_armor.setClass(word.sToI()); //sets the class given by the string (cast to an integer)
				armor.insertArmor(n_armor); //inserts the new object into the list

				break;

			case 2: //blade

				word = strtok(NULL, ","); //continue the tokenization of the string
				n_blade.setType(word); //set the type of blade
				word = strtok(NULL, ","); //keep tokenizing
				n_blade.setMat(word); //set the material of the blade
				word = strtok(NULL, ","); //last tokenization...
				n_blade.setDmg(word); //set the damage of the blade
				blade.insertBlade(n_blade); //insert the blade into the list

				break;

			case 3: //mushroom
				word = strtok(NULL, ",");
				n_mushroom.setSpecies(word); //set the species of mushroom
				word = strtok(NULL, ",");
				n_mushroom.setEffects(word); //set the effects of mushroom
				mushroom.insertMushroom(n_mushroom); //insert the mushroom into the list

				break;

			case 4: //potion
				word = strtok(NULL, ",");
				n_potion.setName(word); //set the name of the potion
				word = strtok(NULL, ",");
				n_potion.setDescription(word); //set the description of the potion
				potion.insertPotion(n_potion); //insert the potion into the list

				break;

			case 5: //ranged
				word = strtok(NULL, ",");
				n_ranged.setType(word); //set the type of ranged weapon
				word = strtok(NULL, ",");
				n_ranged.setDmg(word); //set the damage of the ranged weapon
				ranged.insertRanged(n_ranged); //insert the ranged weapon into the list

				break;

			default:
				cout << "Error: no type given" << std::endl;

			}
		}
		cout << "Armor:" << std::endl;
		armor.displayListFrwd();
		cout << "Mushrooms: " << std::endl;
		mushroom.deleteMushroom(test_del);
		mushroom.displayListFrwd();
		cout << "Potions:" << std::endl;
		potion.displayListFrwd();
		cout << "Ranged Weapons: " << std::endl;
		ranged.displayListFrwd();
		cout << "Blades:" << std::endl;
		blade.deleteBlade(n_blade);
		blade.displayListFrwd();



		inv.close();
	}
	else
		cout << "Error opening file";
	return 0;
}


int createClass(const char* word) {
	enum { ARMOR = 1, BLADE, MUSHROOM, POTION, RANGED }type{}; //enum named "type" that initializes to 0, where armor = 1, blade = 2, etc.
	if (*word == 'A') { //if the first letter of the string is an A
		type = ARMOR; //the class object to be created should be of type Armor
	}
	else if (*word == 'B') { //if the first letter of the string is a B
		type = BLADE; //the class object should be of type Blade
	}
	else if (*word == 'M') { //if the first letter of the string is an M
		type = MUSHROOM; //the class object should be of type Mushroom
	}
	else if (*word == 'P') { //if the first letter of the string is a P
		type = POTION; //the class object should be of type Potion
	}
	else if (*word == 'R') { //if the first letter of the string is an R
		type = RANGED; //the class object should be of type ranged
	}
	return type; //returns either 0 (error) or 1,2,3,4,5 (A,B,M,P,R respectively)
}