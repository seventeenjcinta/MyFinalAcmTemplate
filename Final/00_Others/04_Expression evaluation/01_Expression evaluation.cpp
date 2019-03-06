/// No negative number
LL s[10000],b[10000],st[10000],top;
char S[10000];
LL Cal(LL a,LL b,LL c){
	LL result;
	if (c==-3){
		result=1;
		for (int i=1;i<=b;i++){
			result=result*a;
		}
	}
	else if (c==-4) {
		result=a*b;
	}
	else if (c==-5) {
		result=(a+b);
	}
	else if (c==-6) {
		result=(a-b);
	}
	return result;
}
LL Getans(const char *tmp){
	LL len=0,i=0,total=0,top=-1;
    LL n=strlen(tmp);
    memset(s,0,sizeof s);
    memset(b,0,sizeof b);
    memset(st,0,sizeof st);
	while (i<n){
		if (tmp[i]==' '){
			i++;
			continue;
		}
		if (tmp[i]=='-') s[len++]=-6;
		else if (tmp[i]=='+') s[len++]=-5;
		else if (tmp[i]=='*') s[len++]=-4;
		else if (tmp[i]=='^') s[len++]=-3;
		else if (tmp[i]=='(') s[len++]=-2;
		else if (tmp[i]==')') s[len++]=-1;
		else {
			LL ans=0;
			while (tmp[i]>='0'&&tmp[i]<='9'){
				ans=ans*10+tmp[i]-'0';
				i++;
			}
			s[len++]=ans;
			continue;
		}
		i++;
	}
	for (i=0;i<len;i++){
		if (s[i]>=0){
			b[total++]=s[i];
		}
		else {
			if (s[i]==-1){
				while (st[top]!=-2){
					b[total++]=st[top--];
				}
				top--;
			}
			else if (s[i]==-2) st[++top]=s[i];
			else {
				if (top==-1){
					st[++top]=s[i];
				}
				else if (st[top]==-2) st[++top]=s[i];
				else {
					if (s[i]==-3) {
						while (st[top]==s[i]){
							if (st[top]==-2) break;
							if (top<0) break;
							b[total++]=st[top--];
						}
						st[++top]=s[i];
					}
					else if (s[i]==-4) {
						while (st[top]>=s[i]){
							if (st[top]==-2) break;
							b[total++]=st[top--];
							if (top<0) break;
						}
						st[++top]=s[i];
					}
					else if (s[i]==-5||s[i]==-6) {
						while (1){
							if (st[top]==-2) break;
							if (top<0) break;
							b[total++]=st[top--];
						}
						st[++top]=s[i];
					}
				}
			}
		}
	}
	for (i=top;i>=0;i--)
		b[total++]=st[i];
	top=-1;
	for (int i=0;i<total;i++){
		if (b[i]>0) st[++top]=b[i];
		else {
			LL re=cal(st[top-1],st[top],b[i]);
			st[--top]=re;
		}
	}
	return st[0];
}
int main(){
    cout<<getans("-3");
    return 0;
}
