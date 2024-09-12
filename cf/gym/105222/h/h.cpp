#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    int T;cin>>T;
    while(T --> 0){
        long long x;cin>>x;
        if(x%3==0)cout<<1<<' '<<x/3<<'\n';
        else cout<<0<<' '<<x/3+x%3<<'\n';
    }
}