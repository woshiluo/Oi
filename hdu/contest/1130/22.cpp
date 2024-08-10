#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,a[100010],b[100010],ans;
vector<string>S[100010];
unordered_map<string,int>mp;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void dfs(int A,int B,string s,int id)
{
    S[id].emplace_back(s);
    if(A)dfs(A-1,B,s+'0',id);
    if(B)dfs(A,B-1,s+'1',id);
}
void dfs(int x,string s)
{
    if(!mp[s]){ans++;cout<<s<<endl;}
    mp[s]=1;
    if(x>n)return;
    for(auto y:S[x])
        dfs(x+1,s+y);
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();ans=0;
        for(int i=1;i<=n;i++)
            a[i]=read(),b[i]=read();
        mp.clear();
        for(int i=1;i<=n;i++){
            S[i].clear();
            dfs(a[i],b[i],"",i);
            sort(S[i].begin(),S[i].end());
            S[i].resize(unique(S[i].begin(),S[i].end())-S[i].begin());
        }
        dfs(1,"");
        cout<<ans<<">\n";
    }
}
/*
0
01
1
10
00
001
010
0101
011
0110
101
11
110
100
1001
1010
*/
