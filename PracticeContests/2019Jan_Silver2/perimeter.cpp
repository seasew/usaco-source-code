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
// 0=not part of blob, >=1 part of blob
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
			dfs(newI, newJ);
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
			fin >> std::skipws >> icecream[i][j];
		}
	}

	// set starting label
	curLabel = 1;

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

	// create iterator for first max area
	auto itr = std::max_element(std::begin(areas), std::end(areas));
	int maxarea = *itr;
	// print max area
	fout << maxarea << " ";

	// calculate the index of the maxarea
	int curindex = std::distance(areas, itr);
	// set a minimum perimeter
	int minperi = 0;

	// find all the maximum areas
	// while the area found is still the original max area
	while (areas[curindex] == maxarea)
	{
		// calculate perimeter of curindex
		int curperi = perimeter(curindex);

		// cmp with min perimeter
		if (!minperi)
		{
			// if hasn't been initalized
			minperi = curperi;
		}
		else
		{
			minperi = std::min(minperi, curperi);
		}

		// set the max area to 0
		// (this is so that max_element won't get this value again)
		areas[curindex] = 0;
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}