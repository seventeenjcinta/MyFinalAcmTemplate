// ---
// Tarjan离线算法\\
// 时间复杂度$O(n+q)$
// ---
const int maxn = "Edit";
int par[maxn];           //并查集
int ans[maxn];           //存储答案
vector<int> G[maxn];     //邻接表
vector<PII> query[maxn]; //存储查询信息
bool vis[maxn];          //是否被遍历
inline void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        G[i].clear(), query[i].clear();
        par[i] = i, vis[i] = 0;
    }
}
inline void add_edge(int u, int v) { G[u].push_back(v); }
inline void add_query(int id, int u, int v)
{
    query[u].emplace_back(v, id);
    query[v].emplace_back(u, id);
}
void tarjan(int u)
{
    vis[u] = 1;
    for (auto& v : G[u])
    {
        if (vis[v]) continue;
        tarjan(v);
        unite(u, v);
    }
    for (auto& q : query[u])
    {
        int &v = q.X, &id = q.Y;
        if (!vis[v]) continue;
        ans[id] = find(v);
    }
}
