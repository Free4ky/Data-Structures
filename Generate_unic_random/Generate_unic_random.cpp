// Generate_unic_random.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <unordered_set>
#include <random>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;
int main()
{
    string path = "C:\\Новая папка\\random_uinc.txt";
    default_random_engine dre(std::time(nullptr));
    uniform_int_distribution<> uid(1, 9999999);
    unordered_set<int> uSet;

    while (uSet.size() != 10000)
    {
        uSet.insert(uid(dre));
    }
    unordered_set<int> ::iterator uset_iterator = uSet.begin();
    ofstream fout;
    fout.open(path);
    if (fout.is_open())
    {
        while (uset_iterator != uSet.end()) 
        {
            fout << (*uset_iterator)<<" A A"<< "\n";
            uset_iterator++;
        }
    }
    fout.close();
    return 0;
}