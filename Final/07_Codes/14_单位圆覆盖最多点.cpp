/*
平面上N个点，用一个半径R的圆去覆盖，最多能覆盖多少个点？
比较经典的题目。
对每个点以R为半径画圆，对N个圆两两求交。这一步O(N^2)。问题转化为求被覆盖次数最多的弧。
对每一个圆，求其上的每段弧重叠次数。假如A圆与B圆相交。A上[PI/3, PI/2]的区间被B覆盖(PI为圆周率)。那么对于A圆，我们在PI/3处做一个+1标记，在PI/2处做一个-1标记。
对于[PI*5/3, PI*7/3]这样横跨0点的区间只要在0点处拆成两段即可。
将一个圆上的所有标记排序，从头开始扫描。初始ans = 0，碰到+1标记给ans++，碰到-1标记ans--。扫描过程中ans的最大值就是圆上被覆盖最多的弧。求所有圆的ans的最大值就是答案。
总复杂度O(N^2 * logN)
*/#include <stdio.h>
#include <math.h>


#define eps 1e-6


struct point
{
	double x, y;
};


double dis(point p1, point p2)
{
	point p3;
	p3.x = p2.x - p1.x;
	p3.y = p2.y - p1.y;
	return p3.x * p3.x + p3.y * p3.y;
}


point find_centre(point p1, point p2)
{
	point p3, mid, centre;
	double b, c, ang;
	p3.x = p2.x - p1.x;
	p3.y = p2.y - p1.y;
	mid.x = (p1.x + p2.x) / 2;
	mid.y = (p1.y + p2.y) / 2;
	b = dis(p1, mid);
	c = sqrt(1 - b);
	if(fabs(p3.y) < eps)//垂线的斜角90度
	{
		centre.x = mid.x;
		centre.y = mid.y + c;
	}
	else
	{
		ang = atan(-p3.x / p3.y);
		centre.x = mid.x + c * cos(ang);
		centre.y = mid.y + c * sin(ang);
	}
	return centre;
}


int main()
{
    int n, ans, tmpans, i, j, k;
    point p[305], centre;
    double tmp;
    while(scanf("%d", &n) && n)
    {
		for(i = 0;i < n;i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		ans = 1;
		for(i = 0;i < n;i++)
			for(j = i + 1;j < n;j++)
			{
				if(dis(p[i], p[j]) > 4) continue;
				tmpans = 0;
				centre = find_centre(p[i], p[j]);
				for(k = 0;k < n;k++)
				{
					//if(tmpans + n - k <= ans) break;
					tmp = dis(centre, p[k]);
					//if(tmp < 1.0 || fabs(tmp - 1.0) < eps) tmpans++;
					if(tmp <= 1.000001) tmpans++;
				}
				if(ans < tmpans) ans = tmpans;
			}
		printf("%d\n", ans);
    }
    return 0;
}
