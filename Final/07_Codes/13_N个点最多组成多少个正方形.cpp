
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 1e-6
#define pi acos(-1.0)


#define PRIME 9991


struct point
{
    int x, y;
}p[2201];
int n;


struct HASH
{
    int cnt;
    int next;
}hash[50000];
int hashl;


int Hash(int n)
{
    int i = n % PRIME;
    while(hash[i].next != -1){
        if(hash[hash[i].next].cnt == n) return 1;
        else if(hash[hash[i].next].cnt > n) break;
        i = hash[i].next;
    }
    hash[hashl].cnt = n;
    hash[hashl].next = hash[i].next;
    hash[i].next = hashl;
    hashl++;
    return 0;
}


int Hash2(int n)
{
    int i = n % PRIME;
    while(hash[i].next != -1){
        if(hash[hash[i].next].cnt == n) return 1;
        else if(hash[hash[i].next].cnt > n) return 0;
        i = hash[i].next;
    }
    return 0;
}


int check(double ax, double ay, int &x, int &y)
{
    int a0 = (int)ax;
    int b0 = (int)ay;
    int tag1 = 0, tag2 = 0;
    if(fabs(a0 - ax) < eps){
        tag1 = 1;
        x = a0;
    }
    else if(fabs(a0 + 1 - ax) < eps){
        tag1 = 1;
        x = a0 + 1;
    }
    if(fabs(b0 - ay) < eps){
        tag2 = 1;
        y = b0;
    }
    else if(fabs(b0 + 1 - ay) < eps){
        y = b0 + 1;
        tag2 = 1;
    }
    if(tag1 == 1 && tag2 == 1) return 1;
    else return 0;
}


int squares(point p1, point p2, point &p3, point &p4)
{
    double a = (double)p2.x - p1.x;
    double b = (double)p2.y - p1.y;
    double midx = ((double)p1.x + p2.x) / 2;
    double midy = ((double)p1.y + p2.y) / 2;
    double tmp = a * a + b * b;
    double x1 = sqrt(b * b) / 2;
    double y1;
    if(fabs(b) < eps) y1 = sqrt(a * a + b * b) / 2;
    else y1 = -a * x1 / b;
    x1 += midx;
    y1 += midy;
    if(check(x1, y1, p3.x, p3.y) == 0) return 0;
    x1 = 2 * midx - x1;
    y1 = 2 * midy - y1;
    if(check(x1, y1, p4.x, p4.y) == 0) return 0;
    return 1;
}


int main()
{
    int i, j, cnt;
    while(scanf("%d", &n) != EOF && n)
    {
		for(i = 0;i < PRIME;i++) hash[i].next = -1;
		hashl = PRIME;
		int x1, y1, x2, y2;
		for (i = 0; i < n; i++){
			scanf("%d%d", &p[i].x, &p[i].y);
			Hash((p[i].x + 100000) * 100000 + p[i].y + 100000);
		}
		cnt = 0;
		for (i = 0; i < n; i++){
			for (j = i + 1; j < n; j++)
			{
				point a, b;
				if(squares(p[i], p[j], a, b) == 0) continue;
				if(Hash2((a.x + 100000) * 100000 + a.y + 100000) == 0) continue;
				if(Hash2((b.x + 100000) * 100000 + b.y + 100000) == 0) continue;
				cnt++;
			}
		}
		printf("%d\n", cnt / 2);
	}
    return 0;
}
