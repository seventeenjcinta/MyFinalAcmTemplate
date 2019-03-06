/// 给定一个连通的带边权的图（允许自环和重边），求不同的最小生成树个数。两个生成树不同当它们所用的边的序号不同，换句话说，重边算多次。
struct edge{
    int u, v, w, x;
    inline bool operator< (const edge &rhs) const{
        return x < rhs.x;
    }
}e[100005];
struct count{
    int l, r, use;
}g[100005];
int n, m, fa[50005], siz[50005];

int getfa(int x){
    return fa[x] == x ? x : getfa(fa[x]);
}

void link(int u, int v){
    if(siz[u] > siz[v]) fa[v] = u, siz[u] += siz[v];
    else fa[u] = v, siz[v] += siz[u];
}

bool Kruskal(){
    int cnt = 0, u, v;
    for(int i = 1; i <= m; ++i){
        u = getfa(e[i].u), v = getfa(e[i].v);
        if(u != v){
            link(u, v);
            ++g[e[i].w].use;
            if(++cnt == n - 1) return true;
        }
    }
    return false;
}

int DFS(int w, int i, int k){
    if(k == g[w].use) return 1;
    if(i > g[w].r) return 0;
    int ans = 0, u = getfa(e[i].u), v = getfa(e[i].v);
    if(u != v){
        link(u, v);
        ans = DFS(w, i + 1, k + 1);
        fa[u] = u, fa[v] = v;
    }
    return ans + DFS(w, i + 1, k);
}

int main(){
    int u, v, w, ans;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        fa[i] = i, siz[i] = 1;
    for(int i = 1; i <= m; ++i){
        cin >> u >> v >> w;
       {u, v, 0, w};
    }
    sort(e + 1, e + m + 1);
    w = 0;
    for(int i = 1; i <= m; ++i)
        if(e[i].x == e[i - 1].x) e[i].w = w;
        else{
            g[w].r = i - 1;
            e[i].w = ++w;
            g[w].l = i;
        }
    g[w].r = m;
    ans = Kruskal();
    for(int i = 1; i <= n; ++i)
        fa[i] = i, siz[i] = 1;
    for(int i = 1; i <= w; ++i){
        ans = ans * DFS(i, g[i].l, 0) % 1000003;
        for(int j = g[i].l; j <= g[i].r; ++j){
            u = getfa(e[j].u), v = getfa(e[j].v);
            if(u != v) link(u, v);
        }
    }
    cout << ans << endl;
    return 0;
}
