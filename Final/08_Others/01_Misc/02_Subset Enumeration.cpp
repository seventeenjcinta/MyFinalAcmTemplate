// ---
// 枚举真子集
// ---
for (int s = (S - 1) & S; s; s = (s - 1) & S)
// ---
// 枚举大小为 $k$ 的子集
// ---
void subset(int k, int n)
{
    int t = (1 << k) - 1;
    while (t < (1 << n))
    {
        // do something
        int x = t & -t, y = t + x;
        t = ((t & ~y) / x >> 1) | y;
    }
}