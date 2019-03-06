const int N = 100010;

struct Node
{
    int u;
    int v;
    int w;
};

bool cmp(Node a, Node b)
{
    return a.w < b.w;
}

Node node[N];
int ne[N];
int n, m;
int cnt;

void Ini()
{
    for(int i = 1; i <= n; i ++){
        ne[i] = i;
    }
}

int Find(int x)
{
    int t = x;

    while(t != ne[t]){
        t = ne[t];
    }
    while(x != t){
        int q;

        q = ne[x];
        ne[x] = t;
        x = q;
    }

    return t;
}

void Join(int x, int y)
{
    ne[x] = y;
}

int Kru()
{
    int ans;
    int num;

    ans = 0;
    num = 0;
    for(int i = 0; i < cnt; i ++){
        int u = node[i].u;
        int v = node[i].v;
        int w = node[i].w;

        u = Find(u);
        v = Find(v);
        if(u != v){
            Join(u, v);
            ans += w;
            num ++;
        }
        if(num == n - 1){
            break;
        }
    }

    return ans;
}
