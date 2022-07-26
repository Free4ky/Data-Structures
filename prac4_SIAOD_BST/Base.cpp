#include "Base.h"
#include "Derived.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;
#pragma warning(disable : 4996)

Base::Base(int licenseNubmer, int bitNumber, Base* parent, Base* RightSon, Base* LeftSon)
{
	this->bitNubmer = bitNumber;
	this->licenseNubmer = licenseNubmer;
	this->RightSon = RightSon;
	this->LeftSon = LeftSon;
	this->parent = parent;
}
void Base::buildTree(string path) 
{
	fstream fin;
	streampos tellp();
	fin.open(path, ios_base::in, ios::binary);
	if (fin.is_open()) 
	{
		string line = "";
		char temp;
		char* pch;
		Base* node;
		while (fin.read(&temp, sizeof(char))) 
		{
			line += temp;
			if (temp == '\n') 
			{
				pch = splitString(line);
				node = new Derived(atoi(pch), (int)fin.tellp() - line.length(), 0, 0, 0);//?
				root = node;
				fin.seekg(fin.tellp(), ios::beg);
				line = "";
				break;
			}
		}
		while (fin.read(&temp, sizeof(char))) 
		{
			line += temp;
			if (temp == '\n') 
			{
				pch = splitString(line);
				addNode(atoi(pch), (int)fin.tellp() - line.length() - 1, root);
				line = "";
			}
		}
	}
	else 
	{
		cout << "Can't open the file: " << path;
	}
	fin.close();
}
char* splitString(string line) 
{
	char* str = new char[line.length() + 1];
	strcpy(str, line.c_str());
	char* pch = strtok(str, " ");
	return pch;
}
void Base::addNode(int licenseNumber, int bitNumber, Base* currentPointer) 
{
	if (licenseNumber < currentPointer->getLicenseNumber()) 
	{
		if (currentPointer->LeftSon == NULL) 
		{
			currentPointer->LeftSon = new Derived(licenseNumber, bitNumber, currentPointer, 0, 0);
		}
		else 
		{
			addNode(licenseNumber, bitNumber, currentPointer->LeftSon);
		}
	}
	else
	{
		if (currentPointer->RightSon == NULL) 
		{
			currentPointer->RightSon = new Derived(licenseNumber, bitNumber, currentPointer, 0, 0);
		}
		else 
		{
			addNode(licenseNumber, bitNumber, currentPointer->RightSon);
		}
	}
}
//void Base::printTree(string k)
//{
//	if (LeftSon == NULL && RightSon == NULL) { return; }
//	k += "		";
//	cout << "\n";
//	if (LeftSon != NULL) 
//	{
//		cout << k << LeftSon->getLicenseNumber();
//		LeftSon->printTree(k);
//	}
//	cout << "\n";
//	if (RightSon != NULL) 
//	{
//		cout << k << RightSon->getLicenseNumber();
//		RightSon->printTree(k);
//	}
//}
string setTabs(int level) 
{
	string k = "";
	for (int i = 0; i < level; i++) 
	{
		k += "		";
	}
	return k;
}
void Base::printTree() 
{
	string k = "";
	treeNode* buffer;
	FindRightLeaf(1, root->RightSon);
	while (!NodeStack.empty()) 
	{
		buffer = NodeStack.top();
		NodeStack.pop();
		k = setTabs(buffer->treeLevel + 1);
		if (buffer->node->RightSon != 0) 
		{
			cout << k<<" "<< buffer->node->RightSon->getLicenseNumber()<<"\n" <<k<<"/\n";
		}
		if (buffer->node->LeftSon != 0)
		{
			cout << k <<"\\"<< "\n"<<k<<" "<<buffer->node->LeftSon->getLicenseNumber() << "\n";
		}
	}
	if (root->RightSon != 0) 
	{
		cout <<"		 "<<root->RightSon->getLicenseNumber() <<"\n		/\n";
	}
	cout <<"\n"<<root->getLicenseNumber()<<"\n";
	if (root->LeftSon != 0) 
	{
		cout << "		\\\n" <<"		 "<<root->LeftSon->getLicenseNumber();
	}
	//FindLeftLeaf(1, root->LeftSon);
	k = "		";
	FindLeftLeaf(k,root->LeftSon);
}
//void Base::clear_stack() 
//{
//	while (!NodeStack.empty()) 
//	{
//		NodeStack.pop();
//	}
//	return;
//}
void Base::FindRightLeaf(int level, Base* current) // запуск от правого или левого сына корня
{
	if (current == NULL) { return; }
	if (current->LeftSon == 0 && current->RightSon == 0) { return; }
	treeNode* currentNode = new treeNode(current,level);
	NodeStack.push(currentNode);
	if (current->LeftSon != NULL) 
	{
		FindRightLeaf(level + 1, current->LeftSon);
	}
	if (current->RightSon != NULL) 
	{
		FindRightLeaf(level + 1, current->RightSon);
	}
}
void Base::FindLeftLeaf(string k, Base* current) // запуск от правого или левого сына корня
{
	if (current == NULL) { return; }
	if (current->LeftSon == 0 && current->RightSon == 0) { return; }
	k += "		";
	cout << "\n";
	if (current->RightSon) 
	{
		cout << k <<" "<< current->RightSon->getLicenseNumber() <<"\n"<<k<<"/";
		//cout << k << current->RightSon->getLicenseNumber();
	}
	FindLeftLeaf(k, current->RightSon);
	cout << "\n";
	if (current->LeftSon) 
	{
		cout << k << "\\\n" << k <<" "<<current->LeftSon->getLicenseNumber();
		//cout << k << current->LeftSon->getLicenseNumber();
	}
	FindLeftLeaf(k, current->LeftSon);
}
void Base::execute(string path) 
{
	buildTree(path);
	//cout << root->getLicenseNumber();
	root->printTree();
	cout << "\n";
	auto start = chrono::high_resolution_clock::now();
	FindLine(4374496, path);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
	cout << "Search time is: " << duration.count() << " nanoseconds\n";
	cout <<CompareQuantity<<"\n";
	//deleteNode(11334);
	//root->printTree();
	//deleteNode(12111);
	//root->printTree();
}
int Base::getLicenseNumber() 
{
	return this->licenseNubmer;
}
void Base::FindLine(int license, string path)
{
	CompareQuantity = 0;
	Base* requiredNode = FindNode(license, root);
	string line;
	if (requiredNode)
	{
		fstream fin;
		fin.open(path, ios_base::in,ios::binary);
		if (fin.is_open())
		{
			fin.seekg(requiredNode->bitNubmer, ios::beg);
			getline(fin, line);
		}
		else
		{
			cout << "Can't read file: " << path;
		}
		fin.close();
	}
	else 
	{
		cout <<"\nThere no such licnese";
	}
	cout << "\n"<<line;
}
Base* Base::FindNode(int license, Base* currentPointer) 
{
	if (currentPointer == NULL) { return 0; }
	if (currentPointer->getLicenseNumber() == license) 
	{
		CompareQuantity++;
		return currentPointer;
	}
	else if (license < currentPointer->getLicenseNumber())
	{
		CompareQuantity++;
		FindNode(license, currentPointer->LeftSon);
	}
	else if (license > currentPointer->getLicenseNumber())
	{
		CompareQuantity++;
		FindNode(license, currentPointer->RightSon);
	}
	//return 0;
}
void Base::FindMAX(Base* current) 
{
	if (current == NULL) { return; }
	if (current->getLicenseNumber() > max) 
	{
		max = current->getLicenseNumber();
	}
	FindMAX(current->LeftSon);
	FindMAX(current->RightSon);
}
void Base::deleteNode(int license) 
{
	Base* target = FindNode(license, root);
	if (target) 
	{
		if (target->LeftSon && target->RightSon) // есть оба
		{
			FindMAX(target->LeftSon);
			Base* m = FindNode(max,root);
			if (m) 
			{
				int x = m->licenseNubmer;
				int y = m->bitNubmer;
				deleteNode(max);
				target->licenseNubmer = x;
				target->bitNubmer = y;
				return;
			}
		}
		else if (target -> LeftSon) // есть только левый
		{
			if (target == target->parent->LeftSon) 
			{
				target->parent->LeftSon = target->LeftSon;
			}
			else 
			{
				target->parent->RightSon = target->LeftSon;
			}
		}
		else if (target->RightSon) // есть только правый
		{
			if (target == target->parent->LeftSon)
			{
				target->parent->LeftSon = target->RightSon;
			}
			else
			{
				target->parent->RightSon = target->RightSon;
			}
		}
		else // нет наследников
		{
			if (target == target->parent->LeftSon) {
				target->parent->LeftSon = NULL;
			}
			else {
				target->parent->RightSon = NULL;
			}
		}
	}
	else 
	{
		cout << "\nThere is no such node\n";
	}
}
int Base::max = 0;
int Base::CompareQuantity = 0;
Base* Base::root = NULL;
stack<Base::treeNode*>Base::NodeStack;
//stack <Base::treeNode*> Base::NodeStack