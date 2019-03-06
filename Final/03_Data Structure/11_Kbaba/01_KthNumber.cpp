/// 不带修改区间第 K 大
/// 区间第 k 小 无不存在数据特判  节点范围跟随函数传参
const int N = 100010;

struct Three
{
    int sum;
    int son[2];
};

Three tree[N * 20];
int ma[N];
int n, m;
int root[N];
int tot;

void Up(int x)
{
    tree[x].sum = tree[tree[x].son[0]].sum + tree[tree[x].son[1]].sum;
}

void Build(int &x, int l, int r)
{
    tot ++;
    x = tot;
    if(l == r){
        tree[x].sum = 0;
    }
    else{
        int mid;

        mid = l + ((r - l) >> 1);
        Build(tree[x].son[0], l, mid);
        Build(tree[x].son[1], mid + 1, r);
        Up(x);
    }
}

void Update(int &x, int pre, int pos, int ll, int rr)
{
    tot ++;
    x = tot;
    tree[x] = tree[pre];
    if(ll == rr && ll == pos){
        tree[x].sum ++;
    }
    else{
        int mid;

        mid = ll + ((rr - ll) >> 1);
        if(pos <= mid){
            Update(tree[x].son[0], tree[pre].son[0], pos, ll, mid);
        }
        else{
            Update(tree[x].son[1], tree[pre].son[1], pos, mid + 1, rr);
        }
        Up(x);
    }
}

int Quary(int l, int r, int x, int ll, int rr)
{
    // printf("%d %d %d\n", ll, rr, x);
    if(ll == rr){
        return ll;
    }
    else{
        int mid;
        int t;

        t = tree[tree[r].son[0]].sum - tree[tree[l].son[0]].sum;
        mid = ll + ((rr - ll) >> 1);
        // printf(" %d - %d = %d\n", tree[tree[r].son[0]].sum, tree[tree[l].son[0]].sum, t);
        if(t >= x){
            // printf("gl\n");
            return Quary(tree[l].son[0], tree[r].son[0], x, ll, mid);
        }
        else{
            // printf("gr\n");
            return Quary(tree[l].son[1], tree[r].son[1], x - t, mid + 1, rr);
        }
    }
}

int main(int argc, char const *argv[])
{
    int ncase;

    scanf("%d", &ncase);
    while(ncase --){
        tot = 0;
        id.clear();
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &ma[i]);
            id.pb(ma[i]);
        }
        sort(id.begin(), id.end());
        id.erase(unique(id.begin(), id.end()), id.end());
        Build(root[0], 1, n);
        for(int i = 1; i <= n; i ++){
            // printf("%d\n", Getid(ma[i]));
            Update(root[i], root[i - 1], Getid(ma[i]), 1, n);
        }
        for(int i = 1; i <= m; i ++){
            int l, r, x;

            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", id[Quary(root[l - 1], root[r], x, 1, n) - 1]);
        }
    }

    return 0;
}

/// 整体二分
#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 200020;
const LL INF = 0x3f3f3f3f3f3f3f3f;

struct Node
{
    int kind;
    int pos;
    int l;
    int r;
    int x;
};

Node node[N];
Node now[N];
int bits[N];
LL ans[N];
int n, m;
int cnt;

void Alldoubledive(int ql, int qr, LL l, LL r)
{
    if(l == r){
        for(int i = ql; i <= qr; i ++){
            if(node[i].kind == 2){
                ans[node[i].pos] = l;
            }
        }
    }
    else{
        int mid;
        int now1, now2;

        mid = l + ((r - l) >> 1);
        now1 = ql;
        now2 = qr;
        for(int i = ql; i <= qr; i ++){
            if(node[i].kind == 1){
                if(node[i].l <= mid){
                    Add(node[i].pos, 1);
                    now[now1] = node[i];
                    now1 ++;
                }
                else{
                    now[now2] = node[i];
                    now2 --;
                }
            }
            else{
                int t;

                t = Sum(node[i].r) - Sum(node[i].l - 1);
                if(t >= node[i].x){
                    now[now1] = node[i];
                    now1 ++;
                }
                else{
                    node[i].x -= t;
                    now[now2] = node[i];
                    now2 --;
                }
            }
        }
        for(int i = ql; i < now1; i ++){
            if(now[i].kind == 1){
                Add(now[i].pos, -1);
            }
        }
        reverse(now + now2 + 1, now + qr + 1);  /// 顺序！
        for(int i = ql; i <= qr; i ++){
            node[i] = now[i];
        }
        if(now1 != ql){
            Alldoubledive(ql, now1 - 1, l, mid);
        }
        if(now2 != qr){
            Alldoubledive(now2 + 1, qr, mid + 1, r);
        }
    }
}

