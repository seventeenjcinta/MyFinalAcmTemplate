const int N = 100010;

int ma[N];
int bl[N];	/// 第 i 个元素属于的块的编号
int l[N];	/// 第 i 个块的左边界
int r[N];
int block;
int num;

void build()
{
    block = sqrt(n);
    num = n / block;
    if(n % block){
        num ++;
    }
    for(int i = 1; i <= num; i ++){
        l[i] = (i - 1) * block + 1;
        r[i] = i * block;
    }
    r[num] = n;
    for(int i = 1; i <= n; i ++){
        bl[i] = (i - 1) / block + 1;
    }
}