/****/
//qrec[]: 记录询问 (sorted pair<int, int>[])
//tot: 总询问数 (即qrec[]的大小)
#define maxn 100010
bool vis[maxn];
//memset(vis, false, sizeof(vis));
void tarjan(int now = root){        ///dfs(root)
    //printf("now = %d\n", now);
    fa[now] = now;                  ///union_find
    vis[now] = true;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(!vis[nxt]){
            tarjan(nxt);
            //unite(nxt, now);        ///fa[nxt] = now;
            fa[nxt] = now;          ///unite(nxt, now)
        }
    }
    int id = get_first_query(now);  ///找到询问为(now,*)的第一个询问的下标为id (lower_bound)
    while(id < tot && qrec[id].first == now){   ///遍历所有以x开头的询问, 记录答案
        int query = qrec[id].second;
        if(vis[query]){
            ans[id] = find(query);
            //int loctn = loc(make_pair(query, now));
            //ans[loctn] = ans[id];
            ////printf("lca(%d, %d) = %d\n", now, query, ans[id]);
        }
        id ++;
    }
}
#undef maxn
/****/