// Binsort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"studentRecord.h"
#include"chain.h"

int main()
{	
	studentRecord s;
	chain<studentRecord> theChain;
	for (int i = 1; i <= 20; i++)
	{
		s.score = i / 2;
		s.name = new string(s.score, 'a');
		theChain.insert(0, s);
	}
	cout << "The unsorted chain is" << endl;
	cout << "  " << theChain << endl;
	theChain.binSort(10);
	cout << "The sorted chain is" << endl;
	cout << "  " << theChain << endl;

	system("pause");
    return 0;
}

