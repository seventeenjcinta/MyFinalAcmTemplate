/*
数据范围 100010
1. 插入x数
2. 删除x数(若有多个相同的数，因只删除一个)
3. 查询x数的排名(若有多个相同的数，因输出最小的排名)
4. 查询排名为x的数
5. 求x的前驱(前驱定义为小于x，且最大的数)
6. 求x的后继(后继定义为大于x，且最小的数)
*/
const int N = 100010;
const int INF = 0x7fffffff;

struct Tree
{
    int fa; ///
    int v;
    int siz;    /// 尺寸
    int son[2]; /// 0 - left
    int cnt;    /// 次数
};

Tree tree[N];
int n, m;
int root;
int ts; /// 树的大小

void Clean(int x)
{
    tree[x].son[0] = tree[x].son[1] = tree[x].v = tree[x].fa = tree[x].siz = tree[x].cnt = 0;
}

void Up(int x)
{
    if(x){
        tree[x].siz = tree[x].cnt;
        if(tree[x].son[0]){
            tree[x].siz += tree[tree[x].son[0]].siz;
        }
        if(tree[x].son[1]){
            tree[x].siz += tree[tree[x].son[1]].siz;
        }
    }
}

void Rotate(int x, int kind) /// 0 - zag    1 - zig
{
    int y, z;

    y = tree[x].fa;
    z = tree[y].fa;
    tree[y].son[!kind] = tree[x].son[kind];
    tree[tree[x].son[kind]].fa = y;
    tree[x].son[kind] = y;
    tree[y].fa = x;
    tree[z].son[tree[z].son[1] == y] = x;
    tree[x].fa = z;
    Up(y);
}

void Splay(int x, int goal)
{
    if(x == goal){
        return ;
    }
    while(tree[x].fa != goal){
        int y, z;
        bool rx, ry;

        y = tree[x].fa;
        z = tree[y].fa;
//        Down(z);
//        Down(y);
//        Down(x);
        rx = (x == tree[y].son[0]);
        ry = (y == tree[z].son[0]);
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
        root = x;
    }
}

int Findrank(int x)
{
    int ans;
    int now;

    now = root;
    ans = 0;
    // printf("begin = %d\n", x);
    while(true){
        // cout << now << endl;
        if(tree[now].v > x){
            // printf("Turn left\n");
            now = tree[now].son[0];
        }
        else{
            // printf("Turn right\n");
            if(tree[now].son[0]){
                ans += tree[tree[now].son[0]].siz;
            }
            // printf("now = %d = %d\n", tree[now].v, x);
            if(tree[now].v == x){
                // cout << 998244353 << endl;
                Splay(now, 0);

                return ans + 1;
            }
            ans += tree[now].cnt; ///!
            now = tree[now].son[1];
        }
    }
}

int Findnum(int x)
{
    int now;

    now = root;
    while(true){
        if(tree[now].son[0] && x <= tree[tree[now].son[0]].siz){
            now = tree[now].son[0];
        }
        else{
            int t;

            t = tree[now].cnt;
            if(tree[now].son[0]){
                t += tree[tree[now].son[0]].siz;
            }
            if(x <= t){
                Splay(now, 0);

                return tree[now].v;
            }
            x -= t;
            now = tree[now].son[1];
        }
    }
}

int Findpre(int x)
{
    int now;

    Findrank(x);
    // cout << "ENDDDDDDDDDDDDDDD" << endl;
    now = tree[root].son[0];
    while(tree[now].son[1]){
        now = tree[now].son[1];
    }

    return now;
}

int Findnet(int x)
{
    int now;

    Findrank(x);
    now = tree[root].son[1];
    while(tree[now].son[0]){
        // cout << 666 << endl;
        now = tree[now].son[0];
    }

    return now;
}

void Del(int x)
{
    int t;
    int l;
    int now;

    Findrank(x);
    now = root;
    if(tree[root].cnt > 1){
        tree[root].cnt --;
		tree[root].siz --;
        return ;
    }
    if(!tree[root].son[0] && !tree[root].son[1]){   ///only one
        Clean(root);
        root = 0;

        return ;
    }
    if(!tree[root].son[0]){
        root = tree[root].son[1];
        tree[root].fa = 0;
        Clean(now);

        return ;
    }
    if(!tree[root].son[1]){
        root = tree[root].son[0];
        tree[root].fa = 0;
        Clean(now);

        return ;
    }
    t = Findpre(tree[root].v);
    Splay(t, 0);
    tree[tree[now].son[1]].fa = root;
    tree[root].son[1] = tree[now].son[1];
    Clean(now);
    Up(root);
}

void Insert(int x)
{
    if(!root){
        // cout << 6566 << endl;
        ts ++;
        tree[ts].son[0] = tree[ts].son[1] = tree[ts].fa = 0;
        tree[ts].v = x;
        tree[ts].cnt = 1;
        tree[ts].siz = 1;
        root = ts;

        return;
    }
    else{
        int now;
        int t;

        t = 0;
        now = root;
        while(true){
            if(tree[now].v == x){
                tree[now].cnt ++;
                Up(t);
                Splay(now, 0);
                break;
            }
            t = now;
            now = tree[now].son[tree[now].v < x];
            if(!now){
                ts ++;
                tree[ts].son[0] = tree[ts].son[1] = 0;
                tree[ts].fa = t;
                tree[ts].v = x;
                tree[ts].cnt = 1;
                tree[t].son[tree[t].v < x] = ts;
                Up(t);
                Splay(ts, 0);
                break;
            }
        }
    }
}

void Show()
{
    printf("root = %d\n", root);
    for(int i = 0; i <= ts; i ++){
        printf("%d l = %d r = %d num = %d cnt = %d siz = %d fa = %d\n", i, tree[i].son[0], tree[i].son[1], tree[i].v, tree[i].cnt, tree[i].siz, tree[i].fa);
    }
}

void Ini()
{
	root = ts = 0;
}

int main(int argc, char const *argv[])
{
    while(scanf("%d", &n) == 1){
        Ini();
        for(int i = 0; i < n; i ++){
            int ops, x;

            scanf("%d%d", &ops, &x);
            if(ops == 1){
                Insert(x);
            }
            else if(ops == 2){
                Del(x);
            }
            else if(ops == 3){
                printf("%d\n", Findrank(x));
            }
            else if(ops == 4){
                printf("%d\n", Findnum(x));
            }
            else if(ops == 5){
                Insert(x);
                // Show();
                printf("%d\n", tree[Findpre(x)].v);
                Del(x);
            }
            else{
                Insert(x);
                // Show();
                printf("%d\n", tree[Findnet(x)].v);
                Del(x);
            }
            // Show();
        }
    }

    return 0;
}