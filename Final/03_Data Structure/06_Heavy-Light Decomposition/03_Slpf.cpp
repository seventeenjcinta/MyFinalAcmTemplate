#include <bits/stdc++.h>
using namespace std;
const int N=50010;
int tot=1,num=0,n,m,point[N],next[N*10],pos[N]={0},siz[N]={0},v[N]={0};
int belong[N]={0},fa[N][20]={0},deep[N]={0},map[N];
bool use[N];
char ch[10];
struct S{
    int maxn,sum;
}tr[N*4];
struct C{
    int st,en;
}aa[N*10];
inline void add(int i,int j)
{
    tot+=1;next[tot]=point[i];point[i]=tot;
    aa[tot].st=i;aa[tot].en=j;
    tot+=1;next[tot]=point[j];point[j]=tot;
    aa[tot].st=j;aa[tot].en=i;
}
inline void dfs1(int x)
{
    int i;
    siz[x]=1;
    use[x]=false;
    for(i=1;i<=14;++i){
        if(deep[x]<(1<<i)) break;
        fa[x][i]=fa[fa[x][i-1]][i-1];
    }
    for(i=point[x];i;i=next[i])
      if(use[aa[i].en]){
        fa[aa[i].en][0]=x;
        deep[aa[i].en]=deep[x]+1;
        dfs1(aa[i].en);
        siz[x]+=siz[aa[i].en];
      }
}
inline void dfs2(int x,int y)
{
    int i,k=0;
    num+=1;
    pos[x]=num;
    map[num]=x;
    belong[x]=y;
    for(i=point[x];i;i=next[i])
      if(deep[aa[i].en]>deep[x]&&siz[k]<siz[aa[i].en])
        k=aa[i].en;
    if(k==0) return ;
    dfs2(k,y);
    for(i=point[x];i;i=next[i])
      if(deep[aa[i].en]>deep[x]&&k!=aa[i].en)
        dfs2(aa[i].en,aa[i].en);
}
inline int LCA(int x,int y)
{
    int i;
    if(deep[x]<deep[y])swap(x,y);
    int t=deep[x]-deep[y];
    for(i=0;i<=14;++i)
        if(t&(1<<i))x=fa[x][i];
    for(i=14;i>=0;--i)
        if(fa[x][i]!=fa[y][i])
        {x=fa[x][i];y=fa[y][i];}
    if(x==y)return x;
    else return fa[x][0];
}
#define mid (l+r)/2
#define L k<<1,l,mid
#define R k<<1|1,mid+1,r
inline void build(int k,int l,int r)
{
    if(l==r){
        tr[k].maxn=tr[k].sum=v[map[l]];
        return ;
    }
    build(L);build(R);
    tr[k].maxn=max(tr[k<<1].maxn,tr[k<<1|1].maxn);
    tr[k].sum=tr[k<<1].sum+tr[k<<1|1].sum;
}
void insert(int k,int l,int r,int x,int y)
{
    if(l==r&&l==x){
        tr[k].sum=tr[k].maxn=y;
        return ;
    }
    if(x<=mid) insert(L,x,y);
    else insert(R,x,y);
    tr[k].maxn=max(tr[k<<1].maxn,tr[k<<1|1].maxn);
    tr[k].sum=tr[k<<1].sum+tr[k<<1|1].sum;
}
inline int qurry(int k,int l,int r,int x,int y,int kind)
{
    int sum=0,maxn=-210000000;
    if(x<=l&&y>=r) return kind==0?tr[k].maxn:tr[k].sum;
    if(x<=mid){
        if(kind==0) maxn=max(maxn,qurry(L,x,y,kind));
        else sum+=qurry(L,x,y,kind);
    }
    if(y>mid){
        if(kind==0) maxn=max(maxn,qurry(R,x,y,kind));
        else sum+=qurry(R,x,y,kind);
    }
    return kind==0?maxn:sum;
}
inline int ask(int x,int y,int kind)
{
    int sum=0,maxn=-210000000;
    while(belong[x]!=belong[y]){
        if(kind==0) maxn=max(maxn,qurry(1,1,n,pos[belong[x]],pos[x],kind));
        else sum+=qurry(1,1,n,pos[belong[x]],pos[x],kind);
        x=fa[belong[x]][0];
    }
    if(kind==0) maxn=max(maxn,qurry(1,1,n,pos[y],pos[x],kind));
    else sum+=qurry(1,1,n,pos[y],pos[x],kind);
    return kind==0?maxn:sum;
}
int main()
{
    int i,j,x,y;
    scanf("%d",&n);
    memset(use,1,sizeof(use));
    for(i=1;i<n;++i){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    for(i=1;i<=n;++i) scanf("%d",&v[i]);
    dfs1(1);
    dfs2(1,1);
    build(1,1,n);
    scanf("%d",&m);
    while(m--){
        scanf("%*c%s%d%d",&ch,&x,&y);
        if(ch[0]=='C') insert(1,1,n,pos[x],y),v[x]=y;
        else{
            int lca=LCA(x,y);
            if(ch[1]=='M') printf("%d\n",max(ask(x,lca,0),ask(y,lca,0)));
            else printf("%d\n",ask(x,lca,1)+ask(y,lca,1)-v[lca]);
        }
    }
}