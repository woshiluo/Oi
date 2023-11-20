#include<iostream>
#include<cstdio>
using namespace std;
const int N=200005;
const int M=1000005;
int n,k;
int a[N];
bool vis[N*2+M];
void solve()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        vis[a[i]]=true;
    int alice=1,bob=0;
    for(int t=1;t<=k;t++)
    {
        while(vis[alice]) alice+=2;
        vis[alice]=true;
        while(vis[bob]) bob+=2;
        vis[bob]=true;
    }
    int res;
    for(int i=0;;i++)
        if(!vis[i])
        {
            res=i;
            break;
        }
    if(res%2==0) cout<<"Alice\n";
    else cout<<"Bob\n";
    for(int i=1;i<=n;i++)
        vis[a[i]]=false;
    while(alice>=0) vis[alice]=false,alice-=2;
    while(bob>=0) vis[bob]=false,bob-=2;
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}