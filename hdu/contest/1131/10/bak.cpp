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
        for (int i=0;i<31;i++) f[i]=0;
        while (m--) {
            int op,x;
            cin>>op>>x;
            if (op==1) {
                for (int i=0;i<31;i++) {
                    int tmp=(x>>i&1);
                    if (tmp==0) tmp=f[i];
                      else tmp=(f[i]^1);
                }
            }
            if (op==2) {
                for (int i=0;i<31;i++) 
                  if ()
            }
        }
    }
}