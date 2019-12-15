#pragma once
#include "Person.h"
#include "Enemy.h"
#include "List.h"
#include "Item.h"
#include "Skill.h"
#include <iomanip>

class Player : public Person
{
public:
	Player(string n, int l = 1, int h = 50, int m = 30, int aP = 12, int dP = 8, int mA = 12, int mD = 7, int e = 0, int mo = 500)
		: Person(n, l, h, m, aP, dP, mA, mD), money(mo), exp(e) //accepts default arguments
	{
		addSkill(Fireball());
		equipHelm(OldHelm());
		equipWeapon(OldSword());
		equipArmor(OldVest());
	}
	void addSkill(Skill s)
	{
		skills.insertAtBack(new Skill(s));
	}
	void addItem(Item i)
	{
		items.insert(new Item(i));
	}
	bool useSkill(Skill &s, Enemy &e)
	{
		return s.useSkill(this, &e);
	}
	bool useItem(Item *i, Enemy &e)
	{
		if (items.deleteElement(i)) //checks if item is in inventory
		{
			i->performEffect(this, &e); //if it is, perform effect
			return true;
		}
		else //if it isn't, return false
		{
			cout << "The item " << i->getName() << " was not in your inventory" << endl;
			return false;
		}
	}
	int getEXP() { return exp; }
	int getMoney() { return money; }
	void receiveEXP(Enemy &e) //receives exp and levels up if exp >= 100
	{
		int add = 35 * e.getLevel();
		if (add > 80)
			add = 80 + e.getLevel() / 3;
		cout << "You got " << add << " EXP!" << endl;
		exp += add;
		if (exp >= 100)
		{
			Person temp = *this;
			increaseLevel();
			exp -= 100;
			if (getLevel() == 5)
				addSkill(FireStorm());
			if (getLevel() == 10)
				addSkill(LavaPlume());
			cout << endl;
			cout << "You leveled up!" << endl;
			cout << "HP + " << getHP() - temp.getHP() << endl;
			cout << "MP + " << getMP() - temp.getMP() << endl;
			cout << "ATK + " << getPhysicalAttack() - temp.getPhysicalAttack() << endl;
			cout << "DEF + " << getPhysicalDefense() - temp.getPhysicalDefense() << endl;
			cout << "MAG + " << getMagicalAttack() - temp.getMagicalAttack() << endl;
			cout << "RES + " << getMagicalDefense() - temp.getMagicalDefense() << endl << endl;
		}
	}
	void receiveMoney(Enemy &e) //receives money
	{
		int add = e.getLevel() * 50;
		cout << "You got " << add << " coins!" << endl;
		money += add;
	}

	//normal item/skill displays
	void displayItemList()
	{
		items.print();
	}
	void displaySkillList()
	{
		skills.print();
	}

	bool isPlayer(Person *obj)
	{
		Player *p = dynamic_cast<Player *>(obj);
		return p ? true : false;
	}

	//uses polymorphism to unequip/equip helms/weapons/armor
	void equipHelm(Equip &e)
	{
		if (helm)
			unequipHelm(*helm);
		e.equipItem(this);
		helm = new Equip(e);
	}

	void equipWeapon(Equip &e)
	{
		if (weapon)
			unequipWeapon(*weapon);
		e.equipItem(this);
		weapon = new Equip(e);
	}

	void equipArmor(Equip &e)
	{
		if (armor)
			unequipArmor(*armor);
		e.equipItem(this);
		armor = new Equip(e);
	}

	void unequipHelm(Equip &e)
	{
		e.unequipItem(this);
	}

	void unequipWeapon(Equip &e)
	{
		e.unequipItem(this);
	}

	void unequipArmor(Equip &e)
	{
		e.unequipItem(this);
	}

	//uses polymorphism to add items based on item type (normal / equip)
	bool addItemMain()
	{
		int choice = displayMenu();
		if (choice == 16)
			return false;
		system("cls");
		Item *i = getItem(choice);
		Equip *e = dynamic_cast<Equip *>(i);
		if (e)
		{
			Helm *h = dynamic_cast<Helm *>(e);
			Sword *s = dynamic_cast<Sword *>(e);
			Vest *v = dynamic_cast<Vest *>(e);
			if (h)
				equipHelm(*h);
			else if (s)
				equipWeapon(*s);
			else if (v)
				equipArmor(*v);
		}
		else
			addItem(*i);
		cout << "You got a " << i->getName() << "!\n\n";
		system("pause");
		system("cls");
		return true;
	}

