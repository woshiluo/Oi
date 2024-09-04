#include <bits/stdc++.h>
using namespace std;
int n,m,r0;
double K;
int main()
{
    int abc=0;
    do{
        cout<<++abc<<'\n';
        system("./1data >in.txt");
        system("./1 <in.txt >out.txt");
        system("./1baoli <in.txt >ans.txt");
    }while(system("diff out.txt ans.txt")==0);
}