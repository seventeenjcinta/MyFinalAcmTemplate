const int N = 3;    /// æÿ’Û¥Û–°
const int MOD = 1e9 + 7;

LL a, b, c, d, e, n;

struct Met
{
    LL ma[3][3];
};

Met Mul(Met a, Met b)
{
    Met c;

    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            c.ma[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            LL t;

            t = 0;
            for(int k = 0; k < N; k ++){
                t = (t + a.ma[i][k] * b.ma[k][j] % MOD) % MOD;
            }
            c.ma[i][j] = t;
        }
    }

    return c;
}

Met Quick_mod(Met a, int n)
{
    Met t;

    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j ++){
            t.ma[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i ++){
        t.ma[i][i] = 1;
    }
    while(n){
        if(n & 1){
            t = Mul(t, a);
        }
        n >>= 1;
        a = Mul(a, a);
    }

    return t;
}

int main()
{
    /**
    dp[1] = A;
    dp[2] = B;
    dp[i] = C * dp[i - 2] + D * dp[i - 1] + E;
    */

    now.ma[0][0] = d % MOD;
    now.ma[0][1] = c % MOD;
    now.ma[1][0] = 1;
    now.ma[2][2] = 1;
    now.ma[0][2] = e;

    return 0;
}
