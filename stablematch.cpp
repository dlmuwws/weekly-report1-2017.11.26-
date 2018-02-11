#include<stdlib.h>     
#include<time.h>  
#include<iostream>
using namespace std;
struct man
{
	int flag;
	int m_id;
	int ms[10];  
};
struct woman
{
	int flag;
	int wm_id;
	int wms[10]; 
};
struct man men[10];
struct woman women[10];
void sui_ji_shu(int tmp[10], int j)     
{
	int a[10];
	int i, index, x = 0;
	for (i = 0; i<10; i++)
	{

		a[i] = i;
		tmp[i] = 0;
	}
	
	srand((unsigned)j);//time(NULL)
	for (i = 0; i<10;)
	{
		index = rand() % 10;
		if (a[index] != -1)
		{
			tmp[i] = a[index];
			cout << tmp[i] << endl;
			a[index] = -1;
			++i;
		}
	}
	
}
int exit_freeman(struct man men[10])   
{
	 
	int i;
	for (i = 0; i<10; ++i)
	{
		if (men[i].flag == 0)
			return i + 1;   
	}
	return 0;

}
int has_woman(int i)   
{
	int j;
	for (j = 0; j<10; ++j)
	{
		if (men[i].ms[j] != -1)
			return 1;
	}
	return 0;
}
int first_woman_id(int i)
{
	int j;
	for (j = 0; j<10; ++j)
	{
		if (men[i].ms[j] != -1)
			return j;
	}
}
int woman_love_more(int location, int mf, int mfp)
{
	int i, j, k;
	for (i = 0; i<10; ++i)
	{
		if (women[location].wms[i] == mf)
		{
			j = i;
		}
		if (women[location].wms[i] == mfp)
		{
			k = i;
		}
	}
	if (k<j)
		return 1;
	else
		return 0;
}
int main()
{

	int i, j;
	int index;
	int mf, wmf;
	int wm_id;
	int mfp;
	int location;
	int result[10][10];
	for (i = 0; i<10; ++i)
		for (j = 0; j<10; ++j)
			result[i][j] = 0;
	for (i = 0; i<10; ++i)
	{
		men[i].flag = 0;
		men[i].m_id = i;
		women[i].flag = 0;
		women[i].wm_id = i;
	}
	for (j = 0; j<10; ++j)
	{
		index = rand() % 10;
		sui_ji_shu(men[j].ms, index);

	}
	for (j = 0; j<10; ++j)
	{
		index = rand() % 10;
		sui_ji_shu(women[j].wms, index);

	}
	mf = exit_freeman(men);
	wmf = has_woman(mf - 1);
	while (mf&&wmf)
	{
		wm_id = first_woman_id(mf - 1);
		location = men[mf - 1].ms[wm_id];
		men[mf - 1].ms[wm_id] = -1;
		if (women[location].flag == 0)
		{
			women[location].flag = 1;
			men[mf - 1].flag = 1;
			result[mf - 1][location] = 1;
		}
		else
		{
			for (i = 0; i<10; ++i)
				if (result[i][location] == 1)
				{
					mfp = i;
					break;
				}

			if (woman_love_more(location, mf - 1, mfp))
			{
				men[mf - 1].flag = 0;
			}
			else
			{
				men[mf - 1].flag = 1;
				result[mf - 1][location] = 1;
				result[mfp][location] = 0;
				men[mfp].flag = 0;
			}
		}
		mf = exit_freeman(men);
		wmf = has_woman(mf - 1);
	}
	for (i = 0; i<10; ++i)
	{
		for (j = 0; j<10; ++j)
			cout << result[i][j] << endl;
	}
}