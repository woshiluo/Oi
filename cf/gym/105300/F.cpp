#include <bits/stdc++.h>
using namespace std;
int n;
double a[1000010];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>K;
    for (int i=1;i<=n;i++) {
        int x;
        cin>>x;
        a[i]=log2(x);
    }
    sort(a+1,a+n+1,cmp);
    for (int i=1;i<=22;i++) {
        
          
    }
}
