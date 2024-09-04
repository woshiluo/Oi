#include<bits/stdc++.h>
#define LL long long
using namespace std;
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
        LL Z=read(),X=read(),Y=read();
        if((Z+X-1)/X==(Z+Y-1)/Y){
            if(((Z+X-1)/X)%2==0)
            printf("No\nYes\n");
            else printf("Yes\nNo\n");
            continue;
        }
        printf("Yes\nYes\n");
    }
}