int main(int argc, char const *argv[])
{
    int ncase;

    scanf("%d", &ncase);
    while(ncase --){
        memset(bits, 0, sizeof(bits));
        scanf("%d%d", &n, &m);
        cnt = 1;
        for(int i = 1; i <= n; i ++){
            scanf("%d", &node[cnt].l);
            node[cnt].pos = i;
            node[cnt].kind = 1;
            cnt ++;
        }
        for(int i = 1; i <= m; i ++){
            scanf("%d%d%d", &node[cnt].l, &node[cnt].r, &node[cnt].x);
            node[cnt].pos = i;
            node[cnt].kind = 2;
            cnt ++;
        }
        Alldoubledive(1, cnt - 1, -INF, INF);
        for(int i = 1; i <= m; i ++){
            if(ans[i] == INF){  /// k 大于区间长度
                ans[i] = 0;
            }
            printf("%lld\n", ans[i]);
        }
    }

    return 0;
}


/// 带修改区间第 k 大
/// BZOJ 1901 整体二分
#include <bits/stdc++.h>
#define mid (((l) + (r)) / 2)
#define lowbit(x) (x & (-x))
using namespace std;

inline int ReadInt() {
    static int ch, n;
    ch = getchar(), n = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}

struct oper {
    int type, idx, l, r, k;
}t;

const int maxn = 10000 + 3, maxm = 10000 + 3;
int c[maxn], a[maxn], ans[maxm], n, m, cnt = 0;

