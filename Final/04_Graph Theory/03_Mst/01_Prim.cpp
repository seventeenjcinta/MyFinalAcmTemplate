const int N = 100010;

int ne[N];
int ma[100][100];
int n, m;
int cnt;

int Prim()
{
    int ans = 0;
    int num = 1;
    int minn;
    int v;
    int dis[N];

    memset(dis, 0x3f3f3f3f, sizeof(dis));
    for(int i = 1; i <= n; i ++){
        dis[i] = min(dis[i], ma[1][i]);
    }
    while(num < n){
        minn = 0x3f3f3f3f;
        for(int i = 1; i <= n; i ++){
            if(dis[i] < minn && dis[i]){
                minn = dis[i];
                v = i;
            }
        }
        ans += minn;
        for(int i = 1; i <= n; i ++){
            dis[i] = min(dis[i], ma[v][i]);
        }
        num ++;
    }

    return ans;
}
