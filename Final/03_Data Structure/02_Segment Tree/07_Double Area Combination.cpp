#include <bits/stdc++.h>
using namespace std;
const int MAXN=2020;
struct Node
{
    int l,r;
    int c;
    double lf,rf;
    double cnt;//覆盖一次以上的长度
    double more;//覆盖两次以上的长度
}segTree[MAXN*3];
struct Line
{
    double x,y1,y2;
    double f;
}line[MAXN];

double y[MAXN];

bool cmp(Line a,Line b)
{
    return a.x<b.x;
}

void Build(int i,int l,int r)
{
    segTree[i].l=l;
    segTree[i].r=r;
    segTree[i].cnt=0;
    segTree[i].more=0;
    segTree[i].lf=y[l];
    segTree[i].rf=y[r];
    if(l+1==r)return;
    int mid=(l+r)>>1;
    Build(i<<1,l,mid);
    Build((i << 1) | 1, mid,r);
}
void calen(int i)
{
    if(segTree[i].c>=2)
    {
        segTree[i].more=segTree[i].cnt=segTree[i].rf-segTree[i].lf;
        return;
    }
    else if(segTree[i].c==1)
    {
        segTree[i].cnt=segTree[i].rf-segTree[i].lf;
        if(segTree[i].l+1==segTree[i].r)segTree[i].more=0;
        else segTree[i].more=segTree[i<<1].cnt+segTree[(i<<1)|1].cnt;
    }
    else
    {
        if(segTree[i].l+1==segTree[i].r)
        {
            segTree[i].cnt=segTree[i].more=0;
        }
        else
        {
            segTree[i].cnt=segTree[i<<1].cnt+segTree[(i<<1)|1].cnt;
            segTree[i].more=segTree[i<<1].more+segTree[(i<<1)|1].more;
        }
    }
}
void update(int i,Line e)
{
    if(e.y1==segTree[i].lf&&segTree[i].rf==e.y2)
    {
        segTree[i].c+=e.f;
        calen(i);
        return;
    }
    if(e.y2<=segTree[i<<1].rf) update(i<<1,e);
    else if(e.y1>=segTree[(i<<1)|1].lf) update((i<<1)|1,e);
    else
    {
        Line temp=e;
        temp.y2=segTree[i<<1].rf;
        update(i<<1,temp);
        temp=e;
        temp.y1=segTree[(i<<1)|1].lf;
        update((i<<1)|1,temp);
    }
    calen(i);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n;
    double x1,y1,x2,y2;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int t=1;
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            line[t].x=x1;
            //这里题目描述有问题？左下角和右上角
            line[t].y1=y1;
            line[t].y2=y2;
            line[t].x=x1;
            line[t].f=1;
            y[t]=y1;
            t++;
            line[t].y1=y1;
            line[t].y2=y2;
            line[t].x=x2;
            line[t].f=-1;
            y[t]=y2;
            t++;
        }
        sort(line+1,line+t,cmp);
        sort(y+1,y+t);
        Build(1,1,t-1);
        update(1,line[1]);
        double ans=0;
        for(int i=2;i<t;i++)
        {
            ans+=segTree[1].more*(line[i].x-line[i-1].x);
            update(1,line[i]);
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
