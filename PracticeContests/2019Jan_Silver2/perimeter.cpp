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
// . or # original ice cream
char icecream[1000][1000];
// 0=not part of blob, >=1 pat of blob
int labels[1000][1000];
// areas array, index refers to label
int areas[1000];

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

	// position must be #
	if (!(icecream[i][j] == '#'))
	{
		return;
	}
	// position must be unlabeled
	if (labels[i][j])
	{
		return;
	}

	// mark current
	labels[i][j] = curLabel;
	// update area of current label
	areas[curLabel]++;

	// mark recursively for each direction
	for (int a = 0; a < 4; a++)
	{
		int newI = i + dx[a];
		int newJ = j + dy[a];
		if (icecream[newI][newJ] == '#' && !labels[newI][newJ])
		{
			dfs(i, j);
		}
	}
}

// calculates the perimeter of the label given
int perimeter(int label)
{
	return 0;
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
			fin >> std::noskipws >> icecream[i][j];
		}
	}

	// call dfs for every point that has # and is unlabeled
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (icecream[i][j] == '#' && !labels[i][j])
			{
				dfs(i, j);
				curLabel++;
			}
		}
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}