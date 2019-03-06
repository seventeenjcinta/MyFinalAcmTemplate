//Nlgn
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define maxn 20005
#define eps 1e-10


struct point
{double x,y;};
struct line
{point s,e;double k;};


line L[maxn];
point S[maxn];


int N,Q[maxn];


double cross(point a,point b,point c) // c在直线ab右边返回<0
{return (c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);}


bool operator < (line a,line b) // 直线se右边为可行域
{
	if( fabs(a.k-b.k)<eps )
		return cross(b.s,b.e,a.s)<0;
	return a.k<b.k;
}


point intersection(point u1,point u2,point v1,point v2){
	point ret=u1;
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
		/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	ret.x+=(u2.x-u1.x)*t;
	ret.y+=(u2.y-u1.y)*t;
	return ret;
}


double HalfInSec()
{
	int i,j,k,l;
	sort(L,L+N);  // 极角[-pi,pi]排序

	for(i=1,j=0;i<N;i++)  // 去掉相同极角直线
		if( fabs(L[i].k-L[j].k)>eps )
		L[++j] = L[i];
	N = j+1;


	k = 0,l = 1;
	Q[0] = 0,Q[1] = 1;
	S[1] = intersection(L[0].s,L[0].e,L[1].s,L[1].e);
	for(i=2;i<N;i++)
	{
		while( k<l && cross(L[i].s,L[i].e,S[l])>eps )
			l--;
		while( k<l && cross(L[i].s,L[i].e,S[k+1])>eps )
			k++;
		Q[++l] = i;
		S[l] = intersection(L[Q[l-1]].s,L[Q[l-1]].e,L[i].s,L[i].e);
	}


	while( k<l && cross(L[Q[k]].s,L[Q[k]].e,S[l])>eps )
		l--;
	while( k<l && cross(L[Q[l]].s,L[Q[l]].e,S[k+1])>eps )
		k++;
	S[k] = intersection(L[Q[l]].s,L[Q[l]].e,L[Q[k]].s,L[Q[k]].e);
	S[++l] = S[k];


	double s = 0;
	for(i=k;i<l;i++)
		s += S[i].y*S[i+1].x-S[i+1].y*S[i].x;
	return fabs(s/2);
}
int main()
{
	int i,j,k,l;
	scanf("%d",&N);
	for(i=0;i<N;i++)
		scanf("%lf%lf%lf%lf",&L[i].e.x,&L[i].e.y,&L[i].s.x,&L[i].s.y);
	L[N].s.x = 0,L[N].s.y = 0;
	L[N+1].s.x = 10000,L[N+1].s.y = 0;
	L[N+2].s.x = 10000,L[N+2].s.y = 10000;
	L[N+3].s.x = 0,L[N+3].s.y = 10000;
	L[N].e = L[N+3].s;
	L[N+1].e = L[N].s;
	L[N+2].e = L[N+1].s;
	L[N+3].e = L[N+2].s;
	N += 4;
	for(i=0;i<N;i++)
		L[i].k = atan2(L[i].s.y-L[i].e.y,L[i].s.x-L[i].e.x);
	printf("%.1lf\n",HalfInSec());
}
