typedef long long ll;
const int N = 700005;
int p[N],v[N],s[N];
int np;
void init_pri(int n)
{
    np = 0;
    for(int i=2; i<=n; i++)
    {
        s[i]=s[i-1];
        if(!v[i])
            p[np++]=i,s[i]++;
        for(int j=0; j<np&&i*p[j]<=n; j++)
        {
            v[i*p[j]]=1;
            if(i%p[j]==0)
                break;
        }
    }
}
long long sg(long long x){
    return x*(x+1)/2;
}
long long g(long long x)
{
    return x;
}
long long fk(long long x,int k){
    return x;
}
long long f(long long x)
{
    return x;
}

ll val[N],a[N],n;
int nq,cnt;
ll nl_sift(ll n)
{
    cnt=0;
    nq=sqrt(n+1);
    for(ll i=1; i<=n; i=n/(n/i)+1)
        val[++cnt]=n/i;
    for(int i=1; i<=cnt; i++)
        a[i]=sg(val[i])-g(1);
    ll sj = 0;
    for(int j=0; j<s[nq]; sj+=g(p[j++]))
    {
        ll pp = (ll)p[j]*p[j];
        for(int i=1; pp<=val[i] && i<=cnt; i++)
        {
            ll d = val[i]/p[j];
            int k =(d<nq)?cnt-d+1:n/d;
            a[i]=a[i]+g(p[j])*(sj-a[k]);
        }
    }
    for(int j=s[nq]-1; ~j; sj-=g(p[j--]))
    {
        ll pp = (ll)p[j]*p[j];
        for(int i=1; pp<=val[i] && i<=cnt; i++)
        {
            ll d = val[i]/p[j];
            ll ff = p[j];
            for(int l = 1; p[j]<=d; d/=p[j],l++){
                int k =(d<nq)?cnt-d+1:n/d;
                a[i] = a[i]+f(ff)*(a[k]-sj)+f(ff*=p[j]);///可由值求ff
                //a[i] = a[i]+fk(p[j],l)*(a[k]-sj)+fk(p[j],l+1);///需要指数求ff
            }
        }
    }
    return a[1]+f(1);
}
int main()
{
    init_pri(N/2);
    while(cin >> n)
        cout << nl_sift(n) << ' ' << sg(n) << endl;
    return 0;
}
