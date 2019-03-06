const int N = 50050;
const int INF = 0x7fffffff;

struct Sblay
{
    int fa; ///
    int v;
    int siz;    /// 尺寸
    int son[2]; /// 0 - left
    int cnt;    /// 次数
};

Sblay splay[N * 40];
int n, m;
int root[N * 40];   /// 每颗平衡树的终点qwq
int ts; ///
int ma[N];

void Show()
{
    for(int i = 1; i <= 7; i ++){
        printf("root = %d ", root[i]);
    }
    printf("\n");
    for(int i = 0; i <= ts; i ++){
        printf("%d l = %d r = %d num = %d cnt = %d siz = %d fa = %d\n", i, splay[i].son[0], splay[i].son[1], splay[i].v, splay[i].cnt, splay[i].siz, splay[i].fa);
    }
}

void Clean(int x)
{
    splay[x].son[0] = splay[x].son[1] = splay[x].v = splay[x].fa = splay[x].siz = splay[x].cnt = 0;
}

void Up(int x)
{
    if(x){
        splay[x].siz = splay[x].cnt;
        if(splay[x].son[0]){
            splay[x].siz += splay[splay[x].son[0]].siz;
        }
        if(splay[x].son[1]){
            splay[x].siz += splay[splay[x].son[1]].siz;
        }
    }
}

void Rotate(int x, int kind) /// 0 - zag    1 - zig
{
    int y, z;

    y = splay[x].fa;
    z = splay[y].fa;
    splay[y].son[!kind] = splay[x].son[kind];
    splay[splay[x].son[kind]].fa = y;
    splay[x].son[kind] = y;
    splay[y].fa = x;
    splay[z].son[splay[z].son[1] == y] = x;
    splay[x].fa = z;
    Up(y);
}

void Splay(int num, int x, int goal)
{
    if(x == goal){
        return ;
    }
    while(splay[x].fa != goal){
        int y, z;
        bool rx, ry;

        y = splay[x].fa;
        z = splay[y].fa;
//        Down(z);
//        Down(y);
//        Down(x);
        rx = (x == splay[y].son[0]);
        ry = (y == splay[z].son[0]);
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
        root[num] = x;
    }
}

int Findrank(int num, int x)
{
    int ans;
    int now;

    now = root[num];
    ans = 0;
    // printf("begin = %d %d\n", num, root[num]);
    while(now){ /// 原本是 true  但有可能不存在qwq
        // printf("now = %d v = %d\n", now, splay[now].v);
        if(splay[now].v > x){
            // printf("Turn left\n");
            now = splay[now].son[0];
        }
        else{
            // printf("Turn right\n");
            if(splay[now].son[0]){
                ans += splay[splay[now].son[0]].siz;
            }
            // printf("now = %d = %d\n", splay[now].v, x);
            if(splay[now].v == x){
                // cout << 998244353 << endl;
                Splay(num, now, 0);

                return ans; /// 因为不可合并所以不能 + 1
            }
            ans += splay[now].cnt; ///! /// 算上自己
            now = splay[now].son[1];
        }
    }

    return ans;
}

int Findpre(int num, int x)
{
    int now;

    // printf("pre %d %d\n", num, x);
    Findrank(num, x);
    // cout << "ENDDDDDDDDDDDDDDD" << endl;
    now = splay[root[num]].son[0];
    if(!now){
        return -1;
    }
    while(splay[now].son[1]){
        // printf("now = %d\n", now);
        now = splay[now].son[1];
    }

    return now;
}

int Findnet(int num, int x)
{
    int now;

    Findrank(num, x);
    now = splay[root[num]].son[1];
    if(!now){
        return -1;
    }
    while(splay[now].son[0]){
       // cout << 666 << endl;
       now = splay[now].son[0];
    }

    return now;
}

void Del(int num, int x)
{
    int t;
    int l;
    int now;

    Findrank(num, x);
    now = root[num];
    if(splay[now].cnt > 1){
       splay[now].cnt --;
       splay[now].siz --;

       return ;
    }
    if(!splay[now].son[0] && !splay[now].son[1]){   ///only one
       Clean(now);
       root[num] = 0;

       return ;
    }
    if(!splay[root[num]].son[0]){
       root[num] = splay[now].son[1];
       splay[root[num]].fa = 0;
       Clean(now);

       return ;
    }
    if(!splay[root[num]].son[1]){
       root[num] = splay[root[num]].son[0];
       splay[root[num]].fa = 0;
       Clean(now);

       return ;
    }
    t = Findpre(num, splay[root[num]].v);
    Splay(num, t, 0);
    splay[splay[now].son[1]].fa = root[num];
    splay[root[num]].son[1] = splay[now].son[1];
    Clean(now);
    Up(root[num]);
}

void Insert(int num, int x)
{
    if(!root[num]){
        // cout << 6566 << endl;
        ts ++;
        splay[ts].son[0] = splay[ts].son[1] = splay[ts].fa = 0;
        splay[ts].v = x;
        splay[ts].cnt = 1;
        splay[ts].siz = 1;
        root[num] = ts;

        return;
    }
    else{
        int now;
        int t;

        t = 0;
        now = root[num];
        while(true){
            if(splay[now].v == x){
                splay[now].cnt ++;
                Up(t);
                Splay(num, now, 0);
                break;
            }
            t = now;
            now = splay[now].son[splay[now].v < x];
            if(!now){
                ts ++;
                splay[ts].son[0] = splay[ts].son[1] = 0;
                splay[ts].fa = t;
                splay[ts].v = x;
                splay[ts].cnt = 1;
                splay[t].son[splay[t].v < x] = ts;
                Up(t);
                Splay(num, ts, 0);
                break;
            }
        }
    }
}

