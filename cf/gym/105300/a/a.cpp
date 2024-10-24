#include <bits/stdc++.h>
using namespace std;
int a[100010],n;
long long Calc(int x)
{
    long long sum=0;
    for (int i=1;i<=n;i++)
      if (a[i]>x) sum+=x;
        else sum+=a[i];
    sum=sum*2-1LL*x*n;
    return sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int m=n/2;
    long long Max=-1e18;
    int ans=0;
    for (int i=max(1,m-5);i<=m+5&&i<=n;i++) {
        long long res=Calc(a[i]);
        if (res>Max) Max=res,ans=a[i];
    }
    cout<<ans;
    return 0;
}
/*
7
100
80 
80
85
51
65
2
*/