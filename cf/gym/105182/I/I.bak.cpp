#include<bits/stdc++.h>
using namespace std;
int n;
multiset<int>s;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        s.clear();
        for(int i=1;i<=n;i++){
            int x=read();
            
        }
    }
}
/*
5
2 2 2 1 1

(2+1)*(2+1)*2


*/