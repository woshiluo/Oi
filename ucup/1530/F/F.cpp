#include<bits/stdc++.h>
using namespace std;
int n,L,R,f[1010],g[1010];
long long ans;
priority_queue<int>q;
void dfs(int x)
{
    if(!x)return;
    int delta=x-g[x];
    long long temp=0;
    for(int i=1;i<=delta+1;i++){
        temp+=q.top();q.pop();
    }
    q.push(temp);
    ans+=temp;
    dfs(g[x]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        q.push(-x);
    }
    memset(f,0x3f,sizeof f);
    f[0]=0;
    for(int i=1;i<=n;i++)
    for(int j=i-(L-1);j>=i-(R-1)&&j>=0;j--)
        if(f[i]>f[j]+1)
            g[i]=j,f[i]=f[j]+1;
    // cout<<f[n-1]<<' '<<g[n-1]<<' '<<g[g[n-1]]<<endl;
    if(f[n-1]>100000)
        printf("0\n");
    else{
        dfs(n-1);
        cout<<-ans<<'\n';
    }
}