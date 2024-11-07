#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7;
int n,Q,cnt[310];
int f[305][305][305][3];
int s[305][305];
char S[310];
int main()
{
    scanf("%d%d",&n,&Q);
    scanf("%s",S+1);
    for (int i=1;i<=n;i++) {
        cnt[i]=cnt[i-1];
        if (S[i]=='?') {
            cnt[i]++;
            if (i==1) f[1][1][0][0]=f[1][0][1][1]=f[1][0][0][2]=1;
            else {
                for (int x=0;x<i;x++)
                for (int y=0;y<i;y++) {
                    f[i][x+1][y][0]=(f[i][x+1][y][0]+f[i-1][x][y][1])%Mod;
                    f[i][x+1][y][0]=(f[i][x+1][y][0]+f[i-1][x][y][2])%Mod;
                    f[i][x][y+1][1]=(f[i][x][y+1][1]+f[i-1][x][y][0])%Mod;
                    f[i][x][y+1][1]=(f[i][x][y+1][1]+f[i-1][x][y][2])%Mod;
                    f[i][x][y][2]=(f[i][x][y][2]+f[i-1][x][y][0])%Mod;
                    f[i][x][y][2]=(f[i][x][y][2]+f[i-1][x][y][1])%Mod;
                }
            }
        }
        else {
            if (i==1) {
                if (S[i]=='a') f[1][0][0][0]=1;
                if (S[i]=='b') f[1][0][0][1]=1;
                if (S[i]=='c') f[1][0][0][2]=1;
                continue;
            }
            for (int x=0;x<i;x++)
              for (int y=0;y<i;y++) {
                  if (S[i]=='a') {
                      f[i][x][y][0]=(f[i][x][y][0]+f[i-1][x][y][1])%Mod;
                      f[i][x][y][0]=(f[i][x][y][0]+f[i-1][x][y][2])%Mod;
                  }
                  if (S[i]=='b') {
                      f[i][x][y][1]=(f[i][x][y][1]+f[i-1][x][y][0])%Mod;
                      f[i][x][y][1]=(f[i][x][y][1]+f[i-1][x][y][2])%Mod;
                  }
                  if (S[i]=='c') {
                      f[i][x][y][2]=(f[i][x][y][2]+f[i-1][x][y][0])%Mod;
                      f[i][x][y][2]=(f[i][x][y][2]+f[i-1][x][y][1])%Mod;
                  }
              }
        }
    }
    for (int x=0;x<=n;x++) { 
        s[x][0]=(f[n][x][0][0]+f[n][x][0][2])%Mod;
        for (int y=1;y<=n;y++) {
            s[x][y]=s[x][y-1];
            s[x][y]=(s[x][y]+f[n][x][y][0])%Mod;
            s[x][y]=(s[x][y]+f[n][x][y][1])%Mod;
            s[x][y]=(s[x][y]+f[n][x][y][2])%Mod;
        }
    }
    while (Q--) {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        int ans=0;
        for (int i=0;i<=x;i++) {
            int l=max(cnt[n]-i-z,0);
            int r=min(y,cnt[n]-i);
            if (r<l) continue;
            ans=(ans+s[i][y])%Mod;
            if (l>0) ans=(ans-s[i][l-1]+Mod)%Mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}
