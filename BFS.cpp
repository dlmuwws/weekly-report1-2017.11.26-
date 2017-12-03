#include"stdafx.h"
#include"BFS.h"
#include"block.h"
#include<queue>

BFS::BFS()
{
	
}
void BFS::Init() {
	array<double, 12> winds = { 15,15,15,15,15,15,15,15,15,15,15,15 };
	array<array<point*, 4>, 4 > position;
	vector<point*> pointlist;
	int k = 15;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			point* newpoint = new point(i, j,winds);
			position[i][j] = newpoint;
			pointlist.push_back(newpoint);
			
		}
	}	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << pointlist[k]->getX() << "," << position[i][j]->getY() << "\t";
			k--;
		}
		cout << endl;
	}
	setworsewind(pointlist[3], 2);
	setworsewind(pointlist[4], 1);
	setworsewind(pointlist[4], 0);
	setworsewind(pointlist[6], 1);
	setworsewind(pointlist[6], 0);
	setworsewind(pointlist[8], 3);
	setworsewind(pointlist[9], 0);
	setworsewind(pointlist[9], 1);
	setworsewind(pointlist[9], 2);
	setworsewind(pointlist[9], 3);
	setworsewind(pointlist[9], 4);
	setworsewind(pointlist[9], 5);
	setworsewind(pointlist[11], 4);
	setworsewind(pointlist[14], 4);
	bfs(pointlist[5], pointlist[12], pointlist);
//	bfs(pointlist[5], pointlist[14], pointlist);
}
void BFS::setworsewind(point* curpoint,int time) {
	array<double, 12>winds = curpoint->getwind();
	winds[time] = 20;
	curpoint->setwind(winds);
}
void BFS::bfs(point*curpoint,point*endpoint, vector<point*> pointlist) {
	vector<block*>visited;
	int curtime = 0;
	block*endblock;
	block* startblock = new block(curpoint,NULL, curtime, 0);
	queue<block*> que;
	int reachedend = 0;
	que.push(startblock);
//	cout << que.front()->getpoint()->getX() << ","<<que.front()->getpoint()->getY()<<endl;
	while (!que.empty()) {
		
		block* curblock = que.front();
		vector<pair<int, int>> adjcents;
		adjcents = curblock->getpoint()->getAdjcentPoint(curblock->getpoint());
//		for (int i = 0; i < adjcents.size(); i++) {
//	cout << adjcents[i].first << "," << adjcents[i].second << endl;
//		}
	
		int allreached = 1;

		if ( !adjcents.empty()) {
			for (int i = 0; i < adjcents.size(); i++) {
				point* newpoint= curblock->getpoint()->getpoint(adjcents[i].first, adjcents[i].second, pointlist);
				array<double, 12> winds = newpoint->getwind();
				if (winds[curblock->getingtime()] <=15) {
					if (newpoint->getX()== endpoint->getX() && newpoint->getY() == endpoint->getY()) {
						endblock = new block(newpoint,curblock, curblock->getingtime() + 1,curblock->getingtime() + 1);
						reachedend = 1;
						break;										
					}
					else {
						
						if (!IsInqueue(newpoint, que)&& !IsInvisited(newpoint, visited)) {
							block* newblock = new block(newpoint,curblock, curblock->getingtime() + 1, curblock->getingtime() + 1);
							que.push(newblock);		
						}
						
					}
					
				}
			}
			for (int i = 0; i < adjcents.size(); i++) {
				point* newpoint = curblock->getpoint()->getpoint(adjcents[i].first, adjcents[i].second, pointlist);
				if(!IsInqueue(newpoint,que)&&!IsInvisited(newpoint,visited)){
					allreached = 0;
				}
				
			}
			if (allreached == 0) {
				curblock->setingtime(curblock->getingtime() + 1);
				que.push(curblock);
				que.pop();
			}
			else
			{	
				visited.push_back(curblock);
				que.pop();

			}
		}
		else
		{
			visited.push_back(curblock);
			que.pop();
		}

	}
	vector<block*> route;
/*	if ( reachedend== 1) {
		route.push_back(endblock);
		block*front = endblock->getfrontblock();
		while (front != NULL) {
			route.push_back(front);
			front = front->getfrontblock();
		}


	}*/
	/*for (int i = 0; i < route.size(); i++) {
		
		cout << route[i]->getpoint()->getX() << "," << route[i]->getpoint()->getY() << ":" << route[i]->getreachtime() << endl;
	}*/
}
int BFS::IsInqueue(point* ingpoint, queue<block*>que) {
	int  IsInqueue = 0;
	for (int i = 0; i < que.size(); i++)
	{	
		block* newblock = que.front();
		que.pop();
		if (newblock->getpoint()->getX() == ingpoint->getX() && newblock->getpoint()->getY() == ingpoint->getY()) {
			IsInqueue = 1;
			
		}
		que.push(newblock);
		
	}
	return IsInqueue;
}
int BFS::IsInvisited(point* ingpoint, vector<block*>visited) {
	int  IsInvisited = 0;
	for (int i = 0; i < visited.size(); i++)
	{
		block* newblock = visited[i];
		if (newblock->getpoint()->getX() == ingpoint->getX() && newblock->getpoint()->getY() == ingpoint->getY()) {
			IsInvisited = 1;
			
			break;
		}
	}
	return IsInvisited;
}

