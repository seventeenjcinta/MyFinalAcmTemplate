#include <stdio.h>
#include <math.h>


#define pi acos(-1.0)
#define eps 1e-6
#define inf 1e250
#define Maxn 10005


typedef struct TPoint
{
	double x, y;
}TPoint;


typedef struct TPolygon
{
	TPoint p[Maxn];
	int n;
}TPolygon;


typedef struct TLine
{
	double a, b, c;
}TLine;


double max(double a, double b)
{
	if(a > b) return a;
	return b;
}


double min(double a, double b)
{
	if(a < b) return a;
	return b;
}


double distance(TPoint p1, TPoint p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x)
	 + (p1.y - p2.y) * (p1.y - p2.y));
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


double polygonArea(TPolygon p)
{
    int i, n;
    double area;
    n = p.n;
    area = 0;
    for(i = 1;i <= n;i++)
		area += (p.p[i - 1].x * p.p[i % n].y - p.p[i % n].x * p.p[i - 1].y);


	return area / 2;
}


void ChangeClockwise(TPolygon &polygon)
{
	TPoint tmp;
	int i;
	for(i = 0;i <= (polygon.n - 1) / 2;i++)
	{
		tmp = polygon.p[i];
		polygon.p[i] = polygon.p[polygon.n - 1 - i];
		polygon.p[polygon.n - 1 - i] = tmp;
	}
}


double disPointToSeg(TPoint p1, TPoint p2, TPoint p3)
{
    double a = distance(p1, p2);
    double b = distance(p1, p3);
    double c = distance(p2, p3);
    if(fabs(a + b - c) < eps) return 0;
    if(fabs(a + c - b) < eps || fabs(b + c - a) < eps) return min(a, b);
    double t1 = -a * a + b * b + c * c;
    double t2 = a * a - b * b + c * c;
    if(t1 <= 0 || t2 <= 0) return min(a, b);

    TLine l1 = lineFromSegment(p2, p3);
    return fabs(l1.a * p1.x + l1.b * p1.y + l1.c) / sqrt(l1.a * l1.a + l1.b * l1.b);
}


double disPallSeg(TPoint p1, TPoint p2, TPoint p3, TPoint p4)
{
	return min(min(disPointToSeg(p1, p3, p4), disPointToSeg(p2, p3, p4)),
	 min(disPointToSeg(p3, p1, p2), disPointToSeg(p4, p1, p2)));
}


double angle(TPoint p1, TPoint p2, double SlewRate)
{
	double ang, tmp;
	TPoint p;
	p.x = p2.x - p1.x;
	p.y = p2.y - p1.y;
	if(fabs(p.x) < eps)
	{
		if(p.y > 0) ang = pi / 2;
		else ang = 3 * pi / 2;
	}
	else
	{
        ang = atan(p.y / p.x);
		if(p.x < 0) ang += pi;
	}
	while(ang < 0) ang += 2 * pi;
	if(ang >= pi) SlewRate += pi;
	if(ang > SlewRate) tmp = ang - SlewRate;
	else tmp = pi - (SlewRate - ang);
	while(tmp >= pi) tmp -= pi;
	if(fabs(tmp - pi) < eps) tmp = 0;
	return tmp;
}


int main()
{
	int n, m, i;
	TPolygon polygon1, polygon2;
	double ymin1, ymax2, ans, d;
	int k1, k2;
	while(scanf("%d%d", &n, &m) && n)
	{
		polygon1.n = n;
		polygon2.n = m;
		for(i = 0;i < n;i++)
			scanf("%lf%lf", &polygon1.p[i].x, &polygon1.p[i].y);
		for(i = 0;i < m;i++)
			scanf("%lf%lf", &polygon2.p[i].x, &polygon2.p[i].y);
		if(polygonArea(polygon1) < 0) ChangeClockwise(polygon1);
		if(polygonArea(polygon2) < 0) ChangeClockwise(polygon2);
		ymin1 = inf, ymax2 = -inf;
		for(i = 0;i < n;i++)
			if(polygon1.p[i].y < ymin1) ymin1 = polygon1.p[i].y , k1 = i;
		for(i = 0;i < m;i++)
			if(polygon2.p[i].y > ymax2) ymax2 = polygon2.p[i].y , k2 = i;
		double SlewRate = 0;
		double angle1, angle2;
		ans = inf;
		double Slope = 0;
		while(Slope <= 360)
		{
			while(SlewRate >= pi) SlewRate -= pi;
			if(fabs(pi - SlewRate) < eps) SlewRate = 0;
			angle1 = angle(polygon1.p[k1], polygon1.p[(k1 + 1) % n], SlewRate);
			angle2 = angle(polygon2.p[k2], polygon2.p[(k2 + 1) % m], SlewRate);
			if(fabs(angle1 - angle2) < eps)
			{
				d = disPallSeg(polygon1.p[k1], polygon1.p[(k1 + 1) % n], polygon2.p[k2], polygon2.p[(k2 + 1) % m]);
				if(d < ans) ans = d;
                k1++;
				k1 %= n;
				k2++;
				k2 %= m;
				SlewRate += angle1;
				Slope += angle1;
			}
			else if(angle1 < angle2)
			{
				d = disPointToSeg(polygon2.p[k2], polygon1.p[k1], polygon1.p[(k1 + 1) % n]);
				if(d < ans) ans = d;
				k1++;
				k1 %= n;
				SlewRate += angle1;
				Slope += angle1;
			}
			else
			{
				d = disPointToSeg(polygon1.p[k1], polygon2.p[k2], polygon2.p[(k2 + 1) % m]);
				if(d < ans) ans = d;
				k2++;
				k2 %= m;
				SlewRate += angle2;
				Slope += angle2;
			}
		}
		printf("%.5lf\n", ans);
	}
	return 0;
}
