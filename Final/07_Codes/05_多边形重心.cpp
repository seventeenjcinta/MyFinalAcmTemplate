/*
题目描述：
有一个密度均匀的平面N多边形(3 <= N <= 1000000)，可能凹也可能凸，但没有边相交叉，
另外已知N个有序(顺时针或逆时针)顶点的坐标值，第j个顶点坐标为（Xi ， Yi ），且满
足 (|Xi|, |Yi| <= 20000)，求这个平面多边形的重心。
  解题过程：
  从第1个顶点出发，分别连接第i, i+1个顶点组成三角形Ti,1 < i < n,
  一共n-2个三角形正好是多连形的一个划分，分别求出每个三角形的面积Si，
  总面积为各个面积相加
  根据物理学知识得：n个点(xi,yi)每个重量是mi,则重心是
  X = (x1*M1+x2*M2+...+xn*Mn) / (M1+M2+....+Mn)
  Y = (y1*M1+y2*M2+...+yn*Mn) / (M1+M2+....+Mn)
  另个需要用的知识有：
  已知3点求三角形的面积，设三点分别为p[0].x, p[0].y p[1].x, p[1].y p[1].x, p[1].y
  面积s =[ p[0].x*p[1].y-p[1].x*p[0].y + p[1].x*p[2].y-p[2].x*p[1].y + p[2].x*p[0].y-p[0].x*p[2].y ] / 2 ,
  这是这3个点是逆时针的值，顺时针取负。
  已知3点求重心，x = (p[0].x+p[1].x+p[2].x)/3.0 , y = (p[0].y+p[1].y+p[2].y)/3.0
  另外在求解的过程中，不需要考虑点的输入顺序是顺时针还是逆时针，相除后就抵消了，
  还要注意 一点是不必在求每个小三角形的重心时都除以3，可以在最后除一下

*/
/*fzu_1132*/
#include <stdio.h>
#include <math.h>


typedef struct TPoint
{
    double x;
    double y;
}TPoint;


double triangleArea(TPoint p0, TPoint p1, TPoint p2)
{
    //已知三角形三个顶点的坐标，求三角形的面积
    double k = p0.x * p1.y + p1.x * p2.y
		+ p2.x * p0.y - p1.x * p0.y
		- p2.x * p1.y - p0.x * p2.y;
	//if(k >= 0) return k / 2;
//	else return -k / 2;
       return k / 2;
}


int main()
{
    int i, n, test;
	TPoint p0, p1, p2, center;
    double area, sumarea, sumx, sumy;
    scanf("%d", &test);
    while(test--){
		scanf("%d", &n);
		scanf("%lf%lf", &p0.x, &p0.y);
		scanf("%lf%lf", &p1.x, &p1.y);
        sumx = 0;
        sumy = 0;
        sumarea = 0;
        for(i = 2;i < n;i++){
			scanf("%lf%lf", &p2.x, &p2.y);
            center.x = p0.x + p1.x + p2.x;
            center.y = p0.y + p1.y + p2.y;
            area =  triangleArea(p0, p1, p2);
            sumarea += area;
			sumx += center.x * area;
			sumy += center.y * area;
			p1 = p2;
        }
        printf("%.2lf %.2lf\n", sumx / sumarea / 3, sumy / sumarea / 3);
    }
    return 0;
}
