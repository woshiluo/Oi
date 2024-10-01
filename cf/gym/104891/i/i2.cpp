#include<bits/stdc++.h>
using namespace std;
int A,B,TIME;
int f[110][110][110];
int main()
{
	freopen( "i.in", "r", stdin );
	freopen( "i.ans", "w", stdout );
    int T;cin>>T;
    while(T --> 0){
        cin>>A>>B>>TIME;
        memset(f,-0x3f,sizeof f);
        f[0][0][0]=0;
        for(int i=0;i<=TIME;i++){
            for(int x=0;x<=B;x++)
                f[i][A][x]=max(f[i][A][x],f[i][0][x]+1);
            for(int x=0;x<=A;x++)
                f[i][0][B]=max(f[i][0][B],f[i][x][0]);
            for(int x=0;x<=B;x++)
                f[i][A][x]=max(f[i][A][x],f[i][0][x]+1);
            for(int x=0;x<=A;x++)
            for(int y=0;y<=B;y++)
                f[i+1][x][y]=max(f[i+1][x][y],f[i][x+1][y+1]);
            for(int x=0;x<=A;x++)
                f[i+1][x][0]=max(f[i+1][x][0],f[i][x+1][0]);
            for(int y=0;y<=B;y++)
                f[i+1][0][y]=max(f[i+1][0][y],f[i][0][y+1]);
            f[i+1][0][0]=max(f[i+1][0][0],f[i][0][0]);
        }
        int ans=0;
        for(int x=0;x<=A;x++)
            for(int y=0;y<=B;y++)
            ans=max(ans,f[TIME][x][y]);
        cout<<ans*160<<'\n';
    }
}
/*
1
14 22 89
*/ 
