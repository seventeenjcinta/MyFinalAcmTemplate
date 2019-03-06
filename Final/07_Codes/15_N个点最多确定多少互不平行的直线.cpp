#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define eps 1e-6
#define pi acos(-1)


struct point
{
	double x, y;
};


double FindSlewRate(point p1, point p2)
{
	point p;
	p.x = p2.x - p1.x;
	p.y = p2.y - p1.y;
	if(fabs(p.x) < eps) return pi / 2;
	double tmp = atan(p.y / p.x);
	if(tmp < 0) return pi + tmp;
	return tmp;
}


int cmp(const void *a, const void *b)
{
	double *c = (double *)a;
	double *d = (double *)b;
	if(*c < *d) return -1;
	return 1;
}


int main()
{
	int n, rt;
	point p[205];
	double rate[40005];
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0;i < n;i++)
			scanf("%lf%lf", &p[i].x ,&p[i].y);
		rt = 0;
		for(int i = 0;i < n;i++)
			for(int j = i + 1;j < n;j++)
				rate[rt++] = FindSlewRate(p[i], p[j]);
		qsort(rate, rt, sizeof(rate[0]), cmp);
		int ans = 1;
		for(int i = 1;i < rt;i++)
			if(rate[i] > rate[i - 1]) ans++;
		//×¢ÒâÕâÀïÐ´fabs(rate[i] - rate[i - 1]) > eps Wrong Answer
		printf("%d\n", ans);
	}
	return 0;
}
