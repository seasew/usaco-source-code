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
#include <vector>
#include <functional>
#include <queue>
#include <utility>
#include <list>

int deltai[] = {1, 0, -1, 0};
int deltaj[] = {0, 1, 0, -1};

int n;

// N by N grid (max value is 250)
int grid[250][250];

// true if already visited by search
bool visited[250][250];


int max1;
int max2;

int cursize;

// depth-first-search
void dfs(int i, int j, int target)
{
	// basic checks
	// i and j in bounds?
	if (!(i >= 0 && i < n) || !(j >= 0 && j < n))
	{
		return;
	}
	// i and j match target value?
	if (grid[i][j] != target)
	{
		return;
	}
	// i and j already visited?
	if (visited[i][j])
	{
		return;
	}

	// update visited value
	visited[i][j] = true;
	// update cursize
	cursize++;

	// check all four directions
	for (int a = 0; a < 4; a++)
	{
		// call recursive dfs
		dfs(i + deltai[a], j + deltaj[a], target);
	}

}

// recursive search to find the size of the region at (i, j) with values of t1 and t2
void dfs2(int i, int j, int t1, int t2)
{
	// basic checks
	// i and j in bounds?
	if (!(i >= 0 && i < n) || !(j >= 0 && j < n))
	{
		return;
	}
	// i and j match target value?
	if (grid[i][j] != t1 && grid[i][j] != t2)
	{
		return;
	}
	// i and j already visited?
	if (visited[i][j])
	{
		return;
	}

	visited[i][j] = true;
	cursize++;

	// check four directions
	for (int a = 0; a < 4; a++)
	{
		dfs(i + deltai[a], j + deltaj[a], t1, t2);
	}
}

int main()
{
	// Open Streams
	std::ifstream fin("multimoo.in");

	std::ofstream fout("multimoo.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> grid[i][j];
		}
	}

	// 1-team code
	// iterate through grid
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// if (i, j) has not been visited yet
			if (!visited[i][j])
			{
				// call dfs
				dfs(i, j, grid[i][j]);

				// cmp cursize to max1
				max1 = std::max(max1, cursize);
				// reset cursize
				cursize = 0;

			}
		}
	}


	// clear the bool array
	std::fill(std::begin(visited), std::end(visited), false);

	// 2-team code
	// iterate through grid 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{

			// for each position, call dfs2 for (i,j) and each of the other 4 positions
			for (int a = 0; a < 4; a++)
			{
				// (i, j) is current position
				// grid[newi][newj] is target2
				int newi = i + deltai[a];
				int newj = j + deltaj[a];
				
				// basic checks
				// all indexes must be in bounds
				if (newi >= 0 && newi < n && newj >= 0 && newj < n)
				{
					// at least one position must be unvisited
					if (!visited[i][j] || !visited[newi][newj])
					{
						// the two target values cannot be the same
						if (grid[i][j] != grid[newi][newj])
						{
							dfs2(i, j, grid[i][j], grid[newi][newj]);

							// cmp cursize to max2
							max2 = std::max(max2, cursize);

							// reset cursize
							cursize = 0;
						}
					}
				}
			}
		}
	}

	// write to file
	fout << max1 << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}