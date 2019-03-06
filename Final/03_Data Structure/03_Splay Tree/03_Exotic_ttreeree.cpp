/**
1.查询k在区间内的排名
2.查询区间内排名为k的值
3.修改某一位值上的数值
4.查询k在区间内的前驱(前驱定义为小于x，且最大的数)
5.查询k在区间内的后继(后继定义为大于x，且最小的数)
**/
int n,m,tot;
int num[50003],roots[2000003];
struct Splay
{
    int fa,ch[2],siz,data,occ;	/// occ - cnt
}a[2000003];
int in()
{
    int t=0,f=1;
    char ch=getchar();
    while (!pd(ch))
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (pd(ch)) t=(t<<3)+(t<<1)+ch-'0',ch=getchar();
    return f*t;
}
void ct(int x)
{
    a[x].siz=a[a[x].ch[0]].siz+a[a[x].ch[1]].siz+a[x].occ;
}
void made(int x,int id)
{
    a[id].data=x,
    a[id].occ=a[id].siz=1,
    a[id].ch[0]=a[id].ch[1]=a[id].fa=0;
}
void rorate(int now,bool mk)
{
    int pa=a[now].fa;
    a[a[now].ch[mk]].fa=pa;
    a[pa].ch[!mk]=a[now].ch[mk];
    a[now].fa=a[pa].fa;
    if (a[pa].fa)
    {
        if (a[a[pa].fa].ch[0]==pa) a[a[pa].fa].ch[0]=now;
        else a[a[pa].fa].ch[1]=now;
    }
    a[now].ch[mk]=pa;
    a[pa].fa=now;
    ct(pa);ct(now);
}
void splay(int rt,int now,int goal)
{
    int pa;
    while (a[now].fa!=goal)
    {
        pa=a[now].fa;
        if (a[pa].fa==goal)
        {
            if (a[pa].ch[0]==now) rorate(now,1);
            else rorate(now,0);
        }
        else if (a[a[pa].fa].ch[0]==pa)
        {
            if (a[pa].ch[0]==now) rorate(pa,1);
            else rorate(now,0);
            rorate(now,1);
        }
        else
        {
            if (a[pa].ch[1]==now) rorate(pa,0);
            else rorate(now,1);
            rorate(now,0);
        }
    }
    if (!goal) roots[rt]=now;
}
void insert(int rt,int x,int id)
{
    if (!roots[rt]) {made(x,id);roots[rt]=id;return;}
    int now=roots[rt];
    while (now)
    {
        if (a[now].data==x) {a[now].occ++;a[now].siz++;splay(rt,now,0);return;}
        if (a[now].data>x)
        {
            if (!a[now].ch[0]) {made(x,id);a[now].ch[0]=id;a[id].fa=now;break;}
            else now=a[now].ch[0];
        }
        else
        {
            if (!a[now].ch[1]) {made(x,id);a[now].ch[1]=id;a[id].fa=now;break;}
            else now=a[now].ch[1];
        }
    }
    splay(rt,id,0);
}
int find(int root,int x)
{
    int now=root;
    while (now)
    {
        if (a[now].data==x) return now;
        if (a[now].data>x) now=a[now].ch[0];
        else now=a[now].ch[1];
    }
}
int findmax(int now)
{
    while (a[now].ch[1]) now=a[now].ch[1];
    return now;
}
int find_next_min(int rt,int x)
{
    int now=roots[rt],ans=-0x7fffffff;
    while (now)
    {
        if (a[now].data<x)
        {
            if (ans<a[now].data)ans=a[now].data;
            now=a[now].ch[1];
        }
        else now=a[now].ch[0];
    }
    return ans;
}
int find_next_max(int rt,int x)
{
    int now=roots[rt],t=0,ans=0x7fffffff;
    while (now)
    {
        if (a[now].data>x)
        {
            if (ans>a[now].data) ans=a[now].data,t=now;
            now=a[now].ch[0];
        }
        else now=a[now].ch[1];
    }
    return ans;
}
void replace(int rt,int x,int k)
{
    int now=find(roots[rt],x);
    splay(rt,now,0);
    if (a[now].occ>1) {a[now].occ--;a[now].siz--;}
    //else if (a[now].siz==1) roots[rt]=0;
    else if (!a[now].ch[0])
    {
        roots[rt]=a[now].ch[1];
        a[a[now].ch[1]].fa=0;
    }
    else if (!a[now].ch[1])
    {
        roots[rt]=a[now].ch[0];
        a[a[now].ch[0]].fa=0;
    }
    else
    {
        splay(rt,findmax(a[now].ch[0]),now);
        a[a[now].ch[0]].ch[1]=a[now].ch[1];
        a[a[now].ch[1]].fa=a[now].ch[0];
        a[a[now].ch[0]].fa=0;
        roots[rt]=a[now].ch[0];
        ct(a[now].ch[0]);
    }
    if (!a[now].occ)insert(rt,k,now);
    else insert(rt,k,++tot);
}
int find_rank(int rt,int x)//这里的findrank实际上是在splay里找比x小的数的数量
{
    int now=roots[rt],ans=0;
    while (now)
    {
        if (a[now].data>x) now=a[now].ch[0];
        else if (a[now].data<x)
            ans+=(a[now].occ+a[a[now].ch[0]].siz),
            now=a[now].ch[1];
        else {ans+=a[a[now].ch[0]].siz;break;}
    }
    return ans;
}
void build(int now,int begin,int end)
{
    for (int i=begin;i<=end;i++) insert(now,num[i],++tot);
    if (begin==end) return;
    int mid=(begin+end)>>1;
    build(now<<1,begin,mid);
    build(now<<1|1,mid+1,end);
}
int solve1(int now,int begin,int end,int l,int r,int k)
{
    if (l<=begin&&end<=r) return find_rank(now,k);
    int mid=(begin+end)>>1,rank=0;
    if (mid>=l) rank+=solve1(now<<1,begin,mid,l,r,k);
    if (mid<r) rank+=solve1(now<<1|1,mid+1,end,l,r,k);
    return rank;
}
int solve2(int l,int r,int k)
{
    int begin=0,end=1e8+1,mid;
    while (begin<end)
    {
        mid=(begin+end)>>1;
        // printf("%d %d\n", mid, solve1(1,1,n,l,r,mid));
        if (solve1(1,1,n,l,r,mid)<k)
            begin=mid+1;
        else end=mid;
    }
    return begin-1;
}
void solve3(int now,int begin,int end,int pos,int k)
{
    replace(now,num[pos],k);
    if (begin==end) {num[pos]=k;return;}
    int mid=(begin+end)>>1;
    if (mid>=pos) solve3(now<<1,begin,mid,pos,k);
    else solve3(now<<1|1,mid+1,end,pos,k);
}
int solve4(int now,int begin,int end,int l,int r,int k)
{
    if (l<=begin&&end<=r) return find_next_min(now,k);
    int mid=(begin+end)>>1,ans=-0x7fffffff;
    if (mid>=l) ans=max(ans,solve4(now<<1,begin,mid,l,r,k));
    if (mid<r) ans=max(ans,solve4(now<<1|1,mid+1,end,l,r,k));
    return ans;
}
int solve5(int now,int begin,int end,int l,int r,int k)
{
    if (l<=begin&&end<=r) return find_next_max(now,k);
    int mid=(begin+end)>>1,ans=0x7fffffff;
    if (mid>=l) ans=min(ans,solve5(now<<1,begin,mid,l,r,k));
    if (mid<r) ans=min(ans,solve5(now<<1|1,mid+1,end,l,r,k));
    return ans;
}
int main()
{
    n=in();m=in();
    int opt,x,y,k;
    for (int i=1;i<=n;i++) num[i]=in();
    build(1,1,n);
    while (m--)
    {
        opt=in();
        if (opt!=3)x=in(),y=in(),k=in();
        else x=in(),y=in();
        if (opt==1) printf("%d\n",solve1(1,1,n,x,y,k)+1);
        else if (opt==2) printf("%d\n",solve2(x,y,k));
        else if (opt==3) solve3(1,1,n,x,y);
        else if (opt==4) printf("%d\n",solve4(1,1,n,x,y,k));
        else printf("%d\n",solve5(1,1,n,x,y,k));
    }
}