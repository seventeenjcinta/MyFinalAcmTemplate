/*多边形的核*/
#include <stdio.h>
#include <math.h>


#define Maxn 3005
const double eps = 1e-10;


typedef struct TPodouble
{
	double x;
	double y;
}TPoint;


typedef struct TPolygon
{
	TPoint p[Maxn];
	int n;
};


typedef struct TLine
{
	double a, b, c;
}TLine;


bool same(TPoint p1, TPoint p2)
{
	if(p1.x != p2.x) return false;
	if(p1.y != p2.y) return false;
	return true;
}

double multi(TPoint p1, TPoint p2, TPoint p0)
{
    //求矢量[p0, p1], [p0, p2]的叉积
    //p0是顶点
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    //若结果等于0，则这三点共线
    //若结果大于0，则p0p2在p0p1的逆时针方向
    //若结果小于0，则p0p2在p0p1的顺时针方向
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    //线段所在直线,返回直线方程的三个系统
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint LineInter(TLine l1, TLine l2)
{
    //求两直线得交点坐标
    TPoint tmp;
    double a1 = l1.a;
    double b1 = l1.b;
    double c1 = l1.c;
    double a2 = l2.a;
    double b2 = l2.b;
    double c2 = l2.c;
    //注意这里b1 = 0
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


TPolygon Cut_polygon(TPoint p1, TPoint p2, TPolygon polygon)
{
	TPolygon new_polygon;
	TPoint interp;
	TLine l1, l2;
	int i, j;
	double t1, t2;
	new_polygon.n = 0;
	for(i = 0;i <= polygon.n - 1;i++){
		t1 = multi(p2, polygon.p[i], p1);
		t2 = multi(p2, polygon.p[i + 1], p1);
		if(fabs(t1) < eps || fabs(t2) < eps){
			if(fabs(t1) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i];
			if(fabs(t2) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
		}
		else if(t1 < 0 && t2 < 0){
			new_polygon.p[new_polygon.n++] = polygon.p[i];
			new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
		}
		else if(t1 * t2  < 0){
			l1 = lineFromSegment(p1, p2);
			l2 = lineFromSegment(polygon.p[i], polygon.p[i + 1]);
			interp = LineInter(l1, l2);
			if(t1 < 0) {
				new_polygon.p[new_polygon.n++] = polygon.p[i];
				new_polygon.p[new_polygon.n++] = interp;
			}
			else {
				new_polygon.p[new_polygon.n++] = interp;
				new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
			}
		}
	}
	polygon.n = 0;
	if(new_polygon.n == 0) return polygon;
	polygon.p[polygon.n++] = new_polygon.p[0];
	for(i = 1;i < new_polygon.n;i++){
		if(!same(new_polygon.p[i], new_polygon.p[i - 1])){
			polygon.p[polygon.n++] = new_polygon.p[i];
		}
	}
	if(polygon.n != 1 && same(polygon.p[polygon.n - 1], polygon.p[0])) polygon.n--;
	polygon.p[polygon.n] = polygon.p[0];
	return polygon;
}


double polygonArea(TPolygon p)
{
    //已知多边形各顶点的坐标，求其面积
    int i, n;
    double area;
    n = p.n;
    area = 0;
    for(i = 1;i <= n;i++){
        area += (p.p[i - 1].x * p.p[i % n].y - p.p[i % n].x * p.p[i - 1].y);
    }
	return area / 2;
}


void ChangeClockwise(TPolygon &polygon)
{
	TPoint tmp;
	int i;
	for(i = 0;i <= (polygon.n - 1) / 2;i++){
		tmp = polygon.p[i];
		polygon.p[i] = polygon.p[polygon.n - 1 - i];
		polygon.p[polygon.n - 1 - i] = tmp;
	}
}


int main()
{
	int test, i, j;
	double area;
	TPolygon polygon, new_polygon;
	scanf("%d", &test);
	while(test--){
		scanf("%d", &polygon.n);
		for(i = 0;i <= polygon.n - 1;i++){
			scanf("%lf%lf", &polygon.p[i].x, &polygon.p[i].y);
		}
		/*若是逆时针转化为顺时针*/
		if(polygonArea(polygon) > 0) ChangeClockwise(polygon);
		polygon.p[polygon.n] = polygon.p[0];
		new_polygon = polygon;
		for(i = 0;i <= polygon.n - 1;i++){
			new_polygon = Cut_polygon(polygon.p[i], polygon.p[i + 1], new_polygon);
		}
		area = polygonArea(new_polygon);
		if(area < 0) printf("%.2lf\n", -area);
		else printf("%.2lf\n", area);
	}
	return 0;
}


//是否存在


#include <stdio.h>
#include <math.h>


#define Maxn 3005
const double eps = 1e-10;


typedef struct TPodouble
{
	double x;
	double y;
}TPoint;


typedef struct TPolygon
{
	TPoint p[Maxn];
	int n;
};


typedef struct TLine
{
	double a, b, c;
}TLine;


bool same(TPoint p1, TPoint p2)
{
	if(p1.x != p2.x) return false;
	if(p1.y != p2.y) return false;
	return true;
}

double multi(TPoint p1, TPoint p2, TPoint p0)
{
    //求矢量[p0, p1], [p0, p2]的叉积
    //p0是顶点
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    //若结果等于0，则这三点共线
    //若结果大于0，则p0p2在p0p1的逆时针方向
    //若结果小于0，则p0p2在p0p1的顺时针方向
}


TLine lineFromSegment(TPoint p1, TPoint p2)
{
    //线段所在直线,返回直线方程的三个系统
    TLine tmp;
    tmp.a = p2.y - p1.y;
    tmp.b = p1.x - p2.x;
    tmp.c = p2.x * p1.y - p1.x * p2.y;
    return tmp;
}


TPoint LineInter(TLine l1, TLine l2)
{
    //求两直线得交点坐标
    TPoint tmp;
    double a1 = l1.a;
    double b1 = l1.b;
    double c1 = l1.c;
    double a2 = l2.a;
    double b2 = l2.b;
    double c2 = l2.c;
    //注意这里b1 = 0
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


TPolygon Cut_polygon(TPoint p1, TPoint p2, TPolygon polygon)
{
	TPolygon new_polygon;
	TPoint interp;
	TLine l1, l2;
	int i, j;
	double t1, t2;
	new_polygon.n = 0;
	for(i = 0;i <= polygon.n - 1;i++){
		t1 = multi(p2, polygon.p[i], p1);
		t2 = multi(p2, polygon.p[i + 1], p1);
		if(fabs(t1) < eps || fabs(t2) < eps){
			if(fabs(t1) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i];
			if(fabs(t2) < eps) new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
		}
		else if(t1 < 0 && t2 < 0){
			new_polygon.p[new_polygon.n++] = polygon.p[i];
			new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
		}
		else if(t1 * t2  < 0){
			l1 = lineFromSegment(p1, p2);
			l2 = lineFromSegment(polygon.p[i], polygon.p[i + 1]);
			interp = LineInter(l1, l2);
			if(t1 < 0) {
				new_polygon.p[new_polygon.n++] = polygon.p[i];
				new_polygon.p[new_polygon.n++] = interp;
			}
			else {
				new_polygon.p[new_polygon.n++] = interp;
				new_polygon.p[new_polygon.n++] = polygon.p[i + 1];
			}
		}
	}
	polygon.n = 0;
	if(new_polygon.n == 0) return polygon;
	polygon.p[polygon.n++] = new_polygon.p[0];
	for(i = 1;i < new_polygon.n;i++){
		if(!same(new_polygon.p[i], new_polygon.p[i - 1])){
			polygon.p[polygon.n++] = new_polygon.p[i];
		}
	}
	if(polygon.n != 1 && same(polygon.p[polygon.n - 1], polygon.p[0])) polygon.n--;
	polygon.p[polygon.n] = polygon.p[0];
	return polygon;
}


void ChangeClockwise(TPolygon &polygon)
{
	TPoint tmp;
	int i;
	for(i = 0;i <= (polygon.n - 1) / 2;i++){
		tmp = polygon.p[i];
		polygon.p[i] = polygon.p[polygon.n - 1 - i];
		polygon.p[polygon.n - 1 - i] = tmp;
	}
}


double polygonArea(TPolygon p)
{
    //已知多边形各顶点的坐标，求其面积
    double area;
    int i, n;
    n = p.n;
    area = 0;
    for(i = 1;i <= n;i++){
        area += (p.p[i - 1].x * p.p[i % n].y - p.p[i % n].x * p.p[i - 1].y);
    }
    return area / 2;
}


int main()
{
	int i, j;
	TPolygon polygon, new_polygon;
	while(scanf("%d", &polygon.n) && polygon.n){
		for(i = 0;i <= polygon.n - 1;i++){
			scanf("%lf%lf", &polygon.p[i].x, &polygon.p[i].y);
		}
		/*若是逆时针转化为顺时针*/
		if(polygonArea(polygon) > 0) ChangeClockwise(polygon);
		polygon.p[polygon.n] = polygon.p[0];
		new_polygon = polygon;
		for(i = 0;i <= polygon.n - 1;i++){
			new_polygon = Cut_polygon(polygon.p[i], polygon.p[i + 1], new_polygon);
		}
		if(new_polygon.n > 0) printf("1\n");
		else printf("0\n");
	}
	return 0;
}
