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
#include <math.h>

int p[100];
int n;
int m;
int p1[150];
int p2[150];

bool checkNum()
{
	for (int i = 0; i < m; i++)
	{
		int a1 = p1[i];
		int a2 = p2[i];

		if (p[a1 - 1] == p[a2 - 1])
		{
			return false;
		}
	}

	return true;
}

int generate(int count)
{
	if (count == n)
	{
		if (checkNum())
		{
			// convert the int array
			int out = 0;
			for (int i = 0; i < n; i++)
			{
				out += p[i] * (pow(10, n - i - 1));
			}
			return out;
		}
		else
		{
			return -1;
		}
	}

	// generate the next digit
	for (int i = 1; i <= 4; i++)
	{
		p[count] = i;
		int output = generate(count + 1);
		if (output > 0)
		{
			return output;
		}
	}

	return -1;
}

int main()
{
	// Open Streams
	std::ifstream fin("revegetate.in");

	std::ofstream fout("revegetate.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File 
	fin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		fin >> p1[i] >> p2[i];
	}

	fout << generate(0) << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}