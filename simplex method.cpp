
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int m=6;    //变量个数
const int n=3;    //约束个数

 struct var    //变量
{
	int index;
	double data;
};

vector<double>c(m,0);                    //目标函数系数
vector<double>cb(n,0);
typedef vector<double>row;
vector<row>A;                         //系数矩阵
vector<double>b;   

vector<var*>vars;
vector<var*> varB;   //基变量
vector<var*> varN;   //非基变量

vector<row>B;          //基
vector<row>Binverse;
vector<row>	B_add;           //求Binverse的增广阵

vector<double>reduced_costs;

bool cmp1(double a, double b)
{
	return a > b;
}

//bool cmp2(double*a, double*b)
//{
//	return a < b;
//}

vector<double>get_cb(vector<var*>varB, vector<double>c)          //确定cb
{
	cout << "cb:   ";
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			if (varB[i]->index == j + 1)
			{
				cb[i] = c[j];
				cout << cb[i] << "  ";
			}
		}
	}
	return cb;
}

vector<row> get_B(vector<var*> &varB, vector<row>&A)           //确定B
{
	//row row1(n,0); row row2(n,0); row row3(n,0);
	for (int i=0;i<n;i++ )
	{
		for (int j=0;j<m;j++)
		{
			if (j == varB[i]->index-1)
			{
				B[0][i] = A[0][j];
				B[1][i] = A[1][j];
				B[2][i] = A[2][j];
			}
		}
	}    
	return B;
}

vector<row> get_Binverse(vector<row>&B)                    //求B的逆矩阵
{

	for (int i=0;i<n;i++)
	{
		for (int j= 0; j<n; j++)
		{
			B_add[i][j] = B[i][j];
		}
	}
	for (int i=0;i<n;i++)
	{
		B_add[i][i + n] = 1;
	}


	for (int i = 0; i < n; i++)
	{
		if (B_add[i][i] == 0)
		{
			for (int j = i; j < n; j++)
			{
				if (B_add[j][i] != 0)
				{
					//交换ij行
					double temp;
					for (int p = 0; p<n * 2; p++)
					{
						temp = B_add[j][p];
						B_add[j][p] = B_add[i][p];
						B_add[i][p] = temp;
					}
				}
			}
		}
		else
		{
			double yinzhi;
			for (int k = i + 1; k < n; k++)
			{
				yinzhi = -1 * B_add[k][i] / B_add[i][i];
				for (int u = 0; u < 2 * n; u++)
				{
					B_add[k][u] = B_add[k][u] + B_add[i][u] * yinzhi;
				}
			}
		}
	}

	double k;
	for (int i = 0; i<n; i++)        //左矩阵的对角线 全部 转化为  1  
	{
		k = B_add[i][i];
		for (int j = 0; j<2 * n; j++)
			B_add[i][j] = B_add[i][j] / k;
	}

	for (int i = n - 1; i>0; i--)
	{
		for (int j = 0; j<i; j++)
		{
			k = B_add[j][i];
			for (int u = 0; u<2 * n; u++)
				B_add[j][u] = B_add[j][u] - k*B_add[i][u];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Binverse[i][j] = B_add[i][j + n];
		}
	}
	cout << endl;
	cout << "the inverse matrix is:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Binverse[i][j] << ",";
		}
		cout << endl;
	}
	return Binverse;
}

double get_reduced_cost(var*&var_,vector<double>cb, vector<double>c,vector<row>&Binverse, vector<row>A)          //求某个非基变量的检验数
{
	//cout << "start" << endl;
	double reduced_cost=0;
	double z = 0;
	vector<double>cb_mti_Binverse(n,0);             //1*3
	
	for (int j=0;j<n;j++)
	{
		for (int i = 0; i < n; i++)
		{
			cb_mti_Binverse[j] += cb[i] * Binverse[i][j];
		}
	}
	for (int i=0;i<n;i++)
	{
		z += cb_mti_Binverse[i] * A[i][var_->index - 1];             
	}

	reduced_cost = z - c[var_->index - 1];
	//cout << "ok" << endl;
	return reduced_cost;
}

var* dcid_enter_var(vector<var*> &varN, vector<double>cb, vector<double>c, vector<row>Binverse, vector<row>A)         //确定进基变量
{
	var*var_=varN[0];   //进基变量
	//vector<double>reduced_costs;
	//int index;   //进基变量的下标
	//reduced_costs.clear();
	for (int i=0;i<m-n;i++)
	{
		reduced_costs.push_back(get_reduced_cost(varN[i], cb, c,Binverse, A));
	}
	cout << "reduced costs:" << endl;
	for (int i=0;i<m-n;i++)
	{
		cout << "reduced cost of var" << varN[i]->index << "  is " << reduced_costs[i] << endl;
	}
	sort(reduced_costs.begin(), reduced_costs.end(),cmp1);
	if (reduced_costs[0]>0)
	{
		for (int i = 0; i < m - n; i++)
		{
			if (get_reduced_cost(varN[i], cb, c,Binverse, A) == reduced_costs[0])
			{
				var_ = varN[i];
				break;
			}
		}
	}
	else
	{
		cout << "the current soln has been opt soln" << endl;
	}
	return var_;
}

