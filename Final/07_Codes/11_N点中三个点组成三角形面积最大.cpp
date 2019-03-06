
//Rotating Calipers algorithm




#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MaxNode 50005


int stack[MaxNode];
int top;
double max;


typedef struct TPoint
{
    int x;
    int y;
}TPoint;
TPoint point[MaxNode];


void swap(TPoint point[], int i, int j)
{
    TPoint tmp;
    tmp = point[i];
    point[i] = point[j];
    point[j] = tmp;
}


double multi(TPoint p1, TPoint p2, TPoint p0)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}


double distance(TPoint p1, TPoint p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


int cmp(const void *a, const void *b)
{
    TPoint *c = (TPoint *)a;
    TPoint *d = (TPoint *)b;
    double k = multi(*c, *d, point[0]);
    if(k< 0) return 1;
    else if(k == 0 && distance(*c, point[0]) >= distance(*d, point[0]))
	        return 1;
    else return -1;
}


void grahamScan(int n)
{
    //Graham扫描求凸包
    int i, u;

    //将最左下的点调整到p[0]的位置
    u = 0;
    for(i = 1;i <= n - 1;i++){
        if((point[i].y < point[u].y) ||
		     (point[i].y == point[u].y && point[i].x  < point[u].x))
			u = i;
    }
    swap(point, 0, u);

    //将平p[1]到p[n - 1]按按极角排序，可采用快速排序
    qsort(point + 1, n - 1, sizeof(point[0]), cmp);

    for(i = 0;i <= 2;i++) stack[i] = i;
    top = 2;
    for(i = 3;i <= n - 1;i++){
        while(multi(point[i], point[stack[top]], point[stack[top - 1]]) >= 0){
			top--;
			if(top == 0) break;
        }
        top++;
        stack[top] = i;
    }
}


int main()
{
    double triangleArea(int i, int j, int k);
    void PloygonTriangle();
    int i, n;
    while(scanf("%d", &n) && n != -1){
        for(i = 0;i < n;i++)
			scanf("%d%d", &point[i].x, &point[i].y);
        if(n <= 2){
			printf("0.00\n");
            continue;
        }
        if(n == 3){
            printf("%.2lf\n", triangleArea(0, 1, 2));
            continue;
        }
        grahamScan(n);
        PloygonTriangle();
        printf("%.2lf\n", max);
    }
    return 0;
}


void PloygonTriangle()
{
    double triangleArea(int i, int j, int k);
    int i, j , k;
    double area, area1;
    max = -1;
	for(i = 0;i <= top - 2;i++){
		k = -1;
		for(j = i + 1; j <= top - 1;j++){
			if(k <= j) k= j + 1;
			area = triangleArea(stack[i], stack[j], stack[k]);
			if(area > max) max = area;
			while(k + 1 <= top){
				area1= triangleArea(stack[i], stack[j], stack[k + 1]);
				if(area1 < area) break;
				if(area1 > max) max = area1;
				area = area1;
				k++;
			}
		}
	}
}


double triangleArea(int i, int j, int k)
{
    //已知三角形三个顶点的坐标，求三角形的面积
    double l = fabs(point[i].x * point[j].y + point[j].x * point[k].y
		+ point[k].x * point[i].y - point[j].x * point[i].y
		- point[k].x * point[j].y - point[i].x * point[k].y) / 2;
    return l;
}
