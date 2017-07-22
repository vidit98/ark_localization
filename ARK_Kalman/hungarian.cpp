#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
struct point
{
	float x;
	float y;
};
float dis(point a , point b);//calculates distance between 2 points 

void costmtrx(std::vector<point> m1 , std::vector<point> m2 , std::vector< std::vector<float> > &cm);
/*calculates the cost matrix for hungarian algo .For now only distance is considered for cost*/ 

int find_min(std::vector<float> v1);//finds minimum in a 1D vector

float find_min2d(std::vector< std::vector<float> > cm ,std::vector<int> row , std::vector<int> col);//find minimum in 2D vector

int findzeros(std::vector< std::vector<float> > cm , std::vector<int> &row , std::vector<int> &col, int F ,int &fl);
/* Finds rows or columns containg maximum zeros or minimum zeros depending on thr value of F.If F is 1 it gives max zero containg row/col and min zero
conaining zero row/col. fl tells if it is row or col , if fl == 1 then it means col vector is changed and if fl == 0 implies row vector
is chnaged.*/
void allocation(std::vector< std::vector<float> > cm , std::vector<int> row , std::vector<int> col,std::vector< int > &alloc);
/*Above function implements last step in hungarian algo. After we have our final matrix with required no of zeros we have to allocate it
to respective rows an cols*/
void H_subtraction(std::vector< std::vector<float> > &cm ,std::vector<int> row , std::vector<int> col ,float val);

void display(std::vector< std::vector<float> > cm);

void hungarian(std::vector< std::vector<float> > cm , std::vector< int > &alloc);
/*This function calls required function to implement hungarian algo*/
int s;
int main()
{
	std::cout << "check1" << std::endl;
	std::vector<point> measurement1 , mesasurement2;
	std::vector< std::vector<float> > cost(4 ,std::vector<float>(4, 0));
	/*point a,b,c,d;
	a.x =2 ; a.y =3;
	b.x =3 ; b.y =2;
	c.x = 4 ; c.y = 5;
	d.x = 10 , d.y = 3;
	measurement1.push_back(a);
	measurement1.push_back(b);

	mesasurement2.push_back(c);
	mesasurement2.push_back(d);*/
	//s = m1.size();
	//costmtrx(measurement1,mesasurement2,cost);
	cost[0][3] = 0;
	cost[1][0] = 0;
	cost[1][2] =0;
	cost[3][2] = 2;
	cost[2][2] = 2;
	cost[2][3] = 3;
	cost[3][3] = 3;

	display(cost);
	std::vector< int > alloc1;
	hungarian(cost , alloc1);
	
	for(int i = 0 ; i < 4 ; i++)
	{
		std::cout << i << "  " << alloc1[i] << "\n";
	}
	return 0;
}

float dis(point a , point b)
{
	float dis = sqrt(pow(a.x - b.x ,2) + pow(a.y - b.y,2));
	return dis;
}

void costmtrx(std::vector<point> m1 , std::vector<point> m2 , std::vector< std::vector<float> > &cm)
{
	for(int i = 0 ; i < m1.size() ; i++)
	{
		for(int j = 0 ; j < m2.size(); j++)
		{
			cm[i][j] = dis(m1[i] , m2[j]);
		}
	}

}

int find_min(std::vector<float> v1)
{
	int min=0 ,i;
	for(i = 0 ; i  < v1.size() ; i++)
	{
		if(v1[min] > v1[i])
		{
			min = i;
		}
	}
	return min;
}

float find_min2d(std::vector< std::vector<float> > cm ,std::vector<int> row , std::vector<int> col)
{
	int s = cm[0].size();
	float minv = 0.0;
	for(int i = 0 ; i < s ; i++)
	{
		if(std::count(row.begin() , row.end() , i) == 0)
		{
			for(int j = 0 ; j < s ; j++)
			{
				if(std::count(col.begin() , col.end() , j) == 0)
				{
					if(minv > cm[i][j])
					{
						minv = cm[i][j];
					}
				}
			}
		}
	}

	return minv;
}

