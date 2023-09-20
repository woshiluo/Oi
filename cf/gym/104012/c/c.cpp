#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=105;
int n,k;
int a[N];
int c[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i+=k)
        for(int j=i;j<=min(n,i+k-1);j++)
            c[j-i]++;
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=c[(i-1)%k]*a[i],c[(i-1)%k]--;
    cout<<ans;
    return 0;
}