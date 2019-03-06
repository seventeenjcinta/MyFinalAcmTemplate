const int N = 1e6+7;
char v[N];
int pri[N];

int Init_pri(int n){
    int len = 0;
    memset(v,0,sizeof(v));
    for(int i = 2; i <= n; i++){
        if(v[i] == 0)
            pri[len++] = i;
        for(int j = 0; j<len && pri[j]*i<=n; j++){
            v[i*pri[j]] = true;
            if(i%pri[j]==0) break;
        }
    }
    return len;
}
