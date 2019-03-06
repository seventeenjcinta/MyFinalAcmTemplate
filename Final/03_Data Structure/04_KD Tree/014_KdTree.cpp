#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL maxn = 110000;
const LL INF = 1e18;
const LL dimension = 2;
LL D;

struct Node {
    LL d[dimension], maxpos[dimension], minpos[dimension], v, sum, lazy, cnt;
    //以中心点d作为空间的代表，max和min分别是空间的边界
    LL l, r;
    bool operator < (const Node & b) const  {
        return d[D] < b.d[D];
    }
    bool operator == (const Node & b) const {
        bool ans = 1;
        for (int i = 0; i < dimension; i++) {
            ans &= d[i] == b.d[i];
        }
        return ans;
    }
} p[maxn];

bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
    return x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2;
}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
    return x1>X2||x2<X1||y1>Y2||y2<Y1;
}

struct KDT {
    LL root, cnt, block;
    Node tr[maxn], now;
    //now,用来单点插入
    void pushup(int rt) {
        tr[rt].cnt = 1;
        int l = tr[rt].l, r = tr[rt].r;
        if (l) tr[rt].cnt += tr[l].cnt;
        if (r) tr[rt].cnt += tr[r].cnt;
        for (int i = 0; i < dimension; i++) {
            tr[rt].maxpos[i] = tr[rt].minpos[i] = tr[rt].d[i];
            if (l) {
                tr[rt].minpos[i] = min(tr[rt].minpos[i], tr[l].minpos[i]);
                tr[rt].maxpos[i] = max(tr[rt].maxpos[i], tr[l].maxpos[i]);
            }
            if (r) {
                tr[rt].minpos[i] = min(tr[rt].minpos[i], tr[r].minpos[i]);
                tr[rt].maxpos[i] = max(tr[rt].maxpos[i], tr[r].maxpos[i]);
            }
        }
        tr[rt].sum = tr[l].sum + tr[r].sum + tr[rt].v;
    }

    void pushdown(int rt) {
        if (tr[rt].lazy) {
            int l = tr[rt].l, r = tr[rt].r;
            if (l) {
                tr[l].lazy += tr[rt].lazy;
                tr[l].v += tr[rt].lazy;
                tr[l].sum += tr[l].cnt * tr[rt].lazy;
            }
            if (r) {
                tr[r].lazy += tr[rt].lazy;
                tr[r].v += tr[rt].lazy;
                tr[r].sum += tr[r].cnt * tr[rt].lazy;
            }
            tr[rt].lazy = 0;
        }
    }

    LL rebuild(LL l, LL r, LL dep) { //重构
        if (l > r) return 0;
        D = dep; LL mid = (l + r) >> 1;
        nth_element(p+l, p+mid, p+r+1);
        tr[mid] = p[mid];
        tr[mid].l = rebuild(l, mid-1, (dep+1)%dimension);
        tr[mid].r = rebuild(mid+1, r, (dep+1)%dimension);

        pushup(mid);
        return mid;
    }

    void checkSize() {
        if (cnt == block) {
            for (int i = 1; i <= cnt; i++) p[i] = tr[i];
            root = rebuild(1, cnt, 0);
            block += 10000;
        }
    }

    void ins(LL &rt, bool D) {//单点插入，如果没有就新开点
        if (!rt) {
            rt = ++cnt;
            for (int i = 0; i < dimension; i++) tr[rt].d[i] = tr[rt].maxpos[i] = tr[rt].minpos[i] = now.d[i];
            tr[rt].v = tr[rt].sum = now.v;
            return;
        }
        if (now == tr[rt]) {
            tr[rt].v += now.v, tr[rt].sum += now.v;
            return ;
        }
        pushdown(rt);
        if (now.d[D] < tr[rt].d[D]) ins(tr[rt].l, D^1);
        else ins(tr[rt].r, D^1);
        pushup(rt);
    }
    /*
    int x, y, p;
    scanf("%d%d%d", &x, &y, &p);
    Node &now = Tree.now;
    now.d[0] = x, now.d[1] = y, now.v = p, now.sum = p;
    Tree.ins(Tree.root, 0);
    Tree.checkSize();
    */
    LL query(int rt, int x1, int y1, int x2, int y2) {
        if(!rt) return 0;
        LL res = 0;
        if (out(x1, y1, x2, y2, tr[rt].minpos[0], tr[rt].minpos[1], tr[rt].maxpos[0], tr[rt].maxpos[1]))
            return 0;
        if (in(x1, y1, x2, y2, tr[rt].minpos[0], tr[rt].minpos[1], tr[rt].maxpos[0], tr[rt].maxpos[1]))
            return tr[rt].sum;
        pushdown(rt);
        if (in(x1, y1, x2, y2, tr[rt].d[0], tr[rt].d[1], tr[rt].d[0], tr[rt].d[1]))
            res += tr[rt].v;
        res += query(tr[rt].l, x1, y1, x2, y2) + query(tr[rt].r, x1, y1, x2, y2);
        pushup(rt);
        return res;
    }

