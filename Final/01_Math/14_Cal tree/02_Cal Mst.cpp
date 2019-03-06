/// MST 下，设计方案的美学值期望
/// ans=sum(每条边的权值*它出现在最小生成树中的概率)
typedef long double ld;
const int N=10010,M=200010,K=70;
const ld eps=1e-9;
int n,m,i,j,k,f[N],g[N],cv,ce,POS,v[N],id[N],pool[K][K];ld ans,a[K][K];
struct E{int x,y,d,v;E(){}E(int _x,int _y,int _d){x=_x,y=_y,d=_d;}}e[M],w[K];
inline bool cmp(const E&a,const E&b){return a.d<b.d;}
inline bool cmpv(const E&a,const E&b){return a.v<b.v;}
int F(int x){return f[x]==x?x:f[x]=F(f[x]);}
int G(int x){return g[x]==x?x:g[x]=G(g[x]);}
inline int get(int x){
  if(v[x]<POS)v[x]=POS,id[x]=++cv;
  return id[x];
}
inline void add(int x,int y,int z){
  x=F(x),y=F(y);
  if(x==y)return;
  w[++ce]=E(get(x),get(y),z);
}
inline ld det(int n){
  ld ans=1;
  int i,j,k;
  for(i=1;i<=n;i++){
    for(j=i+1;j<=n;j++)if(fabs(a[j][i])>eps){
      ld t=a[i][i]/a[j][i];
      for(k=i;k<=n;k++)a[i][k]-=t*a[j][k];
      for(k=i;k<=n;k++)swap(a[i][k],a[j][k]);
      ans*=-1;
    }
    ans*=a[i][i];
    if(fabs(ans)<eps)return 0;
  }
  return ans;
}
inline ld cal(int l,int r,int o){
  int i,j,x,y;
  for(i=0;i<n;i++)for(j=0;j<n;j++)a[i][j]=0;
  for(i=l;i<r;i++)if(i!=o){
    x=id[w[i].x]-1,y=id[w[i].y]-1;
    a[x][x]++,a[y][y]++,a[x][y]--,a[y][x]--;
  }
  return det(n-1);
}
inline void work(){
  int i,j,k,x;
  for(i=1;i<=cv;i++)g[i]=i,pool[i][0]=0;
  for(i=1;i<=ce;i++)if(G(w[i].x)!=G(w[i].y))g[g[w[i].x]]=g[w[i].y];
  for(i=1;i<=cv;i++)pool[G(i)][++pool[G(i)][0]]=i;
  for(i=1;i<=ce;i++)w[i].v=G(w[i].x);
  sort(w+1,w+ce+1,cmpv);
  for(i=1;i<=ce;i=j){
    for(j=i;j<=ce&&w[i].v==w[j].v;j++);
    n=pool[x=w[i].v][0];
    for(k=1;k<=n;k++)id[pool[x][k]]=k;
    ld all=cal(i,j,0);
    for(k=i;k<j;k++)ans+=(all-cal(i,j,k))/all*w[k].d;
  }
}
int main(){
  scanf("%d%d",&n,&m);
  for(i=1;i<=m;i++)scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].d,&e[i].v);
  sort(e+1,e+m+1,cmp);
  for(i=1;i<=n;i++)f[i]=i;
  for(i=1;i<=m;i=j){
    POS++,cv=ce=0;
    for(j=i;j<=m&&e[i].d==e[j].d;j++)add(e[j].x,e[j].y,e[j].v);
    work();
    for(k=i;k<j;k++)if(F(e[k].x)!=F(e[k].y))f[f[e[k].x]]=f[e[k].y];
  }
  printf("%.5f",(double)ans);
}
