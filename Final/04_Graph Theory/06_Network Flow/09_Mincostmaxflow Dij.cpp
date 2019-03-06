int he[N];

int Dij()
{
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > Q;
    for(int i = 1; i <= tt; i ++){
        dis[i] = INF;
        pre[i] = -1;
    }
    dis[ss] = 0;
    mincost[ss] = INF;
    mincost[tt] = 0;
    Q.push(mp(dis[ss], ss));
    while(!Q.empty()){
        int u, w;

        u = Q.top().second;
        w = Q.top().first;
        Q.pop();
        if(dis[u] < w){
            continue;
        }
        for(int i = head[u]; i != -1; i = node[i].ne){
            int v;

            v = node[i].to;
            if(node[i].flow > 0 && dis[v] > dis[u] + node[i].v + he[u] - he[v]){
                dis[v] = dis[u] + node[i].v + he[u] - he[v];
                pre[v] = i; /// amazing  Ö±½Ó´æ±ßµÄ±àºÅ
                /// pre[v] = u;
                mincost[v] = min(mincost[u], node[i].flow);
                Q.push(mp(dis[v], v));
            }
        }
    }

    return mincost[tt];
}

int Mincostmaxflow()
{
    int ans;
    int t;

    ans = 0;
    for(int i = 1; i <= tot; i ++){
        he[i] = 0;
    }
    while(true){
        t = Dij();
        if(!t){
            break;
        }
        for(int i = 1; i <= tot; i ++){
            he[i] += dis[i];
        }
        maxflow += t;
        /// cout << 666 << endl;
        for(int i = pre[tt]; i != -1; i = pre[node[i].from]){
            // printf("v = %d %d\n", node[i].v, t);
            ans += t * node[i].v;
            node[i].flow -= t;
            node[i ^ 1].flow += t;
        }
    }

    return ans;
}
