#include<bits/stdc++.h>
using namespace std;
int n,ans=-1e9;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        int temp=1e9;
        for(int j=1;j<=n;j++){
            int x;cin>>x;
            temp=min(temp,x);
        }
        ans=max(ans,temp);
    }
    cout<<ans<<'\n';
}