	//uses item from items list
	bool useItemMain(Enemy &e)
	{
		displayItemList();
		if (items.getSize() == 0)
		{
			system("pause");
			return false;
		}
		int choice;
		cout << "Enter the number of the item in the list (1 - " << items.getSize() << ") or enter -1 to quit: ";
		cin >> choice;
		if (choice == -1)
			return false;
		while (choice < 0 || choice > items.getSize())
		{
			cout << "Enter a number from 1 to " << items.getSize() << ": ";
			cin >> choice;
		}

		//uses the item
		string name = items[choice]->getName();
		if (name == "Potion")
			useItem(new Potion(), e);
		else if (name == "Hi-Potion")
			useItem(new HiPotion(), e);
		else if (name == "Full Potion")
			useItem(new FullPotion(), e);
		else if (name == "Ether")
			useItem(new Ether(), e);
		else if (name == "Hi-Ether")
			useItem(new HiEther(), e);
		else if (name == "Full Ether")
			useItem(new FullEther(), e);
		else if (name == "Bomb")
			useItem(new Bomb(), e);

		cout << "You used a " << name << "!" << endl;
		system("pause");
		system("cls");
		return true;
	}

	//displays skills --> user chooses one to use
	bool useSkillMain(Enemy &e)
	{
		cout << "MP Remaining: " << getMP() << endl << endl;
		for (int i = 1; i <= skills.getSize(); i++)
		{
			cout << i << " - " << skills[i]->getName() << "\t\t" << skills[i]->getDescription() << "\t\t" << skills[i]->getMPCost() << endl;
		}
		cout << (skills.getSize() + 1) << " - Quit" << endl;
		int choice;
		do
		{
			cout << "Enter a skill to use (1 - " << skills.getSize() << ") or press " << (skills.getSize() + 1) << " to quit: ";
			cin >> choice;
		} while (choice < 0 || choice > skills.getSize() + 1);
		system("cls");
		if (choice == skills.getSize() + 1)
			return false;
		else
			return useSkill(*getSkill(choice), e);
	}

	//standard menu for items
	int displayMenu()
	{

		bool valid = true;
		int choice;
		Item *i;
		do
		{
			cout << "Money: " << money << endl << endl;
			for (int c = 1; c <= 15; c++)
			{
				cout << setw(2) << left << c << " - " << setw(20) << left << getItem(c)->getName() << 
					setw(40) << left << getItem(c)->getDescription() << setw(5) << left << getItem(c)->getCost() << endl;
			}
			cout << "16 - Exit" << endl << endl;
			cout << "Enter the number of the item (1-16): ";
			cin >> choice;
			i = getItem(choice);
			if (i != NULL)
			{
				if (money < i->getCost())
				{
					valid = false;
					system("cls");
					cout << "You don't have enough money for this item." << endl << endl;
				}
				else
				{
					valid = true;
					system("cls");
				}
			}
		} while ((choice < 0 || choice > 16) || !valid);
		if (i != NULL)
			money -= i->getCost(); //subtracts money
		return choice;
	}

	//facilitates getting items (composition works better than inheritance, and menu systems use numbers)
	Item *getItem(const int &n)
	{
		switch (n)
		{
		case 1: return new Potion();;
		case 2: return new HiPotion();
		case 3: return new FullPotion();
		case 4: return new Ether();
		case 5: return new HiEther();
		case 6: return new FullEther();
		case 7: return new Bomb();
		case 8: return new HardHelm();
		case 9: return new SharpSword();
		case 10: return new OldStaff();
		case 11: return new LeatherVest();
		case 12: return new LegendaryHat();
		case 13: return new LegendaryKatana();
		case 14: return new LegendaryCoat();
		case 15: return new LegendaryWand();
		default: return NULL;
		}
	}

	Skill *getSkill(const int &n)
	{
		switch (n)
		{
		case 1: return new Fireball();
		case 2: return new FireStorm();
		case 3: return new LavaPlume();
		default: return NULL;
		}
	}

	//for main function
	void displayEquips()
	{
		cout << setw(20) << left << "Name" << setw(30) << left << "Description" << setw(4) << left << "ATK" << setw(4) << "DEF" <<
			setw(4) << "MAG" << setw(4) << "RES" << endl;
		cout << setw(20) << left << ("Helm: " + helm->getName()) << setw(30) << left << helm->getDescription() <<
			setw(4) << left << helm->getAtk() << setw(4) << helm->getDef() << setw(4) << helm->getMag() << setw(4) << helm->getRes() << endl;
		cout << setw(20) << left << ("Sword: " + weapon->getName()) << setw(30) << left << weapon->getDescription() <<
			setw(4) << left << weapon->getAtk() << setw(4) << weapon->getDef() << setw(4) << weapon->getMag() << setw(4) << weapon->getRes() << endl;
		cout << setw(20) << left << ("Armor: " + armor->getName()) << setw(30) << left << armor->getDescription() <<
			setw(4) << left << armor->getAtk() << setw(4) << armor->getDef() << setw(4) << armor->getMag() << setw(4) << armor->getRes() << endl;
		system("pause");
		system("cls");
	}

private:
	List<Item *> items;
	List<Skill *> skills;
	Equip *helm = NULL;
	Equip *weapon = NULL;
	Equip *armor = NULL;
	int money;
	int exp;
};