/*
ID: alina.l1
LANG: C++
PROB: tttt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

void checkSet(std::set<char> s, std::set<char>& cow1, std::set<std::pair<char, char>>& cow2)
{
	if (s.size() == 1)
	{
		cow1.insert(*s.begin());
	}
	else if (s.size() == 2)
	{
		int c1 = *s.begin();
		int c2 = *(std::next(s.begin(), 1));
		std::pair<char, char> sPair(std::min(c1, c2), std::max(c1, c2));

		cow2.insert(sPair);
	}

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

	std::set<char> row1;
	std::set<char> row2;
	std::set<char> row3;
	std::set<char> col1;
	std::set<char> col2;
	std::set<char> col3;
	std::set<char> dR;
	std::set<char> dL;

	// Read File
	const int MAX_LENGTH = 5;
	char row1Str[MAX_LENGTH];
	fin.getline(&(row1Str[0]), MAX_LENGTH);

	char row2Str[MAX_LENGTH];
	fin.getline(&(row2Str[0]), MAX_LENGTH);

	char row3Str[MAX_LENGTH];
	fin.getline(&(row3Str[0]), MAX_LENGTH);

	// initialize the row sets
	for (int i = 0; i < 3; i++)
	{
		row1.insert(row1Str[i]);
		row2.insert(row2Str[i]);
		row3.insert(row3Str[i]);
	}

	// initialize the col sets
	col1.insert(row1Str[0]);
	col1.insert(row2Str[0]);
	col1.insert(row3Str[0]);

	col2.insert(row1Str[1]);
	col2.insert(row2Str[1]);
	col2.insert(row3Str[1]);

	col3.insert(row1Str[2]);
	col3.insert(row2Str[2]);
	col3.insert(row3Str[2]);

	// initialize diagonal right
	dR.insert(row1Str[0]);
	dR.insert(row2Str[1]);
	dR.insert(row3Str[2]);

	// initalize d Left
	dL.insert(row1Str[2]);
	dL.insert(row2Str[1]);
	dL.insert(row3Str[0]);

	std::set<char> cow1;
	std::set<std::pair<char, char>> cow2;

	checkSet(row1, cow1, cow2);
	checkSet(row2, cow1, cow2);
	checkSet(row3, cow1, cow2);
	checkSet(col1, cow1, cow2);
	checkSet(col2, cow1, cow2);
	checkSet(col3, cow1, cow2);
	checkSet(dR, cow1, cow2);
	checkSet(dL, cow1, cow2);

	fout << cow1.size() << "\n" << cow2.size() << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}