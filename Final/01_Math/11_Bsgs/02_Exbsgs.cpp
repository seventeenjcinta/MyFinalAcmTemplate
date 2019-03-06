/// Çó½â a^x = b (mod p)
int t, a, b, m;
unordered_map<LL, int> mp;

LL EXBSGS(int A, int B, int C) {
    A %= C, B %= C;
    if(B == 1) return 0;
    int cnt = 0;
    LL t = 1;
    for(int g = __gcd(A, C); g != 1; g = __gcd(A, C)) {
        if(B % g) return -1;
        C /= g, B /= g;
        t = t * A / g % C;
        cnt++;
        if(B == t) return cnt;
    }
    mp.clear();
    int m = ceil(sqrt(1.0 * C));
    LL base = B;
    for(int i = 0; i < m; i++) {
       mp[base] = i;
       base = base * A % C;
    }
    base = Mod_Pow(A, m, C);
    LL nw = t;
    for(int i = 1; i <= m + 1; i++) {
        nw = base * nw % C;
        if(mp.count(nw)) {
            return i * m - mp[nw] + cnt;
        }
    }
    return -1;
}

LL exbsgs(LL a, LL b, LL p)
{
    if (b == 1LL) return 0;
    ll t, d = 1, k = 0;
    while ((t = gcd(a, p)) != 1)
    {
        if (b % t) return -1;
        ++k, b /= t, p /= t, d = d * (a / t) % p;
        if (b == d) return k;
    }
    map<LL, LL> dic;
    ll m = ceil(sqrt(p));
    ll a_m = Pow(a, m, p), mul = b;
    for (ll j = 1; j <= m; ++j) mul = mul * a % p, dic[mul] = j;
    for (ll i = 1; i <= m; ++i)
    {
        d = d * a_m % p;
        if (dic[d]) return i * m - dic[d] + k;
    }
    return -1;
}

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &a, &b, &m);
        LL ans = EXBSGS(a, b, m);
        printf("%lld\n", ans);
    }
    return 0;
}
