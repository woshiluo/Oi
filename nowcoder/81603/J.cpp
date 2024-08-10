#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int n,m;
        cin>>n>>m;
        if (m==n-2) {
            cout<<-1<<'\n';
            continue;
        }
        int p=n-m;
        int t=p/3;
        if (p%3==0) {
            for (int i=0;i<t;i++) {
                if (i==t-1) cout<<t-i<<' '<<2*t-i<<' '<<3*t-i<<' ';
                else cout<<2*t-i<<' '<<t-i<<' '<<3*t-i<<' ';
            }
            for (int i=p+1;i<=n;i++) cout<<i<<' ';
            cout<<'\n';
            continue;
        }
        for (int i=n;i>p;i--)
          cout<<i<<' ';
        if (p%3) cout<<3*t+1<<' ';
        for (int i=0;i<t;i++) {
            cout<<2*t-i<<' '<<t-i<<' '<<3*t-i<<' ';
        }
        if (p%3==2) cout<<3*t+2<<' ';
        cout<<'\n';
    }
}