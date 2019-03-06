/// 求解 a^x = b (mod p)
const int MAXINT=((1<<30)-1)*2+1;

int A,B,C;
struct Hashmap //哈希表代替map
{
    static const int Ha=999917,maxe=46340;
    int E,lnk[Ha],son[maxe+5],nxt[maxe+5],w[maxe+5];
    int top,stk[maxe+5];
    void clear() {E=0;while (top) lnk[stk[top--]]=0;}
    void Add(int x,int y) {son[++E]=y;nxt[E]=lnk[x];w[E]=MAXINT;lnk[x]=E;}
    bool count(int y){
        int x=y%Ha;
        for (int j=lnk[x];j;j=nxt[j])
            if (y==son[j]) return true;
        return false;
    }
    int& operator [] (int y){
        int x=y%Ha;
        for (int j=lnk[x];j;j=nxt[j])
            if (y==son[j]) return w[j];
        Add(x,y);stk[++top]=x;return w[E];
    }
};
Hashmap f;
int exgcd(int a,int b,int &x,int &y)
{
}
int BSGS(int A,int B,int C)
{
    if (C==1) if (!B) return A!=1; else return -1;
    if (B==1) if (A) return 0; else return -1;
    if (A%C==0) if (!B) return 1; else return -1; //几种特判
    int m=ceil(sqrt(C)),D=1,Base=1;f.clear();
    for (int i=0;i<=m-1;i++){ //先把A^j存进哈希表{
        f[Base]=min(f[Base],i);
        Base=((LL)Base*A)%C;
    }
    for (int i=0;i<=m-1;i++){
        int x,y,r=exgcd(D,C,x,y);
        x=((LL)x*B%C+C)%C; //扩欧求A^j
        if (f.count(x)) return i*m+f[x]; //找到了
        D=((LL)D*Base)%C;
    }
    return -1;
}
int main()
{
    while (~scanf("%d%d%d",&C,&A,&B)){
        int ans=BSGS(A,B,C);
        if (ans==-1) printf("no solution\n"); else
        printf("%d\n",ans);
    }
    return 0;
}
