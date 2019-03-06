#include<stdio.h>
#include<math.h>


#define eps 1e-6
#define MaX 6000


/*-----------多边形结构------------*/
struct POLYGON{
   int n;                                  //多边形顶点数
   double x[MaX],y[MaX];        //顶点坐标
}poly;


int zd[100000][2],znum;      //跖对的集合和跖对的数量




/*------------辅助函数-----------*/
double dist(int a,int b,int c)
{
   double vx1,vx2,vy1,vy2;
   vx1=poly.x[b]-poly.x[a]; vy1=poly.y[b]-poly.y[a];
   vx2=poly.x[c]-poly.x[a]; vy2=poly.y[c]-poly.y[a];
   return fabs(vx1*vy2 - vy1*vx2);
}




/*-------------求凸多边形直径的函数-------------*/
double DIAMETER()
{
   znum=0;
   int i,j,k=1;
   double m,tmp;
   while(dist(poly.n-1,0,k+1) > dist(poly.n-1,0,k)+eps)
      k++;
   i=0; j=k;
   while(i<=k && j<poly.n)
   {
      zd[znum][0]=i; zd[znum++][1]=j;
      while(dist(i,i+1,j+1)>dist(i,i+1,j)-eps && j<poly.n-1)
      {
         zd[znum][0]=i; zd[znum++][1]=j;
         j++;
      }
      i++;
   }
   m=-1;
   for(i=0;i<znum;i++)
   {
      tmp =(poly.x[zd[i][0]]-poly.x[zd[i][1]]) * (poly.x[zd[i][0]]-poly.x[zd[i][1]]);
      tmp+=(poly.y[zd[i][0]]-poly.y[zd[i][1]]) * (poly.y[zd[i][0]]-poly.y[zd[i][1]]);
      if(m<tmp) m=tmp;
   }
   return sqrt(m);
}


/*----------主函数----------*/
int main()
{
   int i;
   while(scanf("%d",&poly.n)==1)
   {
      for(i=0;i<poly.n;i++)
         scanf("%lf %lf",&poly.x[i],&poly.y[i]);
      printf("%.3lf\n",DIAMETER());
   }
   return 0;
}
1.16.19 矩形面积并，周长并
见附录一5.11,5.12
1.16.20 pku2069 最小球覆盖
见附录一5.13,5.14
//最小闭合球
#include<stdio.h>
#include<math.h>
#include<memory>
#include<stdlib.h>
using namespace std;
const double eps = 1e-10;
struct point_type { double x, y, z; };
int npoint, nouter ;
point_type point [1000], outer[4], res;
double radius, tmp ;


inline double dist(point_type p1 , point_type p2)
{
double dx=p1.x-p2.x, dy=p1.y-p2.y,dz=p1.z-p2.z ;
return ( dx*dx + dy*dy + dz*dz ) ;
}


inline double dot( point_type p1 , point_type p2 )
{
return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}


void ball()
{
	point_type q[3];
	double m[3][3],sol[3],L[3],det; int i,j;
	res.x=res.y=res.z=-1000;
	radius=0;
    switch ( nouter )
		{
		case 1 : res=outer[0]; break;
		case 2 :
				 res.x=(outer[0].x+outer[1].x)/2;
				 res.y=(outer[0].y+outer[1].y)/2;
				 res.z=(outer[0].z+outer[1].z)/2;
				 radius=dist(res,outer[0]);
				 break;
		case 3 :
				 for ( i=0; i<2; ++i ) {
					q[i].x=outer[i+1].x-outer[0].x;
					q[i].y=outer[i+1].y-outer[0].y;
					q[i].z=outer[i+1].z-outer[0].z;
					}
				 for ( i=0; i<2; ++i )
					 for ( j=0; j<2; ++j )
						m[i][j]=dot(q[i],q[j])*2 ;
				 for ( i=0; i<2; ++i ) sol[i]=dot(q[i],q[i]);
				 if (fabs(det=m[0][0]*m[1][1]-m[0][1]*m[1][0]) < eps ) return ;

				 L[0]=(sol[0]*m[1][1]-sol[1]*m[0][1])/det;
				 L[1]=(sol[1]*m[0][0]-sol[0]*m[1][0])/det;
				 res.x=outer[0].x+q[0].x*L[0]+q[1].x*L[1];
				 res.y=outer[0].y+q[0].y*L[0]+q[1].y*L[1];
				 res.z=outer[0].z+q[0].z*L[0]+q[1].z*L[1];
				 radius=dist(res,outer[0]);
				 break;
		case 4 :
				 for ( i=0; i<3; ++i ){
					q[i].x=outer[i+1].x-outer[0].x;
					q[i].y=outer[i+1].y-outer[0].y;
					q[i].z=outer[i+1].z-outer[0].z;
					sol[i]=dot(q[i],q[i]);
					}
				 for ( i=0; i<3; ++i)
					 for ( j=0; j<3; ++j) m[i][j]=dot(q[i],q[j])*2;
				 det= m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0]
					 +m[0][2]*m[2][1]*m[1][0] - m[0][2]*m[1][1]*m[2][0]
					 -m[0][1]*m[1][0]*m[2][2] - m[0][0]*m[1][2]*m[2][1];


				 if ( fabs( det )<eps ) return;


				 for ( j=0; j<3; ++j ){
					for ( i=0; i<3; ++i ) m[i][j]=sol[i];
					 L[j]=( m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0]
						  + m[0][2]*m[2][1]*m[1][0] - m[0][2]*m[1][1]*m[2][0]
						  - m[0][1]*m[1][0]*m[2][2] - m[0][0]*m[1][2]*m[2][1]
						  ) / det;
					for( i=0; i<3; ++i ) m[i][j]=dot(q[i],q[j])*2;
					}
				 res=outer[0];
				 for ( i=0; i<3; ++i ) {
					res.x+=q[i].x*L[i];
				    res.y+=q[i].y*L[i];
					res.z+=q[i].z*L[i];
					}
				 radius=dist(res,outer[0]);
		}
}


void minball(int n)
{
  ball();
  if ( nouter <4 )
       for ( int i=0; i<n; ++i )
           if( dist(res,point[i])-radius>eps)
		    {
				outer[nouter]=point[i];
                ++nouter;
				minball(i);
				--nouter;
				if(i>0)
				{
				  point_type Tt = point[i] ;
				  memmove(&point[1], &point[0] , sizeof ( point_type )*i );
				  point[0]=Tt;
				}
			}
}






int main()
{
 int i;
 while(scanf("%d",&npoint)!=EOF,npoint)
	{
	 for(i=0;i<npoint;i++)
       scanf("%lf%lf%lf",&point[i].x,&point[i].y,&point[i].z);
	 nouter=0;
	 minball(npoint);
	 printf("%.8lf\n",sqrt(radius)+eps);
	}
 return 0;
}
