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
bool checked[10][101] = { false };

// array containing the positions of the current blob
std::set<std::pair<int, int>> curblob;

// recursive method to record the current blob (curblob should be empty when this method is called)
void floodfill(int target, int i, int j)
{
	// check 1: i and j are in bounds
	if (!(i >= 0 && i < n && j >= 0 && j < n))
	{
		return;
	}

	// check 2: board[i][j] has color target
	if (board[i][j] != target)
	{
		return;
	}

	// otherwise, continue

	// add i,j to curblob
	curblob.insert(std::make_pair(i, j));
	// set its checked value to true
	checked[i][j] = true;

	// call floodfill for all four directions
	for (int a = 0; a < 4; a++)
	{
		floodfill(target, i + deltai[a], j + deltaj[a]);
	}
}

// turn blobs with color key and size at least k into zeros, return true if blobs found
bool labelBlobs(int key)
{         

	// test
	for (int i = 0; i < 10; i++)
	{
		auto it = std::find(std::begin(board[i]), std::end(board[i]), key);
	}
	// test

	curblob.clear();
	checked[10][101] = { false };

	// keep track of the last

	// while there are still curblobs
	while (curblob.size() > 0)
	{
		// floodfill the first key color found in board

		int nexti, nextj = -1;

		// for each column
		for (int i = 0; i < 10; i++)
		{
			// find the first occurence of key color with the checked value false
			bool continue_search = true;
			while (continue_search)
			{
				auto it = std::find(std::begin(board[i]), std::end(board[i]), key);
				int j = std::distance(std::begin(board[0]), it);

				// stop the search when no more keys can be found
				if (it == std::end(board[i]))
				{
					continue_search = false;
				}
				// stop the search when a key is found and unchecked
				else if (it != std::end(board[i]) && !checked[i][j])
				{
					continue_search = false;
					nexti = i;
					nextj = j;
				}
			}


		}
	}
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