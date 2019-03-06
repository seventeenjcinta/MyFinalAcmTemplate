#include<bits/stdc++.h>
using namespace std;
const int maxn = 300010;
const int dp_maxn = 1010;
const int INF = 0x3f3f3f3f;
const int type_N = 26;

int T, N, dp[dp_maxn][dp_maxn];
char in[60], text[1000010];
struct Trie
{
    int nxt[maxn][type_N],
        fail[maxn],
        cnt[maxn],
        size, root;
    bool finish[maxn];

    int newNode(){
        for(int i = 0; i < type_N; ++ i)
            nxt[size][i] = 0;
        fail[size] = 0;
        cnt[size] = 0;
        finish[size] = false;
        return size ++;
    }
    void init(){
        size = 1;
        root = newNode();
    }
    int idx(char ch){
        /*if(ch == 'A')return 0;
        if(ch == 'G')return 1;
        if(ch == 'C')return 2;
        return 3;*/
        return ch - 'a';
    }
    void insert(char *s){
        int now = root;
        while(*s){
            int index = idx(*s);
            if(!nxt[now][index])
                nxt[now][index] = newNode();
            now = nxt[now][index];
            ++ s;
        }
        ++ cnt[now];
        finish[now] = true;
    }
    void build(){
        queue<int> que;
        fail[root] = root;
        for(int i = 0; i < type_N; ++ i){
            if(nxt[root][i]){
                que.push(nxt[root][i]);
                fail[nxt[root][i]] = root;
            }
            else nxt[root][i] = root;
        }
        while(que.size()){
            int now = que.front();
            que.pop();
            finish[now] = finish[now] || finish[fail[now]];
            for(int i = 0; i < type_N; ++ i){
                if(nxt[now][i]){
                    que.push(nxt[now][i]);
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                }
                else nxt[now][i] = nxt[fail[now]][i];
            }
        }
    }
    int Match(char *s){
        int now = root, ans = 0;
        while(*s){
            int index = idx(*s);
            while(now != root && nxt[now][index] == root){
                //printf("now = %d\n", now);
                now = fail[now];
            }
            now = nxt[now][index];
            int match = now;
            while(match != root){
                //printf("match = %d, now = %d\n", match, now);
                ans += cnt[match];
                cnt[match] = 0;///查找匹配单词个数则加上这句；查找模板串出现次数则删掉这句
                match = fail[match];
            }
             ++ s;
        }
        return ans;
    }
    int meta(char *s){///type_N = 4,
        int len = strlen(s);
        memset(dp, 0x3f, sizeof(dp));
        dp[0][root] = 0;
        for(int i = 0; i < len; ++ i){
            for(int j = 0; j < size; ++ j){
                if(dp[i][j] < INF){
                    for(int k = 0; k < 4; ++ k){
                        int nstatus = nxt[j][k];
                        if(finish[nstatus])continue;
                        dp[i+1][nstatus] = min(dp[i+1][nstatus], dp[i][j] + (k != idx(s[i])));
                    }
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < size; ++ i)
            ans = min(ans, dp[len][i]);
        return ans == INF ? -1 : ans;
    }
}ac;
int main(){
    scanf("%d", &T);
    while(T--){
        ac.init();
        scanf("%d", &N);
        while(N--){
            scanf("%s", in);
            ac.insert(in);
        }
        ac.build();
        scanf("%s", text);
        printf("%d\n", ac.Match(text));
    }
    return 0;
}