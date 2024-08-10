#include<bits/stdc++.h>
#define LL __int128
using namespace std;
LL x,y;
inline LL read()
{
    LL x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
LL gcd(LL x,LL y)
{return y?gcd(y,x%y):x;}
void write(LL x)
{
    if(!x)return;
    write(x/10);
    putchar('0'+x%10);
}
int main()
{
    int T=read();
    while(T --> 0){
        x=read();y=read();
        LL LCM=x/gcd(x,y)*y;
        if(((LCM/x)&1)&&LCM!=x)LCM*=2;
        // if(((LCM/y)&1)&&LCM!=y)LCM*=2,y*=2;
        // write(LCM);putchar(' ');
        write(y);
        putchar(' ');
        write(LCM/y);
        putchar('\n');
    }
}