#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int X,Y;
}a[200010];
bool cmp(Node p1,Node p2)
{
    return p1.X==p2.X?p1.Y<p2.Y:p1.X<p2.X;
}
bool cmp1(Node p1,Node p2)
{
    return p1.Y==p2.Y?p1.X<p2.X:p1.Y<p2.Y;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,K;
    cin>>n>>m>>K;
    for (int i=1;i<=K;i++) 
      cin>>a[i].X>>a[i].Y;
    sort(a+1,a+K+1,cmp);
    int ans=0,x=0,y=0;
    for (int i=1;i<=K;i++) {
        int j=i;
        while (j<K&&a[j+1].X==a[i].X) j++;
        int las=0;
        for (int k=i;k<=j;k++) {
            if (las<a[k].Y-1&&max(k-i,j-k+1)>ans) ans=max(k-i,j-k+1),x=a[i].X,y=las+1;
            las=a[k].Y;
        }
        if (a[j].Y<m&&j-i+1>ans) {
            ans=j-i+1;
            x=a[i].X;y=m;
        }
        i=j;
    }
    sort(a+1,a+K+1,cmp1);
    for (int i=1;i<=K;i++) {
        int j=i;
        while (j<K&&a[j+1].Y==a[i].Y) j++;
        int las=0;
        for (int k=i;k<=j;k++) {
            if (las<a[k].X-1&&max(k-i,j-k+1)>ans) ans=max(k-i,j-k+1),x=las+1,y=a[i].Y;
            las=a[k].X;
        }
        if (a[j].X<n&&j-i+1>ans) {
            ans=j-i+1;
            x=n;y=a[i].Y;
        }
        i=j;
    }
    cout<<ans<<'\n';
    cout<<x<<' '<<y;
    return 0;
}