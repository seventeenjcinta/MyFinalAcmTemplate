/*
两条线不相交，
左边或右边的口被遮住，
交点是某条线的那个纵坐标较高的那点
某条线段水平放置
*/
#include <stdio.h>
#include <math.h>


#define eps 1e-8


struct TPoint
{
	double x, y;
};
struct TLine
{
    double a, b, c;
};


int same(TPoint p1, TPoint p2)
{
	if(fabs(p1.x - p2.x) > eps) return 0;
	if(fabs(p1.y - p2.y) > eps) return 0;
	return 1;
}


double min(double x, double y)
{
    if(x < y) return x;
    else return y;
}


double max(double x, double y)
{
    if(x > y) return x;
    else return y;
}


double multi(TPoint p1, TPoint p2, TPoint p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y)
	     - (p2.x - p0.x) * (p1.y - p0.y);
}


bool isIntersected(TPoint s1, TPoint e1, TPoint s2, TPoint e2)
{
    if(
    (max(s1.x, e1.x) >= min(s2.x, e2.x)) &&
    (max(s2.x, e2.x) >= min(s1.x, e1.x)) &&
    (max(s1.y, e1.y) >= min(s2.y, e2.y)) &&
    (max(s2.y, e2.y) >= min(s1.y, e1.y)) &&
    (multi(s2, e1, s1) * multi(e1, e2, s1) >= 0) &&
    (multi(s1, e2, s2) * multi(e2, e1, s2) >= 0)
    )  return true;

    return false;
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint LineInter(TLine l1, TLine l2)
{
    TPoint tmp;
    double a1 = l1.a;
    double b1 = l1.b;
    double c1 = l1.c;
    double a2 = l2.a;
    double b2 = l2.b;
    double c2 = l2.c;
    if(fabs(b1) < eps){
        tmp.x = -c1 / a1;
        tmp.y = (-c2 - a2 * tmp.x) / b2;
    }
    else{
        tmp.x = (c1 * b2 - b1 * c2) / (b1 * a2 - b2 * a1);
        tmp.y = (-c1 - a1 * tmp.x) / b1;
    }
	return tmp;
}


double triangleArea(TPoint p1, TPoint p2, TPoint p3)
{
	TPoint p4, p5;
	p4.x = p2.x - p1.x;
	p4.y = p2.y - p1.y;
	p5.x = p3.x - p1.x;
	p5.y = p3.y - p1.y;
	return fabs(p5.x * p4.y - p5.y * p4.x) / 2;
}


double find_x(double y, TLine line)
{
	return (-line.c - line.b * y) / line.a;
}


double find_y(double x, TLine line)
{
	if(fabs(line.b) < eps)
	{
		return -1e250;
	}
	else
	{
		return (-line.c - line.a  * x) / line.b;
	}
}


int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	int test;
	double miny, y;
	TLine l1, l2;
	TPoint p1, p2, p3, p4, inter;
	TPoint tp1, tp2;
	scanf("%d", &test);
	while(test--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y,
		&p2.x, &p2.y, &p3.x, &p3.y, &p4.x, &p4.y);
		if(same(p1, p2) || same(p3, p4)
		   || !isIntersected(p1, p2, p3, p4)
		   || fabs(p1.y - p2.y) < eps //平行与x轴
		   || fabs(p3.y - p4.y) < eps
		  )
		{
			printf("0.00\n");
			continue;
		}
		l1 = lineFromSegment(p1, p2);
		l2 = lineFromSegment(p3, p4);
		inter = LineInter(l1, l2);
		if(p1.y > p2.y) tp1 = p1;
		else tp1 = p2;
		if(p3.y > p4.y) tp2 = p3;
		else tp2 = p4;
		if(tp1.y < tp2.y)
		{
			if(tp1.x >= min(p4.x, p3.x) && tp1.x <= max(p4.x, p3.x))
			{
				y = find_y(tp1.x, l2);
				if(y >= tp1.y)
				{
					printf("0.00\n");
					continue;
				}
			}
			miny = tp1.y;
		}
		else
		{
			if(tp2.x >= min(p1.x, p2.x) && tp2.x <= max(p1.x, p2.x))
			{
				y = find_y(tp2.x, l1);
				if(y >= tp2.y)
				{
					printf("0.00\n");
					continue;
				}
			}
			miny = tp2.y;
		}
		if(fabs(miny - inter.y) < eps)
		{
			printf("0.00\n");
			continue;
		}
		tp1.x = find_x(miny, l1);
		tp2.x = find_x(miny, l2);
		tp1.y = tp2.y = miny;
		printf("%.2lf\n", triangleArea(tp1, tp2, inter));
	}
	return 0;
}
