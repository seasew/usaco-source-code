/*
ID: alina.l1
LANG: C++
PROB: family
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

const int MAX_N = 100;
int n;
std::string mothers[MAX_N];
std::string children[MAX_N];


// finds the mother of the child given the two arrays
// if not found, returns ""
std::string findMother(std::string child)
{
	for (int i = 0; i < n; i++)
	{
		if (child == children[i])
		{
			return mothers[i];
		}
	}
}

int ancestor(std::string c1, std::string c2)
{
	int a = 1;
	std::string mother = findMother(c2);
	while (mother != c1)
	{
		if (mother == "")
		{
			return -1;
		}
		mother = findMother(mother);
		a++;
	}

	return a;
}

int main()
{
	// Open Streams
	std::ifstream fin("family.in");

	std::ofstream fout("family.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	std::string c1;
	std::string c2;

	fin >> n >> c1 >> c2;

	// read the next n lines
	for (int i = 0; i < n; i++)
	{
		fin >> mothers[i] >> children[i];
	}

	// Find a and b
	int a = ancestor(c1, c2);
	int b = ancestor(c2, c1);

	if (a == 1 && b == 1)
	{
		fout << "SIBLINGS";
	}

	if ((a < 0 && b > 0) || (b < 0 && a > 0))
	{
		std::string yC;
		int count;
		if (a > 0)
		{
			count = a;
			yC = c2;
			fout << c1;
		}
		else
		{
			count = b;
			yC = c1;
			fout << c2;
		}

		fout << " is the ";

		std::string output = "mother";
		if (count >= 2)
		{
			output = "grand-" + output;
		}
		for (int i = 3; i <= count; i++)
		{
			output = "great-" + output;
		}

		fout << "of " << yC;
	}



	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}