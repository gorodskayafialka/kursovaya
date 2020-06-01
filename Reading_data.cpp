#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "Checking_data.h"
#include "Reading_data.h"

using namespace std;

void reading_and_displaying_initial_data(string filename)
{

	string line;
	fstream f;
	cout << "The initial data: " << endl;
	f.open(filename, ios::in);
	if (f.bad() != 0)
	{
		try
		{
			throw exception("trouble with file");
		}
		catch (const exception& err)
		{
			cout << "Experiencing trouble with opening the 'reading' file";
			return;
		}
	}
	while (!f.eof())
	{
		getline(f, line);
		cout << line;
		cout << endl;
	}
	f.close();
}

List<char>* reading_nodes (string filename)
{
	List<char>* nodes = new List<char>;
	fstream f;
	f.open(filename, ios::in);
	char node;
	int counter = 0;
	f >> node;
	while (!f.eof())
	{
		if (counter < 2)
		{
			if (nodes->get_index(node) == -1)
				nodes->push_back(node);
			counter++;
			f >> node;
			if ((node >= '0') && (node <= '9'))
			{
				while ((node != '\n') && (!f.eof()))
					node = f.get();
			}
		}
		else
		{
			counter = 0;
			f >> node;
		}
	}
	f.close();
	return nodes;
	
}


int** reading_capacities(List <char>* nodes, string filename)
{
	int n = nodes->get_size();
	int**  capacity = new int* [n];
	for (int i = 0; i < n; i++)
	{
		capacity[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			capacity[i][j] = 0;
		}
	}
	fstream f;
	f.open( filename, ios::in);
	char node1, node2;
	int index1, index2;
	int Capacity;
	int line_number = 0;
	while (!f.eof())
	{
		line_number++;
		f >> node1 >> node2 >> Capacity;
		index1 = nodes->get_index(node1);
		index2 = nodes->get_index(node2);
		if (checking_capacity(index1, index2, node1, node2, capacity, line_number))
		capacity[index1][index2] = Capacity;
	}
	f.close();
	return capacity;
}




