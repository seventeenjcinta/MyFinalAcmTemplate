/// $f(a, b, c, m) = \sum_{i = 0}^{n}[(ai+b)/c]$
/// 向下取整
LL likegcd_f(long long a,long long b,long long c,long long n)///F(a,b,c,n)=∑i(0~n) (ai+b)/c
{
    if(a==0) return((b/c)*(n+1));
    if(a>=c||b>=c) return likegcd_f(a%c,b%c,c,n)+(a/c)*n*(n+1)/2+(b/c)*(n+1);
    long long m=(a*n+b)/c;
    long long v=likegcd_f(c,c-b-1,a,m-1);
    return n*m-v;
}

