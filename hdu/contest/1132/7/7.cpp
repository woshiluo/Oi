#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,a[200010],cnt;
inline LL read()
{
    LL x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();cnt=0;
        for(int i=1;i<=n;i++)
            read(),a[i]=0;
        for(int i=1;i<=n;i++){
            int x=read();
            if(!a[x])cnt++;
            a[x]=1;
        }
        if(cnt==n)printf("sha7dow\n");
        else printf("shuishui\n");
    }
}