#include<bits/stdc++.h>
#define LL long long
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
long double dis(long double x,long double y,long double X,long double Y)
{
    return sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
}
int main()
{
    int T=read();
    while(T --> 0){
        int L=read(),x=read(),y=read();
        if(dis(0,0,x,y)<=L)
            printf("Yes\n0\n");
        else if(dis(L,0,x,y)<=L)
            printf("Yes\n%d\n",L);
        else printf("No\n");
    }
}
