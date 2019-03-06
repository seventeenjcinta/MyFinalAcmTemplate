const int N = 110;

struct Node
{
	vector<int> V;
};

Node node[N];
int instack[N];
int low[N];
int dfn[N];
int St[N];
int bl[N];
int ine[N], oute[N];	/// 入度，出度
int index;
int cnt;
int top;
int ans1, ans2;
int n;

void ini()
{
	for(int i = 1; i <= n; i ++){
		node[i].V.clear();
	}
	memset(instack, 0, sizeof(instack));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(St, 0, sizeof(St));
	memset(ine, 0, sizeof(ine));
	memset(oute, 0, sizeof(oute));
	ans1 = ans2 = index = top = cnt = 0;
}

void Tarjan(int u)
{
	int li;

	St[top] = u;
	top ++;
	index ++;
	low[u] = dfn[u] = index;
	instack[u] = 1;
	li = node[u].V.size();
	for(int i = 0; i < li; i ++){
		int v;

		v = node[u].V[i];
		if(!dfn[v]){
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(instack[v]){
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]){
		int v;

		v = -1;
		while(v != u){
			top --;
			v = St[top];
			instack[v] = 0;
			bl[v] = cnt;
		}
		cnt ++;
	}
}

int main(int argc, char const *argv[])
{
	while(scanf("%d", &n) == 1){
		ini();
		for(int i = 1; i <= n; i ++){
			while(true){
				int v;

				scanf("%d", &v);
				if(v){
					node[i].V.pb(v);
				}
				else{
					break;
				}
			}
		}
		for(int i = 1; i <= n; i ++){
			if(!dfn[i]){
				Tarjan(i);
			}
		}
		for(int i = 1; i <= n; i ++){
			int li;

			li = node[i].V.size();
			for(int j = 0; j < li; j ++){
				int v;

				v = node[i].V[j];
				if(bl[v] != bl[i]){
					oute[bl[i]] ++;
					ine[bl[v]] ++;
				}
			}
		}
		for(int i = 0; i < cnt; i ++){
			if(!ine[i]){
				ans1 ++;
			}
			else if(!oute[i]){
				ans2 ++;
			}
		}
		printf("%d\n", ans1);
		if(cnt == 1){
			printf("0\n");
		}
		else{
			printf("%d\n", max(ans1, ans2));
		}
	}

	return 0;
}
