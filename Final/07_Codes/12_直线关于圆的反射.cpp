/*
fzu_1035
1.直线和圆的交点
2.点关于线的对称点
3.点到线的距离
4.直线方程
*/
#include <iostream>


#include <cmath>


using namespace std;


#define INF 999999999
const double eps = 1e-6;


int up;


typedef struct TPoint
{
    double x;
    double y;
}TPoint;


typedef struct TCircle
{
    TPoint center;
    double r;
}TCircle;


typedef struct TLine
{
    //直线标准式中的系数
    double a, b, c;
}TLine;


void SloveLine(TLine &line, TPoint start, TPoint dir)
{
    //根据直线上一点和直线的方向求直线的方程
    if(dir.x == 0){
        line.a = 1;
        line.b = 0;
        line.c = start.x;
    }
    else {
        double k = dir.y / dir.x;
        line.a = k;
        line.b = -1;
        line.c = start.y - k * start.x;
    }
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


TPoint symmetricalPointofLine(TPoint p, TLine L)
{
    //p点关于直线L的对称点
    TPoint p2;
    double d;
    d = L.a * L.a + L.b * L.b;
    p2.x = (L.b * L.b * p.x - L.a * L.a * p.x -
            2 * L.a * L.b * p.y - 2 * L.a * L.c) / d;
    p2.y = (L.a * L.a * p.y - L.b * L.b * p.y -
            2 * L.a * L.b * p.x - 2 * L.b * L.c) / d;
    return p2;
}


double distanc(TPoint p1, TPoint p2)
{
    //计算平面上两个点之间的距离
   return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


bool samedir(TPoint dir, TPoint start, TPoint point)
{
    //判断方向
    TPoint tmp;
    tmp.x = point.x - start.x;
    tmp.y = point.y - start.y;
    if(tmp.x != 0 && dir.x != 0){
        if(tmp.x / dir.x > 0) return true;
        else return false;
    }
    else if(tmp.y != 0 && dir.y != 0){
        if(tmp.y / dir.y > 0) return true;
        else return false;
    }
    return true;
}


bool Intersected(TPoint &point, TLine line, const TCircle circle[],
				 TPoint start, TPoint dir, int which)
{
    //如果圆与直线有(有效交点)交点就存放在变量point中
	double a = line.a, b = line.b, c = line.c;
	double x0 = circle[which].center.x, y0 = circle[which].center.y;
	double r =  circle[which].r;
	//有交点，求交点
	double x2front = b * b + a * a;
	double x1front = -2 * x0 * b * b + 2 * a * b * y0 + 2 * a * c;
	double front = x0 * x0 * b * b + y0 * y0 * b * b
		+ c * c + 2 * c * y0 * b - b * b * r * r;
	double d = x1front * x1front - 4 * x2front * front;
	TPoint p1, p2;
	bool k1, k2;
    if(fabs(d) < eps){
        //x2front不可能等于零
       point.x = -x1front / x2front / 2;
       point.y = (-c - a * point.x) / b;
       //判断方向
       if(samedir(dir, start, point)) return true;
       else return false;
    }
    else if(d < 0) return false;
    else {
        p1.x = (-x1front + sqrt(d)) / 2 / x2front;
        p1.y = (-c - a * p1.x) / b;
        p2.x = (-x1front - sqrt(d)) / 2 / x2front;
        p2.y = (-c - a * p2.x) / b;
        k1 = samedir(dir, start, p1);
        k2 = samedir(dir, start, p2);
        if(k1 == false && k2 == false) return false;
        if(k1 == true && k2 == true){
            double dis1 = distanc(p1, start);
            double dis2 = distanc(p2, start);
            if(dis1 < dis2) point = p1;
            else point = p2;
            return true;
        }
        else if(k1 == true) point = p1;
        else point = p2;
        return true;
    }
}


void Reflect(int &num, TCircle circle[], TPoint start, TPoint dir, int n)
{
    //反复反射
    int i;
    TLine line;
    TPoint interpoint, newstart;
    int u;
    SloveLine(line, start, dir);
    int tag = 0;
    double mindis = INF;
    for(i = 1;i <= n;i++){
        if(i != up && Intersected(interpoint, line, circle, start, dir, i)){
            double dis = distanc(start, interpoint);
            if(dis < mindis){
                tag = 1;
                u = i;
                mindis = dis;
                newstart = interpoint;
            }
        }
    }
    if(tag == 0){
        cout << "inf" << endl;
        return ;
    }
    else {
        if(num == 10){
            cout << "..." << endl;
           return ;
        }
        cout << u << " ";
        num++;
        //新的方向
        TLine line1;
        TPoint p;
        line1 = lineFromSegment(newstart, circle[u].center);
        if(fabs(line1.a * start.x + line1.b * start.y +line1.c) <= eps){
            dir.x = -dir.x;
            dir.y = -dir.y;
        }
        else {
            p = symmetricalPointofLine(start, line1);//start的对称点
            dir.x = p.x - newstart.x;
            dir.y = p.y - newstart.y;
        }

        start = newstart;
        up = u;
        Reflect(num, circle, start, dir, n);
    }
}


int main()
{
    //freopen("fzu_1035.in", "r", stdin);
    //freopen("fzu_1035.out", "w", stdout);
    int n, i, j, num, test = 1;
    TCircle circle[30];
    TPoint start, dir;
    while(cin >> n && n){
        for(i = 1;i <= n;i++){
            cin >> circle[i].center.x >> circle[i].center.y >> circle[i].r;
        }
        cin >> start.x >> start.y >> dir.x >> dir.y;

        cout << "Scene " << test++ << endl;


        num = 0;
        up = -1;
        Reflect(num, circle, start, dir, n);
        cout << endl;
    }
    return 0;
}
