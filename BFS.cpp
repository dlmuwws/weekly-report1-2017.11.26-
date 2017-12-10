#include"BFS.h"
#include"point.h"
#include"marked_point.h"
#include<stdio.h>
#include<queue>
#include"param.h"
#include<iostream>
using namespace std;



BFS::BFS()
{
	point*source = new point();
	point*destination = new point();
}

//void BFS::clearqueue(queue<marked_point*>&q)
//{
//	queue<marked_point*> empty;
	//swap(empty, q);
//}


vector<point*>BFS::getbestroute(point*source_,point*destination_)
{
	bool find = false;
	int time = 0;
	BFS*bfs;
	marked_point* markedsource = new marked_point(source_);
	bfs->push_ingvisitpoint(markedsource);
	markedsource->settime1(time);
	source_->setstate(1);

	list*pointlist;
	while(!ingvisitpoints.empty())
	{
		marked_point*frontpoint = ingvisitpoints.front();
		point*frontpoint_ = pointlist->getpoint(frontpoint->getindex());
		vector<point*>cangotopoints = frontpoint_->get_adjcentpoints;
		vector<pair<int, int>>time_wind_ = frontpoint_->get_time_wind;
		int size = cangotopoints.size();

		bool allmarked = true;
		for (int i = 1; i <= size; i++)
		{
			vector<pair<int, int>>time_wind_ = cangotopoints.at(i)->get_time_wind;
			pair<int, int> time_wind = cangotopoints.at(i)->get_the_time_wind_(time_wind_, time + param::flytime);
			int wind = time_wind.second;     //此时的风速
			if (wind < param::safty_wind)
			{
				if (cangotopoints.at(i)->getstate = 0)
				{
					marked_point* marked_point_ = new marked_point(cangotopoints.at(i));
					marked_point_->settime1(time);
					marked_point_->setindex(cangotopoints.at(i));
					marked_point_->setfront_point_index(frontpoint_);
					bfs->push_ingvisitpoint(marked_point_);
					cangotopoints.at(i)->setstate(1);
				}
				else
				{
					continue;
				}
			}
		}
			for (auto cango: cangotopoints)
			{
				if (cango->getstate = 0)
				{
					bool allmarked = false;                 //还有未标记的点
					break;
				}
			 }

			if (allmarked)     //如果都访问过了，把该点存入visited vector
			{
				ingvisitpoints.pop();   //删除该点
				frontpoint->settime2(time);
				bfs->push_visitedpoint(frontpoint);     //存入访问过的vector里
				frontpoint_->setstate(2);
			}
			else
			{
				int wind_ = frontpoint_->get_the_time_wind_(time_wind_, time).second;
				if (wind_<param::safty_wind)
				{
					frontpoint->settime2(time);
					ingvisitpoints.pop();
					ingvisitpoints.push(frontpoint);
				}
				else
				{
					visitedpoints.push_back(frontpoint);
					frontpoint_->setstate(2);
					ingvisitpoints.pop();
				}
			}
			time += param::flytime;

			for (auto markedpoint:visitedpoints)
			{
				point*point_ = pointlist->getpoint(markedpoint->getindex);
				if (point_->get_x = destination_->get_x&&point_->get_y = destination_->get_y)
				{
					bool find = true;
					bfs->push_bestroute(point_);
					marked_point*behind = markedpoint;
					while (behind->getfront_point_index!=source->getindex)
					{
						bfs->push_bestroute(pointlist->getpoint(behind->getfront_point_index));     //依次找到前面的点放到路径里
						behind = visitedpoints[behind->getfront_point_index];
					}
					    bfs->push_bestroute(source);
				}
			}

			if(find)
			{
				break;
			}
		}


	vector<point*>bestroute_;
	for (int i=0;i<bestroute.size();i++)
	{
		for (int j= bestroute.size()-1;j>=0;j--)
		{
			bestroute_[i] = bestroute[j];
		}
	}
//	bestroute = bestroute_;
	return bestroute_;
}

void BFS::print(vector<point*>bestroute_)
{
	for (int i = 0; i < bestroute_.size(); i++)
	{
		cout << "the  best route is found" << bestroute_[i] << endl;
	}
}
