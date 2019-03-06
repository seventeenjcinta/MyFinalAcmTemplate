const int N = 220;
const LL INF = 0x3f3f3f3f3f3f3f3f;

int n;
int ma[N][N];
LL lx[N],ly[N];
int linky[N];
LL pre[N];
bool vis[N];
bool visx[N];
bool visy[N];
LL slack[N];

void Find(int u)
{
    LL px, py;
    LL yy = 0;
    LL d;

    py = 0;
    yy = 0;
    memset(pre, 0, sizeof(pre));
    memset(slack, 0x3f3f3f3f, sizeof(slack));
    linky[py] = u;
    while(linky[py]){
        px = linky[py];
        d = INF;
        vis[py] = 1;
        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                if(slack[i] > lx[px] + ly[i] - ma[px][i])
                    slack[i] = lx[px] + ly[i] -ma[px][i], pre[i]=py;
                if(slack[i]<d) d=slack[i],yy=i;
            }
        }
        for(int i = 0; i <= n; i++){
            if(vis[i]){
                lx[linky[i]] -= d;
                ly[i] += d;
            }
            else{
                slack[i] -= d;
            }
        }
        py = yy;
    }
    while(py){
        linky[py] = linky[pre[py]];
        py=pre[py];
    }
}

LL Km()
{
    LL ans;

    ans = 0;
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    memset(linky, 0, sizeof(linky));
    for(int i = 1; i <= n; i++){
        memset(vis, 0, sizeof(vis));
        Find(i);
    }
    for(int i = 1; i <= n; ++i){
        ans += lx[i] + ly[i];
    }

    return ans;
}

int main(int argc, char const *argv[])
{
    int ncase;
    int nc;

    nc = 1;
    scanf("%d", &ncase);
    while(ncase --){
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                scanf("%d", &ma[i][j]);
                ma[i][j] = -ma[i][j];
            }
        }
        printf("Case #%d: %lld\n", nc, -Km());
        nc ++;
    }
    return 0;
}