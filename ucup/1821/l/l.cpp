#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;cin>>a>>b>>c;
    cout<<100<<endl;
    for(int i=1;i<=50;i++)
        cout<<a<<' ';
    for(int i=51;i<=95;i++)
        cout<<b<<' ';
    for(int i=96;i<=99;i++)
        cout<<c<<' ';
    cout<<c+1<<endl;
}