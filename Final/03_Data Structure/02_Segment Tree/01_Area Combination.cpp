// 矩形面积并
map<double, int> Hash;
map<int, double> rHash;
struct line
{
    double l, r, h;
    int val;
    line(double l = 0, double r = 0, double h = 0, int val = 0) : l(l), r(r), h(h), val(val) {}
    bool operator<(const line& A) const { return h < A.h; }
};
struct Node
{
    int cover;
    double len;
};
const int maxn = 1000;
Node seg[maxn << 2];
void build(int rt, int l, int r)
{
    seg[rt].cover = seg[rt].len = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
void pushup(int rt, int l, int r)
{
    if (seg[rt].cover > 0)
        seg[rt].len = rHash[r + 1] - rHash[l]; // [l,r)
    else if (l == r)
        seg[rt].len = 0;
    else
        seg[rt].len = seg[lson].len + seg[rson].len;
}
void update(int rt, int l, int r, int L, int R, int val)
{
    if (L <= l && R >= r)
    {
        seg[rt].cover += val;
        pushup(rt, l, r);
        return;
    }
    int mid = l + r >> 1;
    if (mid >= L) update(lson, l, mid, L, R, val);
    if (mid + 1 <= R) update(rson, mid + 1, r, L, R, val);
    pushup(rt, l, r);
}
int main()
{
    int n, kase = 0;
    while (~scanf("%d", &n))
    {
        if (!n) break;
        double x1, x2, y1, y2;
        vector<line> a;
        set<double> xval;
        for (int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a.emplace_back(x1, x2, y1, 1);
            a.emplace_back(x1, x2, y2, -1);
            xval.insert(x1);
            xval.insert(x2);
        }
        // 离散化
        Hash.clear(), rHash.clear();
        int cnt = 0;
        for (auto& v : xval)
        {
            Hash[v] = ++cnt;
            rHash[cnt] = v;
        }
        sort(a.begin(), a.end());
        build(1, 1, cnt);
        double ans = 0;
        for (int i = 0; i < a.size() - 1; i++)
        {
            update(1, 1, cnt, Hash[a[i].l], Hash[a[i].r] - 1,
                   a[i].val); //[l,r)
            ans += (a[i + 1].h - a[i].h) * seg[1].len;
        }
        printf("Test case #%d\n", ++kase);
        printf("Total explored area: %.2lf\n\n", ans);
    }
}