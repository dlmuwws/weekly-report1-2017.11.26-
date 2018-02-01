//最大流增广链方法----最大容量扩张（利用dfs找具有最大瓶颈流量的增广链，沿着增广链调节流量，继续找增广链，直到无法找到）
#include<iostream>
using namespace std;


//定义变量
 const int n = 7; //顶点数
 double f[n][n];   //流量
 double c[n][n]; //容量
 double r[n][n]; //剩余流量- 正向弧等于容量减去流量，反向弧等于容量(满足增广链要求)
 int s, v, t;         //s是搜索起点,v是正在搜索的点,t是搜索终点
 int path[n];   //正在搜索的增广链的顶点标号
 int path_[n];    //具有最大瓶颈容量的增广链的顶点标号
 int c_count;    //正在搜索的增广链的顶点数量
 int count_;  //具有最大瓶颈容量的增广链的顶点数量
 double cap[n]; //正在搜索的增广链的瓶颈流量
 bool find;    //记录是否找到增广链
 double flow;      //增广链的最大瓶颈流量
 double max_flow;  //网络最大流
 
 bool loop(int v, int*path, int count);  //不搜索已经搜索过的点
 void dfs(int v, int t, double r[n][n], int n, int*path, int*path_, int count, int &count_, double*cap, double &flow, bool &find);   //搜索增广链
 double maxflow(double c[n][n], double f[n][n], int s, int t, const int n); //求网络最大流

 int main()
 {
	 s = 0; t = 6;
	 for (int i = 0; i < n; i++)
	 {
		 for (int j = 0; j<n; j++)
		 {
			 c[i][j] = 0;
		 }
	 }
	 c[0][1] = 8; c[0][2] =5; c[1][3] =2; c[1][4]= 6; c[2][3] =5;  c[2][5] = 2; c[3][6] =5; c[4][6] = 6; c[5][6] =2;
	double max_networkflow=maxflow(c, f, s, t, n);
	cout << "max_networkflow=" << max_networkflow << endl;
	for (int i=0;i<n;i++)
	{
		for (int j= 0; j<n; j++)
		{
			cout << f[i][j] << " ";
		}
		cout << endl;
	}
	 system("pause");
	 return 0;
 }

 bool loop(int v, int*path,int count)  
 {
	 for (int i=0;i<count;i++)
	 {
		 if (path[i]==v)
		 {
			 return true;
		 }
	 }
	 return false;
 }

 void dfs(int v, int t,double r[n][n],int n, int*path, int*path_,int counts, int &count_,double*cap,double &flow, bool &find)
 {
	 cout << "v:" << v << endl;
	 cout << "t:" << t << endl;
	 cout << "r:" << endl;
	 for (int i = 0; i<n; i++)
	 {
		 for (int j = 0; j<n; j++)
		 {
			 cout << r[i][j] << " ";
		 }
		 cout << endl;
	 }
	// cout<<"count:"<<counts<<endl;
	 path[counts] = v;
	 double temp=0;
	 int ti= 0;
	 for (int i=0;i<n;i++)
	 {
		 if ((r[v][i]>0)&&(!loop(i,path,counts)))
		 {
			 counts = counts - ti;
			 ti++;
			 //cout << "i: " << i << endl;
			// cout << "count:" << counts << endl;
			 cap[counts] = r[v][i];
			 counts++;
			 if (i != t)
			 {
				 dfs(i, t, r, n, path, path_, counts, count_, cap, flow, find);
			 }
			 else
			 {
				 find = true;  //找到增广链
				 path[counts] = t;
				 for (int k = 0; k <= counts; k++)
				 {
					 cout << "path:" << path[k] << " ";
				 }
				 cout << endl;
				 temp = cap[0];
				 for (int i = 0; i < counts; i++)   //找增广链中的瓶颈流量
				 {
					 if (cap[i] < temp)
					 {
						 temp = cap[i];
					 }
				 }
				 cout << "temp:" << temp << endl;
				 cout << "flow:" << flow << endl;
				 //cout << "count:" << counts << endl;
				 if (temp > flow)   //找到一条具有更大瓶颈流量的增广链，代替原来的
				 {
					 for (int j = 0; j <= counts; j++)
					 {
						 path_[j] = path[j];
					 }
					 count_ = counts;
					 flow = temp;
				 }
			 }
		 }
	 }
 }

 double maxflow(double c[n][n],double f[n][n],int s,int t,const int n)
 {
	 double max_flow = 0;        //初始化
	 bool find = true;
	 for (int i = 0; i < n;i++)   
	 {
		 for (int j=0;j<n;j++)
		 {
			 f[i][j] = 0;
			 r[i][j] = c[i][j];
		 }
	 }
	
	 while (find)   
	 {
		 c_count = 0; flow = 0; find = false;
		 dfs(s,t,r,n,path,path_,c_count,count_,cap,flow,find);
		// cout << "c_count:" <<c_count<< endl;
		 if (find)
		 {
			 cout << "flow:" <<flow<< endl;
			 max_flow += flow;
			 cout << "adjust_path_:" << endl;
			 for (int k = 0; k <= count_; k++)
			 {
				 cout << "path_:" << path_[k] << " ";
			 }
			 cout << endl;
			 for (int k = 0; k < count_;k++)          //求此时的f,调整r
			 {
				 f[path_[k]][path_[k + 1]] += flow;
				 r[path_[k]][path_[k + 1]] -= flow;
				 r[path_[k + 1]][path_[k]] = f[path_[k]][path_[k + 1]];
			 }
		 }
	 }
	 return max_flow;	
 }
