/*
ID: alina.l1
LANG: C++
PROB: palsquare
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int charArrToInt(char* cStr)
{
	std::string str(cStr);
	return std::stoi(str);
}


std::vector<char> conB(int b, int n)
{
	int q;
	bool isFirst = true;

	std::vector<char> r;

	while (isFirst || q != 0)
	{
		isFirst = false;
		q = n / b;

		int curR = n % b;

		if (curR >= 10)
		{
			r.push_back(curR + 55);
		}
		else
		{
			r.push_back(curR + 48);
		}

		n = q;
	}

	return r;
}

int main()
{
	// Open Streams
	std::ifstream fin("palsquare.in");

	std::ofstream fout("palsquare.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File
	const int MAX_LENGTH = 100;
	char str[MAX_LENGTH];
	fin.getline(&(str[0]), MAX_LENGTH);

	int b = charArrToInt(str);

	// TEST
	std::vector<char> output = conB(b, 100);
	for (char nn : output)
	{
		std::cout << nn;
	}
	// TEST

	const int startN = 1;
	const int endN = 300;

	for (int n = startN; n <= endN; n++)
	{
		// base b conversion of n squared
		std::vector<char> nSq = conB(b, n * n);

		// check if palindromic
		bool isP = true;
		for (int i = 0; i < nSq.size(); i++)
		{
			// if not equal
			if (nSq.at(i) != nSq.at(nSq.size() - i - 1))
			{
				isP = false;
				break;
			}
		}

		// if p, output it
		if (isP)
		{
			// print orig n in base b
			std::vector<char> nB = conB(b, n);
			for ( int i = nB.size() - 1; i >= 0; i--)
			{
				fout << nB.at(i);
			}

			fout << " ";

			// print nSq in base b
			for (char cur : nSq)
			{
				fout << cur;
			}
			fout << "\n";
		}
	}

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}