void Ini()
{
    memset(root, 0, sizeof(root));
    ts = 0;
}

void Build(int x, int l, int r)
{
    // printf("build %d %d %d\n", x, l, r);
    for(int i = l; i <= r; i ++){
        Insert(x, ma[i]);
    }
    // printf("root = %d\n", root[x]);
    // Show();
    // printf("%d\n", ts);
    if(l == r){
        return;
    }
    else{
        int mid;

        mid = l + ((r - l) >> 1);
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
    }
}

int Quary1(int x, int l, int r, int v, int ll, int rr)
{
    if(l > r){
        return 0;
    }
    // printf("l = %d r = %d ll = %d rr = %d\n", l, r, ll, rr);
    if(l == ll && r == rr){
        return Findrank(x, v);
    }
    else{
        int mid;
        int t;

        t = 0;
        mid = ll + ((rr - ll) >> 1);
        t += Quary1(x << 1, l, min(mid, r), v, ll, mid);
        t += Quary1(x << 1 | 1, max(mid + 1, l), r, v, mid + 1, rr);

        return t;
    }
}

int Quary2(int l, int r, int x)
{
    int dl, dr, dmid;
    int ans;

    dl = 0;
    ans = dl;
    dr = 1e8 + 1;
    while(dl <= dr){
        dmid = dl + ((dr - dl) >> 1);
        // printf("mid = %d  %d\n", dmid, Quary1(1, l, r, dmid, 1, n));
        if(Quary1(1, l, r, dmid, 1, n) < x){
            ans = dmid;
            dl = dmid + 1;
        }
        else{
            dr = dmid - 1;
        }
    }

    return ans;
}

void Update(int x, int pos, int v, int ll, int rr)
{
    // printf("**** %d %d %d\n", x, ll, rr);
    // Show();
    Del(x, ma[pos]);
    // Show();
    Insert(x, v);
    // Show();
    // printf("*****\n");
    if(ll == rr){
        ma[pos] = v;
    }
    else{
        int mid;

        mid = ll + ((rr - ll) >> 1);
        if(mid >= pos){
            Update(x << 1, pos, v, ll, mid);
        }
        else{
            Update(x << 1 | 1, pos, v, mid + 1, rr);
        }
    }
}

int Quary3(int x, int l, int r, int v, int ll, int rr)
{
    if(l > r){
        return -INF;
    }
    if(ll == l && rr == r){
        int ans;

        // Show();
        Insert(x, v);
        // Show();
        ans = Findpre(x, v);
        Del(x, v);
        // Show();
        // printf("range  %d %d %d %d %d %d\n", l, r, ll, rr, splay[ans].v, ans);
        if(ans == -1){
            return -INF;
        }
        else{
            return splay[ans].v;
        }
    }
    else{
        int mid;
        int ans;

        ans = -INF;

        mid = ll + ((rr - ll) >> 1);
        ans = max(ans, Quary3(x << 1, l, min(mid, r), v, ll, mid));
        ans = max(ans, Quary3(x << 1 | 1, max(mid + 1, l), r, v, mid + 1, rr));

        // printf("range  %d %d %d %d %d\n", l, r, ll, rr, ans);
        return ans;
    }
}

int Quary4(int x, int l, int r, int v, int ll, int rr)
{
    if(l > r){
        return INF;
    }
    // printf("range  %d %d %d %d\n", l, r, ll, rr);
    if(ll == l && rr == r){
        int ans;

        Insert(x, v);
        ans = Findnet(x, v);
        Del(x, v);
        // Show();
        // printf("range  %d %d %d %d %d %d\n", l, r, ll, rr, splay[ans].v, ans);
        if(ans == -1){
            return INF;
        }
        else{
            return splay[ans].v;
        }
    }
    else{
        int mid;
        int ans;

        ans = INF;

        mid = ll + ((rr - ll) >> 1);
        ans = min(ans, Quary4(x << 1, l, min(mid, r), v, ll, mid));
        ans = min(ans, Quary4(x << 1 | 1, max(mid + 1, l), r, v, mid + 1, rr));
        // printf("range  %d %d %d %d %d\n", l, r, ll, rr, ans);

        return ans;
    }
}

int main(int argc, char const *argv[])
{
    while(scanf("%d%d", &n, &m) == 2){
        Ini();
        for(int i = 1; i <= n; i ++){
            scanf("%d", &ma[i]);
        }
        Build(1, 1, n);
        for(int i = 0; i < m; i ++){
            int ops;
            int l, r;

            scanf("%d", &ops);
            if(ops == 1){
                int x;

                scanf("%d%d%d", &l, &r, &x);
                printf("%d\n", Quary1(1, l, r, x, 1, n) + 1);   /// 这里 + 1
            }
            else if(ops == 2){
                int x;
                int t;

                scanf("%d%d%d", &l, &r, &x);
                t = Quary2(l, r, x);
                if(!t){
                    printf("-1\n");
                }
                else{
                    printf("%d\n", Quary2(l, r, x));
                }
            }
            else if(ops == 3){
                int pos, x;

                scanf("%d%d", &pos, &x);
                // Show();
                Update(1, pos, x, 1, n);
                /// printf("%d\n", ma[pos]);
                // printf("root = %d %d %d\n", root[7], root[3], root[1]);
                // Show();
            }
            else if(ops == 4){
                int x;

                scanf("%d%d%d", &l, &r, &x);
                printf("%d\n", Quary3(1, l, r, x, 1, n));
            }
            else if(ops == 5){
                int x;

                scanf("%d%d%d", &l, &r, &x);
                printf("%d\n", Quary4(1, l, r, x, 1, n));
            }
        }
    }

    return 0;
}