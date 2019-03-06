struct bignum{
    int len;
    int a[LEN];

    bignum(){
        memset(a,0,sizeof a);
        len=0;
    }
    int& operator[](int idx){
        return a[idx];
    }
    const int& operator[](int idx) const{
        return a[idx];
    }

    bignum& operator =(const bignum& b){
        len=b.len;
        for (int i=0; i<len; i++)
            a[i]=b[i];
        return *this;
    }
    bignum& operator =(char b[]){
        len=strlen(b);
        for (int i=0; i<len; i++)
            a[i]=b[len-1-i]-'0';
        while (len>0&&!a[len-1]) len--;
        return *this;
    }
    bignum& operator =(const char b[]){
        len=strlen(b);
        for (int i=0; i<len; i++){
            a[i]=b[len-i-1]-'0';
        }
        while (len>0&&!a[len-1]) len--;
        return *this;
    }
    bignum& operator =(long long b){
        len=0;
        while (b){
            a[len++]=b%10;
            b/=10;
        }
        return *this;
    }

    bignum& operator +=(const bignum& b){
        len=max(len,b.len);
        for (int i=0; i<len; i++) a[i]+=b[i];
        for (int i=0; i<len; i++){
            a[i+1]+=a[i]/10;
            a[i]%=10;
        }
        if (a[len]) len++;
        return *this;
    }
    bignum& operator +=(int b){
        a[0]+=b;
        for (int i=0; i<LEN-1; i++){
            a[i+1]+=a[i] / 10;
            a[i]%=10;
        }
        a[LEN]%=10;
        len=LEN;
        while (len>0&&!a[len-1]) len--;
        return *this;
    }
    bignum& operator +=(char b[]){
        bignum bb;
        bb=b;
        return (*this)+=bb;
    }
    bignum& operator +=(const char b[]){
        bignum bb;
        bb=b;
        return (*this)+=bb;
    }

    bignum& operator -=(const bignum& b){
        len=max(len,b.len);
        for (int i=0; i<len; i++) a[i]-=b[i];
        for (int i=0; i<len; i++){
            a[i+1]+=a[i]/10;
            a[i]%=10;
            if (a[i]<0){
                a[i]+=10;
                a[i+1]--;
            }
        }
        while (len>0&&!a[len-1]) len--;
        return *this;
    }
    bignum& operator -=(int b){
        bignum bb;
        bb=b;
        return (*this-=bb);
    }
    bignum& operator -=(char b[]){
        bignum bb;
        bb=b;
        return (*this)-=bb;
    }
    bignum& operator -=(const char b[]){
        bignum bb;
        bb=b;
        return (*this)-=bb;
    }

    bignum& operator *=(const bignum& b){
        bignum ans;
        for (int i=0; i<len; i++)
            for (int j=0; j<b.len; j++)
                ans[i+j]+=a[i]*b[j];
        for (int i=0; i<len+b.len+1; i++){
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
        }

        for (int i=0; i<LEN; i++)
            a[i]=ans[i];
        len=LEN;
        while (len>0&&!a[len-1]) len--;
        return *this;
    }
    bignum& operator *=(const char* b){
        bignum bb;
        bb=b;
        return (*this*=bb);
    }
    bignum& operator *=(char* b){
        bignum bb;
        bb=b;
        return (*this*=bb);
    }
    bignum& operator *=(int b){
        bignum bb;
        bb=b;
        return (*this*=bb);
    }

    void show(){
        for (int i=len-1; i>=0; i--)
            printf("%d",a[i]);
        if (len==0) printf("0");
    }
    void get(){
        char s[LEN];
        scanf("%s",s);
        *this=s;
        while (len>0&&!a[len-1]) len--;
    }
};
bignum operator + (bignum &a,bignum &b){
    bignum ans;
    ans=a;
    ans+=b;
    return ans;
}
bignum operator - (bignum &a,bignum &b){
    bignum ans;
    ans=a;
    ans-=b;
    return ans;
}
bignum operator * (bignum &a,bignum &b){
    bignum ans;
    ans=a;
    ans*=b;
    return ans;
}
bool operator < (bignum &a, bignum &b){
    if (a.len<b.len) return 1;
    if (a.len>b.len) return 0;

    for (int i=a.len-1; i>=0; i--){
        if (a[i]!=b[i]) return a[i]<b[i];
    }
}

bool operator > (bignum &a, bignum &b){
    if (a.len<b.len) return 0;
    if (a.len>b.len) return 1;

    for (int i=a.len-1; i>=0; i--){
        if (a[i]!=b[i]) return a[i]>b[i];
    }
}
bool operator > (bignum &a, long long b){
    bignum bb;
    bb=b;
    return a>bb;
}

bool operator ==(bignum a,bignum b){
    if (a.len!=b.len) return 0;
    for (int i=0; i<a.len; i++){
        if (a[i]!=b[i]) return 0;
    }
    return 1;
}
bool operator ==(bignum a,long long b){
    bignum bb;
    bb=b;
    return a==bb;
}
bool operator ==(bignum a,char *b){
    bignum bb;
    bb=b;
    return a==bb;
}
bool operator ==(bignum a,const char *b){
    bignum bb;
    bb=b;
    return a==bb;
}
bool operator <= (bignum &a, bignum &b){
    return a==b||a<b;
}
bool operator >= (bignum &a, bignum &b){
    return a==b||a>b;
}
bool operator != (bignum &a, bignum &b){
    return !(a==b);
}

