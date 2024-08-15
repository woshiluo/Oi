#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,K,a[200010],b[200010],ans,cnt;
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
int calc()
{
    int temp=0;
    for(int i=1;i<=a[0];i++){
        if(a[0]-i>=a[i]){
            int L=1,R=b[0],M,T=0;
            while(L<=R){
                M=(L+R)>>1;
                if(b[0]-M>=a[i]+b[M])
                    T=M,L=M+1;
                else R=M-1;
            }
            temp=max(temp,i+T);
        }
    }
    for(int i=1;i<=b[0];i++){
        if(b[0]-i>=b[i]){
            int L=1,R=a[0],M,T=0;
            while(L<=R){
                M=(L+R)>>1;
                if(a[0]-M>=a[M]+b[i])
                    T=M,L=M+1;
                else R=M-1;
            }
            temp=max(temp,i+T);
        }
    }
    return temp;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        b[0]=a[0]=cnt=0;
        for(int i=1;i<=n;i++){
            int x=read();
            if(!x)cnt++;
            if(x>0)a[++a[0]]=x;
            if(x<0)b[++b[0]]=-x;
        }
        sort(a+1,a+1+a[0]);
        sort(b+1,b+1+b[0]);
        printf("%d\n",calc()+cnt);
    }
}