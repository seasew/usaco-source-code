/*
ID: alina.l1
LANG: C++
PROB: mooyomooyo
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>
#include <queue>
#include <utility>
#include <iterator>
#include <set>

int deltai[] = {0, 1, 0, -1};
int deltaj[] = {1, 0, -1, 0};

// number of rows, <= 100
int n;
// minimum number of haybales in a blob
int k;
// contains numbers 0-9 representing the board
int board[10][101];
// bool array to keep track of checked positions (default is false)
bool checked[10][101];

// recursive method to record the current blob (curblob should be empty when this method is called)
void floodfill(int target, int i, int j)
{
	

}

int main()
{
	// Open Streams
	std::ifstream fin("mooyomooyo.in");

	std::ofstream fout("mooyomooyo.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// read file
	fin >> n >> k;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// read board "backwards", so that the first row read is the last row in the array
			fin >> board[i][n - j];
		}
	}


	bool hasmore = true;
	while (hasmore)
	{
		// continue floodfilling when value is found
		bool foundval = true;
		while (foundval)
		{
			// find a nonzero value and unchecked
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < n; j++)
				{
					// valid value check
					if (board[i][j] != 0 && !checked[i][j])
					{
						
					}
				}
			}
		}

		// gravity
	}

	// write to file
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// print out board "backwards"
			fout << board[i][n - j];
		}
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}