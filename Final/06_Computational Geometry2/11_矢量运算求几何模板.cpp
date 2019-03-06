#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAX_N 100
using namespace std;


///////////////////////////////////////////////////////////////////
//常量区
const double INF        = 1e10;     // 无穷大
const double EPS        = 1e-15;    // 计算精度
const int LEFT          = 0;        // 点在直线左边
const int RIGHT         = 1;        // 点在直线右边
const int ONLINE        = 2;        // 点在直线上
const int CROSS         = 0;        // 两直线相交
const int COLINE        = 1;        // 两直线共线
const int PARALLEL      = 2;        // 两直线平行
const int NOTCOPLANAR   = 3;        // 两直线不共面
const int INSIDE        = 1;        // 点在图形内部
const int OUTSIDE       = 2;        // 点在图形外部
const int BORDER        = 3;        // 点在图形边界
const int BAOHAN        = 1;        // 大圆包含小圆
const int NEIQIE        = 2;        // 内切
const int XIANJIAO      = 3;        // 相交
const int WAIQIE        = 4;        // 外切
const int XIANLI        = 5;        // 相离
const double pi		   = acos(-1.0)  //圆周率
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//类型定义区
struct Point {              // 二维点或矢量
    double x, y;
    double angle, dis;
    Point() {}
    Point(double x0, double y0): x(x0), y(y0) {}
};
struct Point3D {            //三维点或矢量
    double x, y, z;
    Point3D() {}
    Point3D(double x0, double y0, double z0): x(x0), y(y0), z(z0) {}
};
struct Line {               // 二维的直线或线段
    Point p1, p2;
    Line() {}
    Line(Point p10, Point p20): p1(p10), p2(p20) {}
};
struct Line3D {             // 三维的直线或线段
    Point3D p1, p2;
    Line3D() {}
    Line3D(Point3D p10, Point3D p20): p1(p10), p2(p20) {}
};
struct Rect {              // 用长宽表示矩形的方法 w, h分别表示宽度和高度
    double w, h;
 Rect() {}
 Rect(double _w,double _h) : w(_w),h(_h) {}
};
struct Rect_2 {             // 表示矩形，左下角坐标是(xl, yl)，右上角坐标是(xh, yh)
    double xl, yl, xh, yh;
 Rect_2() {}
 Rect_2(double _xl,double _yl,double _xh,double _yh) : xl(_xl),yl(_yl),xh(_xh),yh(_yh) {}
};
struct Circle {            //圆
 Point c;
 double r;
 Circle() {}
 Circle(Point _c,double _r) :c(_c),r(_r) {}
};
typedef vector<Point> Polygon;      // 二维多边形
typedef vector<Point> Points;       // 二维点集
typedef vector<Point3D> Points3D;   // 三维点集
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//基本函数区
inline double max(double x,double y)
{
    return x > y ? x : y;
}
inline double min(double x, double y)
{
    return x > y ? y : x;
}
inline bool ZERO(double x)              // x == 0
{
    return (fabs(x) < EPS);
}
inline bool ZERO(Point p)               // p == 0
{
    return (ZERO(p.x) && ZERO(p.y));
}
inline bool ZERO(Point3D p)              // p == 0
{
    return (ZERO(p.x) && ZERO(p.y) && ZERO(p.z));
}
inline bool EQ(double x, double y)      // eqaul, x == y
{
    return (fabs(x - y) < EPS);
}
inline bool NEQ(double x, double y)     // not equal, x != y
{
    return (fabs(x - y) >= EPS);
}
inline bool LT(double x, double y)     // less than, x < y
{
    return ( NEQ(x, y) && (x < y) );
}
inline bool GT(double x, double y)     // greater than, x > y
{
    return ( NEQ(x, y) && (x > y) );
}
inline bool LEQ(double x, double y)     // less equal, x <= y
{
    return ( EQ(x, y) || (x < y) );
}
inline bool GEQ(double x, double y)     // greater equal, x >= y
{
    return ( EQ(x, y) || (x > y) );
}
// 注意！！！
// 如果是一个很小的负的浮点数
// 保留有效位数输出的时候会出现-0.000这样的形式，
// 前面多了一个负号
// 这就会导致错误！！！！！！
// 因此在输出浮点数之前，一定要调用次函数进行修正！
inline double FIX(double x)
{
    return (fabs(x) < EPS) ? 0 : x;
}
//////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//二维矢量运算
bool operator==(Point p1, Point p2)
{
    return ( EQ(p1.x, p2.x) &&  EQ(p1.y, p2.y) );
}
bool operator!=(Point p1, Point p2)
{
    return ( NEQ(p1.x, p2.x) ||  NEQ(p1.y, p2.y) );
}
bool operator<(Point p1, Point p2)
{
    if (NEQ(p1.x, p2.x)) {
        return (p1.x < p2.x);
    } else {
        return (p1.y < p2.y);
    }
}
Point operator+(Point p1, Point p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}
Point operator-(Point p1, Point p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}
double operator*(Point p1, Point p2) // 计算叉乘 p1 × p2
{
    return (p1.x * p2.y - p2.x * p1.y);
}
double operator&(Point p1, Point p2) { // 计算点积 p1·p2
    return (p1.x * p2.x + p1.y * p2.y);
}
double Norm(Point p) // 计算矢量p的模
{
    return sqrt(p.x * p.x + p.y * p.y);
}
// 把矢量p旋转角度angle (弧度表示)
// angle > 0表示逆时针旋转
// angle < 0表示顺时针旋转
Point Rotate(Point p, double angle)
{
    Point result;
    result.x = p.x * cos(angle) - p.y * sin(angle);
    result.y = p.x * sin(angle) + p.y * cos(angle);
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
//三维矢量运算
bool operator==(Point3D p1, Point3D p2)
{
    return ( EQ(p1.x, p2.x) && EQ(p1.y, p2.y) && EQ(p1.z, p2.z) );
}
bool operator<(Point3D p1, Point3D p2)
{
    if (NEQ(p1.x, p2.x)) {
        return (p1.x < p2.x);
    } else if (NEQ(p1.y, p2.y)) {
        return (p1.y < p2.y);
    } else {
        return (p1.z < p2.z);
    }
}
Point3D operator+(Point3D p1, Point3D p2)
{
    return Point3D(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}
Point3D operator-(Point3D p1, Point3D p2)
{
    return Point3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}
Point3D operator*(Point3D p1, Point3D p2) // 计算叉乘 p1 x p2
{
    return Point3D(p1.y * p2.z - p1.z * p2.y,
        p1.z * p2.x - p1.x * p2.z,
        p1.x * p2.y - p1.y * p2.x );
}
double operator&(Point3D p1, Point3D p2) { // 计算点积 p1·p2
    return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}
double Norm(Point3D p) // 计算矢量p的模
{
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}


//////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//点.线段.直线问题
//
double Distance(Point p1, Point p2) //2点间的距离
{
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double Distance(Point3D p1, Point3D p2) //2点间的距离,三维
{
 return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}
double Distance(Point p, Line L) // 求二维平面上点到直线的距离
{
    return ( fabs((p - L.p1) * (L.p2 - L.p1)) / Norm(L.p2 - L.p1) );
}
double Distance(Point3D p, Line3D L)// 求三维空间中点到直线的距离
{
    return ( Norm((p - L.p1) * (L.p2 - L.p1)) / Norm(L.p2 - L.p1) );
}
bool OnLine(Point p, Line L) // 判断二维平面上点p是否在直线L上
{
    return ZERO( (p - L.p1) * (L.p2 - L.p1) );
}
bool OnLine(Point3D p, Line3D L) // 判断三维空间中点p是否在直线L上
{
    return ZERO( (p - L.p1) * (L.p2 - L.p1) );
}
int Relation(Point p, Line L) // 计算点p与直线L的相对关系 ,返回ONLINE,LEFT,RIGHT
{
    double res = (L.p2 - L.p1) * (p - L.p1);
    if (EQ(res, 0)) {
        return ONLINE;
    } else if (res > 0) {
        return LEFT;
    } else {
        return RIGHT;
    }
}
bool SameSide(Point p1, Point p2, Line L) // 判断点p1, p2是否在直线L的同侧
{
    double m1 = (p1 - L.p1) * (L.p2 - L.p1);
    double m2 = (p2 - L.p1) * (L.p2 - L.p1);
    return GT(m1 * m2, 0);
}
bool OnLineSeg(Point p, Line L) // 判断二维平面上点p是否在线段l上
{
    return ( ZERO( (L.p1 - p) * (L.p2 - p) ) &&
        LEQ((p.x - L.p1.x)*(p.x - L.p2.x), 0) &&
        LEQ((p.y - L.p1.y)*(p.y - L.p2.y), 0) );
}
bool OnLineSeg(Point3D p, Line3D L) // 判断三维空间中点p是否在线段l上
{
    return ( ZERO((L.p1 - p) * (L.p2 - p)) &&
        EQ( Norm(p - L.p1) + Norm(p - L.p2), Norm(L.p2 - L.p1)) );
}
Point SymPoint(Point p, Line L) // 求二维平面上点p关于直线L的对称点
{
    Point result;
    double a = L.p2.x - L.p1.x;
    double b = L.p2.y - L.p1.y;
    double t = ( (p.x - L.p1.x) * a + (p.y - L.p1.y) * b ) / (a*a + b*b);
    result.x = 2 * L.p1.x + 2 * a * t - p.x;
    result.y = 2 * L.p1.y + 2 * b * t - p.y;
    return result;
}
bool Coplanar(Points3D points) // 判断一个点集中的点是否全部共面
{
    int i;
    Point3D p;


    if (points.size() < 4) return true;
    p = (points[2] - points[0]) * (points[1] - points[0]);
    for (i = 3; i < points.size(); i++) {
        if (! ZERO(p & points[i]) ) return false;
    }
    return true;
}
bool LineIntersect(Line L1, Line L2) // 判断二维的两直线是否相交
{
    return (! ZERO((L1.p1 - L1.p2)*(L2.p1 - L2.p2)) );  // 是否平行
}
bool LineIntersect(Line3D L1, Line3D L2) // 判断三维的两直线是否相交
{
    Point3D p1 = L1.p1 - L1.p2;
    Point3D p2 = L2.p1 - L2.p2;
    Point3D p  = p1 * p2;
    if (ZERO(p)) return false;      // 是否平行
    p = (L2.p1 - L1.p2) * (L1.p1 - L1.p2);
    return ZERO(p & L2.p2);         // 是否共面
}
bool LineSegIntersect(Line L1, Line L2) // 判断二维的两条线段是否相交
{
    return ( GEQ( max(L1.p1.x, L1.p2.x), min(L2.p1.x, L2.p2.x) ) &&
        GEQ( max(L2.p1.x, L2.p2.x), min(L1.p1.x, L1.p2.x) ) &&
        GEQ( max(L1.p1.y, L1.p2.y), min(L2.p1.y, L2.p2.y) ) &&
        GEQ( max(L2.p1.y, L2.p2.y), min(L1.p1.y, L1.p2.y) ) &&
        LEQ( ((L2.p1 - L1.p1) * (L1.p2 - L1.p1)) * ((L2.p2 -  L1.p1) * (L1.p2 - L1.p1)), 0 ) &&
        LEQ( ((L1.p1 - L2.p1) * (L2.p2 - L2.p1)) * ((L1.p2 -  L2.p1) * (L2.p2 - L2.p1)), 0 ) );
}
bool LineSegIntersect(Line3D L1, Line3D L2) // 判断三维的两条线段是否相交
{
    // todo
    return true;
}
// 计算两条二维直线的交点，结果在参数P中返回
// 返回值说明了两条直线的位置关系:  COLINE   -- 共线  PARALLEL -- 平行  CROSS    -- 相交
int CalCrossPoint(Line L1, Line L2, Point& P)
{
    double A1, B1, C1, A2, B2, C2;


    A1 = L1.p2.y - L1.p1.y;
    B1 = L1.p1.x - L1.p2.x;
    C1 = L1.p2.x * L1.p1.y - L1.p1.x * L1.p2.y;


    A2 = L2.p2.y - L2.p1.y;
    B2 = L2.p1.x - L2.p2.x;
    C2 = L2.p2.x * L2.p1.y - L2.p1.x * L2.p2.y;


    if (EQ(A1 * B2, B1 * A2))    {
        if (EQ( (A1 + B1) * C2, (A2 + B2) * C1 )) {
            return COLINE;
        } else {
            return PARALLEL;
        }
    } else {
        P.x = (B2 * C1 - B1 * C2) / (A2 * B1 - A1 * B2);
        P.y = (A1 * C2 - A2 * C1) / (A2 * B1 - A1 * B2);
        return CROSS;
    }
}
// 计算两条三维直线的交点，结果在参数P中返回
// 返回值说明了两条直线的位置关系 COLINE   -- 共线  PARALLEL -- 平行  CROSS    -- 相交  NONCOPLANAR -- 不公面
int CalCrossPoint(Line3D L1, Line3D L2, Point3D& P)
{
    // todo
    return 0;
}
// 计算点P到直线L的最近点
Point NearestPointToLine(Point P, Line L)
{
    Point result;
    double a, b, t;


    a = L.p2.x - L.p1.x;
    b = L.p2.y - L.p1.y;
    t = ( (P.x - L.p1.x) * a + (P.y - L.p1.y) * b ) / (a * a + b * b);


    result.x = L.p1.x + a * t;
    result.y = L.p1.y + b * t;
    return result;
}
// 计算点P到线段L的最近点
Point NearestPointToLineSeg(Point P, Line L)
{
    Point result;
    double a, b, t;


    a = L.p2.x - L.p1.x;
    b = L.p2.y - L.p1.y;
    t = ( (P.x - L.p1.x) * a + (P.y - L.p1.y) * b ) / (a * a + b * b);


    if ( GEQ(t, 0) && LEQ(t, 1) ) {
        result.x = L.p1.x + a * t;
        result.y = L.p1.y + b * t;
    } else {
        if ( Norm(P - L.p1) < Norm(P - L.p2) ) {
            result = L.p1;
        } else {
            result = L.p2;
        }
    }
    return result;
}
// 计算险段L1到线段L2的最短距离
double MinDistance(Line L1, Line L2)
{
    double d1, d2, d3, d4;


    if (LineSegIntersect(L1, L2)) {
        return 0;
    } else {
        d1 = Norm( NearestPointToLineSeg(L1.p1, L2) - L1.p1 );
        d2 = Norm( NearestPointToLineSeg(L1.p2, L2) - L1.p2 );
        d3 = Norm( NearestPointToLineSeg(L2.p1, L1) - L2.p1 );
        d4 = Norm( NearestPointToLineSeg(L2.p2, L1) - L2.p2 );

        return min( min(d1, d2), min(d3, d4) );
    }
}
// 求二维两直线的夹角，
// 返回值是0~Pi之间的弧度
double Inclination(Line L1, Line L2)
{
    Point u = L1.p2 - L1.p1;
    Point v = L2.p2 - L2.p1;
    return acos( (u & v) / (Norm(u)*Norm(v)) );
}
// 求三维两直线的夹角，
// 返回值是0~Pi之间的弧度
double Inclination(Line3D L1, Line3D L2)
{
    Point3D u = L1.p2 - L1.p1;
    Point3D v = L2.p2 - L2.p1;
    return acos( (u & v) / (Norm(u)*Norm(v)) );
}
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// 判断两个矩形是否相交
// 如果相邻不算相交
bool Intersect(Rect_2 r1, Rect_2 r2)
{
    return ( max(r1.xl, r2.xl) < min(r1.xh, r2.xh) &&
             max(r1.yl, r2.yl) < min(r1.yh, r2.yh) );
}
// 判断矩形r2是否可以放置在矩形r1内
// r2可以任意地旋转
//发现原来的给出的方法过不了OJ上的无归之室这题，
//所以用了自己的代码
bool IsContain(Rect r1, Rect r2)      //矩形的w>h
 {
     if(r1.w >r2.w && r1.h > r2.h) return true;
     else
     {
        double r = sqrt(r2.w*r2.w + r2.h*r2.h) / 2.0;
        double alpha = atan2(r2.h,r2.w);
        double sita = asin((r1.h/2.0)/r);
        double x = r * cos(sita - 2*alpha);
        double y = r * sin(sita - 2*alpha);
        if(x < r1.w/2.0 && y < r1.h/2.0 && x > 0 && y > -r1.h/2.0) return true;
        else return false;
     }
}
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//圆
Point Center(const Circle & C) //圆心
{
    return C.c;
}


double Area(const Circle &C)
{
 return pi*C.r*C.r;
}


double CommonArea(const Circle & A, const Circle & B) //两个圆的公共面积
{
    double area = 0.0;
    const Circle & M = (A.r > B.r) ? A : B;
    const Circle & N = (A.r > B.r) ? B : A;
    double D = Distance(Center(M), Center(N));
    if ((D < M.r + N.r) && (D > M.r - N.r))
    {
        double cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);
        double cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);
        double alpha = 2.0 * acos(cosM);
        double beta  = 2.0 * acos(cosN);
        double TM = 0.5 * M.r * M.r * sin(alpha);
        double TN = 0.5 * N.r * N.r * sin(beta);
        double FM = (alpha / (2*pi)) * Area(M);
        double FN = (beta / (2*pi)) * Area(N);
        area = FM + FN - TM - TN;
    }
    else if (D <= M.r - N.r)
    {
        area = Area(N);
    }
    return area;
}

bool IsInCircle(const Circle & C, const Rect_2 & rect)//判断圆是否在矩形内(不允许相切)
{
    return (GT(C.c.x - C.r, rect.xl)
  &&  LT(C.c.x + C.r, rect.xh)
  &&  GT(C.c.y - C.r, rect.yl)
  &&  LT(C.c.y + C.r, rect.yh));
}


//判断2圆的位置关系
//返回:
//BAOHAN   = 1;        // 大圆包含小圆
//NEIQIE   = 2;        // 内切
//XIANJIAO = 3;        // 相交
//WAIQIE   = 4;        // 外切
//XIANLI   = 5;        // 相离
int CirCir(const Circle &c1, const Circle &c2)//判断2圆的位置关系
{
 double dis = Distance(c1.c,c2.c);
 if(LT(dis,fabs(c1.r-c2.r))) return BAOHAN;
 if(EQ(dis,fabs(c1.r-c2.r))) return NEIQIE;
 if(LT(dis,c1.r+c2.r) && GT(dis,fabs(c1.r-c2.r))) return XIANJIAO;
 if(EQ(dis,c1.r+c2.r)) return WAIQIE;
 return XIANLI;
}
////////////////////////////////////////////////////////////////////////


int main()
{
 return 0;
}
