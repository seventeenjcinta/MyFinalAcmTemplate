LL cal(LL a,LL b,LL c,LL n)
{
    LL re;

    re = 0;
    re += (a / c) * n * (n - 1) / 2 + (b / c) * n;
    b %= c;
    a %= c;
    if(a * n + b < c){
        return re;
    }
    else{
        return re+cal(c,(a*n+b)%c,a,(a*n+b)/c);
    }
}
int main()
{
    LL x,y,z;
    while(scanf("%lld%lld%lld",&x,&y,&z) == 3){
        LL ans=0;
        LL n=(y-x)/z+1;
        for(int i=0;i<32;i++){
            ans|=(cal(z,x,1LL<<i,n)&1)<<i;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
