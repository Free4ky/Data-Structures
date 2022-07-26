#include "Base.h"
#include <string>
#include<iostream>
#include <stack>
using namespace std;
Base::Base(char name,Base* parent, Base* LeftSon, Base* RightSon)
{
	setParent(parent);
	setLeftSon(LeftSon);
	setRightSon(RightSon);
	setName(name);
}
void Base::setParent(Base* parent) 
{
	this->parent = parent;
}
void Base::setLeftSon(Base* LeftSon) 
{
	this->LeftSon = LeftSon;
}
void Base::setRightSon(Base* RightSon) 
{
	this->RightSon = RightSon;
}
void Base::setName(char name) 
{
	this->name = name;
}
Base* Base::getParent() 
{
	return parent;
}
Base* Base::getLeftSon() 
{
	return LeftSon;
}
Base* Base::getRightSon() 
{
	return RightSon;
}
char Base::getName() 
{
	return name;
}
string Base::convertor()
{
	setlocale(0, "");
	string infix;
	string prefix;
	cout << "¬ведите арифметическое выражение: ";
	getline(cin, infix);
	reverse(infix.begin(), infix.end());
	for (int i = 0; i < infix.length(); i++) 
	{
		if (infix[i] == '(') 
		{
			infix[i] = ')';
		}
		else if (infix[i] == ')') 
		{
			infix[i] = '(';
		}
	}
	infix = '(' + infix + ')';
	stack <char> st;
	int l = infix.length();
	for (int i = 0; i < l; i++)
	{
		if (isalpha(infix[i]))
		{
			prefix += infix[i];
		}
		else if (isOperator(infix[i]))
		{
			while (Priority(st.top()) >= Priority(infix[i]))
			{
				prefix += st.top();
				st.pop();
			}
			st.push(infix[i]);
		}
		else if (infix[i] == '(')
		{
			st.push(infix[i]);
		}
		else if (infix[i] == ')')
		{
			while (st.top() != '(')
			{
				prefix += st.top();
				st.pop();
			}
			st.pop();
		}
	}
	l = prefix.length();
	//postfix.erase(l - 1);
	reverse(prefix.begin(), prefix.end());
	return prefix;
}
void Base::printNames(string k) 
{
	if (LeftSon == 0 && RightSon == 0) 
	{
		return;
	}
	k += "    ";
	cout << endl;
	cout <<k<<LeftSon->getName();
	LeftSon->printNames(k);
	cout << endl;
	cout <<k<<RightSon->getName();
	RightSon->printNames(k);
}
int Priority(char x)
{
	switch (x)
	{
	case '/':
		return 2;
	case '*':
		return 2;
	case '+':
		return 1;
	case '-':
		return 1;
	case '(':
		return 0;
	default:
		return 0;
	}
}
bool isOperator(char x)
{
	if (x == '*' || x == '/' || x == '+' || x == '-') return true;
	return false;
}