int findzeros(std::vector< std::vector<float> > cm , std::vector<int> &row , std::vector<int> &col, int F ,int &fl)
{
	int max_zero = 0 , mrow = 0 , mcol = 0,count ,min_zero = 200;
	int s = cm[0].size();
	int f = 0;
	
	for (int i = 0; i < s; ++i)
	{
		count = 0;
		if(std::count(row.begin() , row.end() , i) == 0)
		{
			for(int j = 0 ; j < s ; j++)
			{	
				if(std::count(col.begin() , col.end() , j) == 0)
				{
					if(cm[i][j] == 0.0)
					{
						count++;
					}
				}
				
			}
			if(F==0)
			{	
				if(count > max_zero)
				{
					f =0;
					max_zero = count;
					mrow = i;
				}
			}
			else if(F==1)
			{
				if(count < min_zero)
				{
					f =0;
					min_zero = count;
					mrow = i;
				}
			}
		}
	}


	for (int i = 0; i < s; ++i)
	{
		count = 0;
		if(std::count(col.begin() , col.end() , i) == 0)
		{
			for(int j = 0 ; j < s ; j++)
			{	
				if(std::count(row.begin() , row.end() , j) == 0)
				{
					if(cm[j][i] == 0.0)
					{
						count++;
					}
				}
				
			}
			if(F==0)
			{
				if(count > max_zero)
				{
					f =1;
					max_zero = count;
					mcol = i;
				}
			}
			else if(F==1)
			{
				if(count < min_zero)
				{
					f =1;
					min_zero = count;
					mcol = i;
				}
			}
		}
	}

	if(f)
	{
		col.push_back(mcol);
		fl = f;
	}
	else{
		row.push_back(mrow);
		fl = 0;
	}
	if(F==0)
		return max_zero;
	else if(F==1)
		return min_zero;

}

void allocation(std::vector< std::vector<float> > cm , std::vector<int> row , std::vector<int> col,std::vector< int > &alloc)
{
	int row_or_col,zeros,pos1,prev,count = 0,allocations = 0;
	std::vector< int > arr;
	std::vector< int > prev_pos;
	
	for(int i = 0 ; i < 20 ; i++)
	{
		alloc.push_back(0);
	}
	
	while(allocations != cm[0].size())
	{
		std::cout  << "check1";
		zeros = findzeros(cm,row,col,1,row_or_col);
		std::cout <<"zeros" <<zeros << "\n";
		for(int i = 0 ; i < row.size() ; i++)
		{
			std::cout << "row" << row[i];
		}
		for (int i = 0; i < col.size(); ++i)
		{
			std::cout << "col" << col[i];
		}
		if(zeros)
		{	
			arr.push_back(row_or_col);
			if (row_or_col == 1)
			{

				pos1 = col[(col.size() - 1)];
				std::cout << "pos1 " << pos1<<"\n";
				for(int i = 0 ; i < cm[0].size() ; i++)
				{
					if(cm[i][pos1] == 0.0 && std::count(row.begin() , row.end() , i) == 0)
					{
					 	allocations ++;
						prev_pos.push_back(i);
						row.push_back(i);
						alloc[i] = pos1;
						break;
					}

				}


			}
			else if(row_or_col == 0)
			{
				pos1 = row[(row.size() - 1)];
				std::cout << "pos1 " << pos1<<"\n";
				for(int i = 0 ; i < cm[0].size() ; i++)
				{
					if(cm[pos1][i] == 0.0 && std::count(col.begin() , col.end() , i) == 0)
					{
						allocations++;
						prev_pos.push_back(i);
						col.push_back(i);
						alloc[pos1] = i;
						break;
					}

				}

			}
		}
		else
		{
			int flag = 0;
			if(arr[arr.size()-1])
			{
				arr.pop_back();
				row.pop_back();
				alloc.pop_back();
				allocations --;
				pos1 = col[(col.size() - 1)];
				for(int i = 0 ; i < cm[0].size() ; i++)
				{
					if(cm[i][pos1] == 0.0 && i > prev_pos[prev_pos.size() - 1] && std::count(row.begin() , row.end() , i) == 0)
					{
						flag =1;
						allocations++;
						prev_pos[prev_pos.size() - 1] = i;
						row.push_back(i);
						alloc[i] = pos1;
						break;
					}

				}
				if(flag ==0)
				{
					col.pop_back();
					prev_pos.pop_back();
				}

			}
			else if(arr[arr.size() - 1] == 0)
			{
				arr.pop_back();
				col.pop_back();
				alloc.pop_back();
				allocations--;
				pos1 = row[(row.size() - 1)];
				for(int i = 0 ; i < cm[0].size() ; i++)
				{
					if(cm[pos1][i] == 0.0 && i > prev_pos[prev_pos.size() - 1] && std::count(col.begin() , col.end() , i) == 0)
					{
						allocations++;
						flag = 1;
						prev_pos[prev_pos.size() - 1] = i;
						col.push_back(i);
						alloc[pos1] = i;
						break;
					}

				}
				if(flag == 0)
				{
					row.pop_back();
					prev_pos.pop_back();
				}
			}
		}
		
	}
}