inline void add(int x, int v) {
    x++;
    while (x <= n) {
        c[x] += v;
        x += lowbit(x);
    }    
}
inline int sum(int x) {
    x++; int ret = 0;
    while (x > 0) {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

//操作序列，答案区间 [l, r)
void solve(queue<oper> &q, int l, int r) {
    if (q.empty()) return;
    if (l >= r) return;
    if (r - l == 1) {
        while (!q.empty()) {
            t = q.front(); q.pop();
            if (t.type == 3) ans[t.idx] = l;
        }
        return;
    }
    queue<oper> q1, q2;
    queue<int> idp, idn;
    while (!q.empty()) {
        t = q.front(); q.pop();
        if (t.type == 1) {
            if (t.k < mid) add(t.idx, 1), idp.push(t.idx), q1.push(t);
            else q2.push(t);
        }else if (t.type == 2) {
            if (t.k < mid) add(t.idx, -1), idn.push(t.idx), q1.push(t);
            else q2.push(t);
        } else {
            int v = sum(t.r) - sum(t.l - 1);
            if (v + 1 <= t.k) t.k -= v, q2.push(t);
            else q1.push(t);
        }
    }
    while (!idp.empty()) {
        add(idp.front(), -1);
        idp.pop();
    }
    while (!idn.empty()) {
        add(idn.front(), 1);
        idn.pop();
    }
    solve(q1, l, mid);
    solve(q2, mid, r);
}

char str[2];
int main() {
    queue<oper> q;
    n = ReadInt(), m = ReadInt();
    //type 1 +
    //type 2 -
    //type 3 Query
    for (int i = 0; i < n; ++i) {
        t.type = 1, a[i] = t.k = ReadInt();
        t.idx = i;
        q.push(t);
    } 
    for (int i = 0; i < m; ++i) {
        scanf("%s", str);
        if (str[0] == 'Q') {
            t.type = 3, t.l = ReadInt() - 1, t.r = ReadInt() - 1, t.k = ReadInt(), t.idx = cnt++;
            q.push(t);
        } else if (str[0] == 'C') {
            t.type = 2, t.idx = ReadInt() - 1, t.k = a[t.idx];
            q.push(t);
            t.type = 1, a[t.idx] = t.k = ReadInt();
            q.push(t);
        }
    }
    memset(c, 0, sizeof c);
    solve(q, 0, 1e9 + 3);
    for (int i = 0; i < cnt; ++i)
        printf("%d\n", ans[i]);
    return 0;
}


/// 树上路径第 K 大
/// BZOJ 2588
/// 现在第 K 大跑到树上来了嘿嘿嘿
#include <bits/stdc++.h>
#define mid (((l) + (r)) / 2)
using namespace std;

inline int ReadInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}
typedef long long ll;

const int maxn = 100000 + 3;
struct SegNode *pit, *null;
struct SegNode {
    SegNode *ls, *rs;
    int s;
    inline void maintain() {
        s = ls->s + rs->s;
    }
    SegNode(): ls(null), rs(null), s(0) {}
}pool[maxn * 18], *root[maxn];

void init() {
    pit = pool;
    null = new SegNode();
    null->ls = null, null->rs = null;
}

SegNode* modify(const SegNode *o, int l, int r, int v) {
    if (l >= r) return null;
    SegNode *ne = pit++;
    *ne = *o;
    if (r - l == 1)
        ne->s++;
    else {
        if (v < mid) ne->ls = modify(ne->ls, l, mid, v);
        else ne->rs = modify(ne->rs, mid, r, v);
        ne->maintain();
    }
    return ne;
}

vector<int> G[maxn], Ws;
int n, m, w[maxn], ancestor[maxn][18], depth[maxn];

void compress() {
    for (int i = 0; i < n; ++i)
        Ws.push_back(w[i]);
    sort(Ws.begin(), Ws.end());
    Ws.erase(unique(Ws.begin(), Ws.end()), Ws.end());
    for (int i = 0; i < n; ++i)
        w[i] = lower_bound(Ws.begin(), Ws.end(), w[i]) - Ws.begin();
}

void process() {
    for (int w = 1; (1 << w) < n; ++w)
        for (int i = 0; i < n; ++i) if (depth[i] - (1 << w) >= 0)
            ancestor[i][w] = ancestor[ancestor[i][w - 1]][w - 1];
}

int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int lim = log2(depth[a]);
    for (int i = lim; i >= 0; --i)
        if (depth[a] - (1 << i) >= depth[b])
            a = ancestor[a][i];
    if (a == b) return a;
    for (int i = lim; i >= 0; --i)
        if (depth[a] - (1 << i) >= 0 && ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    return ancestor[a][0];
}

int query(const SegNode *a, const SegNode *b, const SegNode *c, const SegNode *d, int l, int r, int k) {
    if (r - l == 1) return Ws[l];
    int s = a->ls->s + b->ls->s - c->ls->s - d->ls->s;
    if (k <= s) return query(a->ls, b->ls, c->ls, d->ls, l, mid, k);
    else return query(a->rs, b->rs, c->rs, d->rs, mid, r, k - s);
}

void dfs(const SegNode *o, int u, int fa) {
    ancestor[u][0] = fa, depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    root[u] = modify(o, 0, Ws.size(), w[u]);
    for (int i = 0; i < (int)G[u].size(); ++i) {
        int v = G[u][i];
        if (v != fa) dfs(root[u], v, u);
    }
}

int main() {
    init();
    n = ReadInt(), m = ReadInt();
    for (int i = 0; i < n; ++i)
        w[i] = ReadInt();
    compress();
    for (int i = 0; i < n - 1; ++i) {
        int f = ReadInt() - 1, t = ReadInt() - 1;
        G[f].push_back(t);
        G[t].push_back(f);
    }
    dfs(null, 0, -1);
    process();
    int lastAns = 0;
    while (m--) {
        int u = (ReadInt() ^ lastAns) - 1, v = ReadInt() - 1, k = ReadInt();
        int lca = LCA(u, v);
        printf("%d", lastAns = query(root[u], root[v], root[lca], lca == 0 ? null : root[ancestor[lca][0]], 0, Ws.size(), k));
        if (m) putchar('\n');
    }
    return 0;
}


/// BZOJ 1146 
/// 主席树 带修改树上路径第 k 大
#include <bits/stdc++.h>
#define mid (((l) + (r)) / 2)
#define lowbit(x) ((x) & -(x))
using namespace std;

inline int ReadInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}
typedef long long ll;

const int maxn = 80000 + 3, maxq = 80000 + 3;
struct SegNode *pit, *null;
struct SegNode {
    SegNode *ls, *rs;
    int s;
    inline void maintain() {
        s = ls->s + rs->s;
    }
    SegNode(): ls(null), rs(null), s(0) {}
}pool[maxn * 85], *root[maxn], *Fen[maxn], *add[100], *dec[100];

void init() {
    pit = pool;
    null = new SegNode();
    null->ls = null, null->rs = null;
}

vector<int> G[maxn], Ws;
int n, m, w[maxn], ancestor[maxn][18], depth[maxn], k[maxn], a[maxn], b[maxn], id[maxn], s[maxn], timestamp = 0;

void compress() {
    for (int i = 0; i < n; ++i)
        Ws.push_back(w[i]);
    for (int i = 0; i < m; ++i) {
        k[i] = ReadInt(), a[i] = ReadInt() - 1, b[i] = ReadInt() - (k[i] > 0);
        if (k[i] == 0) Ws.push_back(b[i]);
    }
    sort(Ws.begin(), Ws.end());
    Ws.erase(unique(Ws.begin(), Ws.end()), Ws.end());
    for (int i = 0; i < n; ++i)
        w[i] = lower_bound(Ws.begin(), Ws.end(), w[i]) - Ws.begin();
    for (int i = 0; i < m; ++i)
        if (k[i] == 0) b[i] = lower_bound(Ws.begin(), Ws.end(), b[i]) - Ws.begin();
}

