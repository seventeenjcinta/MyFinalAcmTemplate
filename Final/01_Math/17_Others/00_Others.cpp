// ---
// 约瑟夫问题\\
// $n$个人围成一圈，从第一个开始报数，第$m$个将被杀掉
// ---
int josephus(int n, int m)
{
    int r = 0;
    for (int k = 1; k <= n; ++k) r = (r + m) % k;
    return r + 1;
}
// ---
// $n^n$最左边一位数
// ---
int leftmost(int n)
{
    double m = n * log10((double)n);
    double g = m - (ll)m;
    return (int)pow(10.0, g);
}
// ---
// $n!$位数
// ---
int count(ll n)
{
    if (n == 1) return 1;
    return (int)ceil(0.5 * log10(2 * M_PI * n) + n * log10(n) - n * log10(M_E));
}
