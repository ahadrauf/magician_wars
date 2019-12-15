#pragma once
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

//base class
class Skill
{
public:
	Skill(string n, string d, int m) : name(n), description(d), mpCost(m) {}
	string getName() { return name; }
	string getDescription() { return description; }
	int getMPCost() { return mpCost; }
	virtual bool useSkill(Person *attacker, Person *defender) { return true; } //for polymorphism
	bool operator==(const Skill &right)
	{
		return (name == right.name) ? true : false;
	}
	bool operator>(const Skill &right)
	{
		return (name > right.name) ? true : false;
	}
	bool operator<(const Skill &right)
	{
		return (name < right.name) ? true : false;
	}
	bool operator==(const Skill *right)
	{
		return (name == right->name) ? true : false;
	}
	bool operator>(const Skill *right)
	{
		return (name > right->name) ? true : false;
	}
	bool operator<(const Skill *right)
	{
		return (name < right->name) ? true : false;
	}

	friend ostream &operator<< (ostream &strm, const Skill &obj)
	{
		strm << obj.name << endl;
		return strm;
	}
private:
	string name;
	string description;
	int mpCost;
};

//The following classes override the useSkill function
class Fireball : public Skill
{
public:
	Fireball() : Skill("Fireball", "Deals a little damage", 10) {}
	bool useSkill(Person *attacker, Person *defender)
	{
		if (attacker->getMP() >= getMPCost())
		{
			attacker->attack(*defender, false, 1.5);
			attacker->addMP(-getMPCost());
			cout << attacker->getName() << " used the skill Fireball!\n\n" << endl;
			PlaySound(TEXT("Fireball.wav"), NULL, SND_SYNC);
			return true;
		}
		else
		{
			cout << "You don't have enough MP to use the skill Fireball!\n";
			system("pause");
			return false;
		}
		
	}

};

class FireStorm : public Skill
{
public:
	FireStorm() : Skill("Fire Storm", "Deals a lot of damage", 20) {}
	bool useSkill(Person *attacker, Person *defender)
	{
		if (attacker->getMP() >= getMPCost())
		{
			attacker->attack(*defender, false, 2.5);
			attacker->addMP(-getMPCost());
			cout << attacker->getName() << " used the skill Fire Storm!" << endl;
			PlaySound(TEXT("Fireballs.wav"), NULL, SND_SYNC);
			return true;
		}
		else
		{
			cout << "You don't have enough MP to use the skill Fire Storm!\n";
			system("pause");
			return false;
		}

	}
};

class LavaPlume : public Skill
{
public:
	LavaPlume() : Skill("Lava Plume", "Deals a lot of damage", 35) {}
	bool useSkill(Person *attacker, Person *defender)
	{
		if (attacker->getMP() >= getMPCost())
		{
			attacker->attack(*defender, false, 4);
			attacker->addMP(-getMPCost());
			cout << attacker->getName() << " used the skill Lava Plume!" << endl;
			PlaySound(TEXT("lava2.wav"), NULL, SND_SYNC);
			return true;
		}
		else
		{
			cout << "You don't have enough MP to use the skill Lava Plume!\n";
			system("pause");
			return false;
		}

	}
};