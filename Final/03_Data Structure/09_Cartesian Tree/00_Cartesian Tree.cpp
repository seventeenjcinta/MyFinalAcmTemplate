const int maxn = "Edit";
int lson[maxn], rson[maxn], fa[maxn];
void build(int n)
{
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        int last = -1;
        while (!s.empty() && a[i] > a[s.top()]) last = s.top(), s.pop();
        if (!s.empty()) rson[s.top()] = i, fa[i] = s.top();
        lson[i] = last;
        if (~last) fa[last] = i;
        s.push(i);
    }
}