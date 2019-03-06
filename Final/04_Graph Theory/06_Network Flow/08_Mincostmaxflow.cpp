struct Node
{
	int from;
	int to;
	int ne;
	int flow;
	int v;
};

Node node[M * 10];
int n, m;
int ss, tt;
int ma[N];
int head[M];
int top;
/// SPFA
int dis[N];
int pre[N];	///
int minn[N];
int mincost[N];
bool inq[N];
int Q[M * 10];
int ql, qr;

void Add_edge(int from, int to, int flow, int v)
{
	node[top].from = from;
	node[top].to = to;
	node[top].flow = flow;
	node[top].v = v;
	node[top].ne = head[from];
	head[from] = top;
	top ++;
}

void ini()
{
	top = 0;
	memset(head, -1, sizeof(head));
}

int Spfa()
{
	for(int i = 0; i <= tt; i ++){
		inq[i] = 0;
		dis[i] = INF;
		pre[i] = -1;
	}
	mincost[ss] = INF;
	mincost[tt] = 0;
	qr = ql = 0;
	dis[ss] = 0;
	minn[ss] = INF;
	inq[ss] = true;
	Q[qr] = ss;
	qr ++;
	while(ql != qr){
		int now;

        /// cout << 12312312312 << endl;
		now = Q[ql];
		/// cout << now << endl;
		ql ++;
		inq[now] = false;
		for(int i = head[now]; i != -1; i = node[i].ne){
			int v;

            /// cout << 123123 << endl;
			v = node[i].to;
			if(node[i].flow > 0 && dis[v] > dis[now] + node[i].v){
				dis[v] = dis[now] + node[i].v;
				pre[v] = i;	/// amazing  直接存边的编号
				/// pre[v] = u;
				mincost[v] = min(mincost[now], node[i].flow);
				if(!inq[v]){
					inq[v] = true;
					Q[qr] = v;
					qr ++;
				}
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
	while(true){
		t = Spfa();
		if(!t){
			break;
		}
		/// cout << 666 << endl;
		for(int i = pre[tt]; i != -1; i = pre[node[i].from]){
			ans += t * node[i].v;
			node[i].flow -= t;
			node[i ^ 1].flow += t;
		}
	}

	return ans;
}