/*
ID: alina.l1
LANG: C++
PROB: gift1
*/

#include <iostream>
#include <fstream>
#include <string>

#define MAX_N 100
#define MAX_LENGTH 100

struct Person
{
	std::string name;
	int money = 0;
};

int locatePerson(std::string name, Person *ptr, int arrLength)
{
	for (int i = 0; i < arrLength; i++)
	{
		// if the two names match
		if ((ptr[i].name).compare(name) == 0)
		{
			return i;
		}
	}

	// person not found
	return -1;
}

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int main()
{

	// Open Streams
	std::ifstream fin("gift1.in");

	std::ofstream fout("gift1.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// number of people
	int n;
	char cStr[MAX_LENGTH];
	fin.getline(cStr, MAX_LENGTH);
	// convert char[] to int
	n = charArrToInt(cStr);

	// array of Persons
	Person persons[MAX_N];

	// read each person's name
	for (int i = 0; i < n; i++)
	{
		cStr[MAX_LENGTH];
		fin.getline(cStr, MAX_LENGTH);
		persons[i].name = cStr;
	}

	
	char c;
	// while not End of File
	while (fin  >> c)
	{
		cStr[MAX_LENGTH];
		fin.getline(cStr, MAX_LENGTH);
		std::string giver(cStr);
		giver = c + giver;

		// read next line
		int amountToGive, nReceivers;
		// convert amountToGive
		cStr[MAX_LENGTH];
		fin.getline(cStr, MAX_LENGTH, ' ');

		amountToGive = charArrToInt(cStr);
		// convert nReceivers
		cStr[MAX_LENGTH];
		fin.getline(cStr, MAX_LENGTH);
		nReceivers = charArrToInt(cStr);

		int amountPerPerson = 0;
		int remainder = 0;


		// only continue if amountToGive and nReceivers is not 0
		if (amountToGive != 0 && nReceivers != 0)
		{
			// calculate each receiver's money amount
			 amountPerPerson = amountToGive / nReceivers;
			// calculate the giver's amount they take back
			 remainder = amountToGive % nReceivers;

			// for the giver: take away the total amount and give them the Remainder
			int giverIndex = locatePerson(giver, persons, n);
			persons[giverIndex].money -= amountToGive;
			persons[giverIndex].money += remainder;

			
		}

		// for each receiver: read their name and give them money
		for (int i = 0; i < nReceivers; i++)
		{
			// read the receiver's name
			cStr[MAX_LENGTH];
			fin.getline(cStr, MAX_LENGTH);
			std::string currentR(cStr);

			// give them money
			int receiverIndex = locatePerson(currentR, persons, n);
			persons[receiverIndex].money += amountPerPerson;
		}
	}

	// OUTPUT: for each person, print out their name and money
	for (int i = 0; i < n; i++)
	{
		fout << persons[i].name << " " << persons[i].money << "\n";
	}

	return 0;
}