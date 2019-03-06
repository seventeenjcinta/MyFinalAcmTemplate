LL Exgcd(LL a, LL b, LL &x, LL &y, LL c = 1)
{
    LL gcd;

    if(!b){
        if(c % a){
            return 0;
        }
        x = c / a;
        y = 0;

        return a;
    }
    gcd = exgcd(b, a % b, y, x, c);
    y -= a / b * x;

    return gcd;
}