void process() {
    for (int w = 1; (1 << w) < n; ++w)
        for (int i = 0; i < n; ++i) if (depth[i] - (1 << w) >= 0)
            ancestor[i][w] = ancestor[ancestor[i][w - 1]][w - 1];
}

int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int lim = log2(depth[a]);
    for (int i = lim; i >= 0; --i)
        if (depth[a] - (1 << i) >= depth[b])
            a = ancestor[a][i];
    if (a == b) return a;
    for (int i = lim; i >= 0; --i)
        if (depth[a] - (1 << i) >= 0 && ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    return ancestor[a][0];
}

SegNode* modify(const SegNode *o, int l, int r, int v, int op) {
    if (l >= r) return null;
    SegNode *ne = pit++;
    *ne = *o;
    if (r - l == 1)
        ne->s += op;
    else {
        if (v < mid) ne->ls = modify(ne->ls, l, mid, v, op);
        else ne->rs = modify(ne->rs, mid, r, v, op);
        ne->maintain();
    }
    return ne;
}

int query(SegNode* add[], int addc, SegNode* dec[], int decc, int l, int r, int k) {
    if (r - l == 1) return Ws[l];
    int s = 0;
    for (int i = 0; i < addc; ++i) s += add[i]->ls->s;
    for (int i = 0; i < decc; ++i) s -= dec[i]->ls->s;
    for (int i = 0; i < addc; ++i) 
        if (k <= s) add[i] = add[i]->ls;
        else add[i] = add[i]->rs;
    for (int i = 0; i < decc; ++i)
        if (k <= s) dec[i] = dec[i]->ls;
        else dec[i] = dec[i]->rs;
    if (k <= s) {
        return query(add, addc, dec, decc, l, mid, k);
    }else return query(add, addc, dec, decc, mid, r, k - s);
}

int dfs(const SegNode *o, int u, int fa) {
    id[u] = timestamp++, ancestor[u][0] = fa, depth[u] = fa == -1 ? 0 : depth[fa] + 1;
    root[u] = modify(o, 0, Ws.size(), w[u], 1);
    s[u] = 1;
    for (int i = 0; i < (int)G[u].size(); ++i) {
        int v = G[u][i];
        if (v != fa) s[u] += dfs(root[u], v, u);
    }
    return s[u];
}

int main() {
    init();
    n = ReadInt(), m = ReadInt();
    for (int i = 0; i < n; ++i)
        w[i] = ReadInt();
    for (int i = 0; i < n - 1; ++i) {
        int f = ReadInt() - 1, t = ReadInt() - 1;
        G[f].push_back(t);
        G[t].push_back(f);
    }
    compress();
    dfs(null, 0, -1);
    process();
    for (int i = 1; i <= n; ++i) Fen[i] = null;
    for (int i = 0; i < m; ++i) {
        if (k[i] == 0) {
            for (int j = id[a[i]] + 1; j <= n; j += lowbit(j)) {
                Fen[j] = modify(Fen[j], 0, Ws.size(), w[a[i]], -1);
                Fen[j] = modify(Fen[j], 0, Ws.size(), b[i], 1);
            }
            for (int j = id[a[i]] + s[a[i]] + 1; j <= n; j += lowbit(j)) {
                Fen[j] = modify(Fen[j], 0, Ws.size(), w[a[i]], 1);
                Fen[j] = modify(Fen[j], 0, Ws.size(), b[i], -1);
            }
            w[a[i]] = b[i];
        }else {
            int lca = LCA(a[i], b[i]), length = depth[a[i]] + depth[b[i]] - 2 * depth[lca] + 1;
            k[i] = length - k[i] + 1;
            if (k[i] <= 0) puts("invalid request!");
            else {
                int addc = 0, decc = 0;
                add[addc++] = root[a[i]], add[addc++] = root[b[i]], dec[decc++] = root[lca];
                if (lca) dec[decc++] = root[ancestor[lca][0]];
                for (int j = id[a[i]] + 1; j > 0; j -= lowbit(j)) add[addc++] = Fen[j];
                for (int j = id[b[i]] + 1; j > 0; j -= lowbit(j)) add[addc++] = Fen[j];
                for (int j = id[lca] + 1; j > 0; j -= lowbit(j)) dec[decc++] = Fen[j];
                if (lca) for (int j = id[ancestor[lca][0]] + 1; j > 0; j -= lowbit(j)) dec[decc++] = Fen[j];
                printf("%d\n", query(add, addc, dec, decc, 0, Ws.size(), k[i]));
            }
        }
    }
    return 0;
}