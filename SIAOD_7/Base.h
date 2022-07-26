#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <conio.h>
#include <functional>
#include <windows.h>
using namespace std;
#define dc (Derived*) 
#pragma warning(disable : 4996)
struct Letters {
	char letter;
	int quantity;
	Letters(char _letter, int _quantity = 1) : letter(_letter), quantity(_quantity) {}
};
struct Cods {
	char letter;
	string code;
	Cods(char _letter, string _code) : letter(_letter), code(_code) {}
};
class Base
{
private:
	static vector<Letters*> alphabet;
	static vector<Cods*> cods;
	string input;
public:
	Base();
	int isUniq(char);
	void createAlphabet();
	void out(int);
	void Sort();
	void execute();

	void devide_vec(Base*);
	void buildTree(Base*);
	void FindLeaf(Base*);
	void decode();
	char* splitString(string);
};

#endif // !BASE_H
