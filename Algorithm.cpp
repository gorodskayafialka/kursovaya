#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "List.h"
#include "Algorithm.h"

using namespace std;

int max_capacity(int** capacity, int n)
{
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (capacity[i][j] > max) max = capacity[i][j];
		}
	}
	return max;
}

void push(int index1, int index2, int* excess, int** capacity, int** flow)
{
	int token;
	if (excess[index1] < (capacity[index1][index2] - flow[index1][index2]))
	{
		token = excess[index1];
	}
	else
	{
		token = capacity[index1][index2] - flow[index1][index2];
	}
	flow[index1][index2] = flow[index1][index2] + token;
	flow[index2][index1] = flow[index2][index1] - token;
	excess[index1] = excess[index1] - token;
	excess[index2] = excess[index2] + token;
}

void relabel(int index, int n, int** capacity, int** flow, int* height)
{
	int token;
	bool found = false;
	for (int i = 0; i < n; i++)
	{
		if ((capacity[index][i] - flow[index][i]) > 0)
		{
			if ((!found) || (height[i] < token))
			{
				token = height[i];
				found = true;
			}
		}
	}
	height[index] = token + 1;
}

void discharge(int index1, int n, int** capacity, int** flow, int* excess, int* height, int* checked)
{
	while (excess[index1] > 0)
	{
		if (checked[index1] < n)
		{
			int index2 = checked[index1];
			if (((capacity[index1][index2] - flow[index1][index2]) > 0) && (height[index1] > height[index2]))
			{
				push(index1, index2, excess, capacity, flow);
			}
			else
			{
				checked[index1]++;
			}
		}
		else
		{
			relabel(index1, n, capacity, flow, height);
			checked[index1] = 0;
		}
	}
}


void displaying_results(int max_flow, List<char>* nodes, int** flow)
{
	if (max_flow == 0)
	{
		try
		{
			throw exception("disconnected");
		}
		catch (const exception& err)
		{
			cout << "Source is not connected with sink";
			return;
		}
	}
	int n = nodes->get_size();
	cout << "Maximum flow is " << max_flow;
	cout << endl << "Here are the flows: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(3) << flow[i][j] << "  ";
		cout << endl;
	}
	cout << "The indexes are nodes in the following order: " << endl;
	nodes->print_to_console();

}

void initiation(int* excess, int* height, int* checked, int** flow, int** capacity, List<int>* indexes, List<char>* nodes)
{
	int n = nodes->get_size();
	int source = nodes->get_index('S');
	int sink = nodes->get_index('T');
	for (int i = 0; i < n; i++)
	{
		checked[i] = 0;
		excess[i] = 0;
		height[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		flow[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			flow[i][j] = 0;
		}
	}
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		if ((i != source) && (i != sink))
		{
			indexes->push_back(i);
		}
	}
	height[source] = n;
	excess[source] = max_capacity(capacity, n)*100;
	for (int i = 0; i < n; i++)
	{
		push(source, i, excess, capacity, flow);
	}
}


int process(int** capacity, List<char>* nodes)
{
	int n = nodes->get_size();
	int source = nodes->get_index('S');
	int last_height;
	int* excess = new int[n];
	int* height = new int[n];
	int* checked = new int[n];
	int** flow = new int* [n];
	int counter = 0;
	List<int>* indexes = new List<int>;
	initiation(excess, height, checked, flow, capacity, indexes, nodes);
	while (counter < (n - 2))
	{
		int index = indexes->at(counter);
		last_height = height[index];
		discharge(index, n, capacity, flow, excess, height, checked);
		if (height[index] > last_height)
		{
			indexes->push_front(index);
			indexes->remove(counter+1);
			counter = 0;
		}
		else
		{
			counter+=1;
		}
	}
	int max_flow = 0;
	for (int i = 0; i < n; i++)
	{
		max_flow = max_flow + flow[source][i];
	}
	displaying_results(max_flow, nodes, flow);
	return (max_flow);
}