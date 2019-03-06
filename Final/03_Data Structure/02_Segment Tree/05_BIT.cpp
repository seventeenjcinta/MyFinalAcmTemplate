int bits[N];
int n;

int lowbit(int x)
{
    return x & -x;
}

int sum(int x)  ///区间求和，注意权值树状数组
{
    int ans = 0;

    while(x > 0){
        ans += bits[x];
        x -= lowbit(x);
    }

    return ans;
}

int add(int x, int v)
{
    while(x <= n){
        bits[x] += v;
        x += lowbit(x);
    }
}

void ini()
{
    memset(bits, 0, sizeof(bits));
}