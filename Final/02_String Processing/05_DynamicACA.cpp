#include<bits/stdc++.h>
using namespace std;
const int type_N = 26;///
const int maxn = 100010;///length of text

int idx(char ch){///Ð¡Ð´×ÖÄ¸idx()
    return ch - 'a';
}

struct Trie{
    Trie *nxt[type_N], *fail;
    int finish;

    void init(){
        for(int i = 0; i < type_N; ++ i)
            nxt[i] = NULL;
        fail = NULL;
        finish = 0;
    }
}root;
int n;
char in[30], text[maxn];

void Insert(char *s){
    int index;
    Trie *now = &root, *tmp;
    while(*s){
        index = idx(*s);
        if(!now->nxt[index]){
            tmp = (Trie*) malloc(sizeof(Trie));
            tmp->init();
            now->nxt[index] = tmp;
        }
        now = now->nxt[index];
        ++ s;
    }
    now->finish ++;
}

void Get_fail(){
    queue<Trie*> Q;
    Q.push(&root);
    Trie *now, *anc;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for(int i = 0; i < type_N; ++ i){
            if(now->nxt[i]){
                Q.push(now->nxt[i]);
                if(now == &root){
                    now->nxt[i]->fail = &root;
                    continue;
                }
                anc = now->fail;
                while(anc){
                    if(anc->nxt[i]){
                        now->nxt[i]->fail = anc->nxt[i];
                        break;
                    }
                    anc = anc->fail;
                }
                if(!anc)
                    now->nxt[i]->fail = &root;
            }
        }
    }
}

int AC_Automaton(char *s){///
    Trie *now = &root, *match;
    int index, ret = 0;
    while(*s){
        index = idx(*s);
        while(now != &root && !now->nxt[index])
            now = now->fail;
        now = now->nxt[index];
        match = now;
        if(!now)now = &root;
        while(match){
            ret += match->finish;
            match = match->fail;
        }
        ++ s;
    }
    return ret;
}

void Del(Trie *now = &root){
    for(int i = 0; i < type_N; ++ i){
        if(now->nxt[i]){
            Del(now->nxt[i]);
            free(now->nxt[i]);
        }
    }
}

void init(){
    Del();
    root.init();
}

int main(){
    while(~scanf("%d", &n)){
        init();
        while(n--){
            scanf("%s", in);
            Insert(in);
        }
        Get_fail();
        while(~scanf("%s", text))///"ctrl+Z" to quit
            printf("%d\n", AC_Automaton(text));
    }
    return 0;
}