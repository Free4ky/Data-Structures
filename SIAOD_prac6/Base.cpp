#include"Derived.h"
#include"Base.h"

Base::Base(Base* parent) 
{
	setField(parent);
	setParent(parent);
	//setVisited(false);
}

void Base::setParent(Base* parent)
{
	this->parent = parent;
	if (parent) 
	{
		parent->children.push_back(this);
	}
}

void Base::setField(Base* parent) 
{
	this->field = new int* [chess_size];
	for (int i = 0; i < chess_size; i++)
	{
		field[i] = new int[chess_size];
	}
	if (parent) 
	{
		for (int i = 0; i < chess_size; i++)
		{
			for (int j = 0; j < chess_size; j++)
			{
				field[i][j] = parent->field[i][j];
			}
		}
	}
	else 
	{
		for (int i = 0; i < chess_size; i++)
		{
			for (int j = 0; j < chess_size; j++)
			{
				field[i][j] = -1;
			}
		}
	}
}

void Base::buildTree(Base* current, int treeLevel) // treeLevel отвечает за текущую координату по y, j за координату по x
{
	if (treeLevel > chess_size - 1) { return; }
	Derived* child;
	if (current->children.empty()) 
	{
		for (int j = 0; j < chess_size; j++)
		{
			if ((current->field[treeLevel][j] == -1)) 
			{
				child = new Derived(current);
				setImPossibleCords(child, j, treeLevel);
			}
		}
	}

	if (current->children.empty()) { return; }

	current->children_iterator = current->children.begin();
	while (current->children_iterator != current->children.end())
	{
		(*(current->children_iterator))->buildTree(*(current->children_iterator), treeLevel + 1);
		current->children_iterator++;
	}
}

void Base::setImPossibleCords(Base* current, int x, int y)
{
	//установка 1 в возможную клетку
	current->field[y][x] = 1;
	// простановка невозможных горизонталей и вертикалей
	for (int i = 0; i < chess_size; i++) 
	{
		for (int j = 0; j < chess_size; j++) 
		{
			if ((i == y && j != x) || (i != y && j == x)) 
			{
				current->field[i][j] = 0;
			}
		}
	}
	// Простановка невозможных диагоналей
	for (int i = 0; i < chess_size; i++) 
	{
		if ((x - y + i >= 0) && (x - y + i < chess_size))
		{
			if (current->field[i][x - y + i] != 1) 
			{
				current->field[i][x - y + i] = 0;
			}
		}
		if ((x + y - i < chess_size) && (x + y - i >= 0)) 
		{
			if (current->field[i][x + y - i] != 1) 
			{
				current->field[i][x + y - i] = 0;
			}
		}
	}
}

void Base::pritMatrix(Base* current) 
{
	int** matrix = current->field;
	int x = 0;
	for (int i = 0; i < chess_size; i++) {
		for (int j = 0; j < chess_size; j++) {
			cout << matrix[i][j] << "\t";
			x++;
			if (x == chess_size) {
				cout << "\n";
				x = 0;
			}
		}
	}
	cout << "\n";
}

bool Base::CheckSolution() 
{
	int queen_count = 0;
	for (int i = 0; i < chess_size; i++) 
	{
		for (int j = 0; j < chess_size; j++) 
		{
			if (field[i][j] == 1) 
			{
				queen_count++;
			}
		}
	}
	if (queen_count == chess_size) 
	{
		return true;
	}
	return false;
}

void Base::FindLeaf(Base* current) 
{
	if (current->children.empty())
	{
		// проверка решения
		if ((current->CheckSolution()))
		{
			AllSolutions.push_back(current);
		}
	}
	else 
	{
		// ищем дальше
		current->children_iterator = current->children.begin();
		while (current->children_iterator != current->children.end()) 
		{
			(*(current->children_iterator))->FindLeaf(*(current->children_iterator));
			current->children_iterator++;
		}
	}
}

vector<Base*>Base::getChildren() { return this->children; }

//void Base::setVisited(bool b)
//{
//	for (int i = 0; i < chess_size; i++) 
//	{
//		visited[i] = b;
//	}
//}


int Base::execute() 
{
	pritMatrix(this);
	buildTree(this);
	FindLeaf(this);

	vector<Base*>::iterator AllSolutions_iterator;

	AllSolutions_iterator = AllSolutions.begin();
	cout << "Example of solution:\n";
	(*AllSolutions_iterator)->pritMatrix((*AllSolutions_iterator));

	AllSolutions_iterator++;

	cout << "Example of solution:\n";
	(*AllSolutions_iterator)->pritMatrix((*AllSolutions_iterator));

	AllSolutions_iterator+=10;

	cout << "Example of solution:\n";
	(*AllSolutions_iterator)->pritMatrix((*AllSolutions_iterator));

	AllSolutions_iterator += 80;

	cout << "Example of solution:\n";
	(*AllSolutions_iterator)->pritMatrix((*AllSolutions_iterator));

	cout <<"Number of solutions: "<<AllSolutions.size()<<"\n";

	return 0;
}
vector<Base*> Base::AllSolutions;