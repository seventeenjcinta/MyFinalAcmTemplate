#define maxn 100010
struct Node
{
    int to, ne;
    int fa, size, son, dep;     /**  dfs()
                                  *  fa: parent node
                                  *  size: cnt_node
                                  *  son: heavy
                                  *  dep: depth of current node
                                  */
    int top, pos;               /**  _dfs()
                                  *  top: top node
                                  *  pos: node's index in *array* seq[]
                                  */
}node[maxn];
int totw;                       /// = 1, for(int i = 1; i < totw; ++ i){}
int seq[maxn];
int head[maxn];
int top;

void add(int from, int to){
    node[top].to = to;
    node[top].ne = head[from];
    head[from] = top;
    top ++;
}

int dfs(int now, int prev = -1, int depth = 0){
    node[now].fa = prev;
    node[now].dep = depth;
    int ret = 1;
    int cur_size = -1;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev)continue;

        int son_size = dfs(nxt, now, depth + 1);
        if(cur_size < son_size){
            cur_size = son_size;
            node[now].son = nxt;
        }

        ret += son_size;
    }
    node[now].size = ret;
    return ret;
}

void _dfs(int now, int prev = -1){
    node[now].pos = totw;
    seq[totw ++] = now;
    if(node[now].top == -1){
        node[now].top = now;
    }
    if(node[now].son != -1){
        node[node[now].son].top = node[now].top;
        _dfs(node[now].son, now);
    }
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev || nxt == node[now].son)
            continue;
        _dfs(nxt, now);
    }
}

void build(int root = 1){
    dfs(root);
    _dfs(root);
}

int lca(int x, int y){
    while(true){
        if(node[x].top == node[y].top){
            return node[x].dep <= node[y].dep ? x : y;
        }
        if(node[node[x].top].dep >= node[node[y].top].dep){
            x = node[node[x].top].fa;
        }
        else {
            y = node[node[y].top].fa;
        }
    }
}

void update(){
    if(/*update node value (node[l] to node[r], node.val += k) */){
        while(1){
            int f1 = node[l].top, f2 = node[r].top;
            if(f1 == f2){
                if(node[l].pos > node[r].pos)swap(l, r);
                updateN(node[l].pos, node[r].pos, k);
                break;
            }
            if(node[f1].dep > node[f2].dep){
                updateN(node[f1].pos, node[l].pos, k);
                l = node[f1].fa;
            }
            else {
                updateN(node[f2].pos, node[r].pos, k);
                r = node[f2].fa;
            }
        }
    }
    else if(/*update edge value (edges between node[l] to node[r], edge.val += k)*/){
        while(1){
            int f1 = node[l].top, f2 = node[r].top;
            if(f1 == f2){
                if(l == r)break;
                if(node[l].pos > node[r].pos)swap(l, r);
                updateE(node[l].pos + 1, node[r].pos, k);
                break;
            }
            if(node[f1].dep > node[f2].dep){
                updateE(node[f1].pos, node[l].pos, k);
                l = node[f1].fa;
            }
            else {
                updateE(node[f2].pos, node[r].pos, k);
                r = node[f2].fa;
            }
        }
    }
}

void ini(){
    memset(head, -1, sizeof(head));
    top = 0;
    totw = 1;
}
#undef maxn