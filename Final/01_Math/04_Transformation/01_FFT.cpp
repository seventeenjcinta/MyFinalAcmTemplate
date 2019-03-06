const double PI = acos(-1.0); //PI
void FFT_d(complex<double> a[],int n,bool on=false) //长度为N (2的次数),默认正变换，逆变换加true
{
    int r=0;
    while((1<<++r)!=n);
    for(int i=0; i<n; i++){
        int tmp=0;
        for(int j=0; j<r; j++)//蝴蝶操作
            if(i&(1<<j))
                tmp+=1<<(r-j-1);
        if(i<tmp)
            swap(a[i],a[tmp]);
    }
    for(int i=1; i<=r; i++){
        int m=1<<i;
        complex<double> wn(cos(2*PI/m),sin(2*PI/m));
        for(int k=0; k<n; k+=m){
            complex<double> w(1,0);
            for(int j=0; j<(m>>1); j++){
                complex<double> t,u;
                t=w*(a[k+j+(m>>1)]);
                u=a[k+j];
                a[k+j]=(u+t);
                a[k+j+(m>>1)]=u-t;
                w=w*wn;
            }
        }
    }
    if(on){
        for(int i=1; i<n>>1; i++)
            swap(a[i],a[n-i]);
        complex<double> in(1.0/n);
        for(int i=0; i<n; i++)
            a[i]=a[i]*in;
    }
}
