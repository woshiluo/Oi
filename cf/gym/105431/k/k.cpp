#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long N,P;
    cin>>N>>P;
    if(N&1)
        cout<<((N-1)/2-(P-1)/2)%P*2<<endl;
    else{
        if((N/2-P/2)%P*2==P)cout<<0<<endl;
        else cout<<(N/2-P/2)%P*2<<endl;
    }
}