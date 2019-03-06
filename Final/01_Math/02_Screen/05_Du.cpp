int m = 2e6,c[1000005],cnt,n;
long long phi[2000005],mu[2000005],p[100005],q[100005];
bool vis[100005];
void init()
{
    phi[1]=mu[1]=1;
    for (int i=2; i<=m; i++){
        if (!phi[i]){
            phi[i]=i-1;
            mu[i]=-1;
            c[++cnt]=i;
        }
        for (int j=1; j<=cnt && i*c[j]<=m; j++)
            if (i%c[j]){
                phi[i*c[j]]=phi[i]*(c[j]-1);
                mu[i*c[j]]=-mu[i];
            }
            else{
                phi[i*c[j]]=phi[i]*c[j];
                mu[i*c[j]]=0;
                break;
            }
    }
    for (int i=2; i<=m; i++)phi[i]+=phi[i-1],mu[i]+=mu[i-1];
}
void du_sift(long long x){
    if(vis[n/x])return;
    int l,r=2,k=n/x,t;
    vis[k]=1;
    p[k]=(x+1)*x>>1,q[k]=1;///根据函数特性定初值
    while(r<x){
        l=r,t=x/l,r=x/t+1;
        if(t<=m)p[k]-=phi[t]*(r-l),q[k]-=mu[t]*(r-l);
        else{
            du_sift(t);
            p[k]-=p[n/t],q[k]-=q[n/t];
        }
    }
}
int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        cnt=0;
        if(n<=m){
            printf("%lld %lld\n",phi[n],mu[n]);
            continue;
        }
        du_sift(n);
        printf("%lld %lld\n",p[1],q[1]);
    }
    return 0;
}