    void update(int rt, int x1, int y1, int x2, int y2, LL add) {
        if(!rt) return ;
        if (out(x1, y1, x2, y2, tr[rt].minpos[0], tr[rt].minpos[1], tr[rt].maxpos[0], tr[rt].maxpos[1]))
            return ;
        if (in(x1, y1, x2, y2, tr[rt].minpos[0], tr[rt].minpos[1], tr[rt].maxpos[0], tr[rt].maxpos[1])) {
            tr[rt].lazy += add;
            tr[rt].sum += add * tr[rt].cnt;
            tr[rt].v += add;
            return ;
        }
        pushdown(rt);
        if (in(x1, y1, x2, y2, tr[rt].d[0], tr[rt].d[1], tr[rt].d[0], tr[rt].d[1])) {
            tr[rt].v += add;
        }
        update(tr[rt].l, x1, y1, x2, y2, add);
        update(tr[rt].r, x1, y1, x2, y2, add);
        pushup(rt);
    }

    void init() {
        root = cnt = 0;
        block = 10000;
    }

    LL getdis(LL val[dimension], LL rt) { //估价函数，用来寻找区间
        LL res = 0;
        for(LL i = 0; i <dimension; i++) {
            if(val[i] < tr[rt].minpos[i]) res += (tr[rt].minpos[i] - val[i]) * (tr[rt].minpos[i] - val[i]);
            if(val[i] > tr[rt].maxpos[i]) res += (val[i] - tr[rt].maxpos[i]) * (val[i] - tr[rt].maxpos[i]);
        }
        return res;
    }

    LL ans;

    void ask(LL val[dimension], LL rt) { //询问最近点
        LL dis = 0;
        for(LL i = 0; i < dimension; i++)
            dis += ((tr[rt].d[i] - val[i]) * (tr[rt].d[i] - val[i]));
        if(dis == 0) dis = INF;
        if(dis < ans)
            ans = dis;
        LL dl = tr[rt].l? getdis(val, tr[rt].l) : INF;
        LL dr = tr[rt].r? getdis(val, tr[rt].r) : INF;
        if(dl < dr) {if(dl < ans) ask(val, tr[rt].l); if(dr < ans) ask(val, tr[rt].r);}
        else {if(dr < ans) ask(val, tr[rt].r); if(dl < ans) ask(val, tr[rt].l);}
    }
} Tree;

int n, m;
int id;
int L[maxn], R[maxn];
int dep[maxn];
vector<int> G[maxn];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    L[u] = ++id;
    for (auto v:G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
    R[u] = id;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        Tree.init();
        id = 0;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dep[0] = -1;
        dfs(1, 0);
        for (int i = 1; i <= n; i++) {
            Node &now = p[i];
            now.d[0] = L[i];
            now.d[1] = dep[i];
        }
        Tree.root = Tree.rebuild(1, n, 0);
        while (m--) {
            int tp, l, x;
            scanf("%d", &tp);
            if (tp == 1){
                scanf("%d%d", &l, &x);
                Tree.update(Tree.root, 1, l, n, l, x);
            } else {
                scanf("%d", &x);
                printf("%lld\n", Tree.query(Tree.root, L[x], 1, R[x], n));
            }
        }
    }
    return 0;
}