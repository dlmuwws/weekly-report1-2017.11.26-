// Chain.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"chain.h"


int main()
{
	chain<int> x, y;
	cout << "the initial size of x,y is" << x.size() <<" "<< y.size()<<endl;

	if (x.empty()) {
		cout << "x is empty" << endl;
	}
	else {
		cout << "x is not empty" << endl;
	}
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);

	cout << "Size of y = " << y.size() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;
	y.output(cout);
	cout << y << endl;

	int index = y.IndexOf(4);
	if (index < 0) cout << "4 not found" << endl;
	else cout << "The index of 4 is " << index << endl;

	index = y.IndexOf(7);
	if (index < 0) cout << "7 is not found" << endl;
	else cout << "The index of 7 is " << index << endl;
	cout << "Element with index 0 is " << y.get(0) << endl;

	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(0);
	cout << "Element 0 erased" << endl;
	cout << "The list is " << y << endl;

	cout << "Size of y = " << y.size() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	chain<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	system("pause");
    return 0;
}

