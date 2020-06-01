#include <iostream>
#include <fstream>
#include "List.h"
#include "Reading_data.h"
#include "Checking_data.h"
#include "Algorithm.h"

using namespace std;

int main()
{
    List<char>* nodes;
   int** capacity;
    string filename = "example7.txt";
    reading_and_displaying_initial_data(filename);
    if (checking_file(filename))
    {
        nodes = reading_nodes(filename);
        if (checking_nodes(nodes))
        {
            capacity = reading_capacities(nodes, filename);
            if (checking_network(capacity, nodes))
                int result = process(capacity, nodes);
        }
    }
}



