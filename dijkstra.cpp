#include <iostream>  
#include <vector>  
#include <stack>  
#include<iomanip>
using namespace std;


int map[][5] = {                     
	{ 0, 10, INT_MAX, INT_MAX, 5 },
	{ INT_MAX, 0, 1, INT_MAX, 2 },
	{ INT_MAX, INT_MAX, 0, 4, INT_MAX },
	{ 7, INT_MAX, 6, 0, INT_MAX },
	{ INT_MAX, 3, 9, 2, 0 }
};

void Dijkstra(
	const int numOfVertex,    
	const int startVertex,    
	int(map)[][5],         
	int *distance,           
	int *prevVertex          
)
{
	vector<bool> isInS;                   
	isInS.reserve(0);
	isInS.assign(numOfVertex, false);    

										
	for (int i = 0; i < numOfVertex; ++i)
	{
		distance[i] = map[startVertex][i];
		if (map[startVertex][i] < INT_MAX)
			prevVertex[i] = startVertex;
		else
			prevVertex[i] = -1;        
	}
	prevVertex[startVertex] = -1;

	
	isInS[startVertex] = true;          


	int u = startVertex;

	for (int i = 1; i < numOfVertex; i++)      
	{

		
		int nextVertex = u;
		int tempDistance = INT_MAX;
		for (int j = 0; j < numOfVertex; ++j)
		{
			if ((isInS[j] == false) && (distance[j] < tempDistance)) 
			{
				nextVertex = j;
				tempDistance = distance[j];
			}
		}
		isInS[nextVertex] = true;  
		u = nextVertex; 


					  
		for (int j = 0; j < numOfVertex; j++)
		{
			if (isInS[j] == false && map[u][j] < INT_MAX)
			{
				int temp = distance[u] + map[u][j];
				if (temp < distance[j])
				{
					distance[j] = temp;
					prevVertex[j] = u;
				}
			}
		}
	}



}


int main(int argc, const char * argv[])
{
	int distance[5];
	int preVertex[5];

	for (int i = 0; i < 5; ++i)
	{
		Dijkstra(5, i, map, distance, preVertex);
		for (int j = 0; j < 5; ++j)
		{
			int index = j;
			stack<int > trace;
			while (preVertex[index] != -1) {
				trace.push(preVertex[index]);
				index = preVertex[index];
			}

			cout << "Route ";
			while (!trace.empty()) {
				cout << trace.top() <<" ";
				trace.pop();
			}
			cout << j;
			cout << " Distance " << distance[j] << endl;


		}
	}

	return 0;