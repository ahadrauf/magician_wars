#pragma once
#include <iostream>
#include <string>
using namespace std;


class Person
{
public:
	Person() : level(0), HP(50), MP(30), atk(1), def(1), mag(1), res(1),
		maxHP(50), maxMP(30) {} //default constructor

	Person(string n) : name(n), level(0), HP(50), MP(30), atk(1), def(1), mag(1), res(1),
		maxHP(50), maxMP(30) {} //constructor used by main

	Person(string n, int l, int h, int m, int aP, int dP, int mA, int mD)
		: name(n), level(l), HP(h), MP(m), atk(aP), def(dP), mag(mA), res(mD),
		maxHP(h), maxMP(m) {} //normal constructor

	string getName() const { return name; }
	int getLevel() const{ return level; }
	int getHP() const{ return HP; }
	int getMP() const{ return MP; }
	int getPhysicalAttack() const{ return atk; }
	int getPhysicalDefense() const{ return def; }
	int getMagicalAttack() const{ return mag; }
	int getMagicalDefense() const{ return res; }
	int calculateDamage(const Person &, const Person &, bool);
	int calculateDamageHelper(const int &, const int &, const int &);
	void attack(Person & defender, bool, double = 1);

	Person operator++()
	{
		increaseLevel();
	}
	virtual Person operator=(const Person &); //for overriding
	friend ostream &operator<< (ostream &strm, Person &obj);

	void addHP(const int &);
	void addMP(const int &);
	void addPhysAttack(const int &);
	void addPhysDefense(const int &);
	void addMagAttack(const int &);
	void addMagDefense(const int &);

	void restoreToFull();
	void increaseLevel(int HPboost = 20, int MPboost = 5, int aBoost = 3, int dBoost = 3, int mBoost = 3, int rBoost = 3); //default arguments
private:
	int level;
	int maxHP;
	int maxMP;
	int HP;
	int MP;
	int atk;
	int def;
	int mag;
	int res;
	string name;
};

void Person::increaseLevel(int HPboost, int MPboost, int aBoost, int dBoost, int mBoost, int rBoost) //randomly increases stats
{
	int tempHPIncrease = rand() % HPboost;
	int tempMPIncrease = rand() % MPboost;
	level++;
	maxHP += tempHPIncrease;
	maxMP += tempMPIncrease;
	HP += tempHPIncrease;
	MP += tempMPIncrease;
	atk += rand() % aBoost;
	def += rand() % dBoost;
	mag += rand() % mBoost;
	res += rand() % rBoost;

}

int Person::calculateDamage(const Person &attacker, const Person &defender, bool isPhysicalAttack) //calculates damage
{
	if (isPhysicalAttack)
	{
		return calculateDamageHelper(attacker.level, attacker.atk, defender.def);
	}
	else
	{
		return calculateDamageHelper(attacker.level, attacker.mag, defender.mag);
	}
}

int Person::calculateDamageHelper(const int &level, const int &attack, const int &defense)
{
	if (defense >= attack)
		return level;
	else
		return 1 + 3 * static_cast<int>(sqrt(level)) * (attack - defense);
}

void Person::attack(Person &defender, bool isPhysicalAttack, double attackMultiplier)
{
	defender.HP -= static_cast<int>(attackMultiplier * calculateDamage(*this, defender, isPhysicalAttack));
	if (defender.HP < 0)
		defender.HP = 0;
}

ostream &operator<< (ostream &strm, Person &obj)
{
	strm << "Name: " << obj.name << endl;
	strm << "Level: " << obj.level << endl;
	strm << "HP: " << obj.HP << "/" << obj.maxHP << "\t\tATK: " << obj.atk << "\t\tDEF: " << obj.def << endl;
	strm << "MP: " << obj.MP << "/" << obj.maxMP << "\t\tMAG: " << obj.mag << "\t\tRES: " << obj.res << endl;
	return strm;
}

Person Person::operator= (const Person &right)
{
	name = right.name;
	level = right.level;
	HP = right.HP;
	MP = right.MP;
	atk = right.atk;
	mag = right.mag;
	def = right.def;
	res = right.res;
	maxHP = right.maxHP;
	maxMP = right.maxMP;
	//cout << 14 << endl;
	return *this;
}

void Person::addHP(const int &value)
{
	HP += value;
	if (HP > maxHP)
		HP = maxHP;
	if (HP < 0)
		HP = 0;
}

void Person::addMP(const int &value)
{
	MP += value;
	if (MP > maxMP)
		MP = maxMP;
	if (MP < 0)
		MP = 0;
}

void Person::addPhysAttack(const int &value)
{
	atk += value;
	if (atk < 0)
		atk = 0;
}

void Person::addMagAttack(const int &value)
{
	mag += value;
	if (mag < 0)
		mag = 0;
}

void Person::addPhysDefense(const int &value)
{
	def += value;
	if (def < 0)
		def = 0;
}

void Person::addMagDefense(const int &value)
{
	res += value;
	if (res < 0)
		res = 0;
}

void Person::restoreToFull()
{
	HP = maxHP;
	MP = maxMP;
}