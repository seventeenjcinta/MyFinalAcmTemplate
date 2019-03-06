const int N = 1000010;

struct Three
{
    int l;
    int r;
    int v;
    int son[2];
};

Three tree[N * 20];
int root[N];
int n, m;
int ma[N];
int tot;	/// 根节点个数

void Build(int &x, int l, int r)
{
    tot ++;
    x = tot;
    tree[x].l = l;
    tree[x].r = r;
    //m printf("%d %d %d\n", x, tree[x].l, tree[x].r);
    if(l == r){
        tree[x].v = ma[l];
    }
    else{
        int mid;

        mid = l + ((r - l) >> 1);
        Build(tree[x].son[0], l, mid);
        Build(tree[x].son[1], mid + 1, r);
    }
}

int Quary(int x, int pos)
{
    int ll, rr;

    ll = tree[x].l;
    rr = tree[x].r;
    // printf("%d %d %d %d\n", x, pos, ll, rr);
    if(ll == rr && ll == pos){
        return tree[x].v;
    }
    else{
        int mid;

        mid = ll + ((rr - ll) >> 1);
        if(pos <= mid){
            return Quary(tree[x].son[0], pos);
        }
        else{
            return Quary(tree[x].son[1], pos);
        }
    }
}

void Update(int &x, int pre, int pos, int v)
{
    int ll, rr;

    ll = tree[pre].l;
    rr = tree[pre].r;
    tot ++;
    x = tot;
    tree[x] = tree[pre];
    if(ll == rr && ll == pos){
        tree[x].v = v;
    }
    else{
        int mid;

        mid = ll + ((rr - ll) >> 1);
        if(pos <= mid){
            Update(tree[x].son[0], tree[pre].son[0], pos, v);
        }
        else{
            Update(tree[x].son[1], tree[pre].son[1], pos, v);
        }
    }
}

int main(int argc, char const *argv[])
{
    while(scanf("%d%d", &n, &m) == 2){
        tot = 0;
        for(int i = 1; i <= n; i ++){
            scanf("%d", &ma[i]);
        }
        Build(root[0], 1, n);
        for(int i = 1; i <= m; i ++){
            int kind, ops, pos, v;

            scanf("%d%d", &kind, &ops);
            if(ops == 1){
                scanf("%d%d", &pos, &v);
                Update(root[i], root[kind], pos, v);
            }
            else{
                scanf("%d", &pos);
                root[i] = root[kind];	///！
                printf("%d\n", Quary(root[i], pos));
            }
        }
    }

    return 0;
}