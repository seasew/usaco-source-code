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

void printArr(int arr[])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << (char) arr[i * 3 + j];
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}

int main()
{
	int after[9] = { '@', '-', '@',
		'@', '-', '-', '-', '-', '@' };
	int arr[9] = { '@', '-', '@', '-', '-', '-', '@', '@', '-' };

	printArr(arr);

	int* newA = rot90(3, arr);
	printArr(newA);

	bool b = isEqual(3, after, newA);

	std::cout << b;

	return 0;
}

