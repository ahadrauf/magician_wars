#pragma once
#include <iostream>
#include "Person.h"
#include "List.h"
#include "Skill.h"

class Enemy : public Person
{

public:
	Enemy() //default constructor
	{
		*this = *getEnemy(1);
	}

	Enemy(string n, int l, bool spells, int HB = 20, int MB = 3, int aB = 3, int dB = 3, int mB = 3, int rB = 3, 
		List<Skill *>s = List<Skill *>()) : Person(n), skills(s) //creates new enemies
	{
		addSkill(Fireball());
		for (int i = 0; i < l; i++)
		{
			increaseLevel(HB, MB, aB, dB, mB, rB);
		}
		canUseSpells = spells;
	}

	Enemy(string n, int l, int h, int m, int aP, int dP, int mA, int mD, bool spells, List<Skill *>s = List<Skill *>())
		: Person(n, l, h, m, aP, dP, mA, mD), skills(s)
	{

		addSkill(Fireball());

	}

	void addSkill(Skill s)
	{
		skills.insertAtBack(new Skill(s));
	}
	void useSkill(Skill *s, Person &p)
	{
		getSkill(s->getName())->useSkill(this, &p);
	}
	Enemy operator=( Enemy &right) //overloads = operator
	{

		Person::operator=(right);

		skills = right.skills;
		canUseSpells = right.canUseSpells;

		return *this;
	}

	void attack(Person &p) //AI for attacking
	{
		if (skills.isEmpty())
		{
			Person::attack(p, true);
		}
		else
		{

			if (canUseSpells && (p.getMagicalDefense() < p.getPhysicalDefense() && getMP() >= skills.getLast()->getMPCost())) //attacks using magic if enemy can
			{
				useSkill(skills.getLast(), p);
			}
			else
			{
				Person::attack(p, true);
			}
		}
	}

	void createNewEnemy() //assigns spells to new enemy
	{
		*this = *getEnemy(getLevel() + 1);
		if (canUseSpells)
		{
			if (getLevel() >= 5)
				addSkill(*(new FireStorm()));
			if (getLevel() >= 10)
				addSkill(*(new LavaPlume()));
		}
	}

	Skill *getSkill(const string &n) //allows for polymorphism
	{
		if (n == "Fireball")
			return new Fireball();
		if (n == "Fire Storm")
			return new FireStorm();
		if (n == "Lava Plume")
			return new LavaPlume();
		return NULL;
	}

	Enemy *getEnemy(int l) //randomly generates new enemy
	{
		int choice = rand() % 5;
		string names[5] = { "Soldier", "Knight", "Mage", "Dark Knight", "Dragon" };
		int boostValues[5][6] = {
				{ 20, 3, 3, 3, 3, 3 },
				{ 30, 1, 5, 5, 1, 3 },
				{ 10, 10, 1, 3, 5, 5 },
				{ 15, 15, 5, 5, 5, 5 },
				{ 30, 20, 7, 7, 7, 7 } }; //growth rates
		bool spells[5] = { false, false, true, true, true };
		return new Enemy(names[choice], l, spells[choice], boostValues[choice][0], boostValues[choice][1], boostValues[choice][2],
			boostValues[choice][3], boostValues[choice][4], boostValues[choice][5]);
		
	}
private:
	List<Skill *> skills;
	Item *helm;
	Item *weapon;
	Item *armor;
	bool canUseSpells = false;
	
};