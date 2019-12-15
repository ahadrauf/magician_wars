#include <iostream>
#include <iomanip>
#include "fstream"
#include <ctime>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include "Person.h"
#include "Item.h"
#include "Skill.h"
#include "Tree.h"

using namespace std;

void play(Player &p, Enemy &e);
void sound();
int displayMenu();

struct SaveData
{
	int turns;
	char name[30];
	int level;
};

bool operator> (const SaveData &left, const SaveData &right)
{
	return left.turns < right.turns; //opposite for high-low in inOrder function
}

bool operator< (const SaveData &left, const SaveData &right)
{
	return left.turns > right.turns;
}

ostream &operator<< (ostream &strm, const SaveData &obj)
{
	strm << setw(30) << left << obj.name << setw(8) << left << obj.turns << setw(8) << left << obj.level << endl << endl;
	return strm;
}

int main()
{
	
	srand((unsigned int)(time(0))); //randomizes time
	SaveData currentGame;
	
	cout << "Enter a player name: "; //initial screen output
	cin.getline(currentGame.name, 30); //sets name
	sound();
	cout << "On a dark and stormy night, the great magician " << currentGame.name << " embarks on a risky \njourney...." << endl;
	Sleep(3000); //delays for 3 seconds
	PlaySound(TEXT("welcome-to-hell.wav"), NULL, SND_SYNC); //plays music
	cout << "\nSuddenly, " << currentGame.name << " was attacked by a swarm of monsters!" << endl;
	cout << "The swarm seemed endless.\n" << currentGame.name << " realized he would have to fight his way out..." << endl << endl;
	system("pause");
	system("cls");

	Player p(currentGame.name); //creates player

	Enemy e; //creates first enemy

	play(p, e); //main game function
	currentGame.level = p.getLevel();
	currentGame.turns = e.getLevel();

	cout << currentGame.name << " fell, defeated by the swarm of enemies." << endl; //death output
	cout << currentGame.name << " was unable to complete his mission, and lay there on the ground " << endl;
	cout << "under the pouring rain contemplating his failure until darkness took him.";
	system("pause");
	system("cls");
	ofstream tempFile("scores.txt", ios::app); //make sure file exists
	tempFile.write(reinterpret_cast<char *>(&currentGame), sizeof(SaveData)); //insert last game
	tempFile.close();
	fstream scores("scores.txt", ios::in | ios::out | ios::binary);
	int count = 0;
	Tree<SaveData> pastScores;
	while (!scores.eof()) //store all files in a binary tree
	{
		SaveData temp;
		scores.seekg(sizeof(SaveData) * count, ios::beg);
		scores.read(reinterpret_cast<char *>(&temp), sizeof(SaveData));
		if (!scores.eof())
			pastScores.insert(temp);
		count++;
	}

	cout << setw(30) << left << "Name" << setw(8) << left << "Rounds" << setw(8) << left << "Level" << endl << endl;
	pastScores.inOrder(); //print scores highest->lowest
	scores.close();

	return 0;

}

void play(Player &p, Enemy &e)
{
	cout << p << endl << e << endl << endl;
	int choice = displayMenu(); //get menu choice
	system("cls");
	switch (choice)
	{
	case 1:
		p.attack(e, true);
		break;
	case 2:
		if (!p.addItemMain())
		{
			system("cls");
			play(p, e);
		}
		break;
	case 3:
		if (!p.useItemMain(e))
		{
			system("cls");
			play(p, e);
		}
		break;
	case 4:
		if (!p.useSkillMain(e))
		{
			system("cls");
			play(p, e);
		}
		break;
	case 5:
		p.displayEquips();
		play(p, e);
		break;
	case 6:
		break;
	}
	cout << p << endl << e << endl << endl; //output data to screen
	if (e.getHP() <= 0) //if you defeat an enemy
	{
		cout << "You defeated an enemy! Good job!\n" << endl;
		p.receiveMoney(e);
		p.receiveEXP(e);
		cout << "\nGenerating new enemy...\n\n";
		e.createNewEnemy();
	}
	else
	{
		cout << "Enemy's turn to attack next...\n\n";
		e.attack(p);
	}
	system("pause");
	system("cls");
	if (p.getHP() > 0) //only continues if player lives
		play(p, e);
}


int displayMenu()
{
	cout << "1 - Attack" << endl;
	cout << "2 - Get Item" << endl;
	cout << "3 - Use Item" << endl;
	cout << "4 - Use Skill" << endl;
	cout << "5 - View Equips" << endl;
	cout << "6 - Do nothing" << endl << endl;
	int choice;
	do
	{
		cout << "Enter a number 1-6: ";
		cin >> choice;
	} while (choice < 1 || choice > 6);

	switch (choice) //plays sound based on choice
	{
	case 1: PlaySound(TEXT("sword.wav"), NULL, SND_SYNC);
		break;
	case 2: PlaySound(TEXT("welcome1.wav"), NULL, SND_SYNC);
		break;
	case 3: PlaySound(TEXT("menu.wav"), NULL, SND_SYNC);
	}
	return choice;
}

void sound() //continuous rain noise
{
	LPCWSTR a = L"open rainynight.mp3 type mpegvideo";

	int error = 99;

	error = mciSendString(a, NULL, 0, 0);

	int error2;

	LPCWSTR b = L"play rainynight.mp3";

	error2 = mciSendString(b, NULL, 0, 0);
}