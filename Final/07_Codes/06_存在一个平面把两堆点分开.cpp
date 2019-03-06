#include <stdio.h>
struct point
{
	double x, y, z;
}pa[201], pb[201];
int main()
{
	int n, m, i;
	while (scanf("%d", &n), n != -1)
	{
		for (i = 0; i < n; i++)
			scanf("%lf%lf%lf", &pa[i].x, &pa[i].y, &pa[i].z);
		scanf("%d", &m);
		for (i = 0; i < m; i++)
			scanf("%lf%lf%lf", &pb[i].x, &pb[i].y, &pb[i].z);
		int cnt = 0, finish = 0;
		double a = 0, b = 0, c = 0, d = 0;
		while (cnt < 100000 && !finish)
		{
			finish = 1;
			for (i = 0; i < n; i++)
				if (a * pa[i].x + b * pa[i].y + c * pa[i].z + d > 0)
				{
					a -= pa[i].x;
					b -= pa[i].y;
					c -= pa[i].z;
					d -= 3;
					finish = 0;
				}
			for (i = 0; i < m; i++)
				if (a * pb[i].x + b * pb[i].y + c * pb[i].z + d <= 0)
				{
					a += pb[i].x;
					b += pb[i].y;
					c += pb[i].z;
					d += 3;
					finish = 0;
				}
			cnt++;
		}
		printf("%lf %lf %lf %lf\n", a, b, c, d);
	}
	return 0;
}
