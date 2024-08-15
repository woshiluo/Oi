#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,A,B,C;
char sA[200010],sB[200010],sC[200010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    int T=read();
    while(T --> 0){
        A=B=C=0;
        n=read();
        scanf("%s%s%s",sA+1,sB+1,sC+1);
        for(int i=1;i<=n;i++){
            if(sA[i]==sB[i]&&sA[i]==sC[i])
                A++,B++,C++;
            else if(sA[i]==sB[i])A++,B++;
            else if(sA[i]==sC[i])A++,C++;
            else if(sB[i]==sC[i])B++,C++;
        }
        if(A>B)swap(A,B);
        if(B>C)swap(B,C);
        if(A>B)swap(A,B);
        printf("%d\n",(A+B)/2);
    }
}