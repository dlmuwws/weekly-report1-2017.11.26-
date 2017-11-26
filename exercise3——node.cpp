#include "node.h"
#include <iostream>
using namespace std;


node::node()
{
	this->data= 0;
	this->next= NULL;
}
void node::print()
{
	cout << data << endl;
}
