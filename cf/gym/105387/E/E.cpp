#include<bits/stdc++.h>
#define LL long long
using namespace std;
int vis[1000010];
int a[1000010],b[1000010],c[1000010];
int check(int n)
{
    a[0]=0;
    for(int i=1;i*i<=n;i++)
    if(n%i==0){
        a[++a[0]]=i;
        if(i*i!=n)
            a[++a[0]]=n/i;
    }
    sort(a+1,a+1+a[0]);
    int temp=0;
    for(int i=1;i<=a[0];i++)
    if(temp>=a[i]-1)
        temp+=a[i];
    else break;
    return temp>=n;
}
int main()
{
    for(int i=1;i<=350000;i++)
        vis[i]=check(i);
    for(int i=1;i<=350000;i++)
    if(vis[i])b[++b[0]]=i;
    c[++c[0]]=1;
    for(int i=2;i<=b[0];i++){
        bool flag=1;
        for(int j=2;j*j<=b[i];j++)
        if(b[i]%j==0&&((vis[j]&&j%(b[i]-j)==0)||(vis[b[i]/j]&&(b[i]/j)%j==0)))
            flag=0;
        if(flag)c[++c[0]]=b[i];
    }
    int m;cin>>m;
    cout<<c[m]<<'\n';
}