void H_subtraction(std::vector< std::vector<float> > &cm ,std::vector<int> row , std::vector<int> col ,float val)
{
	int s = cm[0].size();
	for(int i = 0 ; i < s ; i++)
	{
		if(std::count(row.begin() , row.end() , i) == 0)
		{
			for(int j = 0 ; j < s ; j++)
			{
				if(std::count(col.begin() , col.end() , j) == 0)
				{
					cm[i][j] = cm[i][j] - val;
				}
			}
		}
		else
		{
			for(int j = 0 ; j < s ; j++)
			{
				if(std::count(col.begin() , col.end() , j) != 0)
				{
					cm[i][j] = cm[i][j] + val;
				}
			}
		}
	}
}

void display(std::vector< std::vector<float> > cm)
{
	for (int i = 0; i < cm[0].size(); ++i)
	{
		for (int j = 0; j < cm[0].size(); ++j)
		{
			std::cout << cm[i][j] << " " ;
		}
		std::cout << "\n";
	}
}

void hungarian(std::vector< std::vector<float> > cm , std::vector< int > &alloc)
{
	int idx;
	std::vector< std::vector<float> > cm_1 = cm;
	int s = cm[0].size();
	for(int i = 0 ; i<s ; i++)
	{
		idx = find_min(cm_1[i]);
		
		for(int j = 0 ; j < s ; j++)
		{
			cm_1[i][j] = cm_1[i][j] - cm[i][idx];
			//std::cout << "idx" << cm_1[i][j] << "\n";
		}
	}
	display(cm_1);
	for (int i = 0; i < s; ++i)
	{
		float min = cm_1[0][i];
		for (int j = 0; j < s; ++j)
		{
			if(min > cm_1[j][i])
			{
				min = cm_1[j][i];
			}		
		}
		for (int j = 0; j < s; ++j)
		{
			cm_1[j][i] = cm_1[j][i] - min;
		}
	}
	display(cm_1);
	int line;
	std::vector<int> row1;
	std::vector<int> col1;
	row1.push_back(-1);
	col1.push_back(-1);
	float min;int o;
	while(line!=s)
	{
		display(cm_1);
		while(findzeros(cm_1 , row1,col1,0,o))
		{
			line++;
		}

		if(line == s)
		{
			break;
		}
		else
		{
		
			min = find_min2d(cm_1 , row1 ,col1);
			H_subtraction(cm_1 , row1 ,col1 , min);
		}
		line = 0;
		row1.clear();
		col1.clear();
		row1.push_back(-1);
		col1.push_back(-1);

	}	

	row1.clear();
	col1.clear();
	//std::vector<int> alloc;
	allocation(cm_1, row1 , col1 , alloc);
}