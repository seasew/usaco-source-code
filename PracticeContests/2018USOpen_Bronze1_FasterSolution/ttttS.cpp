/*
ID: alina.l1
LANG: C++
PROB: tttt2
*/

#include <iostream>
#include <fstream>
#include <string>

static const int N = 3;
char board[N][N];

// 1 cow win with this char?
int cowWin(char c)
{
	// check rows and cols
	for (int i = 0; i < N; i++)
	{
		// check ith row
		if (board[i][0] == c && board[i][1] == c && board[i][2] == c)
		{
			return 1;
		}
		// check ith column
		if (board[0][i] == c && board[1][i] == c && board[2][i] == c)
		{
			return 1;
		}
	}

	// check diagonals
	if (board[0][0] == c && board[1][1] == c && board[2][2] == c)
	{
		return 1;
	}
	if (board[0][2] == c && board[1][1] == c && board[2][0] == c)
	{
		return 1;
	}

	return 0;
}

// do these three chars have exactly two chars in them?
bool check3(char c1, char c2, char a, char b, char c)
{
	// a, b, c must be either c1 or c2
	if (a != c1 && a != c2)
	{
		return false;
	}
	if (b != c1 && b != c2)
	{
		return false;
	}
	if (c != c1 && c != c2)
	{
		return false;
	}

	// make sure that they are not all one char
	if (a == b && b == c)
	{
		return false;
	}

	return true;
}

// can a team of two cows win?
int teamWin(char c1, char c2)
{
	// use check3 for each row, col, and diagonal

	// check rows and cols
	for (int i = 0; i < N; i++)
	{
		// row
		if (check3(c1, c2, board[i][0], board[i][1], board[i][2]))
		{
			return 1;
		}
		// col
		if (check3(c1, c2, board[0][i], board[1][i], board[2][i]))
		{
			return 1;
		}
	}

	// check diagonals
	if (check3(c1, c2, board[0][0], board[1][1], board[2][2]))
	{
		return 1;
	}

	if (check3(c1, c2, board[0][2], board[1][1], board[2][0]))
	{
		return 1;
	}

	return 0;
}

int main()
{
	// Open Streams
	std::ifstream fin("tttt.in");

	std::ofstream fout("tttt.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read board
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> board[i][j];
		}
	}

	// check cow1 with all 26 letters
	int cow1 = 0;
	for (int i = 'A'; i <= 'Z'; i++)
	{
		cow1 += cowWin(i);
	}
	int cowTeam = 0;
	for (int i = 'A'; i <= 'Z'; i++)
	{
		for (int j = i + 1; j <= 'Z'; j++)
		{
			cowTeam += teamWin(i, j);
		}
	}

	fout << cow1 << "\n" << cowTeam << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}