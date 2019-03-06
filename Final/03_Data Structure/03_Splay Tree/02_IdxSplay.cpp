#include <bits/stdc++.h>
using namespace std;
 
const int N = 100010;
const int INF = 0x7fffffff;
 
struct Tree
{
    int fa;	/// 
    int v;
    int maxx;
    int lazy;
    int cnt;
    int son[2];	/// 0 - left
    bool rev;	/// 翻转标记
};
 
Tree tree[N];
int n, m;
int root;
 
void Ini(int x, int v)
{
    tree[x].v = tree[x].maxx = v;
    tree[x].cnt = 1;
    tree[x].lazy = tree[x].rev = tree[x].son[0] = tree[x].son[1] = 0;
}
 
void Up(int x)
{
    tree[x].maxx = tree[x].v;
    tree[x].cnt = 1;
    if(tree[x].son[0]){
        tree[x].maxx = max(tree[x].maxx, tree[tree[x].son[0]].maxx);
        tree[x].cnt += tree[tree[x].son[0]].cnt;
    }
    if(tree[x].son[1]){
        tree[x].maxx = max(tree[x].maxx, tree[tree[x].son[1]].maxx);
        tree[x].cnt += tree[tree[x].son[1]].cnt;
    }
}
 
void Down(int x)
{
    int t;
 
    if(!x){
        return ;
    }
    t = tree[x].lazy;
    if(t){
        if(tree[x].son[0]){
            tree[tree[x].son[0]].v += t;
            tree[tree[x].son[0]].maxx += t;
            tree[tree[x].son[0]].lazy += t;
        }
        if(tree[x].son[1]){
            tree[tree[x].son[1]].v += t;
            tree[tree[x].son[1]].maxx += t;
            tree[tree[x].son[1]].lazy += t;
        }
    }
    tree[x].lazy = 0;
    if(tree[x].rev){
        tree[tree[x].son[0]].rev ^= 1;
        tree[tree[x].son[1]].rev ^= 1;
        swap(tree[x].son[0], tree[x].son[1]);
        tree[x].rev = 0;
    }
}
void Rotate(int x, int kind) /// 0 - zag    1 - zig
{
    int y, z;
 
    y = tree[x].fa;
    z = tree[y].fa;
    tree[y].son[!kind] = tree[x].son[kind];
    tree[tree[x].son[kind]].fa = y;
    tree[x].son[kind] = y;
    tree[y].fa = x;
    tree[z].son[tree[z].son[1] == y] = x;
    tree[x].fa = z;
    Up(y);
}
 
void Splay(int x, int goal)
{
    if(x == goal){
        return ;
    }
    while(tree[x].fa != goal){
        int y, z;
        bool rx, ry;
 
        y = tree[x].fa;
        z = tree[y].fa;
        Down(z);
        Down(y);
        Down(x);
        rx = (x == tree[y].son[0]);
        ry = (y == tree[z].son[0]);
        if(z == goal){
            Rotate(x, rx);
        }
        else{
            if(rx == ry){
                Rotate(y, ry);
            }
            else{
                Rotate(x, rx);
            }
            Rotate(x, ry);
        }
    }
    Up(x);
    if(!goal){
        root = x;
    }
}
 
int Find(int x)
{
    int t;
 
    t = root;
    Down(t);
    while(tree[tree[t].son[0]].cnt != x){
        if(x < tree[tree[t].son[0]].cnt){
            t = tree[t].son[0];
        }
        else{
            x -= (tree[tree[t].son[0]].cnt + 1);
            t = tree[t].son[1];
        }
        Down(t);
    }
 
    return t;
}
 
void Update(int l, int r, int v)
{
    int x, y;
 
    x = Find(l - 1);
    y = Find(r + 1);
    Splay(x, 0);
    Splay(y, x);
    tree[tree[y].son[0]].maxx += v;
    tree[tree[y].son[0]].lazy += v;
    tree[tree[y].son[0]].v += v;
}
 
void Reverse(int l, int r)
{
    int x, y;
 
    x = Find(l - 1);
    y = Find(r + 1);
    Splay(x, 0);
    Splay(y, x);
    tree[tree[y].son[0]].rev ^= 1;
}
 
int Quary(int l, int r)
{
    int x, y;
 
    x = Find(l - 1);
    y = Find(r + 1);
    Splay(x, 0);
    Splay(y, x);
 
    return tree[tree[y].son[0]].maxx;
}
 
int Build(int l, int r)
{
    int mid;
    int ll, rr;
 
    if(l > r){
        return 0;
    }
    else if(l == r){
        return l;
    }
    mid = l + ((r - l) >> 1);
    ll = Build(l, mid - 1);
    rr = Build(mid + 1, r);
    tree[mid].son[0] = ll;
    tree[mid].son[1] = rr;
    tree[ll].fa = tree[rr].fa = mid;
    Up(mid);
 
    return mid;
}
 
void Init(int n)
{
    int li;
 
    Ini(0, -INF);
    Ini(1, -INF);
    Ini(n + 2, -INF);
    li = n + 1;
    for(int i = 2; i <= li; i ++){
        Ini(i, 0);
    }
    root = Build(1, n + 2);
    tree[root].fa = 0;
    tree[0].fa = 0;
    tree[0].son[1] = root;
    tree[0].cnt = 0;
}
 
int main(int argc, char const *argv[])
{
    while(scanf("%d%d", &n, &m) == 2){
        Init(n);
        for(int i = 0; i < m; i ++){
            int x;
            int l, r;
 
            scanf("%d", &x);
            if(x == 1){
                int v;
 
                scanf("%d%d%d", &l, &r, &v);
                Update(l, r, v);
            }
            else if(x == 2){
                scanf("%d%d", &l, &r);
                Reverse(l, r);
            }
            else{
                scanf("%d%d", &l, &r);
                printf("%d\n", Quary(l, r));
            }
        }
    }
 
    return 0;
}