bignum& operator /=(bignum &a,bignum &b){
    bignum ans;
    bignum bb;
    ans.len=a.len;

    for (int i=ans.len-1; i>=0; i--){
        int l=0,r=9,mid;
        while (l<r){
            mid=(l+r)/2+1;
            ans[i]=mid;
            bb=b;
            bb*=ans;

            if (bb<=a) l=mid;
            else r=mid-1;
        }
        ans[i]=l;
    }

    while (ans.len>0&&!ans[ans.len-1]) ans.len--;
    a=ans;
    return a;
}
bignum& operator /= (bignum& a,long long b){
    bignum bb;
    bb=b;
    a/=bb;
    return a;
}
bignum& operator /= (bignum& a,char *b){
    bignum bb;
    bb=b;
    a/=bb;
    return a;
}
bignum& operator /= (bignum& a,const char *b){
    bignum bb;
    bb=b;
    a/=bb;
    return a;
}
bignum operator / (bignum& a,bignum& b){
    bignum ans;
    ans=a;
    ans/=b;
    return ans;
}
bignum operator / (bignum& a,int b){
    bignum ans,bb;
    ans=a;
    bb=b;
    ans/=b;
    return ans;
}
bignum operator / (bignum& a,char *b){
    bignum ans,bb;
    ans=a;
    bb=b;
    ans/=b;
    return ans;
}
bignum operator / (bignum& a,const char *b){
    bignum ans,bb;
    ans=a;
    bb=b;
    ans/=b;
    return ans;
}
bignum operator %= (bignum& a,bignum& b){
    bignum d;
    d=a/b;
    a-=d*b;
    return a;
}
long long operator %= (bignum& a,long long b){
    long long ans=0,w=1;
    for (int i=0; i<a.len; i++){
        ans=(ans+a[i]*w%b)%b;
        w=w*10%b;
    }
    a=ans;
    return ans;
}
bignum operator %= (bignum& a,char *b){
    bignum bb;
    bb=b;
    a%=bb;
    return a;
}
bignum operator %= (bignum& a,const char *b){
    bignum bb;
    bb=b;
    a%=bb;
    return a;
}
bignum operator % (bignum& a,bignum& b){
    bignum ans;
    ans=a;
    ans%=b;
    return ans;
}
long long operator % (bignum& a,long long b){
    long long ans=0,w=1;
    for (int i=0; i<a.len; i++){
        ans=(ans+a[i]*w%b)%b;
        w=w*10%b;
    }
    return ans;
}
bignum operator % (bignum& a,char *b){
    bignum bb;
    bb=b;
    return a%bb;
}
bignum operator % (bignum& a,const char *b){
    bignum bb;
    bb=b;
    return a%bb;
}
bignum pow(bignum a,int x){
    bignum ans;
    ans=1;
    while (x){
        if (x%2) ans*=a;
        a=a*a;
        x>>=1;
    }
    return ans;
}
bignum groot(bignum &a,int x){
    bignum ans;
    ans.len=a.len/x+5;
    bignum tmp;
    for (int i=ans.len-1; i>=0; i--){
        int l=0,r=9,mid;
        while (l<r){
            mid=(l+r)>>1;
            mid++;
            ans[i]=mid;
            tmp=pow(ans,x);
            if (tmp<=a) l=mid;
            else r=mid-1;
        }
        ans[i]=l;
    }

    while (ans.len>0&&!ans[ans.len-1]) ans.len--;
    return ans;
}
bignum gcd(bignum a,bignum b){
    return a%b==0LL?b:gcd(b,a%b);
}
int solve(bignum k){
    if (k==1) return 1;
    if (pow(groot(k,2),2)==k) return 2;
    if (pow(groot(k,3),3)==k) return 3;
    return 1;
}

bool check[N+10];
long long prime[100000],tot=0;
map<long long,long long> MAP1,MAP2;
map<long long,long long>::iterator iter;
int main(){
    memset(check,0,sizeof check);
    for (int i=2; i<=N; i++){
        if (!check[i]) prime[tot++]=i;
        for (int j=0; j<tot; j++){
            if (i*prime[j]>N) break;
            check[i*prime[j]]=true;
            if (i%prime[j]==0) break;
        }
    }

    int T;
    scanf("%d",&T);
    while (T--){
        bignum a,b,d,tmp;
        a.get();
        b.get();
        MAP1.clear();
        MAP2.clear();
        for (int i=0; i<tot; i++){
            if (a%prime[i]==0){
                MAP1[prime[i]]=0;
                while (a%prime[i]==0){
                    a/=prime[i];
                    MAP1[prime[i]]++;
                }
            }
        }
        for (int i=0; i<tot; i++){
            if (b%prime[i]==0){
                MAP2[prime[i]]=0;
                while (b%prime[i]==0){
                    b/=prime[i];
                    MAP2[prime[i]]++;
                }
            }
        }
        long long ans1=1,ans2=1;
        for (iter=MAP1.begin(); iter!=MAP1.end(); iter++){
            ans1*=iter->second;
        }
        for (iter=MAP2.begin(); iter!=MAP2.end(); iter++){
            ans2*=iter->second;
        }
        if (a==1){
            printf("%lld %lld\n",ans1,ans2);
            continue;
        }
        d=gcd(a,b);
        long n = solve(d);
        bignum g=groot(d,n);
        long long c = 0;
        while (a%g==0LL){
            a/=g;
            c++;
        }
        ans1 *= c;
        ans1 *= solve(a);
        c=0;
        while (b%g==0LL){
            b/=g;
            c++;
        }
        ans2 *= c;
        ans2*=solve(b);
        printf("%lld %lld\n",ans1,ans2);
    }
    return 0;
}
