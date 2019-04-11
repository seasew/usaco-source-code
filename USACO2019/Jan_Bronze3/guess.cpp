/*
ID: alina.l1
LANG: C++
PROB: guess
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

int charArrToInt(char cStr[])
{
	std::string str(cStr);
	return std::stoi(str);
}

struct Animal
{
	std::string name;
	int cN;
	std::set<std::string> c;
};

std::vector<Animal> a;

int getSim(int i, int j)
{
	Animal a1 = a.at(i);
	Animal a2 = a.at(j);

	int value = 0;

	// for each characteristic in a1
	for (int x = 0; x < a1.cN; x++)
	{
		// if this a1Ch is also in a2, update value
		if ((a2.c).count(*std::next((a1.c).begin(), x)) == 1)
		{
			value++;
		}
	}

	return value;
}

int main()
{
	// Open Streams
	std::ifstream fin("guess.in");

	std::ofstream fout("guess.out");

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
	int n = charArrToInt(str);

	for (int i = 0; i < n; i++)
	{
		// read the animal name
		fin.getline(&(str[0]), MAX_LENGTH, ' ');
		std::string name(str);

		// read the number of characteristics
		fin.getline(&(str[0]), MAX_LENGTH, ' ');
		int cN = charArrToInt(str);

		// read the characteristics
		std::set<std::string> aCh;
		for (int j = 0; j < cN; j++)
		{
			if (j == cN - 1)
			{
				fin.getline(&(str[0]), MAX_LENGTH);
			}
			else
			{
				fin.getline(&(str[0]), MAX_LENGTH, ' ');
			}
			std::string curC(str);

			// add this characteristic to the animal
			aCh.insert(curC);
		}

		// add the animal
		struct Animal animal = {name, cN, aCh};
		a.push_back(animal);
	}

	int max = 0;
	// iterate through all pairs of animals
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int out = getSim(i, j);
			if (out > max)
			{
				max = out;
			}
		}
	}

	fout << max+1 << "\n";

	// Close Streams
	fin.close();
	fout.close();

	return 0;
}