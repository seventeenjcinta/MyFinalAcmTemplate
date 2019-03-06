/*圆和简单多边形*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#define M 30
#define eps 1e-7
const double PI = acos(-1.0);


class pnt_type
{
public:
	double x,y;
};
class state_type
{
public:
	double angle;
	double CoverArea;
};


pnt_type pnt[M];
pnt_type center;


int n;
double R;


bool read_data()
{
	n = 3;
	int i;
	if (cin >> pnt[1].x >> pnt[1].y)
	{
		for (i=2;i<=n;i++) cin >> pnt[i].x >> pnt[i].y;
		cin >> center.x >> center.y >> R;
		return true;
	}
	return false;
}
inline double Area2(pnt_type &a,pnt_type &b,pnt_type &c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
inline double dot(pnt_type &a,pnt_type &b,pnt_type &c)
{
	return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}
inline double dist(pnt_type &a,pnt_type &b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}


void init()
{
	int i;
	double temp,sum;
	for (i=2;i<n;i++)
	{
		temp = Area2(pnt[1],pnt[i],pnt[i + 1]);
		sum += temp;
	}
	if (sum < 0) reverse(pnt + 1,pnt + n + 1);
	pnt[n + 1] = pnt[1];
}


inline bool inCircle(pnt_type &s)
{
	return dist(center,s) <= R;
}


bool SameSide(pnt_type a,pnt_type b)
{
	if (dist(a,center) > dist(b,center)) swap(a,b);
	return dot(a,b,center) < eps;
}


double ShadomOnCircle(pnt_type a,pnt_type b)
{
	double flag = Area2(center,a,b),res = 0;
	if (fabs(flag) < eps) return 0;


	bool ina = inCircle(a),inb = inCircle(b);
	if (ina && inb)
	{
		res = fabs(Area2(center,a,b)) / 2;
	}
	else if (!ina && !inb)
	{
		if (SameSide(a,b))
		{
			double theta = acos(dot(center,a,b) / dist(center,a) / dist(center,b));
			res = R * R * theta / 2;
		}
		else
		{
			double height = fabs(Area2(center,a,b)) / dist(a,b);
			double theta = acos(dot(center,a,b) / dist(center,a) / dist(center,b));
			if (height >= R)
			{
				res = R * R * theta / 2;
			}
			else
			{
				double _theta = 2 * acos(height / R);
				res = R * R * (theta - _theta) / 2 + R * R * sin(_theta) / 2;
			}
		}
	}
	else
	{
		if (!ina && inb) swap(a,b);
		double height = fabs(Area2(center,a,b)) / dist(a,b);
		double temp = dot(a,center,b);
		double theta = acos(dot(center,a,b) / dist(center,a) / dist(center,b)),theta1,theta2;
		if (fabs(temp) < eps)
		{
			double _theta = acos(height / R);
			res += R * height / 2 * sin(_theta);
			res += R * R / 2 * (theta - _theta);
		}
		else
		{
			theta1 = asin(height / R); theta2 = asin(height / dist(a,center));
			if (temp > 0)
			{
				res += dist(center,a) * R / 2 * sin(PI - theta1 - theta2);
				res += R * R / 2 * (theta + theta1 + theta2 - PI);
			}
			else
			{
				res += dist(center,a) * R / 2 * sin(theta2 - theta1);
				res += R * R / 2 * (theta - theta2 + theta1);
			}
		}
	}
	if (flag < 0) return -res; else return res;
}


double Cover()
{
	int i;
	double res = 0;
	for (i=1;i<=n;i++)
		res += ShadomOnCircle(pnt[i],pnt[i + 1]);
	return res;
}


int main()
{
	double ans;
	while (read_data())
	{
		init();
		ans = Cover();
		printf("%.2lf\n",ans);
	}
	return 0;
}
