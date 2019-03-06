LL quickmod(LL a, LL b, LL MOD)
{
    LL ans;

    ans = 1;
    while(b){
        if(b & 1){
            ans = (ans * a) % MOD;
        }
        b >>= 1;
        a = a * a % MOD;
    }

    return ans % MOD;
}
