const int N = 550;

int ma[N][N];
int used[N];    /// 另一边的使用情况
int ne[N];

bool Find(int x)
{
    for(int i = 1; i <= m; i ++){   /// 遍历另一边
        if(ma[x][i] && !used[i]){	/// 单向
            used[i] = 1;
            if(!ne[i] || Find(ne[i])){  /// 没有就直接上 || 如果有就腾开再上
                ne[i] = x;

                return true;
            }
        }
    }

    return false;
}

int match()
{
    int ans;

    ans = 0;
    memset(ne, 0, sizeof(ne));
    for(int i = 1; i <= n; i ++){   /// 遍历一边
        memset(used, 0, sizeof(used));
        if(Find(i)){
            ans ++;
        }
    }

    return ans;
}
