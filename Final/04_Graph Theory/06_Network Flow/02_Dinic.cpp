const int N = 100010;
const int INF = 0x3f3f3f3f;

struct Node
{
    int to;
    int w;
    int ne;
};

Node node[N];
int Q[N];   /// 队列  注意数组的大小
int head[N];
int cur[N];	/// 前向弧优化
int di[N];
int ma[N];
int ss, tt;
int top;
int n, m;

void ini()
{
    top = 0;
    memset(head, -1, sizeof(head));
}

void add_edge(int from, int to, int w)
{
    node[top].to = to;
    node[top].w = w;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

bool build()
{
    int l, r;
    int now;

    memset(di, 0, sizeof(di));
    di[ss] = 1;
    l = r = 0;
    Q[r] = ss;
    r ++;
    while(l != r){
        now = Q[l];
        l ++;
        if(now == tt){
            return true;
        }
        for(int i = head[now]; i != -1; i = node[i].ne){
            int v, w;

            v = node[i].to;
            w = node[i].w;
            if(w && !di[v]){
                di[v] = di[now] + 1;
                Q[r] = v;
                r ++;
            }
        }
    }

    return false;
}

int dfs(int u, int maxf)
{
    int ans;

    if(u == tt){
        return maxf;
    }
    ans = 0;
    for(int &i = cur[u]; i != -1; i = node[i].ne){
        int v, w;

        v = node[i].to;
        w = node[i].w;
        if(w && di[v] == di[u] + 1){
            int t;

            t = dfs(v, min(maxf - ans, w));
            node[i].w -= t;
            node[i ^ 1].w += t;
            ans += t;
            if(ans == maxf){
                return ans;
            }
        }
    }
    if(!ans){
        di[u] = -2;
    }

    return ans;
}

int Dinic()
{
    int ans;

    ans = 0;
    while(build()){
        for(int i = 1; i <= tt; i ++){
            cur[i] = head[i];
        }
        ans += dfs(ss, INF);
    }

    return ans;
}

int main(int argc, char const *argv[])
{
    while(scanf("%d%d", &m, &n) == 2){
        ss = 1;
        tt = n;
        ini();
        for(int i = 1; i <= m; i ++){
            int u, v, w;

            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge(v, u, 0);
        }
        printf("%d\n", Dinic());
    }

    return 0;
}