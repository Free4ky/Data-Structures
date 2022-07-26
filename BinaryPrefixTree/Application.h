#ifndef APPLICATION_H
#define APPLICATION_H
using namespace std;
#include "Base.h"
class Application : public Base
{
public:
	void buildTree(string);
	Application(char name = 'x', Base* parent = 0, Base* LeftSon = 0, Base* RightSon = 0);
	int execute();
};
#endif // !APPLICATION_H
