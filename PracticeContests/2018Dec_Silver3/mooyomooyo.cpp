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
#include <list>

int deltai[] = {0, 1, 0, -1};
int deltaj[] = {1, 0, -1, 0};

// number of rows, <= 100
int n;
// minimum number of haybales in a blob
int k;
// contains numbers 0-9 representing the board
int board[20][200];
// bool array to keep track of checked positions (default is false)
bool checked[20][200] = {false};
// current blob
std::list<std::pair<int, int>> curblob;

// recursive method to record the current blob (curblob should be empty when this method is called)
void floodfill(int target, int i, int j)
{
	// basic checks
	if (i < 0 || i >= 10 || j < 0 || j >= n)
	{
		return;
	}
	if (board[i][j] != target)
	{
		return;
	}

	// if already been checked
	if (checked[i][j])
	{
		return;
	}

	// update checked array
	checked[i][j] = true;
	// update curblob
	curblob.insert(curblob.end(), std::make_pair(i, j));

	// check all four directions 
	for (int a = 0; a < 4; a++)
	{
		floodfill(target, i + deltai[a], j + deltaj[a]);
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
	for (int j = n - 1; j >= 0; j--)
	{
		for (int i = 0; i < 10; i++)
		{
			// read board "backwards", so that the first row read is the last row in the array
			char c;
			fin >> c;
			board[i][j] = c - '0';
		}
	}


	bool hasmore = true;
	while (hasmore)
	{
		// reset checked array values to false
		std::fill(&checked[0][0], &checked[0][0] + sizeof(checked), false);

		// continue floodfilling when value is found
		bool foundvalue = true;
		int count = 0;
		while (foundvalue)
		{
			foundvalue = false;

			// find a nonzero value and unchecked
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < n; j++)
				{
					// value has to be nonzero and unchecked
					if (board[i][j] != 0 && !checked[i][j])
					{
						// since a value was found, set true
						foundvalue = true;

						// floodfill! found a blob with size at least k?
						floodfill(board[i][j], i, j);

						// if it is a valid blob
						if (curblob.size() >= k)
						{
							// update count
							count++;

							// turn to 0s
							for (std::pair<int, int> pos : curblob)
							{
								board[pos.first][pos.second] = 0;
							}
						}

						// clear curblob
						curblob.clear();
					}
				}
			}
		}

		// if no valid blob was found, the game ends
		if (count == 0)
		{
			hasmore = false;
			break;
		}

		// now that all the valid blobs have been turned to 0s, use gravity
		// for each column
		for (int i = 0; i < 10; i++)
		{
			// keeps track of the current j to begin overwriting
			int bottom = 0;
			// keeps track of the next nonzero to move down
			int top = 0;

			while (top < n && bottom < n)
			{
				// find the next nonzero
				while (top < n && board[i][top] == 0)
				{
					top++;
				}

				// find the next zero
				while (bottom < n && board[i][bottom] != 0)
				{
					bottom++;
				}

				// if indexes out of bounds
				if (top >= n || bottom >= n)
				{
					// exit
					break;
				}

				// only move down if bottom < top
				if (bottom < top)
				{
					// move down
					board[i][bottom] = board[i][top];
					board[i][top] = 0;
				}

				bottom++;
				top++;
			}
		}
	}

	// write to file
	// for each row (starting with the highest one)
	for (int j = n - 1; j >= 0; j--)
	{
		// for each column
		for (int i = 0; i < 10; i++)
		{
			// print out board "backwards"
			fout << board[i][j];
		}
		fout << "\n";
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}