#include <bits/stdc++.h>
using namespace std;
int n,a[200010],L[200010],R[200010];
long long ans;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    L[0]=R[n]=0;
    for(int i=1;i<=n;i++)
        L[i]=max(L[i-1]-1,a[i]);
    for(int i=n;i;i--)
        R[i]=max(R[i+1]-1,a[i]);
    for(int i=1;i<=n;i++)
        ans+=max(R[i],L[i]);
    cout<<ans<<endl;
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