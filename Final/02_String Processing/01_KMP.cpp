int next[N];
char S[N], T[N];
int slen, tlen;

void getNext()
{
    int j, k;
    j = 0; k = -1; next[0] = -1;
    while(j < tlen){
        if(k == -1 || T[j] == T[k])
            next[++j] = ++k;//表示T[j-1]和T[k-1]相匹配，当j处失配时，直接用next[j]处来匹配当前失配处
        else
            k = next[k];
    }
}

/*
返回模式串T在主串S中首次出现的位置
返回的位置是从0开始的。
*/

int KMP_Index()
{
    int i = 0, j = 0;
    getNext();

    while(i < slen && j < tlen){
        if(j == -1 || S[i] == T[j]){
            i++; j++;
        }
        else
            j = next[j];
    }
    if(j == tlen)
        return i - tlen;
    else
        return -1;
}

/*
返回模式串在主串S中出现的次数
*/

int KMP_Count()
{
    int ans = 0;
    int i, j = 0;

    if(slen == 1 && tlen == 1){
        if(S[0] == T[0])
            return 1;
        else
            return 0;
    }

    getNext();
    for(i = 0; i < slen; i++){
        while(j > 0 && S[i] != T[j])
            j = next[j];
        if(S[i] == T[j])
            j++;
        if(j == tlen){
            ans++;
            j = next[j];
        }
    }
    
    return ans;
}

int main()
{
    int TT;
    int i, cc;

    data>>TT;
    while(TT--){
        data>>S>>T;
        slen = strlen(S);
        tlen = strlen(T);
        getNext();
        for(int i=0;i<=tlen;i++)
            cout<<next[i]<<" ";
        cout<<endl;
        cout<<"模式串T在主串S中首次出现的位置是: "<<KMP_Index()<<endl;
        cout<<"模式串T在主串S中出现的次数为: "<<KMP_Count()<<endl;
    }
    return 0;
}
/*
3
ababcabcacbabcac
abcac
*/