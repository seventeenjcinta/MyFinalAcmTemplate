void fre() {  }
#define MS(x, y) memset(x, y, sizeof(x))
#define ls o<<1
#define rs o<<1|1
typedef long long LL;
typedef unsigned long long UL;
typedef unsigned int UI;
template <class T1, class T2>inline void gmax(T1 &a, T2 b) { if (b > a)a = b; }
template <class T1, class T2>inline void gmin(T1 &a, T2 b) { if (b < a)a = b; }
const int N = 2e5 + 10, M = 0, Z = 1e9 + 7, inf = 0x3f3f3f3f;
template <class T1, class T2>inline void gadd(T1 &a, T2 b) { a = (a + b) % Z; }
int casenum, casei;
LL sqr(LL x)
{
    return x * x;
}
struct point
{
    LL x, y;
    point(){}
    point(LL x, LL y) : x(x), y(y) {}
    friend point operator + (const point &a, const point &b){
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator - (const point &a, const point &b){
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator * (const point &a, const double &b){
        return point(a.x * b, a.y * b);
    }
    friend point operator / (const point &a, const double &b){
        return point(a.x / b, a.y / b);
    }
    friend bool operator == (const point &a, const point &b){
        return a.x == b.x && a.y == b.y;
    }
};
LL det(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}
LL dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}
LL dist(point a, point b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}
struct polygon_convex
{
    vector<point> p;
    polygon_convex(int size = 0){
        p.resize(size);
    }
};
bool comp_less(const point &a, const point &b)
{
    return a.x - b.x < 0 || a.x - b.x == 0 && a.y - b.y < 0;
}
polygon_convex convex_hull(vector<point> a)
{
    polygon_convex res(2 * a.size() + 5);
    sort(a.begin(), a.end(), comp_less);
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = 0;
    for(int i = 0; i < a.size(); i ++){
        while(m > 1 && det(res.p[m - 1] - res.p[m - 2], a[i] - res.p[m - 2]) <= 0) -- m;
        res.p[m ++] = a[i];
    }
    int k = m;
    for(int i = int(a.size()) - 2; i >= 0; i --){
        while(m > k && det(res.p[m - 1] - res.p[m - 2], a[i] - res.p[m - 2]) <= 0) -- m;
        res.p[m ++] = a[i];
    }
    res.p.resize(m);
    if(a.size() > 1) res.p.resize(m - 1);
    return res;
}

LL cross(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}
int R;

double rotating_calipers(point *p, int n)
{
    int U = 1;
    double ans = 2.0 * R;
    p[n] = p[0];
    for(int i = 0; i < n; i ++){
        while(cross(p[i], p[i + 1], p[U + 1]) - cross(p[i], p[i + 1], p[U]) <= 0) U = (U + 1) % n;
        double d = sqrt(dist(p[i], p[i + 1]));
        double h = 1.0 * fabs(cross(p[i], p[i + 1], p[U])) / d;
        gmin(ans, h);
    }
    return ans;
}
int n;
point t, p[N];
polygon_convex a;
int main()
{
    scanf("%d%d", &n, &R);
    for(int i = 0; i < n; i ++){
        scanf("%lld%lld", &t.x, &t.y);
        a.p.push_back(t);
    }
    a = convex_hull(a.p);
    n = a.p.size();
    for(int i = 0; i < n; i ++){
        p[i] = a.p[i];
    }
    double ans;
    if(n <= 2){
        printf("0.000000000");
    }
    else {
        ans = rotating_calipers(p, n);
        printf("%.10f\n", ans);
    }
    return 0;
}
