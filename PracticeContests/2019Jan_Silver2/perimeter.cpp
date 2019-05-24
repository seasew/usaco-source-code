/*
ID: alina.l1
LANG: C++
PROB: perimeter
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

int n;
int curLabel;
// 1=not part of blob & is ice cream, >1 part of blob, 0 is no ice cream 
int labels[1000][1000];

// area array
int areas[500000];

const int dx[] = {1, 0, -1, 0};
const int dy[] = { 0, -1, 0, 1 };

// depth first search
void dfs(int i, int j)
{
	// i and j must be in bounds
	if (!(i >= 0 && i < n && j >= 0 && j < n))
	{
		return;
	}

	// position must be unlabeled & be ice cream
	if (labels[i][j] != 1)
	{
		return;
	}

	// mark current
	labels[i][j] = curLabel;
	areas[curLabel]++;

	// mark recursively for each direction
	for (int a = 0; a < 4; a++)
	{
		int newI = i + dx[a];
		int newJ = j + dy[a];
		if (labels[newI][newJ] == 1)
		{
			dfs(newI, newJ);
		}
	}
}

// calculates the perimeter of the label given
int perimeter(int label)
{
	int peri = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (labels[i][j] == label)
			{
				// original four sides
				peri += 4;

				// subtract as needed
				// check all four directions
				for (int a = 0; a < 4; a++)
				{
					int newI = i + dx[a];
					int newJ = j + dy[a];

					// if in bounds
					if (newI >= 0 && newI < n && newJ >= 0 && newJ < n)
					{
						// check
						if (labels[newI][newJ] == label)
						{
							peri--;
						}
					}
				}
			}
		}
	}

	return peri;
}

int main()
{
	// Open Streams
	std::ifstream fin("C:\\Users\\alina_000\\Pictures\\From Internet\\10.in");

	std::ofstream fout("perimeter.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 100;
	}

	// Read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char ch;
			fin >> ch;

			// has ice cream = 1
			if (ch == '#')
			{
				labels[i][j] = 1;
			}
		}
	}
	// set starting label
	curLabel = 2;

	// call dfs for every point that has 0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (labels[i][j] == 1)
			{
				dfs(i, j);
				// update label for next blob
				curLabel++;
			}
		}
	}

	// find maxArea of areas
	int maxArea = 0;
	for (int area : areas)
	{
		maxArea = std::max(maxArea, area);
	}

	// find the labels that have value of maxArea
	int minPeri = 0;
	for (int i = 2; i < 500000; i++)
	{
		if (areas[i] == maxArea)
		{
			int peri = perimeter(i);
			if (minPeri == 0)
			{
				minPeri = peri;
			}
			else
			{
				minPeri = std::min(minPeri, peri);
			}
		}
	}

	fout << maxArea << " " << minPeri << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}