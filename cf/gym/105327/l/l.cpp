#include<bits/stdc++.h>
using namespace std;
int n,a[100010],b[100010];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<=30;i++){
        int temp=0;
        for(int j=1;j<=n;j++)
        if(a[j]>>i&1)
            b[++temp]|=1<<i;
    }
    for(int i=1;i<=n;i++)
        printf("%d ",b[i]);
}