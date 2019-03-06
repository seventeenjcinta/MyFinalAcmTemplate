/// 二进制优化
const int N = 550;
const int M = N / 32 + 1;   /// 二进制压位

int ma[N][M];
int b[M];               /// 辅助 ne 数组
int ne[N];
int n, m;
int tot;

inline void set1(int v[],int x){v[x>>5]|=1<<(x&31);}    /// 等价于 v[x] = 1
inline void flip(int v[],int x){v[x>>5]^=1<<(x&31);}	///  把所有二进制位逐位取反

bool Find(int x)
{
    /// printf("%d %d\n", x, tot);
    for(int i = 0; i <= tot; i ++){    /// 一定从 0 开始
    	while(true){
            int t;
            int q;

            /// printf("%d %d %d %d\n", x, i, ma[x][i], b[i]);
	        t = ma[x][i] & b[i];
	        if(!t){
                break;
	        }
	        q = i << 5 | __builtin_ctz(t);	/// o 末尾 0 的个数，x = 0 时结果未定义
	        /// printf("%d %d\n", o, y);
	        flip(b, q);
	        if(!ne[q] || Find(ne[q])){
	            ne[q] = x;
                return true;
	        }
   		}
   	}

    return false;
}

int Match()
{
    int ans;

    ans = 0;
    memset(ne, 0, sizeof(ne));
    for(int i = 1; i <= n; i ++){   /// 遍历一边
        for(int j = 1; j <= m/*(n???)*/; j ++){ 	/// 待思考
            set1(b, j);
        }
        if(Find(i)){
            ans ++;
        }
    }

    return ans;
}

int main()
{
    int ncase;

    scanf("%d", &ncase);
    while(ncase --){
        memset(ma, 0, sizeof(ma));
        scanf("%d%d", &m, &n);
        tot = m >> 5;   /// 压位后大小除 32
        for(int i = 1; i <= m; i ++){
            int t;

            scanf("%d", &t);
            for(int j = 0; j < t; j ++){
                int x;

                scanf("%d", &x);
                set1(ma[x], i);
                /// ma[x][i] = 1;
            }
        }
    }

    return 0;
}
