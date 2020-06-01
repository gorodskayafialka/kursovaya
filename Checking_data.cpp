#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "Checking_data.h"

bool checking_file(string filename)
{
	int line_number = 0, position = 0;
	char symbol;
	fstream f;
	int skip;
	f.open(filename, ios::in);
	if (f.bad() != 0)
	{
		try
		{
			throw exception("trouble with file");
		}
		catch (const exception& err)
		{
			return false;
		}
	}
	symbol = f.get(); 
	if (f.eof())
	{
		try
		{
			throw exception("empty file");
		}
		catch (const exception& err)
		{
			cout << "Entry file is empty";
			return false;
		}
	}
	f.unget();
	while (!f.eof())
	{
		position = 0;
		line_number++;
		for (int i = 0; i < 2; i++)
		{
			symbol = f.get();
			position++;
			if ((symbol < 65) || (symbol > 90))
			{
				try
				{
					throw exception("wrong node name");
				}
				catch (const exception& err)
				{
					cout << "Data problem: node can only be named as a capital latin letter. Line " << line_number << ", position " << position;
					return false;
				}
			}
			symbol = f.get();
			position++;
			if (symbol != ' ')
			{
				try
				{
					throw exception("missing space");
				}
				catch (const exception& err)
				{
					cout << "Data problem: nodes and capacities should be devided by spaces. Line " << line_number << ", position " << position;
					return false;
				}
			}
		}
		symbol = f.get();
		position++;
		if ((symbol < '1') || (symbol > '9'))
		{
			try
			{
				throw exception("wrong capacity");
			}
			catch (const exception& err)
			{
				cout << "Data problem: capacity should be a positive number. Line " << line_number << ", position " << position;
				return false;
			}
		}
		else
		{
			f.unget();
			f >> skip;
		}
		symbol = f.get();
		position++;
		if ((symbol != '\n') && (!f.eof()))
		{
			try
			{
				throw exception("not ending line");
			}
			catch (const exception& err)
			{
				cout << "Data problem: Every line must contain only 2 nodes and traffic capacity. Line " << line_number << ", position " << position;
				return false;
			}
		}
	}
	return true;
}


bool checking_nodes(List<char>* nodes)
{
	if ((nodes->get_index('S') == -1) || (nodes->get_index('T') == -1))
	{
		try
		{
			throw exception("missing nodes");
		}
		catch (const exception& err)
		{
			cout << "List of nodes must contain source S and sink T";
			return false;
		}
	}
	else return true;
}


bool checking_capacity(int index1, int index2, char node1, char node2, int** capacity, int line_number)
{
	if (index1 == index2)
	{
		try
		{
			throw exception("loop");
		}
		catch (const exception& err)
		{
			cout << "There's a loop in node " << node1 << " (line " << line_number << "). It will be ignored." << endl;
			return false;
		}
	}
	if (node1 == 'T')
	{
		try
		{
			throw exception("edge from sink");
		}
		catch (const exception& err)
		{
			cout << "There's an edgestarting at the sink (line " << line_number << "). It will be ignored." << endl;
			return false;
		}
	}
	if (node2 == 'S')
	{
		try
		{
			throw exception("edge to source");
		}
		catch (const exception& err)
		{
			cout << "There's a flow ending at the soure(line " << line_number << "). It will be ignored." << endl;
			return false;
		}
	}
	if (capacity[index1][index2] != 0)
	{
		try
		{
			throw exception("contradicting capacity");
		}
		catch (const exception& err)
		{
			cout << "There is  another value of the capacity from " << node1 << " to " << node2 << "(line " << line_number << "). The latest entry will be ignored in favour of the first." << endl;
			return false;
		}
	}
	return true;
}

bool checking_network(int **capacity, List<char>* nodes)
{
	int n = nodes->get_size();
	int source = nodes->get_index('S');
	int sink = nodes->get_index('T');
	bool flag = false;
	for (int i = 0; i < n; i++)
	{
		flag = false;
		if (i == source) continue;
		for (int j = 0; j < n; j++)
		{
			if (capacity[j][i] != 0) flag = true;
		}
		if (flag == false)
		{
			try
			{
				throw exception("no incoming edges");
			}
			catch (const exception& err)
			{
				cout << "Node " << nodes->at(i) << " has no incoming edges.";
				return false;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		flag = false;
		if (i == sink) continue;
		for (int j = 0; j < n; j++)
		{
			if (capacity[i][j] != 0) flag = true;
		}
			if (flag == false)
			{
				try
				{
					throw exception("no exiting edges");
				}
				catch (const exception& err)
				{
					cout << "Node " << nodes->at(i) << " has no exiting edges";
					return false;
				}
		}
	}
	return true;
}