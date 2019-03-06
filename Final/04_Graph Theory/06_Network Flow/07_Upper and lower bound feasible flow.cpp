/// 若有源汇，先将汇点往源点流一条容量为 INF 的流(反向边正常建立)
int main(int argc, char const *argv[])
{
    int ncase;

    scanf("%d", &ncase);
    while(ncase --){
        scanf("%d%d", &n, &m);
        ini();
        ss = n + 1;
        tt = ss + 1;
        sum = 0;
        memset(cntf, 0, sizeof(cntf));
        for(int i = 1; i <= m; i ++){
            int from, to, upp; /// upp - 上界    low[i]  下界

            scanf("%d%d%d%d", &from, &to, &low[i], &upp);
            add_edge(from, to, upp - low[i], i);    ////
            add_edge(to, from, 0, i);
            cntf[from] -= low[i];
            cntf[to] += low[i];
        }
        for(int i = 1; i <= n; i ++){
            if(cntf[i] < 0){
                add_edge(i, tt, -cntf[i], 0);
                add_edge(tt, i, 0, 0);
            }
            else if(cntf[i] > 0){
                sum += cntf[i];
                add_edge(ss, i, cntf[i], 0);
                add_edge(i, ss, 0, 0);
            }
        }
        //cout << sum << endl;
        if(Dinic() == sum){
            printf("YES\n");
            for(int i = 1; i <= n; i ++){
                for(int j = head[i]; j != -1; j = node[j].ne){
                    if(!node[j].num || j % 2 == 0){
                        continue;
                    }
                    ans[node[j].num] = node[j].w + low[node[j].num];
                }
            }
            for(int i = 1; i <= m; i ++){
                printf("%d\n", ans[i]);
            }
        }
        else{
            printf("NO\n");
        }
    }

    return 0;
}