#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,m;
mt19937 mt(time(0));
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
LL ksm(LL B,LL K,LL A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
int calc(int X,int Y)
{
    while(X&&Y){
        int Min=min(X,Y);
        if(mt()&1){
            X+=Min;
            Y-=Min;
        }else{
            X-=Min;
            Y+=Min;
        }
    }
    return X;
}
int main()
{
    LL X=read(),Y=read();
    cout<<X*ksm(X+Y,mod-2)%mod<<' '<<Y*ksm(X+Y,mod-2)%mod<<endl;
    /*int T=read();
    while(T --> 0){
        n=read();m=read();
        int temp=0;
        for(int i=1;i<=10000;i++)
        if(calc(n,m))temp++;
        cout<<temp<<' '<<10000-temp<<'\n';
    }*/
}