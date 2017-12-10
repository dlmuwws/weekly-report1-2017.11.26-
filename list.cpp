#include"list.h"
#include<vector>

list::list()
{

}

point*list::getpoint(int index)
{
	for (auto point_ : pointlist)
	{
		if (point_->getindex = index)
		{
			return point_;
			break;
		}
	}
}
