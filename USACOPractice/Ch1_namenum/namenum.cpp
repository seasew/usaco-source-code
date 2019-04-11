/*
ID: alina.l1
LANG: C++
PROB: namenum
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define MAX_NAME_LEN 100
#define MAX_LEN 20

int lettertonum(char letter)
{
	if (letter == 'A' || letter == 'B' || letter == 'C')
	{
		return 2;
	}
	else if (letter == 'D' || letter == 'E' || letter == 'F')
	{
		return 3;
	}
	else if (letter == 'G' || letter == 'H' || letter == 'I')
	{
		return 4;
	}
	else if (letter == 'J' || letter == 'K' || letter == 'L')
	{
		return 5;
	}
	else if (letter == 'M' || letter == 'N' || letter == 'O')
	{
		return 6;
	}
	else if (letter == 'P' || letter == 'R' || letter == 'S')
	{
		return 7;
	}
	else if (letter == 'T' || letter == 'U' || letter == 'V')
	{
		return 8;
	}
	else if (letter == 'W' || letter == 'X' || letter == 'Y')
	{
		return 9;
	}
	else
	{
		std::cout << "Invalid letter: ";
		std::cout << letter;
		std::cout << "\n";
		return -1;
	}
	
}

int main()
{
	// Open Streams
	std::ifstream fin("namenum.in");

	std::ofstream fout("namenum.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File

	int num[MAX_LEN];
	int nLen = 0;

	while (isdigit(fin.peek()))
	{
		std::string str(1, fin.get());
		num[nLen] = std::stoi(str);
		nLen++;
	}

	// Read dictionary file
	std::ifstream din("dict.txt");

	std::vector<std::string> dict;

	while (isalpha(din.peek()))
	{
		char c[MAX_NAME_LEN];
		din.getline(c, MAX_NAME_LEN);

		std::string next(c);

		dict.push_back(next);
	}

	din.close();

	// Iterate through dictionary
	bool hasName = false;
	// for each name, check if its number conversion matches the number
	for (int i = 0; i < dict.size(); i++)
	{
		std::string name = dict.at(i);

		int nameI = 0;
		int digit = num[nameI];
		int letterton = lettertonum(name[nameI]);

		if (name.length() == nLen)
		{
			while (nameI < name.length() && nameI < nLen && digit == letterton && letterton > 0)
			{
				nameI++;
				digit = num[nameI];
				letterton = lettertonum(name[nameI]);
			}

			// if it gets all the way to the end
			if (nameI == name.length())
			{
				// print the name
				fout << name;
				fout << "\n";

				hasName = true;
			}
		}
	}


	if (!hasName)
	{
		fout << "NONE";
		fout << "\n";
	}
	
	// Close Streams
	fin.close();
	fout.close();

	return 0;
}