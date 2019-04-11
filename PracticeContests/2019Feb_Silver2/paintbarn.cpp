/*
ID: alina.l1
LANG: C++
PROB: paintbarn
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

int main()
{
	// Open Streams
	std::ifstream fin("paintbarn.in");

	std::ofstream fout("paintbarn.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File 
	fin >> VARIABLE;

	// Write to File
	fout << "This is my OUTPUT!!!";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}