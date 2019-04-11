/*
ID: alina.l1
LANG: C++
PROB: starter_code
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

int a;
int b;
int c;

int min;
int max;


bool check()
{
	if (a == b - 1 && b == c - 1)
	{
		return true;
	}

	return false;
}

int moveMin()
{
	int s1 = b - a;
	int s2 = c - b;

	if (s1 == 1 && s2 == 1)
	{
		return 0;
	}
	else if (s1 == 2 || s2 == 2)
	{
		return 1;
	}
	else if (s1 > 2 || s2 > 2)
	{
		return 2;
	}
	
	return -1;
}

int main()
{
	// Open Streams
	std::ifstream fin("herding.in");

	std::ofstream fout("herding.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	int oA;
	int oB;
	int oC;
	int x1;
	int x2;
	int x3;
	fin >> x1 >> x2 >> x3;

	if (x1 < x2 && x1 < x3)
	{
		oA = x1;

		if (x2 < x3)
		{
			oB = x2;
			oC = x3;
		}
		else
		{
			oB = x3;
			oC = x2;
		}
	}
	if (x2 < x1 && x2 < x3)
	{
		oA = x2;
		if (x1 < x3)
		{
			oB = x1;
			oC = x3;
		}
		else
		{
			oB = x3;
			oC = x1;
		}
	}
	if (x3 < x1 && x3 < x2)
	{
		oA = x3;
		if (x1 < x2)
		{
			oB = x1;
			oC = x2;
		}
		else
		{
			oB = x2;
			oC = x1;
		}
	}
	a = oA;
	b = oB;
	c = oC;
	min = moveMin();


	max = 0;
	a = oA;
	b = oB;
	c = oC;

	if (!check())
	{
		int s1 = b - a;
		int s2 = c - b;
		if (s2 > s1)
		{
			if (a != b - 1)
			{
				max++;
				a = b;
				b++;
			}

			max += (c - 2) - a;
		}
		else
		{
			if (b != c - 1)
			{
				max++;
				c = b;
				b--;

			}
			max += c - (a + 2);
		}
	}

	fout << min << "\n" << max << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}