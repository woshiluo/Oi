#include<bits/stdc++.h>
#define LL long long
using namespace std;
int sum[100010];
inline int read()
{
    int x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int calc(int x)
{
    int temp=0;
    while(x)temp+=x%10,x/=10;
    return temp;
}
int main()
{
    // cout<<calc(1234)<<endl;
    for(int i=1;i<=9;i++)
        sum[i]=i;
    for(int i=10;i<=1000;i++){
        int tot=calc(i);
        sum[i]=sum[i-1]+(sum[i-1]-sum[i-tot-1]!=i-1-(i-tot)+1);
    }
    for(int i=1;i<=1000;i++)
    if(sum[i]==sum[i-1])
        cout<<i<<endl;
}