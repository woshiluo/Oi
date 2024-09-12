#include<bits/stdc++.h>
using namespace std;
int Len,n,a[100010],Max,Min;
char str[100010];
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
        Len=read();
        scanf("%s",str+1);
        n=0;Max=-1e9;Min=1e9;bool flag=0;
        for(int i=1;i<=Len;i++){
            if(str[i]^str[i-1])
                a[++n]=0;
            a[n]++;
        }
        for(int i=1;i<=n;i++)
        if(a[i]>1){
            flag=1;
            int temp=max(i,n-i+1);
            Max=max(Max,temp);
            Min=min(Min,temp);
        }
        if(!flag)Max=Min=0;
        printf("%d\n",Max-Min);
    }
    
}
/*
1
20
11001101100110110011
*/