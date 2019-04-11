/*
ID: alina.l1
LANG: C++
PROB: ride
*/


#include <iostream>
#include <fstream>
#include <string>

#define MAX_NAME_LENGTH 10

int calculateValue(char * ptr)
{
	int value = 1;

	for (int i = 0; (ptr[i] != '\0') && (isalpha(ptr[i])); i++)
	{
		value *= ptr[i] - 'A' + 1;
	}

	return value % 47;
}

int main()
{
	// Open Streams
	std::ifstream fin("ride.in");

	std::ofstream fout("ride.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	char comet[MAX_NAME_LENGTH];
	char group[MAX_NAME_LENGTH];

	fin.getline(comet, MAX_NAME_LENGTH);
	fin.getline(group, MAX_NAME_LENGTH);


	int cometValue = calculateValue(comet);
	int groupValue = calculateValue(group);

	std::cout << cometValue;
	std::cout << groupValue;

	if (cometValue == groupValue)
	{
		fout << "GO\n";
	}
	else
	{
		fout << "STAY\n";
	}
	return 0;
}

