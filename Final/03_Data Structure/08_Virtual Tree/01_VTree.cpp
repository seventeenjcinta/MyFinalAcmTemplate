/**
- 输入每个询问的点，并且按照dfs序为关键字排序
- 将第1个点压到栈当中，开始构建虚树
- 枚举到下一个点u，计算u与栈顶点v的公共祖先lca
- 假设栈中栈顶下方的点为w（若栈中只有1个点就直跳过这一步），若w点的深度大于lca就把v向w连一条边，并且弹掉v，重复此步，否则就到下一步
- 若lca不是当前的v，那么就把lca和v连边，把v弹出，让lca成为栈顶元素（注：这个操作的意思是如果栈顶没有这个lca那么就压入），否则不做任何操作
- 最后把u压入栈中
- 回到3操作枚举下个点，直到枚举完了所有点
- 把栈顶v与栈顶下方的点为w连边，并且把v弹掉，这么做直到栈里只有一个点
- 栈里剩下的点就是虚树的根了
*/
const int maxn = "Edit";
vector<int> vtree[maxn];
void build(vector<int>& vec)
{
    sort(vec.begin(), vec.end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
    static int s[maxn];
    int top = 0;
    s[top] = 0;
    vtree[0].clear();
    for (auto& u : vec){
        int vlca = lca(u, s[top]);
        vtree[u].clear();
        if (vlca == s[top])
            s[++top] = u;
        else{
            while (top && dep[s[top - 1]] >= dep[vlca]){
                vtree[s[top - 1]].push_back(s[top]);
                top--;
            }
            if (s[top] != vlca){
                vtree[vlca].clear();
                vtree[vlca].push_back(s[top--]);
                s[++top] = vlca;
            }
            s[++top] = u;
        }
    }
    for (int i = 0; i < top; ++i) vtree[s[i]].push_back(s[i + 1]);
}
