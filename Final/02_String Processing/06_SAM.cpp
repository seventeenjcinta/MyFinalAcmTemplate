#define maxn 200010         ///两倍字符串长度
#define sigma 26			///字符集大小
struct SuffixAutomaton{
    int root;               ///root = 0;
    int size, last;
    int go[maxn][sigma];    ///转移
    int maxlen[maxn];       ///节点i代表的子串的最长长度
    int par[maxn];          ///parent树中节点i的父节点
    int cnt[maxn];          ///节点i的right集合大小
    int who[maxn];          ///who[i]是按照maxlen从小到大排序后的第i个节点下标
    int a[maxn];            ///辅助拓扑排序的数组(计数排序)
    SuffixAutomaton():
        size(0){}

    int new_node(int len){
        memset(go[size], -1, sizeof(go[size]));
        maxlen[size] = len;
        par[size] = -1;
        return size ++;
    }
    int idx(char ch){
        return ch - 'a';
    }
    void extend(int ch){
        //printf("extending: %c\n", 'a' + ch);
        int p, q, np, nq;
        p = last;
        np = new_node(maxlen[p] + 1);
        while(p != -1 && go[p][ch] == -1){///在所有的last的祖先中，为所有没有标号为x的边的节点添加一条边指向节点np=ST(Tx)
            go[p][ch] = np;
            p = par[p];
        }
        if(p == -1){///如果last的所有祖先没有标号为x的边，则状态np=trans(Tx)的parent为root
            //printf("par[%d] = root\n", np);
            par[np] = root;
        }
        else {///找到第一个有标号为x的边的状态p，令q=trans(p,x)
            q = go[p][ch];
            if(maxlen[p] + 1 == maxlen[q]){///如果maxlen[p] + 1 == maxlen[q]则直接令q的parent为np
                par[np] = q;
            }
            else {///否则新建节点nq，令maxlen[nq] = maxlen[p] + 1
                nq = new_node(maxlen[p] + 1);
                memcpy(go[nq], go[q], sizeof(go[q]));///nq的状态转移函数与q的完全相同
                par[nq] = par[q];
                par[q] = nq;        ///将parent树上的关系由q->par[q] 修改为 q->nq->par[q]
                par[np] = nq;       ///np=ST(Tx)的parent也是nq
                while(p != -1 && go[p][ch] == q){
                    go[p][ch] = nq;
                    p = par[p];
                }
            }
        }
        last = np;
        cnt[np] = 1;
        //printf("cnt[%d] = %d\n", np, cnt[np]);
    }
    void count(){///拓扑排序并计数每个节点表示的子串出现次数
        memset(a, 0, sizeof(a));
        for(int i = 0; i < size; ++ i)a[maxlen[i]] ++;
        for(int i = 1; i < size; ++ i)a[i] += a[i-1];
        for(int i = size - 1; i >= 0; -- i)who[--a[maxlen[i]]] = i; ///计数排序
        for(int i = size - 1; i >= 0; -- i){
            if(par[who[i]] != -1){
                cnt[par[who[i]]] += cnt[who[i]];
            }
        }
    }
    void init(char *s){
        size = 0;
        last = root = new_node(0);
        memset(cnt, 0, sizeof(cnt));
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            extend(idx(s[i]));
        }
        count();
    }
}sam;
#undef sigma
#undef maxn