#include<vector>
#include<iomanip>
#include<string>
using namespace std;



class CPoint
{
public:
	CPoint()
	{
		m_x = 0.0;
		m_y = 0.0;
	}

	CPoint(double x, double y)
	{
		m_x = x;
		m_y = y;
	}

	double GetX() const
	{
		return m_x;
	}

	double GetY() const
	{
		return m_y;
	}
private:
	double m_x;
	double m_y;
};

class CLinearRegression
{
public:
	
	int Init(const vector< CPoint>& points)
	{
		if (points.size() == 0)
		{
			return -1;
		}

		m_points = points;
	}

	
	int Run()
	{
		
		m_a = 0;
		m_b = 0;
		double minCost = CaculateCost(m_a, m_b);

		double curCost = 0.0;
		
		for (double a = MIN_a; a< = MAX_a; a += INC)
		{
			curCost = CaculateCost(a, m_b);
			if (curCost< minCost)
			{
				m_a = a;
				minCost = curCost;
			}
		}

		
		for (double b = MIN_b; b<  MAX_b; b += INC)
		{
			curCost = CaculateCost(m_a, b);
			if (curCost< minCost)
			{
				m_b = b;
				minCost = curCost;
			}
		}
	}

	
	

private:
	
	double CaculateCost(double a, double b)
	{
		double cost = 0.0;
		double xReal = 0.0;
		double yReal = 0.0;
		double yPredict = 0.0;
		double yDef = 0.0;
		for (int i = 0; i< m_points.size(); ++i)
		{
			
			xReal = m_points[i].GetX();
			
			yReal = m_points[i].GetY();
			
			yPredict = a*xReal + b;

			yDef = yPredict - yReal;
			
			cost += (yDef*yDef);
		}
		return cost;
	}

public:
	CLinearRegression()
	{
	}

private:
	
	/*const static double MIN_a = -2768.0;
	const static double MAX_a = 2768.0;
	const static double MIN_b = -2768.0;
	const static double MAX_b = 2768.0;*/

	const static double INC = 0.5;
	
	double m_a;
	double m_b;
	vector< CPoint> m_points;
};