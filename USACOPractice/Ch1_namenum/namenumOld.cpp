/*
ID: alina.l1
LANG: C++
PROB: namenum
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define CHAR_ARR_LEN 3
#define MAX_NAME_LEN 1000
#define MAX_LEN 12

bool inDict(std::string name, std::vector<std::string> &dict)
{
	std::cout << "+";
	std::cout << name;
	std::cout << "+";

	std::cout << dict.size();

	if (name.compare("GREG") == 0)
	{
		std::cout << "here!";

		for (int i = 0; i < dict.size(); i++)
		{
			std::cout << dict.at(i);
			std::cout << "--";
		}
	}

	for (int i = 0; i < dict.size(); i++)
	{
		
		if ((dict.at(i)).compare(name) == 0)
		{
			return true;
		}
	}

	return false;
}

char* numToLetter(int num)
{
	char* out = 0;
	if (num == 2)
	{
		out = new char[CHAR_ARR_LEN] {'A', 'B', 'C'};
	}
	else if (num == 3)
	{
		out = new char[CHAR_ARR_LEN] { 'D', 'E', 'F' };
	}
	else if (num == 4)
	{
		out = new char[CHAR_ARR_LEN] { 'G', 'H', 'I' };
	}
	else if (num == 5)
	{
		out = new char[CHAR_ARR_LEN] { 'J', 'K', 'L' };
	}
	else if (num == 6)
	{
		out = new char[CHAR_ARR_LEN] { 'M', 'N', 'O' };
	}
	else if (num == 7)
	{
		out = new char[CHAR_ARR_LEN] { 'P', 'R', 'S' };
	}
	else if (num == 8)
	{
		out = new char[CHAR_ARR_LEN] { 'T', 'U', 'V' };
	}
	else// (num == 9)
	{
		out = new char[CHAR_ARR_LEN] { 'W', 'X', 'Y' };
	}

	return out;
}



void add(std::vector<std::string> &output, std::string str, int* num, int nLen, std::vector<std::string> dict)
{
	if (str.length() == nLen)
	{
		// we are done adding chars
		// check if the current str is in Dict
		if (inDict(str, dict))
		{
			// if it is, then add it to output
			output.push_back(str);
		}

		// DONE
		return;
	}

	// continue adding chars
	// get the char array for the current digit
	int len = str.length();
	int digit = num[len];
	char* list = numToLetter(digit);
	for (int i = 0; i < CHAR_ARR_LEN; i++)
	{
		add(output, str + list[i], num, nLen, dict);
	}
}


std::vector<std::string> permutate(int* num, int nLen, std::vector<std::string> dict)
{
	std::vector<std::string> output;
	add(output, "", num, nLen, dict);

	return output;
}


int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}


int main()
{
	// Open Streams
	std::ifstream fin("namenum.in");

	std::ofstream fout("namenum.out");

	// Check
	if (!fin.is_open() || !fout.is_open())
	{
		std::cout << "File could not be opened.";
		fin.close();
		fout.close();
		return 1;
	}

	// Read File

	int num[MAX_LEN];
	int nLen = 0;

	while (isdigit(fin.peek()))
	{
		std::string str(1, fin.get());
		num[nLen] = std::stoi(str);
		nLen++;
	}

	// Read dictionary file
	std::ifstream din("dict.txt");

	std::vector<std::string> dict;

	while (isalpha(din.peek()))
	{
		char c[MAX_LEN];
		din.getline(c, MAX_LEN);

		std::string next(c);

		dict.push_back(next);
	}

	din.close();

	// Calculate
	std::vector<std::string> output = permutate(num, nLen, dict);

	// Write to File
	for (unsigned int i = 0; i < output.size(); i++)
	{
		fout << output.at(i);
	}
	
	if (output.size() == 0)
	{
		fout << "NONE";
	}

	fout << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}