#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL n,A,B;
void solve(LL m)
{
    for(LL i=1;i<m;i++){
        LL temp1=n/i;
        LL temp2=n/(i+1);
        A+=(temp1-temp2);
        B+=(temp1-temp2)*i;
    }
}
void solve2(LL m)
{
    LL i=1;
    for(i=1;(i+1)*(i+1)<=m;i++){
        LL temp1=n/i;
        LL temp2=n/(i+1);
        A+=(temp1-temp2);
        B+=(temp1-temp2)*i;
    }
    // cout<<i<<' '<<A<<' '<<B<<"\n";
    for(i=n/i;i>1;i--){
        A++;
        B+=n/i;
    }
}
int main()
{
    cin>>n;
    for(LL i=2;i*i<=n;i++)
    if(n%i==0){
        solve(i);
        cout<<A<<' '<<B<<'\n';
        return 0;
    }
    solve2(n);
    cout<<A<<'\n'<<B<<'\n';
}