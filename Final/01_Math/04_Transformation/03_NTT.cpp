const int mod = (479<<21)+1;
const int g = 3;  //原根
long long quick_mod(long long a,long long b)
{
    long long ans=1;
    while(b){
        if(b&1)
            ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void NTT(int n,long long a[],bool on=false) //长度为N (2的次数),默认正变换，逆变换加true
{
    int r=0;
    while((1<<++r)!=n);
    for(int i=0; i<n; i++){
        int tmp=0;
        for(int j=0; j<r; j++)//蝴蝶操作
            if(i&(1<<j))
                tmp+=1<<(r-j-1);
        if(i<tmp)
            swap(a[i],a[tmp]);
    }
    for(int i=1; i<=r; i++){
        int m=1<<i;
        long long wn=quick_mod(g,(mod-1)/m);
        for(int k=0; k<n; k+=m){
            long long w=1;
            for(int j=0; j<(m>>1); j++){
                long long t,u;
                t=w*(a[k+j+(m>>1)]%mod)%mod;
                u=a[k+j]%mod;
                a[k+j]=(u+t)%mod;
                a[k+j+(m>>1)]=((u-t)%mod+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(on){
        for(int i=1; i<n>>1; i++)
            swap(a[i],a[n-i]);
        long long inv=quick_mod(n,mod-2);
        for(int i=0; i<n; i++)
            a[i]=a[i]%mod*inv%mod;
    }
}
