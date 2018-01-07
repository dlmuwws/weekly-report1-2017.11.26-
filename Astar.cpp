#include"Astar.h"
#include<math.h>
#include<algorithm>
#include<iostream>
using namespace std;

bool cmp(Astar_node a, Astar_node b)
{
	return a.getF(a.getG(),a.getH()) < b.getF(a.getG(),a.getH());
}

const int unit = 10; const int dia_unit = 14;
Astar::Astar(const int (&matrix_)[row_num][col_num]):matrix(matrix_)
{
}

//Astar::~Astar(void)
//{
//}

void Astar::found(Astar_node&current, Astar_node *newpoint)
{
	int newG = caculate_G(current, newpoint);
	if (newG < newpoint->getG())
	{
		newpoint->setG(newG);
		newpoint->set_parent(&visitedList.back());

	}

}

void Astar::unfound(Astar_node&current, Astar_node &end, Astar_node&newpoint)
{
	newpoint.setG(caculate_G(current, &newpoint));
	newpoint.set_parent(&visitedList.back());
	newpoint.setH(caculate_H(newpoint, end));
	visitingList.push_back(newpoint);

}

int Astar::caculate_G(Astar_node&current, Astar_node*newpoint)
{
	int value = (abs(newpoint->get_row() - current.get_row()) + abs(newpoint->get_col() - current.get_col())) == 2 ? dia_unit : unit;
	value += current.getG();
	return value;
}
int Astar::caculate_H(Astar_node&newpoint, Astar_node&end)
{
	int value = (abs(newpoint.get_row()-end.get_row()) + abs(newpoint.get_col()-end.get_col()));
	return value;
}

Astar_node Astar::findminimum()
{
	sort(visitingList.begin(),visitingList.end(),cmp);
	return visitingList.front();
}

bool Astar::CanReach(int row, int col)
{
	if (row>-1 && row<row_num && col>-1 && col<col_num)
	{
		return matrix[row][col] == 0;
	}
	else
	{
		return false;
	}
}
bool Astar::CanReach(Astar_node&current, int row, int col, bool allowcorner)
{
		if (!CanReach(row, col) || in_visitedlist(row, col))
		{
			return false;
		}
		if (abs(current.get_row() - row) + abs(current.get_row() - col) == 1)
		{
			return true;
		}
		else if (allowcorner)
		{
			int nRow = row - current.get_row();
			int nCol = col - current.get_col();
			return (CanReach(current.get_row() + nRow, current.get_col()) && CanReach(current.get_row(), current.get_col() + nCol));
		}
		return false;
}

Astar_node* Astar::in_visitinglist(int row, int col)             //判断在不在待访问队列
{
	auto it = find(visitingList.begin(), visitingList.end(), Astar_node(row, col));
	return it != visitingList.end() ?&(*it) : nullptr;
}

bool Astar::in_visitedlist(int row, int col)             //判断在不在访问队列
{
	auto it = find(visitedList.begin(), visitedList.end(),Astar_node(row, col));
	return it != visitedList.end();
}

vector<Astar_node>Astar::get_adj_points(Astar_node current, vector<Astar_node> &adjpoints, bool allowcorner)
{
	for (int row = current.get_row()- 1; row <= current.get_row()+ 1; ++row)
	{
		for (int col = current.get_col() - 1; col<= current.get_col() + 1; ++col)
		{
			Astar_node newpoint = Astar_node(row,col);
			if (CanReach(current,row,col,allowcorner))
			{
				adjpoints.push_back(newpoint);
			}
		}
	}
	return adjpoints;
}
void Astar::findpath(int start_X, int start_Y, int endX, int endY, bool bAllowCorner)
{
	Astar_node S_N(start_X,start_Y);
	S_N.setG(0);
	visitingList.push_back(S_N);
	while (!visitingList.empty())
	{
		Astar_node current = findminimum();
		visitingList.pop_front();
		visitedList.push_back(current);
		// 寻找周围可到的点
		vector<Astar_node> surroundArray;
		surroundArray=get_adj_points(current, surroundArray, bAllowCorner);
		vector<Astar_node>::iterator it;
		for (it = surroundArray.begin(); it != surroundArray.end(); ++it)
		{
			Astar_node*newpoint = in_visitinglist((*it).get_row(), (*it).get_col());

			if (newpoint)
			{
				found(current, newpoint);
			}
			else
			{
				unfound(current, Astar_node(endX, endY), *it);
				if ((*it) ==Astar_node(endX, endY))
				{
					Astar_node *pNodew = &visitedList.back();
					while (pNodew->get_parent())
					{
						AstarPath.push_front(point(pNodew->get_row(), pNodew->get_col()));
						pNodew = pNodew->get_parent();
					}
					cout << "find!!!!" << endl;
					break;
				}
			}
		}
	}
}
