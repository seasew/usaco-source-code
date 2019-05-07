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

	fin >> VARIABLE;

	// Write to File
	fout << "";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}