#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;


class Item //base class Item (used for polymorphsim)
{
public:
	Item() : cost(0) {}
	Item(const char *n, const int c, const char *d)
	{
		name = n;
		cost = c;
		description = d;
	}

	Item(const Item &i) : name(i.name), cost(i.cost), description(i.description) {}
	Item(const Item *i) : name(i->name), cost(i->cost), description(i->description) {}
	string getName() const
	{
		return name;
	}
	string getDescription() const
	{
		return description;
	}
	int getCost() const
	{
		return cost;
	}
	virtual void performEffect(Person *, Person *) { } //virtual function for polymorphism

	bool operator==(const Item &right)
	{
		return (name == right.name) ? true : false;
	}
	bool operator>(const Item &right)
	{
		return (name > right.name) ? true : false;
	}
	bool operator<(const Item &right)
	{
		return (name < right.name) ? true : false;
	}
	bool operator==(const Item *right)
	{
		return (name == right->name) ? true : false;
	}
	bool operator>(const Item *right)
	{
		return (name > right->name) ? true : false;
	}
	bool operator<(const Item *right)
	{
		return (name < right->name) ? true : false;
	}

	friend ostream &operator<< (ostream &strm, const Item &obj)
	{
		strm << obj.name << endl;
		return strm;
	}
private:
	int cost;
	string name;
	string description;
};


//The following items have various effects
class Potion : public Item
{
public:
	Potion() : Item("Potion", 100, "Heals 20 HP") {}
	void performEffect(Person *player, Person *enemy)
	{
		player->addHP(20);
	}
};

class HiPotion : public Item
{
public:
	HiPotion() : Item("Hi-Potion", 400, "Heals 50 HP") {}
	void performEffect(Person *player, Person *enemy)
	{
		player->addHP(50);
	}
};

class FullPotion : public Item
{
public:
	FullPotion() : Item("Full Potion", 900, "Heals full HP") {}
	void performEffect(Person *player, Person *enemy)
	{
		player->addHP(9999);
	}
};

class Ether : public Item
{
public:
	Ether() : Item("Ether", 200, "Heals 10 MP") {}
	void performEffect(Person *player, Person *enemy)
	{
		player->addMP(10);
	}
};

class HiEther : public Item
{
public:
	HiEther() : Item("Hi-Ether", 500, "Heals 30 MP") {}
	void performEffect(Person *player, Person *enemy)
	{
		player->addMP(30);
	}
};

class FullEther : public Item
{
public:
	FullEther() : Item("Full Ether", 1000, "Heals full MP") {}
	void performEffect(Person *player, Person *enemy)
	{
		player->addMP(9999);
	}
};

class Bomb : public Item
{
public:
	Bomb() : Item("Bomb", 300, "Deals 20 damage") {}
	void performEffect(Person *player, Person *enemy)
	{
		enemy->addHP(-20);
	}
};


//Creates a new base class for equipment
class Equip : public Item
{
public:
	Equip(char *name, int cost, char *description, int pAB, int pDB, int mAB, int mDB)
		: Item(name, cost, description), atkBoost(pAB), defBoost(pDB), magBoost(mAB), resBoost(mDB) {}
	void equipItem(Person *p)
	{
		p->addPhysAttack(atkBoost);
		p->addPhysDefense(defBoost);
		p->addMagAttack(magBoost);
		p->addMagDefense(resBoost);
	}
	void unequipItem(Person *p)
	{
		p->addPhysAttack(-atkBoost);
		p->addPhysDefense(-defBoost);
		p->addMagAttack(-magBoost);
		p->addMagDefense(-resBoost);
	}
	int getAtk() { return atkBoost; }
	int getDef() { return defBoost; }
	int getMag() { return magBoost; }
	int getRes() { return resBoost; }
private:
	int atkBoost;
	int defBoost;
	int magBoost;
	int resBoost;
};


//The following classes are equipments
class Helm : public Equip
{
public:
	Helm(char *n, int c, char *de, int a, int d, int m, int r) : Equip(n, c, de, a, d, m, r) {};
};

class Sword : public Equip
{
public:
	Sword(char *n, int c, char *de, int a, int d, int m, int r) : Equip(n, c, de, a, d, m, r) {};
};

class Vest : public Equip
{
public:
	Vest(char *n, int c, char *de, int a, int d, int m, int r) : Equip(n, c, de, a, d, m, r) {};
};

class OldHelm : public Helm
{
public:
	OldHelm() : Helm("Old Helm", 0, "An old helm", 0, 2, 0, 2) {};
};

class OldSword : public Sword
{
public:
	OldSword() : Sword("Old Sword", 0, "An old sword", 5, 0, 0, 0) {};
};

class OldVest : public Vest
{
public:
	OldVest() : Vest("Old Vest", 0, "An old vest", 0, 4, 0, 3) {};
};

class HardHelm : public Helm
{
public:
	HardHelm() : Helm("Hard Helm", 600, "A steel helm", 0, 6, 0, 4) {};
};

class SharpSword : public Sword
{
public:
	SharpSword() : Sword("Sharp Sword", 800, "A very sharp sword", 10, 0, 0, 0) {};
};

class LeatherVest : public Vest
{
public:
	LeatherVest() : Vest("Leather Vest", 700, "A leather vest", 0, 10, 0, 5) {};
};

class LegendaryHat : public Helm
{
public:
	LegendaryHat() : Helm("Legendary Hat", 1000, "A mysterious yet powerful beanie", 0, 10, 0, 10) {};
};

class LegendaryKatana : public Sword
{
public:
	LegendaryKatana() : Sword("Legendary Katana", 1300, "A very sharp katana", 20, 0, 0, 0) {};
};

class LegendaryCoat : public Vest
{
public:
	LegendaryCoat() : Vest("Legendary Coat", 1200, "A waterproof windbreaker!", 0, 15, 0, 15) {};
};

class OldStaff : public Sword
{
public:
	OldStaff() : Sword("Old Staff", 500, "An old staff used for magic", 0, 0, 7, 0) {}
};

class LegendaryWand : public Sword
{
public:
	LegendaryWand() : Sword("Legendary Wand", 1500, "A branch from Yggdrasil", 0, 0, 25, 0) {}
};