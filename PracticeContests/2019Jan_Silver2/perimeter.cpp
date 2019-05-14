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

// . or # original ice cream
char icecream[1000][1000];
// 0=not part of blob, >=1 pat of blob
int labels[1000][1000];

const int dx[] = {1, 0, -1, 0};
const int dy[] = { 0, -1, 0, 1 };

// depth first search
void dfs(int i, int j, int label)
{
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
	labels[i][j] = label;

	// mark recursively for each direction
	for (int a = 0; a < 4; a++)
	{
		dfs(i + dx[a], j + dy[a], label);
	}
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

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}