var* dcid_leav_var(var*varE_,vector<double>b, vector<row>Binverse, vector<row>A,vector<var*> &varB)        //确定出基变量
{
	var*var_=varB[0];         //出基变量
	vector<double>b_(n,0);
	vector<double>y_(n,0);
	for (int j= 0; j<n; j++)
	{ 
		for (int i = 0; i < n; i++)
		{
			b_[j] += Binverse[j][i] * b[i];
			y_[j] += Binverse[j][i] * A[i][varE_->index-1];
		}
	}
	vector<double>ratio;
	vector<int>index;
	int q = 0;
	for (int i=0;i<n;i++)
	{
		if (y_[i]>0)
		{
			q++;
			ratio.push_back(b_[i] / y_[i]);
			index.push_back(i);
		}
	}
	if (q==0)
	{
		cout << "find unbounded soln !!!!!" << endl;
		var_ = NULL;
	}
	else
	{
		int size = ratio.size();
		if (size > 1)
		{
			for (int i = 0; i < size - 1; i++)
			{
				for (int j = i + 1; j < size; j++)
				{
					if (ratio[i] > ratio[j])
					{
						double a = ratio[i]; int b = index[i];
						ratio[i] = ratio[j]; index[i] = index[j];
						ratio[j] = a; index[j] = b;
					}
				}
			}
		}
		int p = ratio.size();
		cout << "ratio:" << endl;
		for (int i = 0; i < p; i++)
		{
			cout << ratio[i] << "  ";
		}
		var_ = varB[index[0]];
	}
	return var_;
}

vector<var*> changeB(var* var1, var*var2)             //进基出基操作,var1进基，var2出基
{
	var*var3=var2;                      //临时储存出基变量
	vector<var*>::iterator it;
	it = varB.begin();
	for (it; it != varB.end();)
	{
		if (*it == var2)
		{
			it = varB.erase(it);
		}
		else
			it++;
	}
	varB.push_back(var1);                //var1进基
	//cout <<"test:"<< varB[2]->index << endl;
	it = varN.begin();
	for (it; it != varN.end();)
	{
		if (*it == var1)
		{
			it = varN.erase(it);
		}
		else
			it++;
	}
	varN.push_back(var3);         //出基变量进入varN
	//cout << "test:" << varN[2]->index << endl;
	return varB;
}

void set_varB(vector<row>Binverse, vector<double>b)
{
	//cout << "start" << endl;
	for (int j = 0; j<n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			varB[j]->data += Binverse[j][i] * b[i];
		}
	}
	//cout << "ok" << endl;
}


 vector<var*>get_varN(vector<var*>&newvarB, vector<var*>vars)
{
	 vector<var*>newvarN;
	for (int i = 0; i<m; i++)
	{
		int k = 0;
		for (int j = 0; j<n; j++)
		{
			if (vars[i]->index == newvarB[j]->index)
			{
				k++;
			}
		}
		if (k == 0)
		{
			newvarN.push_back(vars[i]);
		}
		else
			continue;
	}
	//test:
	//cout << "newvarN2" << newvarN[1]->index<< endl;
	return newvarN;
}


