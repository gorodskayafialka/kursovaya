#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include "../List.h"
#include "../Checking_data.cpp"
#include "../Reading_data.cpp"
#include "../Algorithm.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Preflowtests
{
	TEST_CLASS(Preflowtests)
	{
	public:
		TEST_METHOD(file_check_positive)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\correctfileformat.txt";
			Assert::AreEqual(checking_file(filename), true);
		}

		TEST_METHOD(file_check_wrong_node_name)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\wrongnodename.txt";
			try
			{
				checking_file(filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("wrong node name", e.what());
			}
			Assert::AreEqual(checking_file(filename), false);
		}

		TEST_METHOD(file_check_no_space)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\nospace.txt";
			try
			{
				checking_file(filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("missing space", e.what());
			}
			Assert::AreEqual(checking_file(filename), false);
		}

		TEST_METHOD(file_check_wrong_capacity)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\wrongcapacity.txt";
			try
			{
				checking_file(filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("wrong capacity", e.what());
			}
			Assert::AreEqual(checking_file(filename), false);
		}

		TEST_METHOD(file_check_not_ending_line)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\notendingline.txt";
			try
			{
				checking_file(filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("not_ending_line", e.what());
			}
			Assert::AreEqual(checking_file(filename), false);
		}

		TEST_METHOD(file_check_empty)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\empty.txt";
			try
			{
				checking_file(filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("empty file", e.what());
			}
			Assert::AreEqual(checking_file(filename), false);
		}

		TEST_METHOD(nodes_check_possitive)
		{
			List<char>* nodes = new List<char>;
			nodes->push_back('A');
			nodes->push_back('S');
			nodes->push_back('B');
			nodes->push_back('T');
			Assert::AreEqual(checking_nodes(nodes), true);
		}


		TEST_METHOD(nodes_check_no_T)
		{
			List<char>* nodes = new List<char>;
			nodes->push_back('A');
			nodes->push_back('B');
			nodes->push_back('S');
			try
			{
				checking_nodes(nodes);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("missing nodes", e.what());
			}
			Assert::AreEqual(checking_nodes(nodes), false);
		}
		TEST_METHOD(nodes_check_no_S)
		{
			List<char>* nodes = new List<char>;
			nodes->push_back('A');
			nodes->push_back('B');
			nodes->push_back('T');
			try
			{
				checking_nodes(nodes);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("missing nodes", e.what());
			}
			Assert::AreEqual(checking_nodes(nodes), false);
		}

		TEST_METHOD(correct_nodes)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\readingnodes.txt";
			List<char>* nodes = reading_nodes(filename);
			Assert::AreEqual(nodes->at(0), 'S');
			Assert::AreEqual(nodes->at(1), 'K');
			Assert::AreEqual(nodes->at(2), 'T');
		}

		TEST_METHOD(loop)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\loop.txt";
			List<char>* nodes = reading_nodes(filename);
			try
			{
				reading_capacities(nodes, filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("loop", e.what());
			}
		}

		TEST_METHOD(edge_from_sink)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\edgefromsink.txt";
			List<char>* nodes = reading_nodes(filename);
			try
			{
				reading_capacities(nodes, filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("edge from sink", e.what());
			}
		}

		TEST_METHOD(edge_to_source)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\edgetosource.txt";
			List<char>* nodes = reading_nodes(filename);
			try
			{
				reading_capacities(nodes, filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("edge to source", e.what());
			}
		}

		TEST_METHOD(contradiction)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\contradiction.txt";
			List<char>* nodes = reading_nodes(filename);
			try
			{
				reading_capacities(nodes, filename);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("contradicting capacity", e.what());
			}
		}

		TEST_METHOD(correct_capacities)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\capacities.txt";
			List<char>* nodes = reading_nodes(filename);
			int** capacities = reading_capacities(nodes, filename);
			Assert::AreEqual(capacities[0][0], 0);
			Assert::AreEqual(capacities[0][1], 2);
			Assert::AreEqual(capacities[0][2], 3);
			Assert::AreEqual(capacities[1][0], 0);
			Assert::AreEqual(capacities[1][1], 0);
			Assert::AreEqual(capacities[1][2], 2);
			Assert::AreEqual(capacities[2][0], 0);
			Assert::AreEqual(capacities[2][1], 0);
			Assert::AreEqual(capacities[2][2], 0);
		}

		TEST_METHOD(correct_network)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\capacities.txt";
			List<char>* nodes = reading_nodes(filename);
			int** capacities = reading_capacities(nodes, filename);
			Assert::AreEqual(checking_network(capacities, nodes), true);
		}

		TEST_METHOD(no_incoming_edges)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\noincomingedges.txt";
			List<char>* nodes = reading_nodes(filename);
			int** capacities = reading_capacities(nodes, filename);
			try
			{
				checking_network(capacities, nodes);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("no incoming edges", e.what());
			}
			Assert::AreEqual(checking_network(capacities, nodes), false);
		}

		TEST_METHOD(no_exiting_edges)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\noexitingedges.txt";
			List<char>* nodes = reading_nodes(filename);
			int** capacities = reading_capacities(nodes, filename);
			try
			{
				checking_network(capacities, nodes);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("no exiting edges", e.what());
			}
			Assert::AreEqual(checking_network(capacities, nodes), false);
		}

		TEST_METHOD(correct_initiation_and_push)
		{
			List<char>* nodes = new List<char>;
			nodes->push_back('S');
			nodes->push_back('B');
			nodes->push_back('T');
			int n = nodes->get_size();
			int** capacity = new int* [n];
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
			capacity[0][1] = 4;
			capacity[0][2] = 2;
			capacity[1][2] = 5;
			int source = nodes->get_index('S');
			int* excess = new int[n];
			int* hight = new int[n];
			int* checked = new int[n];
			int** flow = new int* [n];
			int counter = 0;
			List<int>* indexes = new List<int>;
			initiation(excess, hight, checked, flow, capacity, indexes, nodes);
			Assert::AreEqual(excess[0], 494);
			Assert::AreEqual(excess[1], 4);
			Assert::AreEqual(excess[2], 2);
			for (int i = 0; i < n; i++)
			{
				Assert::AreEqual(checked[i], 0);
			}
			Assert::AreEqual(hight[0], n);
			for (int i = 1; i < n; i++)
			{
				Assert::AreEqual(hight[i], 0);
				Assert::AreEqual(checked[i], 0);
			}
			Assert::AreEqual(flow[0][0], 0);
			Assert::AreEqual(flow[0][1], 4);
			Assert::AreEqual(flow[0][2], 2);
			Assert::AreEqual(flow[1][0], -4);
			Assert::AreEqual(flow[1][1], 0);
			Assert::AreEqual(flow[1][2], 0);
			Assert::AreEqual(flow[2][0], -2);
			Assert::AreEqual(flow[2][1], 0);
			Assert::AreEqual(flow[2][2], 0);
			Assert::AreEqual(indexes->at(0), 1);

		}

		TEST_METHOD(correct_process)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\process.txt";
			List<char>* nodes;
			int** capacity;
			nodes = reading_nodes(filename);
			capacity = reading_capacities(nodes, filename);
			int result = process(capacity, nodes);
			Assert::AreEqual(result, 5);
		}

		TEST_METHOD(disconnected)
		{
			string filename = "C:\\Users\\Гость\\source\\repos\\Preflow-push_algorithm\\Preflow_tests\\disconnected.txt";
			List<char>* nodes;
			int** capacity;
			nodes = reading_nodes(filename);
			capacity = reading_capacities(nodes, filename);
			try
			{
				 process(capacity, nodes);
			}
			catch (std::exception e)
			{
				Assert::AreEqual("disconnected", e.what());
			}	
		}

		TEST_METHOD(max_of_capacity)
		{
			int n = 2;
			int** capacity = new int* [n];
			for (int i = 0; i < n; i++)
			{
				capacity[i] = new int[n];
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					capacity[i][j] = i + j;
				}
			}
			Assert::AreEqual(max_capacity(capacity, n), 2);
		}


		TEST_METHOD(relabeling)
		{
			int n = 3;
			int** capacity = new int* [n];
			int** flow = new int* [n];
			int* height = new int [n];
			for (int i = 0; i < n; i++)
			{
				capacity[i] = new int[n];
				flow[i] = new int[n];
				height[i] = i+3;
			}
			capacity[0][0] = 7;
			capacity[0][1] = 9;
			capacity[0][2] = 10;
			flow[0][0] = 7; 
			flow[0][1] = 8;
			flow[0][1] = 3;
			relabel(0, n, capacity, flow, height);
			Assert::AreEqual(height[0], 5);
		}

	};
}
