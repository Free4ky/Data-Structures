#include"Base.h"
#include"Derived.h"
#include <iostream>

int main()
{
	Base* root = new Base();
	root->execute();
}