bool  solve(int &d,vector<var*> &varB,vector<double>c, vector<row>A, vector<double>b, vector<var*>& varN, vector<var*> vars)
{
	bool a = true;
	while (a)
	{
		cout <<"start the " <<d<<"th" << "  iteration" << endl;
		B.clear(); B_add.clear(); Binverse.clear(); reduced_costs.clear();    //每次迭代都把上次的B和检验数等重置
		row row4; row row5; row row6;
		for (int i = 0; i<n; i++)
		{
			row4.push_back(0);
			row5.push_back(0);
			row6.push_back(0);
		}
		Binverse.push_back(row4);
		Binverse.push_back(row5);
		Binverse.push_back(row6);

		B.push_back(row4);
		B.push_back(row5);
		B.push_back(row6);
		row row7(2 * n, 0); row row8(2 * n, 0); row row9(2 * n, 0);
		B_add.push_back(row7);  	B_add.push_back(row8);  	B_add.push_back(row9);
		//B = get_B(varB, A);
		cout << "B:" << endl;
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j<n; j++)
			{
				cout << get_B(varB, A)[i][j] << "  ";
			}
			cout << endl;
		}
		cb = get_cb(varB, c);
		Binverse = get_Binverse(get_B(varB, A));
		set_varB(Binverse, b);
		cout << "varB:" << endl;
		for (int i=0;i<n;i++)
		{
			cout << varB[i]->data << "  ";
		}
		for (int i = 0; i<n; i++)
		{
			if (varB[i]->data < 0)
			{
				cout << "this is an infeasible  soln, please find a feasible initial soln " << endl;
				a = false;
				break;
			}
			else
				continue;
		}
		//if (!a)
		//{
			//cout << "infeasible soln" << endl;
			//break;
		//}
		cout << endl;
		cout << "finish the feasiblity check" << endl;
		//%%%%%%停止迭代条件 %%%%%
		int k = 0;  int f = 0;
		for (int i=0;i<m-n;i++)
		{
			if (get_reduced_cost(varN[i],cb,c,Binverse, A)<=0)
			{
				//cout << "the reduced costs of var" << varN[i]->index <<"is  "<< get_reduced_cost(varN[i], cb,c, Binverse, A) << "  " << endl;
				k++;
				if (get_reduced_cost(varN[i], cb, c, Binverse, A) == 0)
				{
					f++;
				}
			}
		}
		if (k==m-n)
		{
			if (f>0)
			{
				cout << "there exists alternative opt soln!!!!!" << endl;
			}
			else
			{
				cout << "all reduced_cost are negative:" << endl;
			}
				for (int i = 0; i < m - n; i++)
				{
					cout << "reduced cost of var" << varN[i]->index << "  is " << get_reduced_cost(varN[i], cb, c, Binverse, A) << endl;
				}
				cout << "having got the opt soln, stop iteration" << endl;
				cout << "the opt soln is:" << endl;
				for (int i = 0; i < n; i++)
				{
					cout << "var" << varB[i]->index << " = " << varB[i]->data << "  ";
				}
			a = false;
			break;
		}
		//if haven't got the opt soln:
		var*var1 = dcid_enter_var(varN, cb, c,Binverse, A);
		cout << "var" << var1->index << " enter the basis" << endl;
		var*var2 = dcid_leav_var(var1, b, Binverse, A, varB);
		if (var2==NULL)
		{
			a = false;
			break;
		}
		cout << endl;
		cout << "var" << var2->index << " leave the basis" << endl;
		for (int i=0;i<n;i++)
		{
			varB[i]->data = 0;
		}

		vector<var*>newvarB=changeB(var1, var2);             //得到新的基变量
		cout << "the new varB:" << endl;
		for (int i=0;i<n;i++)
		{
			cout << "varB" << i + 1 << ":" << newvarB[i]->index << endl;
		}
		vector<var*>newvarN = get_varN(newvarB, vars);
		cout << "the new varN:" << endl;
		for (int i = 0; i<m-n; i++)
		{
			cout << "varN " << i + 1 << ":" << newvarN[i]->index << endl;
		}
		cout << "finish the " << d << "th" << "  iteration" << endl;
		int h=d+1;
		a=solve(h,newvarB,c,A,b,newvarN,vars);    
	}
	return a;
}


int main()
{
	cout << "start!!!!" << endl; 
	for (int i=0;i<m;i++)
	{
		c.push_back(0);
	}
	c[0] = -2; c[1] = 3; c[2] = -7; c[3] = 0;  c[4] = 0;  c[5] = 0;
	b.push_back(3); b.push_back(2); b.push_back(1);

	row row1(6, 0);    row1[0] = 1; row1[1] = 1; row1[2] = 2; row1[3] = 1;
	row row2(6, 0);     row2[0] = 1; row2[1] = -1; row2[4] = 1;
	row row3(6, 0);      row3[1] = -1; row3[2] = 1; row3[5] = 1;
	
	A.push_back(row1);
	A.push_back(row2);
	A.push_back(row3);

	cout << "there are " << m << " vars" << " and " << n << " constraints" << endl;
	cout << "c:" << endl;
	for (int i=0;i<m;i++)
	{
		cout << "c" << i+1<< "=" << c[i] << ",";
	}
	cout << endl;
	cout << "A:" << endl;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}

	    var*var1=new var();  var*var2=new var(); var*var3=new var(); var*var4=new var(); var*var5=new var(); var*var6=new var();
	    vars.push_back(var1); vars.push_back(var2); vars.push_back(var3); vars.push_back(var4); vars.push_back(var5); vars.push_back(var6);
	    for (int i = 0; i<m; i++)
		{
		vars[i]->index = i + 1;
		vars[i]->data = 0;
		}

	varB.push_back(vars[3]);
	varB.push_back(vars[4]);
	varB.push_back(vars[5]);
	varN.push_back(vars[0]);
	varN.push_back(vars[1]);
	varN.push_back(vars[2]);
	
	cout << "find an initial soln:" << endl;

	cout << "varB:" << endl;
	for (int i=0;i<n;i++)
	{
		cout << "varB" << i + 1 << ":" << "var" << varB[i]->index<<"     ";
	}
	cout << endl;
	cout << "varN:" << endl;
	for (int i = 0; i<m-n; i++)
	{
		cout << "varN" << i + 1 << ":" << "var" << varN[i]->index << "     ";
	}
	cout << endl;
	cout << "start interations!!!" << endl;
//%%%%%%%迭代求解
	int d = 1;
	solve(d, varB, c, A, b, varN,vars);
	cout << endl;
	cout << "finish!!!" << endl;
	//print();
	return 0;
}
