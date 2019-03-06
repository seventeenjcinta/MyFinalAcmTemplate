const int N = 1010;

Node node[N];
LL dis[N];
int n, m;

bool SPFA()
{
    queue<int> Q;
    bool inq[N];
    int cnt[N];

    memset(dis, 0x3f3f3f3f, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    memset(inq, 0, sizeof(inq));
    dis[n] = 0;
    cnt[n] ++;
    inq[n] = 1;
    Q.push(n);
    while(!Q.empty()){
        int now;
        int li;

        now = Q.front();
        inq[now] = 0;
        Q.pop();
        for(int i = 0; i < li; i ++){
            if(dis[node[now].V[i]] > dis[now] + node[now].W[i]){
                dis[node[now].V[i]] = dis[now] + node[now].W[i];
                if(!inq[node[now].V[i]]){
                    inq[node[now].V[i]] = 1;
                    Q.push(node[now].V[i]);
                    cnt[node[now].V[i]] ++;
                    if(cnt[node[now].V[i]] > n + 1){
                    	return false;
                    }
                }
            }
        }
    }

    return true;
}
