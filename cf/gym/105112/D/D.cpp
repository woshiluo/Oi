#include<bits/stdc++.h>
using namespace std;
char str[10][30];
int d,h,a[30],cnt[200];
double ans=0;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    for(int i=1;i<=7;i++)
        scanf("%s",str[i]+1);
    d=read();h=read();
    for(int i=0;i<128;i++){
        if(i==0)cnt[i]=0;
        else cnt[i]=cnt[i>>1]+(i&1);
        if(cnt[i]<d)continue;
        for(int j=1;j<=24;j++){
            int temp=0;
            for(int k=1;k<=7;k++)
            if(i>>(k-1)&1)
                temp+=str[k][j]=='.';
            a[j]=temp;
        }
        sort(a+1,a+25);
        reverse(a+1,a+25);
        int tot=0;
        for(int j=1;j<=h;j++)
            tot+=a[j];
        ans=max(ans,1.0*tot/(h*cnt[i]));
    }
    printf("%.10f",ans);
}