struct Quary
{
    int l;
    int r;
    int num;
//    bool operator < (const Quary node) const
//    {
//        return (pos[l] < pos[node.l])||(pos[l] == pos[node.l] && (pos[l] & 1 ? r < node.r : r > node.r));
//    }
};
 
Quary quary[N];
int pos[N];
int ans[N];
int block;
int n, m;
int l, r;
 
bool cmp(Quary a, Quary b)
{
    if(pos[a.l] == pos[b.l]){
        return a.r < b.r;
    }
    else{
        return pos[a.l] < pos[b.l];
    }	
}

void add(int x)
{
    ///
}
 
void del(int x)
{
	///
}
 
int main(int argc, char const *argv[])
{
    while(scanf("%d%d", &n, &m) == 2){
        memset(cnt, 0, sizeof(cnt));
        block = sqrt(n);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &ma[i]);
            pos[i] = i / block;
        }
        for(int i = 1; i <= m; i ++){
            int num, l, r;
 
            scanf("%d%d%d%d", &quary[i].opt, &quary[i].l, &quary[i].r, &quary[i].x);
            quary[i].num = i;
        }
        sort(quary + 1, quary + m + 1, cmp);
        l = 1;
        r = 0;
        for(int i = 1; i <= m; i ++){
            while(l > quary[i].l){
                l --;
                add(l);
            }
            while(r < quary[i].r){
                r ++;
                add(r);
            }
            while(l < quary[i].l){
                del(l);
                l ++;
            }
            while(r > quary[i].r){
                del(r);
                r --;
            }
            ans[quary[i].num] = ask(quary[i]);
        }
    }
 
    return 0;
}