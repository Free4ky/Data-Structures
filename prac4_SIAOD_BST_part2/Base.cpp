#include "Base.h"
#include "Derived.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#pragma warning(disable : 4996)

using namespace std;
Base::Base() 
{
	//this->path = "C:\\Ќова€ папка\\myFile4.txt";
	this->path = "C:\\Ќова€ папка\\random_uinc.txt";
}
void Base::buildTree() 
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
				NodeQuantity++;
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
				addNode(atoi(pch), (int)fin.tellp() - line.length() - 1, root,1);
				NodeQuantity++;
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
void Base::addNode(int licenseNumber, int bitNumber, Base* current, int treeLevel)
{
	Derived* currentPointer = (Derived*)current;
	if (licenseNumber < currentPointer->getLicenseNumber())
	{
		if (currentPointer->getLeftSon() == NULL)
		{
			currentPointer->setLeftSon(new Derived(licenseNumber, bitNumber, currentPointer, 0, 0,treeLevel));
			LastAddedNode = currentPointer->getLeftSon();
			rebalance();
		}
		else
		{
			addNode(licenseNumber, bitNumber, currentPointer->getLeftSon(), treeLevel + 1);
		}
	}
	else
	{
		if (currentPointer->getRightSon() == NULL)
		{
			currentPointer->setRightSon(new Derived(licenseNumber, bitNumber, currentPointer, 0, 0));
			LastAddedNode = currentPointer->getRightSon();
			rebalance();
		}
		else
		{
			addNode(licenseNumber, bitNumber, currentPointer->getRightSon(), treeLevel + 1);
		}
	}
}
int Base::whatTurn(Base* reference, Base* current) 
{
	Derived* referenceNode = (Derived*)reference;
	Derived* currentNode = (Derived*)current;
	if ((Derived*)referenceNode->getLeftSon() != NULL && currentNode == ((Derived*)referenceNode->getLeftSon())->getLeftSon())
	{
		return 2; // правый поворот
	}
	else if ((Derived*)referenceNode->getRightSon() && currentNode == ((Derived*)referenceNode->getRightSon())->getRightSon())
	{
		return 1; // левый поворот
	}
	else if ((Derived*)referenceNode->getLeftSon() && currentNode == ((Derived*)referenceNode->getLeftSon())->getRightSon())
	{
		return 3; // двойной поворот LR
	}
	else if ((Derived*)referenceNode->getRightSon() && currentNode == ((Derived*)referenceNode->getRightSon())->getLeftSon())
	{
		return 4; // двойной поворот RL
	}
	whatTurn(referenceNode, currentNode->getParent());
}
Base* Base::findReferenceNode(Base* currentNode) 
{
	if (currentNode == NULL) { return NULL; }
	Derived* current = (Derived*)currentNode;
	if (abs(current->getBalance()) > 1) 
	{
		return current;
	}
	findReferenceNode(current->getParent());
}
void Base::rebalance()
{
	//addNode(license, bit, currentNode);
	newBalacne(root);
	Base* referenceNode = findReferenceNode(LastAddedNode);
	if (referenceNode) 
	{
		switch (whatTurn(referenceNode, LastAddedNode))
		{
		case 1:
			TurnLeft(referenceNode);
			break;

		case 2:
			TurnRight(referenceNode);
			break;

		case 3:
			TurnLR(referenceNode);
			break;

		case 4:
			TurnRL(referenceNode);
			break;
		}
	}
}
int Base::countLevels(int start,Base* current) 
{
	Derived* currentNode = (Derived*)current;
	if (currentNode == NULL) { return start; }
	int x = countLevels(start + 1, currentNode->getLeftSon());
	int y = countLevels(start + 1, currentNode->getRightSon());
	return (x > y) ? x : y;
}
void Base::newBalacne(Base* current) 
{
	if (current == NULL) { return; }
	Derived* currentNode = (Derived*)current;
	int h_right = countLevels(0, currentNode->getRightSon());
	int h_left = countLevels(0, currentNode->getLeftSon());
	currentNode->setBalance(h_right - h_left);
	newBalacne(currentNode->getRightSon());
	newBalacne(currentNode->getLeftSon());
}
void Base::TurnLeft(Base* reference) 
{
	RotateQuantity++;
	if (reference == NULL) { return; }
	Derived* referenceNode = (Derived*)reference;
	Base* buf = referenceNode->getRightSon();
	Derived* buffer = (Derived*)referenceNode->getRightSon();
	referenceNode->setRightSon(buffer->getLeftSon());
	if (buffer->getLeftSon()) 
	{
		((Derived*)buffer->getLeftSon())->setParent(referenceNode);
		buffer->setParent(referenceNode->getParent());
	}
	if (referenceNode == root) 
	{
		root = buffer;
		buffer->setParent(0);
	}
	else 
	{
		if (reference == ((Derived*)referenceNode->getParent())->getLeftSon())
		{
			((Derived*)referenceNode->getParent())->setLeftSon(buf);
			buffer->setParent((Derived*)referenceNode->getParent());
		}
		else if (reference == ((Derived*)referenceNode->getParent())->getRightSon())
		{
			((Derived*)referenceNode->getParent())->setRightSon(buf);
			buffer->setParent((Derived*)referenceNode->getParent());
		}
	}
	buffer->setLeftSon(reference);
	referenceNode->setParent(buf);
}
void Base::TurnRight(Base* refernce) 
{
	RotateQuantity++;
	if (refernce == NULL) { return; }
	Derived* refernceNode = (Derived*)refernce;
	Base* buf = refernceNode->getLeftSon();
	Derived* buffer = (Derived*)buf;
	refernceNode->setLeftSon(buffer->getRightSon());
	if (buffer->getRightSon()) 
	{
		((Derived*)buffer->getRightSon())->setParent(refernceNode);
		buffer->setParent(refernceNode->getParent());
	}
	if (refernceNode == root) 
	{
		root = buffer;
		buffer->setParent(0);
	}
	else if (refernce == ((Derived*)refernceNode->getParent())->getRightSon()) 
	{
		((Derived*)refernceNode->getParent())->setRightSon(buf);
		buffer->setParent((Derived*)refernceNode->getParent());
	}
	else if (refernce == ((Derived*)refernceNode->getParent())->getLeftSon())
	{
		((Derived*)refernceNode->getParent())->setLeftSon(buf);
		buffer->setParent((Derived*)refernceNode->getParent());
	}
	buffer->setRightSon(refernce);
	refernceNode->setParent(buf);
}
void Base::TurnLR(Base* reference) 
{
	Derived* referenceNode = (Derived*)reference;
	TurnLeft(referenceNode->getLeftSon());
	TurnRight(reference);
}
void Base::TurnRL(Base* reference) 
{
	Derived* referenceNode = (Derived*)reference;
	TurnRight(referenceNode->getRightSon());
	TurnLeft(reference);
}
void Base::FindLine(int license)
{
	CompareQuantity = 0;
	Base* requiredNode = FindNode(license, root);
	string line;
	if (requiredNode)
	{
		fstream fin;
		fin.open(path, ios_base::in, ios::binary);
		if (fin.is_open())
		{
			fin.seekg(((Derived*)requiredNode)->getBitNumber(), ios::beg);
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
		cout << "\nThere no such licnese";
	}
	cout << "\n" << line<<"\n";
}
Base* Base::FindNode(int license, Base* current)
{
	Derived* currentPointer = (Derived*)current;
	if (current == NULL) { return 0; }
	if (currentPointer->getLicenseNumber() == license)
	{
		CompareQuantity++;
		return currentPointer;
	}
	else if (license < currentPointer->getLicenseNumber())
	{
		CompareQuantity++;
		FindNode(license, currentPointer->getLeftSon());
	}
	else if (license > currentPointer->getLicenseNumber())
	{
		CompareQuantity++;
		FindNode(license, currentPointer->getRightSon());
	}
	//return 0;
}
void Base::FindMAX(Base* current) 
{
	if (current == NULL) { return; }
	Derived* currentNode = (Derived*)current;
	if (currentNode->getLicenseNumber() > max) 
	{
		max = currentNode->getLicenseNumber();
	}
	FindMAX(currentNode->getLeftSon());
	FindMAX(currentNode->getRightSon());
}
void Base::deleteNode(int licenseNumber) 
{
	Base* trgt = FindNode(licenseNumber, root);
	Derived* target = (Derived*)trgt;
	if (target)
	{
		if (target->getLeftSon() && target->getRightSon()) // есть оба
		{
			FindMAX(target->getLeftSon());
			Base* mx = FindNode(max, root);
			Derived* m = (Derived*)mx;
			if (m)
			{
				int x = m->getLicenseNumber();
				int y = m->getBitNumber();
				deleteNode(max);
				target->setLicenseNumber(x);
				target->setBitNumber(y);
				return;
			}
		}
		else if (target->getLeftSon()) // есть только левый
		{
			if (target == ((Derived*)target->getParent())->getLeftSon())
			{
				((Derived*)target->getParent())->setLeftSon(target->getLeftSon());
			}
			else
			{
				((Derived*)target->getParent())->setRightSon(target->getLeftSon());
			}
		}
		else if (target->getRightSon()) // есть только правый
		{
			if (target == ((Derived*)target->getParent())->getLeftSon())
			{
				((Derived*)target->getParent())->setLeftSon(target->getRightSon());
			}
			else
			{
				((Derived*)target->getParent())->setLeftSon(target->getRightSon());
			}
			NodeQuantity--;
		}
		else // нет наследников
		{
			if (target == ((Derived*)target->getParent())->getLeftSon()) {
				((Derived*)target->getParent())->setLeftSon(NULL);
			}
			else {
				((Derived*)target->getParent())->setRightSon(NULL);
			}
			NodeQuantity--;
		}
	}
	else
	{
		cout << "\nThere is no such node\n";
	}
}
Base* Base::FindLeaf(Base* current) 
{
	Derived* currentNode = (Derived*)current;
	if (!currentNode->getRightSon() && !currentNode->getLeftSon()) 
	{
		return current;
	}
	int h_right = countLevels(0, currentNode->getRightSon());
	int h_left = countLevels(0, currentNode->getLeftSon());
	if (h_right > h_left) 
	{
		FindLeaf(currentNode->getRightSon());
	}
	else 
	{
		FindLeaf(currentNode->getLeftSon());
	}
}
void Base::deleteAndRebalance(int license) 
{
	Base* trgt = FindNode(license,root);
	Derived* target = (Derived*)trgt;
	int h_right = countLevels(0,target->getRightSon());
	int h_left = countLevels(0,target->getLeftSon());
	if (!target->getRightSon() && !target->getLeftSon()) 
	{
		if (target == ((Derived*)target->getParent())->getLeftSon()) 
		{
			if (((Derived*)target->getParent())->getRightSon()) 
			{
				LastAddedNode = ((Derived*)target->getParent())->getRightSon();
			}
			else 
			{
				LastAddedNode = target->getParent();
			}
		}
		else if (target == ((Derived*)target->getParent())->getRightSon())
		{
			if (((Derived*)target->getParent())->getLeftSon())
			{
				LastAddedNode = ((Derived*)target->getParent())->getLeftSon();
			}
			else
			{
				LastAddedNode = target->getParent();
			}
		}
	}
	if (h_right > h_left) 
	{
		if (target->getRightSon())
		{
			LastAddedNode = FindLeaf(target->getRightSon());
		}
	}
	else 
	{
		if (target->getLeftSon())
		{
			LastAddedNode = FindLeaf(target->getLeftSon());
		}
	}
	//LastAddedNode = FindNode(99862, root);
	deleteNode(license);
	rebalance();
}
string setTabs(int level)
{
	string k = "";
	for (int i = 0; i < level; i++)
	{
		k += "	";
	}
	return k;
}

void Base::printTree(int treeLevel,Base* current) 
{
	if (current == NULL) { return; }
	Derived* currentNode = (Derived*)current;
	currentNode->setTreeLevel(treeLevel);
	printTree(treeLevel + 1,currentNode->getRightSon());
	if ((Derived*)currentNode->getParent() && currentNode == ((Derived*)currentNode->getParent())->getLeftSon())
	{
		cout << setTabs(currentNode->getTreeLevel()) <<"\\"<< "\n" << setTabs(currentNode->getTreeLevel()) <<" "<<currentNode->getLicenseNumber() <<"\n";
	}
	else if ((Derived*)currentNode->getParent() && currentNode == ((Derived*)currentNode->getParent())->getRightSon())
	{
		cout << setTabs(currentNode->getTreeLevel()) << " " << currentNode->getLicenseNumber() << "\n" << setTabs(currentNode->getTreeLevel()) << "/\n";
	}
	else 
	{
		cout << setTabs(currentNode->getTreeLevel()) << currentNode->getLicenseNumber() << "\n";
	}
	printTree(treeLevel + 1,currentNode->getLeftSon());
}
int Base::execute() 
{
	buildTree();
	auto start = chrono::high_resolution_clock::now();
	FindLine(4374496);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
	//cout << "Search time is: " << duration.count() << " nanoseconds\n";
	Derived* root1 = (Derived*)root;
	//printTree(0,root);
	cout << "\n";
	//deleteAndRebalance(40583);
	//printTree(0, root);
	cout << "Search time is: " << duration.count() << " nanoseconds\n";
	cout << "\nRotate quantity is: " << RotateQuantity <<"\nNode quantity is: " <<NodeQuantity <<"\nCompare quantity is: " << CompareQuantity;
	return 0;
}
Base* Base::root = NULL;
Base* Base::LastAddedNode = NULL;
int Base::max = 0;
int Base::RotateQuantity = 0;
int Base::NodeQuantity = 0;
int Base::CompareQuantity = 0;