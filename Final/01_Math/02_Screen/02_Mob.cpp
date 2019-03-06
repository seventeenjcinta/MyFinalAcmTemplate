const int N = 1e6+7;
char v[N];
int pri[N];
int mu[N];

int Mobi(int x)/// 计算 x 的莫比乌斯函数
{
    int ans = 1;
    for(int i = 2,q = sqrt(x)+1; i < q; i++){
        if(x%i==0){
            x/=i;
            if(x%i)
                ans = -ans;
            else
                return 0;
            q = sqrt(x)+1;
        }
    }
    if(x!=1)
        ans = -ans;
    return ans;
}

void Init_mu(int n)
{
    memset(v,0,sizeof(v));
    int len = 0;
    mu[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(v[i] == 0)
            mu[i] = -1,pri[len++] = i;
        for(int j = 0,k; j<len && (k=i*pri[j])<=n; j++){
            v[k] = 1;
            if(i%pri[j])
                mu[k]=-mu[i];
            else
            {
                mu[k]=0;
                break;
            }
        }
    }
}
