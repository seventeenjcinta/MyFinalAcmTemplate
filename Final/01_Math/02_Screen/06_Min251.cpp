#include<bits/stdc++.h>
using namespace std;
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
ll val[N],a[N],n;
int nq,cnt;
ll solve(ll n)
{
    cnt=0;
    nq=sqrt(n+1);
    for(ll i=1; i<=n; i=n/(n/i)+1)
        val[++cnt]=n/i;
    for(int i=1; i<=cnt; i++)
        a[i]=val[i]-1;
    for(int j=0; j<s[nq]; j++)
    {
        ll pp = (ll)p[j]*p[j];
        for(int i=1; pp<=val[i] && i<=cnt; i++)
        {
            ll d = val[i]/p[j];
            int k =(d<nq)?cnt-d+1:n/d;
            a[i]=a[i]-(a[k]-j);
        }
    }
    return a[1];
}
int main()
{
    init_pri(N/2);
    while(cin >> n)
        cout << solve(n) << endl;
    return 0;
}
