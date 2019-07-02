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

// array containing the positions of the current blob
std::set<std::pair<int, int>> curblob;

// recursive method to record the current blob (curblob should be empty when this method is called)
bool hasMore(int key, int i, int j)
{
	// label i and j position
	curblob.insert(std::make_pair(i, j));

	bool hasmore = false;

	// check for values with key color in all four directions
	for (int a = 0; a < 4; a++)
	{
		int newi = i + deltai[a];
		int newj = j + deltaj[a];

		// if the color matches and newi,newj doesn't already exist in curblob
		if (board[newi][newj] == key && (curblob.find(std::make_pair(newi, newj)) == curblob.end()))
		{
			bool b = hasMore(key, newi, newj);
			if (b)
			{
				hasmore = true;
			}
		}
	}

	return hasmore;
}

// turn blobs with color key and size at least k into zeros, return true if blobs found
bool labelBlobs(int key)
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

	bool hasBlobs = true;

	while (hasBlobs)
	{
		// turn blobs into zeros for each of the 9 colors
		for (int i = 1; i <= 9; i++)
		{
			hasBlobs = labelBlobs(i);
		}

		// only continue if there are blobs, otherwise the while loop exits
		if (hasBlobs)
		{
			// gravity
			// for each of the 10 col, start at index [n-1]
			// find haybales until the previous one is 0 but the current one is not
			for (int i = 0; i < 10; i++)
			{
				int lasti = n - 1;
				while (board[i][lasti] == 0)
				{
					lasti--;
				}

				// lasti is the last index of a colored hay bale
				// remove all zeros in range 0 to lasti + 1
				std::remove(std::begin(board), std::begin(board) + lasti + 1, 0);
			}

		}
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