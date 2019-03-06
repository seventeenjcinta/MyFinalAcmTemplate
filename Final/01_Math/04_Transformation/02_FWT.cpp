const int mod = 1e9+7;
int inv2 = 500000004;
void FWT(int a[], int n)//请确保n为2的整数次幂
{
    for(int d = 1; d < n; d <<= 1){
        for(int m=d<<1,i=0;i<n;i+=m){
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                //xor_MOD:a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
                //xor:a[i+j]=x+y,a[i+j+d]=x-y;
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
        }
    }
}

void UFWT(int a[],int n)//请确保n为2的整数次幂
{
    for(int d=1;d<n;d<<=1){
        for(int m=d<<1,i=0;i<n;i+=m){
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                //xor_MOD:a[i+j]=1LL*(x+y)*inv2%mod,a[i+j+d]=(1LL*(x-y)*inv2%mod+mod)%mod;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
                //or:a[i+j+d]=y-x;
            }
        }
    }
}
