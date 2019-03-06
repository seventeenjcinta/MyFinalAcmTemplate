const int N = 100010;

struct Tree
{
    int l;
    int r;
    LL sum;
    LL lazy;
};

Tree tree[N * 4];
int ma[N];
int n, m;

void up(int x)
{
    tree[x].sum = tree[x << 1].sum + tree[x << 1 | 1].sum;
}

void down(int x)
{
    LL t = tree[x].lazy;

    if(t){
        tree[x].lazy = 0;
        tree[x << 1].sum += (tree[x << 1].r - tree[x << 1].l + 1) * t;
        tree[x << 1].lazy += t;
        tree[x << 1 | 1].sum += (tree[x << 1 | 1].r - tree[x << 1 | 1].l + 1) * t;
        tree[x << 1 | 1].lazy += t;
    }
}

void build(int x, int l, int r)
{
    tree[x].l = l;
    tree[x].r = r;
    tree[x].lazy = 0;
    if(l == r){
        tree[x].sum = ma[l];
    }
    else{
        int mid = l + ((r - l) >> 1);

        build(x << 1, l, mid);
        build(x << 1 | 1, mid + 1, r);
        up(x);
    }
}

void update(int x, int l, int r, int v)
{
    int ll = tree[x].l;
    int rr = tree[x].r;

    if(l > r){
        return ;
    }
    if(ll == l && rr == r){
        tree[x].sum += (tree[x].r - tree[x].l + 1) * v;
        tree[x].lazy += v;
    }
    else{
        int mid = ll + ((rr - ll) >> 1);

        down(x);
        update(x << 1, l, min(mid, r), v);
        update(x << 1 | 1, max(mid + 1, l), r, v);
        up(x);
    }
}

LL quary(int x, int l, int r)
{
    int ll = tree[x].l;
    int rr = tree[x].r;

    if(l > r){
        return 0;
    }
    if(ll == l && rr == r){
        return tree[x].sum;
    }
    else{
        int mid = ll + ((rr - ll) >> 1);
        LL t = 0;

        down(x);
        t += quary(x << 1, l, min(mid, r));
        t += quary(x << 1 | 1, max(mid + 1, l), r);
        up(x);

        return t;
    }
}

/// 区间乘加
struct Three
{
    int l;
    int r;
    LL lazya;
    LL lazym;
    LL sum;
};

Three tree[N * 4];
int n, m, MOD;
int ma[N];

void Up(int x)
{
    tree[x].sum = (tree[x << 1].sum + tree[x << 1 | 1].sum) % MOD;
}

void Down(int x)
{
    tree[x << 1].sum = ((tree[x << 1].r - tree[x << 1].l + 1) * tree[x].lazya % MOD + tree[x << 1].sum * tree[x].lazym % MOD) % MOD;
    tree[x << 1 | 1].sum = ((tree[x << 1 | 1].r - tree[x << 1 | 1].l + 1) * tree[x].lazya % MOD + tree[x << 1 | 1].sum * tree[x].lazym % MOD) % MOD;
    tree[x << 1].lazya = (tree[x << 1].lazya * tree[x].lazym % MOD + tree[x].lazya) % MOD;
    tree[x << 1 | 1].lazya = (tree[x << 1 | 1].lazya * tree[x].lazym % MOD + tree[x].lazya) % MOD;
    tree[x << 1].lazym = (tree[x << 1].lazym * tree[x].lazym) % MOD;
    tree[x << 1 | 1].lazym = (tree[x << 1 | 1].lazym * tree[x].lazym) % MOD;
    tree[x].lazya = 0;
    tree[x].lazym = 1;
}

void Build(int x, int l, int r)
{
    tree[x].l = l;
    tree[x].r = r;
    tree[x].lazya = 0;
    tree[x].lazym = 1;
    if(l == r){
        tree[x].sum = ma[l];
    }
    else{
        int mid;

        mid = l + ((r - l) >> 1);
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
        Up(x);
    }
}

void Update(int x, int l, int r, int v, int kind)   /// 0 - mul   1 - add
{
    int ll, rr;

    ll = tree[x].l;
    rr = tree[x].r;
    if(l > r){
        return ;
    }
    if(ll == l && rr == r){
        if(kind){	/// Add
            tree[x].lazya = (tree[x].lazya + v) % MOD;
            tree[x].sum = (tree[x].sum + (rr - ll + 1) * v % MOD) % MOD;
        }
        else{
            tree[x].lazya = (tree[x].lazya * v) % MOD;
            tree[x].lazym = (tree[x].lazym * v) % MOD;
            tree[x].sum = (tree[x].sum * v) % MOD;
        }
    }
    else{
        int mid;

        mid = ll + ((rr - ll) >> 1);
        Down(x);
        Update(x << 1, l, min(mid, r), v, kind);
        Update(x << 1 | 1, max(mid + 1, l), r, v, kind);
        Up(x);
    }
}

LL Quary(int x, int l, int r)
{
    int ll, rr;

    if(l > r){
        return 0;
    }
    //printf("%d %d %d\n", x, l, r);
    ll = tree[x].l;
    rr = tree[x].r;
    //printf("%d %d\n", ll, rr);
    if(ll == l && rr == r){
        return tree[x].sum;
    }
    else{
        int mid;
        LL ans;

        ans = 0;
        mid = ll + ((rr - ll) >> 1);
        Down(x);
        ans = (ans + Quary(x << 1, l, min(mid, r))) % MOD;
        ans = (ans + Quary(x << 1 | 1, max(mid + 1, l), r)) % MOD;

        return ans % MOD;
    }
}