#include <bits/stdc++.h>
using namespace std;
const int dx[8]={-1,1,0,0,-1,1,-1,1},dy[8]={0,0,-1,1,-1,-1,1,1};
int n,m;
char s[110][110];
bool vis[110][110];
bool Check(int i,int j)
{
    if (!vis[i][j]) return true;
    for (int k=0;k<8;k++) {
        int x=i+dx[k],y=j+dy[k];
        if (x<1||x>n||y<1||y>m) continue;
        if (!vis[x][y]) return true;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
      scanf("%s",s[i]+1);
    for (int i=1;i<=n;i++)
      for (int j=1;j<=m;j++) 
        if (s[i][j]=='.') {
            vis[i][j]=true;
            for (int k=0;k<8;k++) {
                int x=i+dx[k],y=j+dy[k];
                if (x<1||x>n||y<1||y>m) continue;
                vis[x][y]=true;
            }
        }
    for (int i=1;i<=n;i++) 
      for  (int j=1;j<=m;j++) 
        if (s[i][j]=='#'&&!Check(i,j)) {
            puts("Impossible");
            return 0;
        }
    puts("Possible");
    for (int i=1;i<=n;i++) {
       for (int j=1;j<=m;j++) 
         if (!vis[i][j]) 
            printf("#");
          else printf(".");
        puts("");
    }
}