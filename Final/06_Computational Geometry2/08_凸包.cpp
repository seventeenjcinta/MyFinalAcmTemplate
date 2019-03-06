//水平序
#define maxn 100005


struct point
{double x,y;}p[maxn],s[maxn];
bool operator < (point a,point b)
{return a.x<b.x || a.x==b.x&&a.y<b.y;}


int n,f;


double cp(point a,point b,point c)
{return (c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);}


void Convex(point *p,int &n)
{
	sort(p,p+n);
	int i,j,r,top,m;
	s[0] = p[0];s[1] = p[1];top = 1;
	for(i=2;i<n;i++)
	{
		while( top>0 && cp(p[i],s[top],s[top-1])>=0 ) top--;
		top++;s[top] = p[i];
	}
	m = top;
	top++;s[top] = p[n-2];
	for(i=n-3;i>=0;i--)
	{
		while( top>m && cp(p[i],s[top],s[top-1])>=0 ) top--;
		top++;s[top] = p[i];
	}
	top--;
	n = top+1;
}


// 极角序
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define maxn 100005
int N;
struct A
{
	int x,y;
	int v,l;
}P[maxn];
int xmult(int x1,int y1,int x2,int y2,int x3,int y3)
{
	return (y2-y1)*(x3-x1)-(y3-y1)*(x2-x1);
}
void swap(A &a,A &b)
{
	A t = a;a = b,b = t;
}
bool operator < (A a,A b)
{
	int k = xmult(P[0].x,P[0].y,a.x,a.y,b.x,b.y);
	if( k<0 )
		return 1;
	else if( k==0 )
	{
		if( abs(P[0].x-a.x)<abs(P[0].x-b.x) )
			return 1;
		if( abs(P[0].y-a.y)<abs(P[0].y-b.y) )
			return 1;
	}
	return 0;
}
void Grem_scan(int n)
{
	int i,j,k,l;
	k = 0x7fffffff;
	for(i=0;i<n;i++)
		if( P[i].x<k || P[i].x==k && P[i].y<P[l].y )
		k = P[i].x,l = i;
	swap(P[l],P[0]);
	sort(P+1,P+n);

	l = 3;
	for(i=3;i<n;i++)
	{
		while( xmult(P[l-2].x,P[l-2].y,P[l-1].x,P[l-1].y,P[i].x,P[i].y)>0 )
			l--;
		P[l++] = P[i];
	}
}
main()
{
	int i,j,k,l;
	N = 0;
	while( scanf("%d%d",&P[N].x,&P[N].y)!=EOF )
		N++;
	Grem_scan(N);
	for(i=0;i<N;i++)
		if( P[i].x==0 && P[i].y==0 )
		break;
	k = i++;
	printf("(0,0)\n");
	while( i!=k )
		printf("(%d,%d)\n",P[i].x,P[i].y),i = (i+1)%N;
}


//卷包裹法
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define maxn 55
struct A
{
	int x,y;
}P[maxn];
int T,N;
bool B[maxn];
int as[maxn],L;
int xmult(A a,A b,A c)
{
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
main()
{
	int i,j,k,l;
	scanf("%d",&T);
	while( T-- )
	{
		scanf("%d",&N);
		k = 0x7ffffff;
		for(i=0;i<N;i++)
		{
			scanf("%d%d%d",&j,&P[i].x,&P[i].y);
			if( P[i].y<k )
				k = P[i].y,l = i;
		}
		memset(B,0,sizeof(B));
		B[l] = 1;
		as[0] = l;
		L = 1;
		while( 1 )
		{
			A a,b;
			if( L==1 )
				a.x = 0,a.y = P[as[0]].y;
			else
				a = P[as[L-2]];
			b = P[as[L-1]];


			k = -1;
			for(i=0;i<N;i++)
			{
				if( B[i] )
					continue;
				if( xmult(a,b,P[i])<0 )
					continue;
				if( k==-1 || xmult(P[as[L-1]],P[k],P[i])<0 || xmult(P[as[L-1]],P[k],P[i])==0 && P[i].y<P[k].y )
					k = i;
			}
			if( k==-1 )
				break;
			B[k] = 1;
			as[L++] = k;
		}
		printf("%d ",L);
		for(i=0;i<L;i++)
			printf("%d ",as[i]+1);
		printf("\n");
	}
}
