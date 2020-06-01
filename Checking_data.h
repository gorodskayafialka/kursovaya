#pragma once
bool checking_file(string filename);

bool checking_nodes(List<char>* nodes);

bool checking_capacity(int index1, int index2, char node1, char node2, int** capacity, int line_number);

bool checking_network(int** capacity, List<char>* nodes);