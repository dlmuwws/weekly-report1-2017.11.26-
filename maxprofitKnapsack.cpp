// maxprofitKnapsack.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include "maxHeap.h"
#include "mergeSort.h"

using namespace std;

struct bbNode
{
	
	bbNode* parent;        
	bool leftChild;        

						   
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	}

};

struct heapNode
{
	
	bbNode* liveNode;
	double upperProfit;
	double profit;
	double weight;
	int upperWeight;    
	int level;          

						
	heapNode() {};

	heapNode(bbNode* theLiveNode, double theUpperProfit, double theProfit,
		double theWeight, int theLevel)
	{
		liveNode = theLiveNode;
		upperProfit = theUpperProfit;
		profit = theProfit;
		weight = theWeight;
		level = theLevel;
	}

	int  operator < (const heapNode right)
	{
		return upperProfit < right.upperProfit;
	}

	
	operator double() { return upperProfit; }
};


struct element
{
	
	int id;   
	double profitDensity;

	element() {}

	element(int theID, double theProfitDensity)
	{
		id = theID;
		profitDensity = theProfitDensity;
	}

	operator double() { return profitDensity; }
};


double capacity;
int numberOfObjects;
double *weight;
double *profit;
double weightOfCurrentPacking;
double profitFromCurrentPacking;
int *bestPackingSoFar;
maxHeap<heapNode> liveNodeMaxHeap;

double maxProfitBBKnapsack();
void addLiveNode(double, double, double, int, bbNode*, bool);
double profitBound(int);

double knapsack(double *theProfit, double *theWeight, int theNumberOfObjects,
	double theCapacity, int *bestPacking)
{
	capacity = theCapacity;
	numberOfObjects = theNumberOfObjects;

	
	element *q = new element[numberOfObjects];


	double weightSum = 0.0;         
	double profitSum = 0.0;         
	for (int i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, theProfit[i] / theWeight[i]);
		profitSum += theProfit[i];
		weightSum += theWeight[i];
	}

	if (weightSum <= capacity)   // all objects fit
	{
		fill(bestPacking + 1, bestPacking + numberOfObjects + 1, 1);
		return profitSum;
	}

	// sort into increasing density order
	mergeSort(q, numberOfObjects);


	profit = new double[numberOfObjects + 1];
	weight = new double[numberOfObjects + 1];
	for (int i = 1; i <= numberOfObjects; i++)
	{
		profit[i] = theProfit[q[numberOfObjects - i].id];
		weight[i] = theWeight[q[numberOfObjects - i].id];
	}
	weightOfCurrentPacking = 0.0;
	profitFromCurrentPacking = 0.0;
	bestPackingSoFar = new int[numberOfObjects + 1];

	
	double maxProfit = maxProfitBBKnapsack();
	for (int i = 1; i <= numberOfObjects; i++)
		bestPacking[q[numberOfObjects - i].id] = bestPackingSoFar[i];
	return maxProfit;
}

double maxProfitBBKnapsack()
{
	bbNode* eNode = NULL;
	int eNodeLevel = 1;
	double maxProfitSoFar = 0.0;
	double maxPossibleProfitInSubtree = profitBound(1);

	
	while (eNodeLevel != numberOfObjects + 1)
	{
		double weightOfLeftChild = weightOfCurrentPacking
			+ weight[eNodeLevel];
		if (weightOfLeftChild <= capacity)
		{
			if (profitFromCurrentPacking + profit[eNodeLevel]
		> maxProfitSoFar)
				maxProfitSoFar = profitFromCurrentPacking
				+ profit[eNodeLevel];
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking + profit[eNodeLevel],
				weightOfCurrentPacking + weight[eNodeLevel],
				eNodeLevel + 1, eNode, true);
		}
		maxPossibleProfitInSubtree = profitBound(eNodeLevel + 1);

		
		if (maxPossibleProfitInSubtree >= maxProfitSoFar)
			
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking,
				weightOfCurrentPacking,
				eNodeLevel + 1, eNode, false);

		
		heapNode nextENode = liveNodeMaxHeap.top();
		liveNodeMaxHeap.pop();
		eNode = nextENode.liveNode;
		weightOfCurrentPacking = nextENode.weight;
		profitFromCurrentPacking = nextENode.profit;
		maxPossibleProfitInSubtree = nextENode.upperProfit;
		eNodeLevel = nextENode.level;
	}

	
	for (int j = numberOfObjects; j > 0; j--)
	{
		bestPackingSoFar[j] = (eNode->leftChild) ? 1 : 0;
		eNode = eNode->parent;
	}

	return profitFromCurrentPacking;
}

void addLiveNode(double upperProfit, double theProfit,
	double theWeight, int theLevel, bbNode* theParent,
	bool leftChild)
{
	bbNode* b = new bbNode(theParent, leftChild);

	
	liveNodeMaxHeap.push(heapNode(b, upperProfit, theProfit,
		theWeight, theLevel));
}

double profitBound(int currentLevel)
{
	double remainingCapacity = capacity - weightOfCurrentPacking;
	double profitBound = profitFromCurrentPacking;

	
	while (currentLevel <= numberOfObjects &&
		weight[currentLevel] <= remainingCapacity)
	{
		remainingCapacity -= weight[currentLevel];
		profitBound += profit[currentLevel];
		currentLevel++;
	}

	
	if (currentLevel <= numberOfObjects)
		profitBound += profit[currentLevel] / weight[currentLevel]
		* remainingCapacity;
	return profitBound;
}

void main(void)
{
	double p[] = { 0, 6, 3, 5, 4, 6 };
	double w[] = { 0, 2, 2, 6, 5, 4 };
	int n = 5;
	int c = 10;
	int *bestx = new int[n + 1];
	cout << "Optimal value is " << knapsack(p, w, n, c, bestx) << endl;
	cout << "Packing vector is ";
	copy(bestx + 1, bestx + n + 1, ostream_iterator<int>(cout, "  "));
	cout << endl;
	system("pause");
}