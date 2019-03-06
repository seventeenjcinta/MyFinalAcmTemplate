#include <bits/stdc++.h>
using namespace std;
#define maxn 1000000

struct edage{
    int x,y,val;
}ed[maxn];

struct node{
    int fa;
    int dep;
    int siz;
    int son;//和该节点在同一重链上的节点
    int top;
    int id;
}no[maxn];
int num;
int val[maxn];

vector<int> v[maxn];
void dfs1(int u,int f,int dep){
    no[u].dep=dep;
    no[u].siz=1;
    no[u].son=0;
    no[u].fa=f;
    for(int i=0;i<v[u].size();i++){
        int ff=v[u][i];
        if(ff==f) continue;
        dfs1(ff,u,dep+1);
        no[u].siz+=no[ff].siz;
        if(no[no[u].son].siz<no[ff].siz) no[u].son=ff;
    }
}
void dfs2(int u,int tp){
    no[u].top=tp;
    no[u].id=++num;
    if(no[u].son) dfs2(no[u].son,tp);
    for(int i=0;i<v[u].size();i++){
        int ff=v[u][i];
        if(ff==no[u].fa||ff==no[u].son) continue;
        dfs2(ff,ff);
    }
}

struct node2{
    int l;
    int r;
    int val;
    int lazy;
}tree[4*maxn];

void pushup(int x){
    tree[x].val=max(tree[x<<1].val,tree[x<<1|1].val);
}

void build(int rt,int l,int r){
    tree[rt].l=l;
    tree[rt].r=r;
    if(l==r){
        tree[rt].val=val[l];
        return ;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}
void update(int rt,int pos,int va){
    int l=tree[rt].l;
    int r=tree[rt].r;
    if(l==r){
        tree[rt].val=va;
        return ;
    }
    int mid=(l+r)/2;
    if(pos<=mid) update(rt<<1,pos,va);
    else update(rt<<1|1,pos,va);
    pushup(rt);
}

int query(int rt,int s,int t){
    int l=tree[rt].l;
    int r=tree[rt].r;
    if(l==s&&t==r){
        return tree[rt].val;
    }
    int mid=(l+r)/2;
    if(t<=mid) return query(rt<<1,s,t);
    else if(s>mid) return query(rt<<1|1,s,t);
    return max(query(rt<<1,s,mid),query(rt<<1|1,mid+1,t));
}
int youth(int u,int v){
    int tp1=no[u].top,tp2=no[v].top;
    int ans=0;
    while(tp1!=tp2){
        if(no[tp1].dep<no[tp2].dep){
            swap(tp1,tp2);
            swap(u,v);
        }
        ans=max(query(1,no[tp1].id,no[u].id),ans);
       // printf("1\n");
        u=no[tp1].fa;
        tp1=no[u].top;
    }
    if(u==v) return ans;
    if(no[u].dep>no[v].dep) swap(u,v);
    ans=max(query(1,no[no[u].son].id,no[v].id),ans);
    //printf("2\n");
    return ans;
}
void Clear(int n){
    for(int i=1;i<=n;i++){
        v[i].clear();
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<n;i++){

            scanf("%d%d%d",&ed[i].x,&ed[i].y,&ed[i].val);
            v[ed[i].x].push_back(ed[i].y);
            v[ed[i].y].push_back(ed[i].x);
        }
        //printf("a");
        dfs1(1,0,1);
        dfs2(1,1);
  
        for(int i=1;i<n;i++){
            if(no[ed[i].x].dep<no[ed[i].y].dep) swap(ed[i].x,ed[i].y);
            val[no[ed[i].x].id]=ed[i].val;
        }
  
        build(1,1,num);
  
        char s[200];
        while(~scanf("%s",s)&&s[0]!='D'){
            int x,y;
            scanf("%d%d",&x,&y);
            if(s[0]=='Q'){
                printf("%d\n",youth(x,y));
            }
            if(s[0]=='C'){
                update(1,no[ed[x].x].id,y);
            }
  
        }
        Clear(n);
    }
    
    return 0;
}