
#include <iostream>
#include <string.h>

#define MAX_NUM 50

using namespace std;

void loadM(int *M1, char *filename, int col)
{
	FILE *fp;
	if((fp = fopen(filename, "r")) == NULL)
	{
		cout << "read File " << filename << "Error" << endl;
		exit(1);
	}
	int number = 0;
	char c;
	int i = 0, j = 0;
	while((c = fgetc(fp)) != EOF)
	{
		if(c == '\t')
		{
			M1[i * col + j] = number;
			number = 0;
			j++;
		}
		else if(c == '\n')
		{
			cout << " number is " << number << endl;
			M1[i * col + j] = number;
			i++; j = 0;
			number = 0;
		}
		else{
			if(c <= '9' && c >= '0' )
				number = number * 10 + c -48;
		}

	}
}

void print(const int *M, int col)
{
	int i, j;
	for( i = 0; i < col; i++)
	{
		for(j = 0; j < col; j++)
			cout << M[i * col + j] << "\t" ;
		cout << endl;
	}
}

void Floyd(int *MFloyd, int *M1, int col)
{
	int i, j, k;
	for(i = 0; i < col; i++)
		for(j = 0; j < col; j++)
			MFloyd[i*col+j] = M1[i*col+j];
	for(k = 0; k < col; k++)
	{
		MFloyd[k*col+k] = 0;
//		M2Floyd[k*col+k] = 0;
	}
	for(k = 0; k < col; k++)
		for(i = 0; i < col; i++)
			for(j = 0; j < col; j++)
				if(MFloyd[i*col+k] + MFloyd[k*col+j] < MFloyd[i*col+j])
				{
					MFloyd[i*col+j] = MFloyd[i*col+k] + MFloyd[k*col+j];
//					M2Floyd[i*col+j] = M2Floyd[i*col+k] + M2Floyd[k*col+j];
				}
}

int BranchAndBound(int *M1Floyd, int *M2Floyd, int *M1, int *M2, int col)
{
	int i;

	int depth = 0;
	int stack[MAX_NUM] = {0};
	int visited[MAX_NUM] = {0};
	int currentDist = 0;
	int currentCost = 0;
	int distBound = 9999;
	int costBound = 1500;

	int bestPath[MAX_NUM];

	int bestLength;
	int minimumCost;
	int shortestDist;

	stack[depth] = 0;
	stack[depth+1] = 0;
	visited[0] = 1;

	while(depth >= 0)
	{

		int cur, next;
		cur = stack[depth];
		next = stack[depth+1];


		for(i = next+1; i < col; i++)
		{
			if(M1[cur*col+i] == 9999)
			{
				continue;
			}
			if(visited[i] == 1)
			{
				continue;
			}
			if((currentDist + M1Floyd[cur*col+49] >= distBound) || (currentCost + M2Floyd[cur*col+49] >= costBound))
			{
				continue;
			}
			if(i < col)
			{
				break;
			}
		}

		if(i == col)
		{
			depth--;
			currentDist -= M1[stack[depth] * col + stack[depth+1]];
			currentCost -= M2[stack[depth] * col + stack[depth+1]];
			visited[stack[depth+1]] = 0;
//			cout << "get here" << endl;
		}else{
			currentDist += M1[stack[depth] * col + i];
			currentCost += M2[stack[depth] * col + i];

			depth++;
			stack[depth] = i;
			stack[depth + 1] = 0;
			visited[i] = 1;
			if(i == 49)
			{
				int j;
				for(j = 0; j <= depth; j++)
				{
					bestPath[j] = stack[j];
				}
				bestLength = depth;
				shortestDist = currentDist;
				minimumCost = currentCost;
				cout << "minimumCost is " << minimumCost << endl;
				cout << "minimumPath is " ;
				for(j = 0; j <= depth; j++)
				{
					cout << bestPath[j] << "->";
				}
				cout << endl;

				distBound = currentDist;
				cout << "CurrentDist is " << distBound << endl;

//				cout << "DIST BOUND = " << distBound << endl;
				depth--;
				currentDist -= M1[stack[depth]*col+stack[depth+1]];
				currentCost -= M2[stack[depth]*col+stack[depth+1]];
				visited[stack[depth+1]] = 0;
				depth--;
				currentDist -= M1[stack[depth]*col+stack[depth+1]];
				currentCost -= M2[stack[depth]*col+stack[depth+1]];
				visited[stack[depth+1]] = 0;
			}
		}
	}


	return shortestDist;
}

void initM2(int *M2, int *M1, int col)
{
	int i, j;
	for(i = 0; i < col; i++)
	{
		for (j = 0; j < col; j++)
			if(M1[i*col+j] == 9999)
				M2[i*col+j] = 9999;
	}
}

int main()
{
	int M1[MAX_NUM][MAX_NUM];
	int M2[MAX_NUM][MAX_NUM];
	loadM(M1[0], "/u1/lxp/assignment2/m1.txt", MAX_NUM);
	loadM(M2[0], "/u1/lxp/assignment2/m2.txt", MAX_NUM);

	print(M1[0], MAX_NUM);

	initM2(M2[0], M1[0], MAX_NUM);   //get some correction of the data
//	print(M2[0], MAX_NUM);
	int M1Floyd[MAX_NUM][MAX_NUM];
	int M2Floyd[MAX_NUM][MAX_NUM];

//	for(int i = 0; i < MAX_NUM; i++)
//		for(int j = 0; j < MAX_NUM; j++)
//			M2Floyd[i][j] = M2[i][j];

	Floyd(M1Floyd[0], M1[0], MAX_NUM);
	Floyd(M2Floyd[0], M2[0], MAX_NUM);

	/*print(M1Floyd[0], MAX_NUM);
	print(M2Floyd[0], MAX_NUM);*/

	int ShortestDist = BranchAndBound(M1Floyd[0], M2Floyd[0], M1[0], M2[0], MAX_NUM);
	cout << ShortestDist << endl;
}
