#include"Astar.h"
#include <iostream>
using namespace std;

int main()
{
	int graph[row_num][col_num] =
	{
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};
	Astar Test(graph);
	Test.findpath(0, 0, 4, 6,true);
	deque<point> Path = Test.Getpath();
	int size = Path.size();
	cout << "Path:" << endl;
	for (int i=0;i<size;i++)
	{
		cout << Path[i].x << "  " << Path[i].y << endl;
	}
	cout << "ok" << endl;
	system("pause");
	return 0;
}
