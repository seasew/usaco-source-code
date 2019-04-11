/*
ID: alina.l1
LANG: C++
PROB: transform
*/

#include <iostream>
#include <fstream>
#include <string>

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

int calI(int n, int i, int j)
{
	return (n * i) + j;
}

int* rot90(int n, int* orig)
{
	int* arr = new int[n * n];
	// rotates the array/square 90 deg clockwise
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[calI(n, i, j)] = orig[calI(n, (n - 1) - j, i)];
			std::cout << arr[calI(n, i, j)];
			std::cout << "\n";
		}

		std::cout << "\n";
	}

	
	return arr;
}

int* rot180(int n, int* orig)
{
	return rot90(n, rot90(n, orig));
}

int* rot270(int n, int* orig)
{
	return rot90(n, rot90(n, rot90(n, orig)));
}

int* reflect(int n, int* orig)
{
	int* arr = new int[n * n];
	// reflects the array over mid-vert line
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[calI(n, i, j)] = orig[calI(n, i, (n - 1) - j)];
		}
	}

	return arr;
}

bool isEqual(int n, int* a1, int* a2)
{
	// checks if two arrays have equal contents
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a1[calI(n, i, j)] != a2[calI(n, i, j)])
			{
				return false;
			}
		}
	}

	return true;
}

int main()
{
	const int MAX_LENGTH = 5;
	int n;
	
	// Open Streams
	std::ifstream fin("transform.in");

	std::ofstream fout("transform.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	char str[MAX_LENGTH];
	fin.getline(&(str[0]), MAX_LENGTH);
	n = charArrToInt(str);
	int len = n * n;

	int* before = new int[len];
	int* after = new int[len];

	// read first square
	for (int i = 0; i < n * n; i++)
	{
		char c = fin.get();
		while (c != '-' && c != '@')
		{
			c = fin.get();
		}

		before[i] = c;
	}

	// read second square
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char c = fin.get();
			while (c != '-' && c != '@')
			{
				c = fin.get();
			}

			after[calI(n, i, j)] = c;
		}
	}
	
	int output;

	// 1: check rot90
	if (isEqual(n, after, rot90(n, before)))
	{
		output = 1;
	}
	// 2: check rot180
	else if (isEqual(n, after, rot180(n, before)))
	{
		output = 2;
	}
	// 3: check rot270
	else if (isEqual(n, after, rot270(n, before)))
	{
		output = 3;
	}
	// 4: check reflection
	else if (isEqual(n, after, reflect(n, before)))
	{
		output = 4;
	}
	// 5: check combo(reflect + rot)
	else if (isEqual(n, after,  rot90(n, reflect(n, before))) || isEqual(n, after, rot180(n, reflect(n, before))) || isEqual(n, after, rot270(n, reflect(n, before))))
	{
		output = 5;
	}
	// 6: check no change
	else if (isEqual(n, before, after))
	{
		output = 6;
	}
	// 7: invaild
	else
	{
		output = 7;
	}

	// Write to File
	fout << output;
	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}