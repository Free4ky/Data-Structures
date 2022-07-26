#include "Base.h"
#include "Derived.h"
Base::Base() 
{
}
void Base::createAlphabet() 
{
	int x;
	char b;
	for (int i = 0; i < input.length(); i++) 
	{
		x = isUniq(input[i]);
		if (x == -1) 
		{
			alphabet.push_back(new Letters(input[i]));
		}
		else 
		{
			alphabet[x]->quantity++;
		}
	}
}
int Base::isUniq(char letter)
{
	for (int i = 0; i < alphabet.size(); i++) 
	{
		if (alphabet[i]->letter == letter)
		{
			return i;
		}
	}
	return -1;
}
void Base::out(int cs) 
{
	switch (cs)
	{
	case 1:
		for (int i = 0; i < alphabet.size(); i++)
		{
			cout << alphabet[i]->letter << "\t" << alphabet[i]->quantity << '\n';
		}
		cout << '\n';
		break;
	case 2:
		for (int i = 0; i < cods.size(); i++)
		{
			cout << cods[i]->letter << "\t" << cods[i]->code << '\n';
		}
		cout << '\n';
	}
}
void Base::Sort() 
{
	sort(alphabet.begin(), alphabet.end(), [](const Letters* a, const Letters* b)
	{
		return a->quantity > b->quantity;
	});
}
char tolower_rus(char c)
{
	return  tolower(c,std::locale("Rus"));
}
void Base::execute() 
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Input line\n";
	getline(cin, input);
	transform(input.begin(), input.end(), input.begin(), tolower_rus);
	cout << input<<'\n';
	createAlphabet();
	Sort();
	out(1);
	Base* root = new Derived(0);
	buildTree(root);
	FindLeaf(root);
	out(2);
	decode();
}
void Base::devide_vec(Base* current) 
{
	Derived* c = dc current;
	int left_sum = 0;
	int right_sum = 0;
	if (c->getParent() == 0) // корневой объект
	{
		for (int i = 0; i < alphabet.size(); i++)
		{
			if (left_sum <= right_sum)
			{
				c->add(alphabet[i], 1);
				left_sum += alphabet[i]->quantity;
			}
			else
			{
				c->add(alphabet[i], 2);
				right_sum += alphabet[i]->quantity;
			}
		}
	}
	else 
	{
		vector<Letters*> cr = c->getVec(1);
		for (int i = 0; i < cr.size(); i++)
		{
			if (left_sum <= right_sum)
			{
				c->add(cr[i], 1);
				left_sum += cr[i]->quantity;
			}
			else
			{
				c->add(cr[i], 2);
				right_sum += cr[i]->quantity;
			}
		}
	}
}
void Base::buildTree(Base* now_ptr) 
{
	if (((dc now_ptr)->getVec(1).size() <= 1) && ((dc now_ptr)->getParent() != 0)) { return; }
	now_ptr->devide_vec(now_ptr);
	Base* left_child = new Derived(0, now_ptr);
	(dc now_ptr)->setLeftSon(left_child);

	left_child->buildTree(left_child);

	Base* right_child = new Derived(1, now_ptr);
	(dc now_ptr)->setRightSon(right_child);

	right_child->buildTree(right_child);
}
void Base::FindLeaf(Base* current) 
{
	if ((dc current) == 0) { return; }
	if ((dc current)->getLeftSon() == 0 && (dc current)->getRightSon() == 0) // this is leaf
	{
		cods.push_back(new Cods(((dc current)->getVec(1))[0]->letter, (dc current)->getCode()));
	}
	else 
	{
		FindLeaf((dc current)->getRightSon());
		FindLeaf((dc current)->getLeftSon());
	}
}
char* Base::splitString(string line) 
{
	char* str = new char[line.length() + 1];
	strcpy(str, line.c_str());
	char* pch = strtok(str, " ");
	return pch;
}
void Base::decode() 
{
	char* pch;
	string code_line;
	getline(cin, code_line);
	pch = splitString(code_line);
	do 
	{
		for (int i = 0; i < cods.size(); i++) 
		{
			if (cods[i]->code == pch) 
			{
				cout << cods[i]->letter;
				break;
			}
		}
		pch = strtok(NULL, " ");
	} while (pch != NULL);
}
vector<Letters*>Base::alphabet;
vector<Cods*>Base::cods;