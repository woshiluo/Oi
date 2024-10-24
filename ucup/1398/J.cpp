#include <bits/stdc++.h>
using namespace std;
map<long long,int> mp,mpp;
vector<long long> V,v;
int ans=0;
void Solve(long long n)
{
    if (n==1) return ;
    long long mid=n/2;
    mpp.clear();v.clear();
    for (int i=0;i<(int)V.size();i++) {
        long long x=V[i];long long y=n-x+1;
        if (x<=mid) {
            if (mp.find(y)==mp.end()) {
                if (mp[x]==2) continue;
                ans++;mpp[x]=2;v.push_back(x);
            }
            continue;
        }
        if (mp[x]==1) {
            if (mp.find(y)==mp.end()) mpp[y]=2,v.push_back(y),ans++;
              else if (mp[y]==1) mpp[y]=1,v.push_back(y);
                else mpp[y]=1,v.push_back(y);
        }
        else {
            if (mp[y]==1) mpp[y]=1,v.push_back(y);
              else if (mp[y]==2) mpp[y]=2,v.push_back(y); 
        }
    }
    mp=mpp;V=v;
    Solve(n>>1);
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int m;
    cin>>n>>m;
    for (int i=1;i<=m;i++) {
        long long x;
        cin>>x;
        V.push_back(x);
        mp[x]=1;
    }
    Solve(n);
    cout<<ans;
}