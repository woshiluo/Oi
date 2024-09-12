#include<bits/stdc++.h>
using namespace std;
int n,X[100010],Y[100010];
int MAX1,MAX0;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        X[i]=read();Y[i]=read();
        MAX1=max(MAX1,Y[i]);
        MAX0=max(MAX0,X[i]-Y[i]);
    }
    printf("%d\n",MAX1+MAX0);
    for(int i=1;i<=MAX1;i++)
        printf("1");
    for(int i=1;i<=MAX0;i++)
        printf("0");
    printf("\n");
    for(int i=1;i<=n;i++){
        int pos=MAX1-Y[i];
        printf("%d\n",pos);
    }
}
/*
5
2 2 2 1 1

(2+1)*(2+1)*2


*/