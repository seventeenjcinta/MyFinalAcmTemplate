//Xc = 2*R*sinA/3/A
//A为圆心角的一半
#include <stdio.h>
#include <math.h>
int main()
{
	double r, angle;
	while(scanf("%lf%lf", &r, &angle) != EOF){
		angle /= 2;
		printf("%.6lf\n", 2 * r * sin(angle) / 3 / angle);
	}
	return 0;
}
