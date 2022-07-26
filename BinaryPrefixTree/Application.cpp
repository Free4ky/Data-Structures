#include "Base.h"
#include "Application.h"
#include "Derived.h"
#include<iostream>
#include <stack>
using namespace std;
Application::Application(char name,Base*parent, Base*LeftSon, Base*RightSon) : Base(name,parent,LeftSon,RightSon) {}
void Application::buildTree(string prefix) 
{
	setlocale(0, "");
	cout <<"Исходное выражение в префиксной записи: "<<prefix;
	stack<Base*>objects;
	reverse(prefix.begin(), prefix.end());
	Base* buffer;
	Base* left;
	Base* right;
	for (int i = 0; i < prefix.length(); i++) 
	{
		if (isalpha(prefix[i])) 
		{
			buffer = new Derived(prefix[i], 0, 0, 0);
			objects.push(buffer);
		}
		if (isOperator(prefix[i])) 
		{
			if (objects.size() > 1) 
			{
				left = objects.top();
				objects.pop();
				right = objects.top();
				objects.pop();
				buffer = new Derived(prefix[i], 0, left, right);
				left->setParent(buffer);
				right->setParent(buffer);
				objects.push(buffer);
			}
		}
	}
	buffer = objects.top();
	this->setLeftSon(buffer->getLeftSon());
	this->setRightSon(buffer->getRightSon());
	this->setName(buffer->getName());
}
int Application::execute() 
{
	setlocale(0, "");
	buildTree(convertor());
	cout <<endl<<"Дерево выражения имеет вид:\n"<< this->getName();
	printNames("");
	return 0;
}