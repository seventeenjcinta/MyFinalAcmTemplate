const int N = 1e6+7;
int pri[N];
int phi[N];
void init_phi(int n)
{
    memset(phi,0,sizeof(phi));
    int len = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; i++){
        if(phi[i] == 0)
            phi[i] = i-1,pri[len++] = i;
        for(int j = 0; j<len && (k=i*pri[j])<=n; j++)
            if(i%pri[j])
                phi[k]=phi[i]*phi[pri[j]];
            else{
                phi[k]=phi[i]*pri[j];
                break;
            }
    }
}

LL phi(LL x)//如果返回值小于0则输入违规，允许超int，但超时不负责
{
    if(x<2)return x;
    LL ans = x;
    for(int i = 2,q = sqrt(x)+1; i < q; i++){
        if(x%i==0){
            ans-=ans/i;
            while(x%i==0)x/=i;
            q = sqrt(x)+1;
        }
    }
    if(x!=1)
        ans-=ans/x;
    return ans;
}
