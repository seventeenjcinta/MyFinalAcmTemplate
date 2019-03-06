/*
假设地球是球体，
设地球上某点的经度为lambda,纬度为phi，
则这点的空间坐标是
x=cos(phi)*cos(lambda)
y=cos(phi)*sin(lambda)
z=sin(phi)
设地球上两点的空间坐标分别为(x1,y1,z1),(x2,y2,z2)
直线距离即为R*sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1)),
则它们的夹角为
A = acos(x1 * x2 + y1 * y2 + z1 * z2)，
则两地距离为 A * R，其中R为地球平均半径6371
*/


/*
这里坐标都要乘以半径R，但由于是求角度，所以统一都没有乘
注意这里还要判断坐标的正负和经度纬度的规定有关
pku_3407
*/
#include <stdio.h>
#include <math.h>


const double pi = acos(-1.0);


struct TPoint
{
   double x, y, z;
};

int main()
{
    double w1, wm1, j1, jm1, wd1, wd2;
    double w2, wm2, j2, jm2, jd1, jd2;
    TPoint p1, p2;
    char chr1, chr2;
    while(scanf("%lf%lf ", &w1, &wm1) != EOF){
        scanf("%c ", &chr1);
        scanf("%lf %lf %c", &j1, &jm1, &chr2);
        wd1 = (w1 + wm1 / 60) * pi / 180;
        jd1 = (j1 + jm1 / 60) * pi / 180;
        if(chr1 == 'S') wd1 *= -1.0;
        if(chr2 == 'W') jd1 *= -1.0;
        p1.x = cos(wd1) * cos(jd1);
        p1.y = cos(wd1) * sin(jd1);
        p1.z = sin(wd1);
        scanf("%lf %lf %c %lf %lf %c", &w2, &wm2, &chr1, &j2, &jm2, &chr2);
        wd2 = (w2 + wm2 / 60) * pi / 180;
        jd2 = (j2 + jm2 / 60) * pi / 180;
        if(chr1 == 'S') wd2 *= -1.0;
        if(chr2 == 'W') jd2 *= -1.0;
        p2.x = cos(wd2) * cos(jd2);
        p2.y = cos(wd2) * sin(jd2);
        p2.z = sin(wd2);
        double a = acos(p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
        printf("%.3lf\n", a * 6370.0);
    }
    return 0;
}
