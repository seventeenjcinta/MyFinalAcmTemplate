LL exgcd(LL a, LL b, LL& x, LL& y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    LL res = exgcd(b, a%b, y, x);
    y -= (a/b)*x;
    return res;
}

LL reverse(LL a, LL p) {
    LL x, y;
    exgcd(a, p, x, y);
    return (x % p + p)%p;
}

LL C(LL n, LL m, LL p) {
    if(m>n) return 0;
    LL res = 1, i, a, b;
    for(i = 1; i <= m; i++) {
        a = (n+1-i) % p;
        b = reverse(i%p, p);
        res = res*a%p*b%p;
    }
    return res;
}

LL Lucas(LL n, LL m, LL p) {
    if(m == 0) return 1;
    return Lucas(n/p, m/p, p)*C(n%p, m%p, p) % p;
}

LL cal(LL n, LL a, LL b, LL p) {
    if(!n) return 1;
    LL i, y = n/p, tmp = 1;
    for(i = 1; i <= p; i++) if(i%a) tmp = tmp*i%p;
    LL ans = pow(tmp, y, p);
    for(i = y*p+1; i <= n; i++) if(i%a) ans = ans*i%p;
    return ans * cal(n/a, a, b, p)%p;
}

LL multiLucas(LL n, LL m, LL a, LL b, LL p) {
    LL i, t1, t2, t3, s = 0, tmp;
    for(i = n; i; i/=a) s += i/a;
    for(i = m; i; i/=a) s -= i/a;
    for(i = n-m; i; i/=a) s -= i/a;
    tmp = pow(a, s, p);
    t1 = cal(n, a, b, p);
    t2 = cal(m, a, b, p);
    t3 = cal(n-m, a, b, p);
    return tmp*t1%p*reverse(t2, p)%p*reverse(t3, p)%p;
}


LL exLucas(LL n, LL m, LL p) {
    LL i, d, c, t, x, y, q[100], a[100], e = 0;
    for(i = 2; i*i <= p; i++) {
        if(p % i == 0) {
            q[++e] = 1;
            t = 0;
            while(p%i==0) {
                p /= i;
                q[e] *= i;
                t++;
            }
            if(q[e] == i) a[e] = Lucas(n, m, q[e]);
            else a[e] = multiLucas(n, m, i, t, q[e]);
        }
    }
    if(p > 1) {
        q[++e] = p;
        a[e] = Lucas(n, m, p);
    }
    for(i = 2; i <= e; i++) {
        d = exgcd(q[1], q[i], x, y);
        c = a[i]-a[1];
        if(c%d) exit(-1);
        t = q[i]/d;
        x = (c/d*x%t+t)%t;
        a[1] = q[1]*x+a[1];
        q[1] = q[1]*q[i]/d;
    }
    return a[1];
}
