#include<bits/stdc++.h>
#define LL long long
const int mod=998244353;
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int gcd(int x,int y)
{return y?gcd(y,x%y):x;}
int main()
{
    int T=read();
    while(T --> 0){
        int x=read(),y=read(),z=read();
        int G=gcd(gcd(x,y),z);
        x/=G;y/=G;z/=G;
        if((x&1)+(y&1)+(z&1)==3)
            printf("NO\n");
        else printf("YES\n");
    }
}