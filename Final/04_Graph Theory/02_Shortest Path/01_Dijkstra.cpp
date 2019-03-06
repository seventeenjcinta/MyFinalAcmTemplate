Edge edge[N];
int n, m;
LL dis[N];

void Dij()
{
  	priority_queue< pair<int, int> > Q;
	memset(dis, 0x3f3f3f3f, sizeof(dis));
  	dis[1] = 0;
    Q.push(mp(0, 1));
    while(!Q.empty()){
        int w;
        int u;

        u = Q.top().second;
        Q.pop();
        for(int i = head[u]; i != -1; i = node[i].ne){
            int v;

            v = node[i].to;
            if(dis[v] > dis[u] + node[i].w){
                dis[v] = dis[u] + node[i].w
                Q.push(mp(-dis[v], node[i].w);
            }
        }
    }
}
