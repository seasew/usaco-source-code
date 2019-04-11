/*
ID: alina.l1
LANG: C++
PROB: shell
*/

#include <iostream>
#include <fstream>
#include <string>

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int swap(int a, int b, int pos)
{
	// if shellA is being swapped
	if (a == pos)
	{
		// swap
		return b;
	}
	// if shellB is being swapped
	else if (b == pos)
	{
		// swap
		return a;
	}
	else
	{
		// if pos is not being changed
		return pos;
	}
}

int main()
{
	// Open Streams
	std::ifstream fin("shell.in");

	std::ofstream fout("shell.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	const int MAX_LENGTH = 5;
	char str[MAX_LENGTH];
	fin.getline(&(str[0]), MAX_LENGTH);

	int n = charArrToInt(str);

	// current positions if the pebble was under shells 1, 2 or 3
	int pos1 = 1;
	int pos2 = 2;
	int pos3 = 3;

	// scores for 1, 2, or 3
	int s1 = 0;
	int s2 = 0;
	int s3 = 0; 

	// for each swap
	for (int i = 0; i < n; i++)
	{
		// read a
		fin.getline(&(str[0]), MAX_LENGTH, ' ');
		int a = charArrToInt(str);

		// read b
		fin.getline(&(str[0]), MAX_LENGTH, ' ');
		int b = charArrToInt(str);

		// read g
		fin.getline(&(str[0]), MAX_LENGTH);
		int g = charArrToInt(str);

		// shell 1:
		// set new position 
		pos1 = swap(a, b, pos1);
		// if guess is correct
		if (pos1 == g)
		{
			s1++;
		}

		// shell 2:
		// set new position 
		pos2 = swap(a, b, pos2);
		// if guess is correct
		if (pos2 == g)
		{
			s2++;
		}

		// shell 3:
		// set new position 
		pos3 = swap(a, b, pos3);
		// if guess is correct
		if (pos3 == g)
		{
			s3++;
		}
	}

	std::cout << pos1;
	std::cout << pos2;
	std::cout << pos3;

	// get max score
	if (s1 >= s2 && s1 >= s3)
	{
		fout << s1;
	}
	else if (s2 >= s1 && s2 >= s3)
	{
		fout << s2;
	}
	else
	{
		fout << s3;
	}

	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}