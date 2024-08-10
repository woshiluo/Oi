#include <bits/stdc++.h>
using namespace std;
const int N=1e5;
const int Mod=998244353;
int T;
int cnt[N+10],g[N+10],p[N+10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    p[0]=1;
    for (int i=1;i<=N;i++) p[i]=(p[i-1]+p[i-1])%Mod;
    while (T--) {
        int n;
        cin>>n;
        for (int i=1;i<=N;i++) cnt[i]=0,g[i]=0;
        for (int i=1;i<=n;i++) {
            int x;
            cin>>x;
            cnt[x]++;
        }
        // cout<<"ok"<<endl;
        int ans=0;
        for (int i=N;i>=1;i--) {
            int s=0;
            for (int j=i;j<=N;j+=i)
              s+=cnt[j];
            g[i]=(p[s]-1+Mod)%Mod;
            for (int j=i+i;j<=N;j+=i)
              g[i]=(g[i]-g[j])%Mod;
            g[i]=(g[i]+Mod)%Mod;
            if (g[i]&&!cnt[i]) ans++;
        }
        if (ans&1) cout<<"dXqwq"<<'\n';
          else cout<<"Haitang"<<'\n';
    }
    return 0;
}