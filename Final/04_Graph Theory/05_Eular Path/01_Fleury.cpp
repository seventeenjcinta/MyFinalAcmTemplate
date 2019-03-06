// ---
// 若有两个点的度数是奇数，则此时这两个点只能作为欧拉路径的起点和终点。
// ---
const int maxn = "Edit";
int G[maxn][maxn];
int deg[maxn][maxn];
vector<int> ans;
inline void init() { memset(G, 0, sizeof(G)), memset(deg, 0, sizeof(deg)); }
inline void AddEdge(int u, int v) { deg[u]++, deg[v]++, G[u][v]++, G[v][u]++; }
void Fleury(int s)
{
    for (int i = 0; i < n; i++)
        if (G[s][i]){
            G[s][i]--, G[i][s]--;
            Fleury(i);
        }
    ans.push_back(s);
}
