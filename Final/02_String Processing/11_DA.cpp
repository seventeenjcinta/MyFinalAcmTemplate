const int N = int(2e5)+10;
int cmp(int *r,int a,int b,int l){
    return (r[a]==r[b]) && (r[a+l]==r[b+l]);
}
// 用于比较第一关键字与第二关键字,
// 比较特殊的地方是,预处理的时候,r[n]=0(小于前面出现过的字符)

int wa[N],wb[N],ws[N],wv[N];
int rank[N],height[N];
void DA(int *r,int *sa,int n,int m){ //此处N比输入的N要多1，为人工添加的一个字符，用于避免CMP时越界
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) ws[i]=0;
    for(i=0;i<n;i++) ws[x[i]=r[i]]++;
    for(i=1;i<m;i++) ws[i]+=ws[i-1];
    for(i=n-1;i>=0;i--) sa[--ws[x[i]]]=i; //预处理长度为1
    for(j=1,p=1;p<n;j*=2,m=p) //通过已经求出的长度J的SA，来求2*J的SA
    {
        for(p=0,i=n-j;i<n;i++) y[p++]=i; // 特殊处理没有第二关键字的
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j; //利用长度J的，按第二关键字排序
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) ws[i]=0;
        for(i=0;i<n;i++) ws[wv[i]]++;
        for(i=1;i<m;i++) ws[i]+=ws[i-1];
        for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];  //基数排序部分
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;  //更新名次数组x[],注意判定相同的
    }
}

void calheight(int *r,int *sa,int n){ // 此处N为实际长度
    int i,j,k=0;        // height[]的合法范围为 1-N, 其中0是结尾加入的字符
    for(i=1;i<=n;i++) rank[sa[i]]=i;  // 根据SA求RANK
    for(i=0;i<n; height[rank[i++]] = k ) // 定义：h[i] = height[ rank[i] ]
    for(k?k--:0,j=sa[rank[i]-1]; r[i+k]==r[j+k]; k++); //根据 h[i] >= h[i-1]-1 来优化计算height过程
}

char str[N];
int sa[N];
int main(){
    char str[N];
    scanf("%s",str);
    int n = strlen(str);
    str[n]=0;

    da(str,sa,n+1,128);  //注意区分此处为n+1,因为添加了一个结尾字符用于区别比较
    calheight(str,sa,n);
}
