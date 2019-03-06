#define maxn 3000010
#define sigma 26
struct Palindromic_Tree{
    int go[maxn][sigma], fail[maxn];
    int depth[maxn], cnt[maxn];
    int size, last, len;
    char s[maxn];
    int idx(char ch){
        return ch - 'a';
    }
    int new_node(int length){
        memset(go[size], 0, sizeof(go[size]));
        fail[size] = 0;
        depth[size] = length;
        cnt[size] = 0;
        return size++;
    }
    void Extend(int ch, int pos){
        int p = last;
        while (s[pos - depth[p] - 1] != s[pos]){
            p = fail[p];
        }
        if (!go[p][ch]){
            int now = new_node(depth[p] + 2), fa = fail[p];
            while (s[pos - depth[fa] - 1] != s[pos])
                fa = fail[fa];
            fail[now] = go[fa][ch];
            if (fail[now] == 0) fail[now] = 1;
            go[p][ch] = now;
        }
        last = go[p][ch];
        cnt[last]++;
    }
    void init(char *x){
        len = strlen(x + 1);
        for (int i = 1; i <= len; i++)
            s[i] = x[i];
        size = 0;
        new_node(-1);
        new_node(0);
        fail[0] = fail[1] = 0;
        depth[0] = -1;
        last = 1;
        for (int i = 1; i <= len; i++)
            Extend(idx(s[i]), i);
    }
}pam;
#undef sigma
#undef maxn