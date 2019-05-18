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
// 0=not part of blob, >=1 part of blob
int labels[1000][1000];
// areas array, index refers to label
int maxArea;
int curArea;
std::vector<int> maxAreaI;

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
	if (labels[i][j] != 0)
	{
		return;
	}

	// mark current
	labels[i][j] = curLabel;
	// update area of current label
	curArea++;

	// mark recursively for each direction
	for (int a = 0; a < 4; a++)
	{
		int newI = i + dx[a];
		int newJ = j + dy[a];
		if (labels[newI][newJ] == 0)
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
	std::ifstream fin("perimeter.in");

	std::ofstream fout("perimeter.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read file
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char ch;
			fin >> ch;

			// has ice cream = 0
			if (ch == '#')
			{
				labels[i][j] = 0;
			}
			// does not have ice cream = -1
			else // if (ch == '.')
			{
				labels[i][j] = -1;
			}
		}
	}

	// set starting label
	curLabel = 1;
	// set starting area
	maxArea = 0;
	curArea = 0;

	// call dfs for every point that has 0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (labels[i][j] == 0)
			{
				dfs(i, j);

				// cmp curArea with maxArea
				maxArea = std::max(maxArea, curArea);

				if (curArea > maxArea)
				{
					maxAreaI.clear();
					maxAreaI.push_back(curLabel);
				}
				// if they have equal areas, record the label
				else if (curArea == maxArea)
				{
					maxAreaI.push_back(curLabel);
				}

				// reset curarea for next
				curArea = 0;
				// update label for next blob
				curLabel++;
			}
		}
	}

	// now there is a max area, a vector with all the labels that have maxArea area
	int minPeri = 0;
	for (int label : maxAreaI)
	{
		int peri = perimeter(label);
		if (minPeri == 0)
		{
			minPeri = peri;
		}
		else
		{
			minPeri = std::min(minPeri, peri);
		}
	}

	fout << maxArea << " " << minPeri << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}